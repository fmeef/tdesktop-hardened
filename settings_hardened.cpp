/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "settings/settings_hardened.h"

#include "base/battery_saving.h"
#include "boxes/peers/edit_peer_permissions_box.h"
#include "core/application.h"
#include "core/core_settings.h"
#include "lang/lang_keys.h"
#include "ui/layers/generic_box.h"
#include "ui/widgets/buttons.h"
#include "ui/power_saving.h"
#include "ui/vertical_list.h"
#include "settings/settings_common.h"
#include "styles/style_menu_icons.h"
#include "styles/style_layers.h"
#include "styles/style_settings.h"

namespace Settings {
namespace {

constexpr auto kForceDisableTooltipDuration = 3 * crl::time(1000);

} // namespace

void HardenedBox(
        not_null<Ui::GenericBox*> box,
        Hardened::Flags highlightFlags) {
    box->setStyle(st::layerBox);
    box->setTitle(tr::lng_settings_power_title());
    box->setWidth(st::boxWideWidth);

    const auto container = box->verticalLayout();
  
}

EditFlagsDescriptor<Hardened::Flags> HardenedLabels() {
    using namespace Hardened;
    using Label = EditFlagsLabel<Flags>;


    return { .labels = {
        { },
    }, .st = &st::hardenedButton };
}

} // namespace Settings
