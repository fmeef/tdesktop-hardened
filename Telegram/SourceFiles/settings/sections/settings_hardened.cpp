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


namespace Settings {

namespace {
using namespace Builder;

void BuildHardenedSectionContent(SectionBuilder &context) {
    
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

rpl::producer<QString> Hardened::title() {
    return tr::lng_settings_section_hardened();
}

void Hardened::setupContent() {
    
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

}
