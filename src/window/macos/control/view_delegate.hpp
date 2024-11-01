#ifndef VIEW_DELEGATE_HPP
#define VIEW_DELEGATE_HPP

#include <MetalKit/MTKView.hpp>
#include "../view/mtl_renderer.hpp"

class view_delegate : public MTK::ViewDelegate {
public:
    view_delegate(MTL::Device *device);

    ~view_delegate() override;

    void drawInMTKView(MTK::View *view) override;

private:
    mtl_renderer *renderer;
};


#endif //VIEW_DELEGATE_HPP
