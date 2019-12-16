/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** engine_system_builder
*/

#include "engine.h"
#include "system.h"
#include "systems/sfml_renderer_system.h"
#include "systems/movable_system.h"
#include "systems/controllable_system.h"
#include "systems/parallax_system.h"
#include <stdlib.h>

void engine_add_system(gc_engine *engine, const gc_system *system)
{
    engine->systems = list_add(engine->systems, (void *)system);
}

void engine_add_buildin_systems(gc_engine *engine)
{
    engine->systems = NULL;
    engine->add_system = &engine_add_system;
    engine->get_system = &engine_get_system;
    engine->add_system(engine, &parallax_system);
    engine->add_system(engine, new_system(&movable_system));
    engine->add_system(engine, &controllable_system);
}

int engine_use_sfml(gc_engine *engine, const char *title, int framerate)
{
    gc_system *renderer = new_system(&sfml_renderer, engine, title, framerate);

    if (!renderer)
        return (-1);
    engine->add_system(engine, renderer);
    return (0);
}