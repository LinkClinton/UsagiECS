// Fireworks ECS Demo

// Fires random fireworks from the land. The fireworks fly into the sky for
// some distance and explode. The sparks fly away from the explosion center
// and gradually disappear.

//#define NDEBUG

#include <Core/_detail/EntityDatabaseAccessExternal.hpp>

#include "System_fireworks_spawn.hpp"
#include "System_fireworks_explode.hpp"
#include "System_sprite_render.hpp"
#include "System_physics.hpp"
#include "System_remove_out_of_bound.hpp"
#include "System_spark_fade.hpp"
#include "Service_master_clock.hpp"
#include "Service_stat.hpp"

#define UPDATE_SYSTEM(sys) \
    sys.update(rt, EntityDatabaseAccessExternal< \
        Database, \
        ComponentAccessSystemAttribute<decltype(sys)> \
    >(&db)) \
/**/

int main()
{
    Database db;

    System_fireworks_spawn      sys_spawn;
    System_fireworks_explode    sys_explode;
    System_spark_fade           sys_fade;
    System_physics              sys_physics;
    System_remove_out_of_bound  sys_remove_oob;
    System_sprite_render        sys_render;
    using namespace std::chrono_literals;

    struct RuntimeServices
        : Service_master_clock_default
        , Service_stat
    {
    } rt;

    while(true)
    {
        USAGI_SERVICE(rt, Service_master_clock).tick();
        auto &stat = USAGI_SERVICE(rt, Service_stat);

        Clock timer;
        stat.time_input = timer.tick();

        UPDATE_SYSTEM(sys_spawn);
        stat.time_spawn = timer.tick();

        UPDATE_SYSTEM(sys_explode);
        stat.time_explode = timer.tick();

        UPDATE_SYSTEM(sys_fade);
        stat.time_fade = timer.tick();

        UPDATE_SYSTEM(sys_physics);
        stat.time_physics = timer.tick();

        UPDATE_SYSTEM(sys_remove_oob);
        stat.time_remove = timer.tick();


        stat.sprite_count = UPDATE_SYSTEM(sys_render);
        stat.time_render = timer.tick();

        db.reclaim_pages();
    }

    return 0;
}
