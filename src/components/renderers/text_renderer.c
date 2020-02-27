/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sprite_renderer
*/

#include "components/renderer.h"
#include "vector2.h"
#include "xml.h"
#include "sprite.h"
#include "text.h"
#include "my.h"
#include <malloc.h>
#include <SFML/Graphics.h>

int color_from_text(char *txt)
{
	if (txt == NULL)
		return (*(int *)&sfWhite);
	if (!my_strcmp(txt, "black"))
		return (*(int *)&sfBlack);
	if (!my_strcmp(txt, "white"))
		return (*(int *)&sfWhite);
	return (*(int *)&sfWhite);
}

void text_ctr(struct renderer *cmp, va_list args)
{
    gc_text *gctext = malloc(sizeof(gc_text));

    if (!gctext)
        return;
    cmp->data = gctext;
    gctext->text = va_arg(args, char *);
    gctext->font = va_arg(args, sfFont *);
    gctext->color = color_from_text(va_arg(args, char *));
}

void text_fdctr(gc_scene *scene, struct renderer *cmp, node *n)
{
    gc_text *gctext = malloc(sizeof(gc_text));

    if (!gctext)
        return;
    cmp->data = gctext;
    gctext->text = xml_getproperty(n, "text");
    if (!gctext->text)
        return;
    gctext->font = scene->get_data(scene, "font", xml_getproperty(n, "src"));
}
