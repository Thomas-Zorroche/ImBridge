#pragma once

#define DEFAULT_SLIDER_SPEED 0.1f

#include <functional>

namespace ImBridge
{

using CallbackInt = std::function<void(int)>;

using CallbackCombo = std::function<void(unsigned int)>;

}


