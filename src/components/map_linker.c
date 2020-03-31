/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** map_linker.c
*/

#include "components/renderer.h"
#include "component.h"
#include "components/vertex_component.h"
#include "components/map_linker.h"
#include "map_utils.h"
#include "my.h"


static void init(gc_entity *entity, struct vertex_component *vert, int x, int y)
{
    struct renderer *rend;
    struct tile *tile = get_tile_at(vert, (gc_vector2i){x, y});

    if (!tile) {
        my_printf("No tile found at %d, %d. Can't link entity to it.\n", x, y);
        return;
    }
    tile->entity = entity;
    rend = GETCMP(entity, renderer);
    if (rend) {
        rend->is_visible = false;
        rend->is_centered_x = true;
    }
}

static void ctr(void *component, va_list args)
{
    gc_entity *entity = va_arg(args, gc_entity *);
    gc_scene *scene = va_arg(args, gc_scene *);
    gc_list *maps;
    struct vertex_component *vert;
    int x = va_arg(args, int);
    int y = va_arg(args, int);

    if (!scene || !(maps = scene->get_entity_by_cmp(scene, "vertex_component")))
        return;
    vert = GETCMP(maps->data, vertex_component);
    init(entity, vert, x, y);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    gc_list *maps = scene->get_entity_by_cmp(scene, "vertex_component");
    struct vertex_component *vert;
    int x = xml_getintprop(n, "x");
    int y = xml_getintprop(n, "y");

    if (!maps)
        return;
    vert = GETCMP(maps->data, vertex_component);
    init(entity, vert, x, y);
}

static void dtr(void *component)
{
    (void)component;
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct map_linker map_linker = {
    base: {
        name: "map_linker",
        size: sizeof(struct map_linker),
        dependencies: (char *[]) {
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};