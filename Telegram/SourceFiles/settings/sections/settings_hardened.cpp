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
#include "core/core_settings.h"
#include "core/application.h"
#include "ui/ui_utility.h"
#include "ui/widgets/checkbox.h"
#include "ui/vertical_list.h"
#include <QAction>


namespace Settings {

namespace {
using namespace Builder;

void BuildHardenedSectionContent(SectionBuilder &builder) {
    const auto controller = builder.controller();
    const auto session = builder.session();
    const auto settings = &Core::App().settings();
    builder.addDivider();
    builder.addSkip();
    builder.addSubsectionTitle({
        .id = u"hardened/main"_q,
        .title = tr::lng_settings_section_lottie(),
        .keywords = { u"hardened"_q },
    });
    const auto animated = builder.addButton({
        .id = u"hardened/show_animated_stickers"_q,
        .title = tr::lng_settings_hardened_anim_stickers(),
        .toggled = settings->hideAnimatedStickersValue() | rpl::map([](bool checked) {
            return !checked;
        }),
        .keywords = { u"animated"_q, u"stickers"_q }
    });
    
    if (animated) {
        animated->toggledValue() | rpl::filter([=](bool checked) {
            return (settings->hideAnimatedStickers() == checked);
        })
        | rpl::on_next([=](bool checked) {
            settings->setHideAnimatedStickers(!checked);
            Core::App().saveSettingsDelayed();
        }, animated->lifetime());
    }
    
    
    const auto all = builder.addButton({
        .id = u"hardened/show_all_lottie"_q,
        .title = tr::lng_settings_hardened_all_lottie(),
        .toggled = settings->hideAllLottieValue() | rpl::map([](bool checked) {
            return !checked;
        }),
        .keywords = { u"animated"_q, u"lottie"_q }
    });
    
    if (all) {
        all->toggledValue() | rpl::filter([=](bool checked) {
            return (settings->hideAllLottie() == checked);
        })
        | rpl::on_next([=](bool checked) {
            settings->setHideAllLottie(!checked);
            Core::App().saveSettingsDelayed();
        }, all->lifetime());
    }
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
    .title = &tr::lng_settings_hardened_menu,
    .icon = &st::menuIconLock,
}, [] (SectionBuilder &builder) {
    BuildHardenedSectionContent(builder);
});

const SectionBuildMethod kHardenedSection = kMeta.build;

rpl::producer<QString> Hardened::title() {
    return tr::lng_settings_hardened_menu();
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
