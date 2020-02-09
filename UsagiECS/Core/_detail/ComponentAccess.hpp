#pragma once

#include <Core/Entity/Component.hpp>

namespace usagi
{
// At places requiring access validations, use these two templates with
// ComponentAccess instead of using the ComponentAccess trait classes.

template <typename ComponentAccess, Component C>
constexpr bool HasComponentWriteAccess =
    ComponentAccess::template WRITE<C>;

template <typename ComponentAccess, Component C>
constexpr bool HasComponentReadAccess =
    HasComponentWriteAccess<ComponentAccess, C> ||
    ComponentAccess::template READ<C>;
}
