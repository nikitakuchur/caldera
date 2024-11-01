#include "app_delegate.hpp"

#include "view_delegate.hpp"

app_delegate::app_delegate(int width, int height, const char *title) : width(width), height(height), title(title) {
}

app_delegate::~app_delegate() {
    mtk_view->release();
    window->release();
    device->release();
    delete delegate;
}

void app_delegate::applicationWillFinishLaunching(NS::Notification *notification) {
    NS::Application *app = reinterpret_cast<NS::Application *>(notification->object());
    app->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
}

void app_delegate::applicationDidFinishLaunching(NS::Notification *notification) {
    CGRect frame = (CGRect){
        {100.0, 100.0},
        {static_cast<float>(width), static_cast<float>(height)}
    };

    window = NS::Window::alloc()->init(
        frame,
        NS::WindowStyleMaskClosable | NS::WindowStyleMaskResizable |
        NS::WindowStyleMaskMiniaturizable | NS::WindowStyleMaskTitled,
        NS::BackingStoreBuffered,
        false
    );

    device = MTL::CreateSystemDefaultDevice();

    mtk_view = MTK::View::alloc()->init(frame, device);
    mtk_view->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    mtk_view->setClearColor(MTL::ClearColor::Make(1.0, 1.0, 0.6, 1.0));

    delegate = new view_delegate(device);
    mtk_view->setDelegate(delegate);

    window->setContentView(mtk_view);
    window->setTitle(NS::String::string(title, NS::StringEncoding::UTF8StringEncoding));
    window->makeKeyAndOrderFront(nullptr);

    NS::Application *app = reinterpret_cast<NS::Application *>(notification->object());
    app->activateIgnoringOtherApps(true);
}

bool app_delegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application *sender) {
    return true;
}
