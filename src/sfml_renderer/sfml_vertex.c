/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** sfml_vertex
*/

#include "sfml_renderer.h"
#include "vector2.h"
#include "sprite.h"
#include "text.h"
#include "components/transform_component.h"
#include "systems/sfml_renderer_system.h"
#include "components/vertex_component.h"
#include <math.h>
#include <stdint.h>
#include <SFML/Graphics.h>

#define ANGLE_X 45
#define ANGLE_Y 35

sfVector2f get_tile_coords(int x, int y, int z)
{
	return (sfVector2f){
		cos(ANGLE_X) * y * 64 - cos (ANGLE_X) * x * 64,
		(sin(ANGLE_Y) * x  * 64 + sin (ANGLE_Y) * y * 64 - z) + 250
	};
}

void draw_tile(struct sfml_renderer_system *this, struct vertex_component \
*info, struct tile tile)
{
    sfVertex *vert1 = sfVertexArray_getVertex(this->vertices, 1);
    sfVertex *vert2 = sfVertexArray_getVertex(this->vertices, 2);
    sfVertex *vert3 = sfVertexArray_getVertex(this->vertices, 3);
	int corners[9];

	if (tile.corners[0]->z == INT32_MAX || !tile.corners[3]->y)
		return;
	for (int i = 0; i < 3; i++) {
		corners[i * 3] = tile.corners[i + 1]->x;
		corners[i * 3 + 1] = tile.corners[i + 1]->y;
		corners[i * 3 + 2] = tile.corners[i + 1]->z;
	}
	vert1->position = get_tile_coords(corners[0], corners[1], corners[2]);
    vert2->position = get_tile_coords(corners[3], corners[4], corners[5]);
    vert3->position = get_tile_coords(corners[6], corners[7], corners[8]);
    this->states->texture = (sfTexture *)tile.texture;
	sfRenderWindow_drawVertexArray(this->window, this->vertices, this->states);
}

void draw_line(struct sfml_renderer_system *this, struct vertex_component \
*info, int x, int y)
{
	sfVertex *vert1 = sfVertexArray_getVertex(this->vertices, 1);

	if (y < 0 || x < 0)
		return;
	if (!info->vertices[y] || info->vertices[y][x].z == INT32_MAX)
		return;
	//printf("Drawing line for vertex at %d, %d\n", x, y);
	vert1->position = get_tile_coords(info->vertices[y][x].x, info->vertices[y][x].y, info->vertices[y][x].z);
	sfRenderWindow_drawVertexArray(this->window, this->vertices, NULL);
}


void sfmlrenderer_draw_tilemap(struct sfml_renderer_system *this, \
struct vertex_component *info)
{
    sfVertex *vert0 = sfVertexArray_getVertex(this->vertices, 0);
	int corners[3];
	int i;

	if (!info || !info->map)
		return;
	for (i = 0; info->map[i].corners[0]->z != INT32_MIN; i++);
	//my_printf("zdzdzdzd\n");
    for (i--; i >= 0; i--) {
		//my_printf("mdr %i\n", i);
		corners[0] = info->map[i].corners[0]->x;
		corners[1] = info->map[i].corners[0]->y;
		corners[2] = info->map[i].corners[0]->z;
        //if (!info->map[i].corners[0]->y)
       //     continue; 
        vert0->position = get_tile_coords(corners[0], corners[1], corners[2]);
        draw_tile(this, info, info->map[i]);
    }
}