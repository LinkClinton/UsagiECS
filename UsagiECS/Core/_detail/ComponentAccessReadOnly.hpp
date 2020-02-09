#pragma once

#include <Core/Entity/Component.hpp>

namespace usagi
{
struct ComponentAccessReadOnly
{
    template <Component C>
    static constexpr bool READ = true;

    template <Component C>
    static constexpr bool WRITE = false;
};
}
