// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

import simd

struct TextureSize {

    static let background = MTLSizeMake(512, 512, 0)
    static let original   = MTLSizeMake(1024, 320, 0)
    static let merged     = MTLSizeMake(1024, 640, 0)
    static let upscaled   = MTLSizeMake(2048, 1280, 0)
}

extension Renderer {

    func setup() {

        track()

        shaderOptions = ShaderOptions.init(
            
            blur: config.blur,
            blurRadius: config.blurRadius,
            bloom: config.bloom,
            bloomRadius: config.bloomRadius,
            bloomBrightness: config.bloomBrightness,
            bloomWeight: config.bloomWeight,
            flicker: config.flicker,
            flickerWeight: config.flickerWeight,
            dotMask: config.dotMask,
            dotMaskBrightness: config.dotMaskBrightness,
            scanlines: config.scanlines,
            scanlineBrightness: config.scanlineBrightness,
            scanlineWeight: config.scanlineWeight,
            disalignment: config.disalignment,
            disalignmentH: config.disalignmentH,
            disalignmentV: config.disalignmentV
        )
        
        buildMetal()
        kernelManager = KernelManager.init(view: mtkView, device: device, renderer: self)
        splashScreen = SplashScreen.init(view: mtkView, device: device, renderer: self)
        canvas = Canvas.init(view: mtkView, device: device, renderer: self)
        monis = Monitors.init(view: mtkView, device: device, renderer: self)
        console = Console.init(view: mtkView, device: device, renderer: self)
        
        buildSamplers()
        buildPipeline()
        buildVertexBuffers()
        
        reshape()
    }

    internal func buildMetal() {

        track()

        // Metal layer
        metalLayer = mtkView.layer as? CAMetalLayer
        metalAssert(metalLayer != nil,
                    "The Core Animation layer could not be accessed.")

        metalLayer.device = device
        metalLayer.pixelFormat = MTLPixelFormat.bgra8Unorm
        metalLayer.framebufferOnly = true
        metalLayer.frame = metalLayer.frame

        // Command queue
        queue = device.makeCommandQueue()
        metalAssert(queue != nil,
                    "The Command Queue could not be created.")
    }
    
    internal func buildSamplers() {

        let descriptor = MTLSamplerDescriptor()
        descriptor.sAddressMode = MTLSamplerAddressMode.clampToEdge
        descriptor.tAddressMode = MTLSamplerAddressMode.clampToEdge
        descriptor.mipFilter = MTLSamplerMipFilter.notMipmapped

        // Nearest neighbor sampler
        descriptor.minFilter = MTLSamplerMinMagFilter.linear
        descriptor.magFilter = MTLSamplerMinMagFilter.linear
        samplerLinear = device.makeSamplerState(descriptor: descriptor)

        // Linear sampler
        descriptor.minFilter = MTLSamplerMinMagFilter.nearest
        descriptor.magFilter = MTLSamplerMinMagFilter.nearest
        samplerNearest = device.makeSamplerState(descriptor: descriptor)
    }

    func buildPipeline() {

        // Get vertex and fragment shader from library
        let vertexFunc = kernelManager.makeFunction(name: "vertex_main")
        let fragmentFunc = kernelManager.makeFunction(name: "fragment_main")
        metalAssert(vertexFunc != nil && fragmentFunc != nil,
                    "Cannot create Render Pipeline function objects.")
        
        // Create depth stencil state
        let stencilDescriptor = MTLDepthStencilDescriptor.init()
        stencilDescriptor.depthCompareFunction = MTLCompareFunction.less
        stencilDescriptor.isDepthWriteEnabled = true
        depthState = device.makeDepthStencilState(descriptor: stencilDescriptor)

        // Setup vertex descriptor
        let vertexDescriptor = MTLVertexDescriptor.init()

        // Positions
        vertexDescriptor.attributes[0].format = MTLVertexFormat.float4
        vertexDescriptor.attributes[0].offset = 0
        vertexDescriptor.attributes[0].bufferIndex = 0

        // Texture coordinates
        vertexDescriptor.attributes[1].format = MTLVertexFormat.half2
        vertexDescriptor.attributes[1].offset = 16
        vertexDescriptor.attributes[1].bufferIndex = 1

        // Single interleaved buffer
        vertexDescriptor.layouts[0].stride = 24
        vertexDescriptor.layouts[0].stepRate = 1
        vertexDescriptor.layouts[0].stepFunction = MTLVertexStepFunction.perVertex

        // Render pipeline
        let pipelineDescriptor = MTLRenderPipelineDescriptor.init()
        pipelineDescriptor.label = "vAmiga Metal pipeline"
        pipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormat.depth32Float
        pipelineDescriptor.vertexFunction = vertexFunc
        pipelineDescriptor.fragmentFunction = fragmentFunc

        // Color attachment
        let colorAttachment = pipelineDescriptor.colorAttachments[0]!
        colorAttachment.pixelFormat = MTLPixelFormat.bgra8Unorm
        colorAttachment.isBlendingEnabled = true
        colorAttachment.rgbBlendOperation = MTLBlendOperation.add
        colorAttachment.alphaBlendOperation = MTLBlendOperation.add
        colorAttachment.sourceRGBBlendFactor = MTLBlendFactor.sourceAlpha
        colorAttachment.sourceAlphaBlendFactor = MTLBlendFactor.sourceAlpha
        colorAttachment.destinationRGBBlendFactor = MTLBlendFactor.oneMinusSourceAlpha
        colorAttachment.destinationAlphaBlendFactor = MTLBlendFactor.oneMinusSourceAlpha
        do {
            try pipeline = device.makeRenderPipelineState(descriptor: pipelineDescriptor)
        } catch {
            metalAssert(false, "Cannot create the Metal GPU pipeline.")
        }
    }

    func buildVertexBuffers() {

        splashScreen.buildVertexBuffers()
        canvas.buildVertexBuffers()
    }
    
    func buildMatrices2D() {

        let model = Renderer.translationMatrix(x: 0, y: 0, z: 0.99)
        let view = matrix_identity_float4x4
        let proj = matrix_identity_float4x4
        let mvp = proj * view * model
        
        canvas.vertexUniforms2D.mvp = mvp
        monis.vertexUniforms2D.mvp = mvp
    }

    func buildMatrices3D() {

        let xAngle = -angleX.current / 180.0 * .pi
        let yAngle = angleY.current / 180.0 * .pi
        let zAngle = angleZ.current / 180.0 * .pi

        let xShift = -shiftX.current
        let yShift = -shiftY.current
        let zShift = shiftZ.current

        let aspect = Float(size.width) / Float(size.height)
        
        let view = matrix_identity_float4x4
        let proj = Renderer.perspectiveMatrix(fovY: Float(65.0 * (.pi / 180.0)),
                                     aspect: aspect,
                                     nearZ: 0.1,
                                     farZ: 100.0)

        let transEye = Renderer.translationMatrix(x: xShift,
                                         y: yShift,
                                         z: zShift + 1.393 - 0.16)

        let transRotX = Renderer.translationMatrix(x: 0.0,
                                          y: 0.0,
                                          z: 0.16)

        let rotX = Renderer.rotationMatrix(radians: xAngle, x: 0.5, y: 0.0, z: 0.0)
        let rotY = Renderer.rotationMatrix(radians: yAngle, x: 0.0, y: 0.5, z: 0.0)
        let rotZ = Renderer.rotationMatrix(radians: zAngle, x: 0.0, y: 0.0, z: 0.5)

        // Chain all transformations
        let model = transEye * rotX * transRotX * rotY * rotZ
        let mvp = proj * view * model
        
        canvas.vertexUniforms3D.mvp = mvp
        monis.vertexUniforms3D.mvp = mvp
    }

    func buildDepthBuffer() {

        let width = Int(size.width)
        let height = Int(size.height)

        precondition(width != 0)
        precondition(height != 0)

        let descriptor = MTLTextureDescriptor.texture2DDescriptor(
            pixelFormat: MTLPixelFormat.depth32Float,
            width: width,
            height: height,
            mipmapped: false)
        descriptor.resourceOptions = MTLResourceOptions.storageModePrivate
        descriptor.usage = MTLTextureUsage.renderTarget

        depthTexture = device.makeTexture(descriptor: descriptor)
        metalAssert(depthTexture != nil,
                    "Could not create depth texture.")
    }
    
    //
    // Matrix utilities
    //
    
    static func perspectiveMatrix(fovY: Float,
                                  aspect: Float,
                                  nearZ: Float,
                                  farZ: Float) -> matrix_float4x4 {
        
        // Variant 1: Keeps correct aspect ratio independent of window size
        let yscale = 1.0 / tanf(fovY * 0.5) // 1 / tan == cot
        let xscale = yscale / aspect
        let q = farZ / (farZ - nearZ)
        
        // Alternative: Adjust to window size
        // float yscale = 1.0f / tanf(fovY * 0.5f);
        // float xscale = 0.75 * yscale;
        // float q = farZ / (farZ - nearZ);
        
        var m = matrix_float4x4()
        m.columns.0 = SIMD4<Float>(xscale, 0.0, 0.0, 0.0)
        m.columns.1 = SIMD4<Float>(0.0, yscale, 0.0, 0.0)
        m.columns.2 = SIMD4<Float>(0.0, 0.0, q, 1.0)
        m.columns.3 = SIMD4<Float>(0.0, 0.0, q * -nearZ, 0.0)
        
        return m
    }
    
    static func scalingMatrix(xs: Float, ys: Float, zs: Float) -> matrix_float4x4 {
        
        var m = matrix_float4x4()
        m.columns.0 = SIMD4<Float>(xs, 0.0, 0.0, 0.0)
        m.columns.1 = SIMD4<Float>(0.0, ys, 0.0, 0.0)
        m.columns.2 = SIMD4<Float>(0.0, 0.0, zs, 0.0)
        m.columns.3 = SIMD4<Float>(0.0, 0.0, 0.0, 1.0)
        
        return m
    }
    
    static func translationMatrix(x: Float,
                                  y: Float,
                                  z: Float) -> matrix_float4x4 {
        
        var m = matrix_identity_float4x4
        m.columns.3 = SIMD4<Float>(x, y, z, 1.0)
        
        return m
    }
    
    static func rotationMatrix(radians: Float,
                               x: Float,
                               y: Float,
                               z: Float) -> matrix_float4x4 {
        
        var v = vector_float3(x, y, z)
        v = normalize(v)
        let cos = cosf(radians)
        let cosp = 1.0 - cos
        let sin = sinf(radians)
        
        var m = matrix_float4x4()
        m.columns.0 = SIMD4<Float>(cos + cosp * v.x * v.x,
                                   cosp * v.x * v.y + v.z * sin,
                                   cosp * v.x * v.z - v.y * sin,
                                   0.0)
        m.columns.1 = SIMD4<Float>(cosp * v.x * v.y - v.z * sin,
                                   cos + cosp * v.y * v.y,
                                   cosp * v.y * v.z + v.x * sin,
                                   0.0)
        m.columns.2 = SIMD4<Float>(cosp * v.x * v.z + v.y * sin,
                                   cosp * v.y * v.z - v.x * sin,
                                   cos + cosp * v.z * v.z,
                                   0.0)
        m.columns.3 = SIMD4<Float>(0.0,
                                   0.0,
                                   0.0,
                                   1.0)
        return m
    }
    
    //
    // Error handling
    //
    
    func metalAssert(_ cond: Bool, _ msg: String) {
        
        if !cond {
            
            let alert = NSAlert()
            
            alert.alertStyle = .critical
            alert.icon = NSImage.init(named: "metal")
            alert.messageText = "Failed to initialize Metal Hardware"
            alert.informativeText = msg
            alert.addButton(withTitle: "OK")
            alert.runModal()
            
            exit(1)
        }
    }
}
