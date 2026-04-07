/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/

#include "settings/sections/settings_hardened.h"

#include "settings/settings_common_session.h"

#include "settings/settings_builder.h"
#include "settings/sections/settings_main.h"
#include "core/core_settings.h"
#include "lang/lang_keys.h"
#include "styles/style_menu_icons.h"
#include "window/window_session_controller.h"
#include "window/window_controller.h"
#include "window/themes/window_theme_editor_box.h"
#include "ui/widgets/menu/menu_add_action_callback.h"
#include "ui/wrap/vertical_layout.h"
#include "ui/ui_utility.h"
#include "ui/vertical_list.h"


namespace Settings {

namespace {
using namespace Builder;



void SetupAllHardened(not_null<Window::SessionController*> controller, not_null<Ui::VerticalLayout*> container) {
    Ui::AddSkip(container);
    const auto title = Ui::AddSubsectionTitle(
        container,
        tr::lng_settings_section_hardened());
    
    
    const auto session = &controller->session();
    
    auto wrap = object_ptr<Ui::VerticalLayout>(container);
    const auto inner = wrap.data();
}


void BuildHardenedSectionContent(SectionBuilder &builder) {
    const auto controller = builder.controller();
    const auto session = builder.session();
    builder.add([controller](const WidgetContext &ctx) {
        SetupAllHardened(controller, ctx.container.get());
        return SectionBuilder::WidgetToAdd{};
    }, [] {
        return SearchEntry{
            .id = u"hardened/main"_q,
            .title = tr::lng_settings_section_hardened(tr::now),
            .keywords = { u"hardened"_q },
            .icon = { &st::menuIconLock }
        };
    });
}


class Hardened : public Section<Hardened> {
public:
    Hardened(QWidget *parent, not_null<Window::SessionController*> controller);
    [[nodiscard]] rpl::producer<QString> title() override;
    
    void fillTopBarMenu(
        const Ui::Menu::MenuCallback &addAction) override;
    
private:
    void setupContent();
};

const auto kMeta = BuildHelper({
    .id = Hardened::Id(),
    .parentId = MainId(),
    .title = &tr::lng_settings_section_hardened,
    .icon = &st::menuIconLock,
}, [] (SectionBuilder &builder) {
    BuildHardenedSectionContent(builder);
});

const SectionBuildMethod kHardenedSection = kMeta.build;

rpl::producer<QString> Hardened::title() {
    return tr::lng_settings_section_hardened();
}

void Hardened::setupContent() {
    const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);
    build(content, kHardenedSection);
    
    Ui::ResizeFitChild(this, content);
}

Hardened::Hardened(QWidget *parent, not_null<Window::SessionController*> controller) : Section(parent, controller) {
    setupContent();
}

void Hardened::fillTopBarMenu(const Ui::Menu::MenuCallback &addAction) {
    const auto window = &controller()->window();
    const auto createTheme = addAction(
        tr::lng_settings_bg_theme_create(tr::now),
        [=] { window->show(Box(Window::Theme::CreateBox, window)); },
        &st::menuIconChangeColors);
    createTheme->setProperty(
        "highlight-control-id",
        u"chat/themes-create"_q);
}

}

Type HardenedId() {
    return Hardened::Id();
}

}
