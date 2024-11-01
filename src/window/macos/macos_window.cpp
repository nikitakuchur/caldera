#include "macos_window.hpp"

#include <AppKit/NSApplication.hpp>
#include <Foundation/NSAutoreleasePool.hpp>

#include "control/app_delegate.hpp"

bool macos_window_create(int width, int height, const char *title) {
    NS::AutoreleasePool* autorelease_pool = NS::AutoreleasePool::alloc()->init();

    app_delegate controller(width, height, title);

    NS::Application* app = NS::Application::sharedApplication();
    app->setDelegate(&controller);
    app->run();

    autorelease_pool->release();
    return true;
}

void macos_window_set_key_callback(window_key_callback callback) {

}

void macos_window_set_mouse_btn_callback(window_mouse_btn_callback callback) {

}

void macos_window_swap_buffers() {

}

void macos_window_poll_events() {

}

bool macos_window_is_closed() {
    return true;
}

void macos_window_close() {

}

void macos_window_destroy() {

}