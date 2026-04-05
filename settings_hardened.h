/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "base/flags.h"

template <typename Flags>
struct EditFlagsDescriptor;

namespace Hardened {
enum Flag : uint32;
using Flags = base::flags<Flag>;
} // namespace PowerSaving

namespace Ui {
class GenericBox;
class RpWidget;
} // namespace Ui

namespace Settings {

void HardenedBox(
    not_null<Ui::GenericBox*> box,
    PowerSaving::Flags highlightFlags = PowerSaving::Flags());

[[nodiscard]] EditFlagsDescriptor<PowerSaving::Flags> HardenedLabels();

} // namespace Settings

