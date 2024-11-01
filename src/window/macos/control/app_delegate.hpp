#ifndef APP_DELEGATE_HPP
#define APP_DELEGATE_HPP

#include <AppKit/NSApplication.hpp>
#include <MetalKit/MTKView.hpp>

#include "view_delegate.hpp"


class app_delegate : public NS::ApplicationDelegate {
public:
    app_delegate(int width, int height, const char *title);

    ~app_delegate();

    void applicationWillFinishLaunching(NS::Notification *pNotification) override;

    void applicationDidFinishLaunching(NS::Notification *pNotification) override;

    bool applicationShouldTerminateAfterLastWindowClosed(NS::Application *pSender) override;

private:
    int width;
    int height;
    const char *title;

    NS::Window *window{};
    MTK::View *mtk_view{};
    MTL::Device *device{};
    view_delegate *delegate{};
};


#endif //APP_DELEGATE_HPP
