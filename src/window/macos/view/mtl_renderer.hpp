#ifndef MTL_RENDERER_HPP
#define MTL_RENDERER_HPP

#include <Metal/MTLDevice.hpp>
#include <MetalKit/MTKView.hpp>


class mtl_renderer {
public:
    mtl_renderer(MTL::Device *device);

    ~mtl_renderer();

    void draw(MTK::View *view);

private:
    MTL::Device *device;
    MTL::CommandQueue *command_queue;
};


#endif //MTL_RENDERER_HPP
