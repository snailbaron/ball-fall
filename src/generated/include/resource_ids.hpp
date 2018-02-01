#pragma once

#include <cstdint>

namespace res {

enum class BitmapId : uint32_t {
    Ball,
    BrickGold,
    BrickGreen,
    BrickRed,
    PlatformLeft,
    PlatformMiddle,
    PlatformRight,
};

enum class FontId : uint32_t {
    Mecha,
    MechaBold,
    MechaCondensed,
    MechaCondensedBold,
    ComfortaaBold,
    ComfortaaLight,
    ComfortaaRegular,
};

} // namespace res
