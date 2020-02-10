#pragma once

#include <execution>

#include "Type.hpp"
#include "Runtime.hpp"

struct System_sprite_render
{
    using ReadAccess = ComponentFilter<
        ComponentSprite,
        ComponentPosition,
        ComponentColor
    >;

    // EntityDB is a concept that covers all instantiations of the
    // database template
    // EntityDatabaseAccess adds layer of permission checking. if the system
    // does not have access to some components, the access is denied.
    template <typename RuntimeServices, typename EntityDatabaseAccess>
    std::size_t update(RuntimeServices&& rt, EntityDatabaseAccess&& db)
    {
        std::atomic<std::size_t> count = 0;
        std::for_each(std::execution::par, db.begin(), db.end(), [&](auto&& p) {
            for (auto&& e : db.page_view(p, ReadAccess()))
            {
                printf("render!");
                ++count; // VERY EXPENSIVE
            }
            });

        return count.load();
    }
};
