#include "view_delegate.hpp"

#include "../view/mtl_renderer.hpp"

view_delegate::view_delegate(MTL::Device *device): ViewDelegate(), renderer(new mtl_renderer(device)) {
}

view_delegate::~view_delegate() {
    delete renderer;
}

void view_delegate::drawInMTKView(MTK::View *view) {
    renderer->draw(view);
}
