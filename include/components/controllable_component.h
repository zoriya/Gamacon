/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#pragma once

#include "component.h"

struct controllable_component
{
    gc_component base;
    int left_key;
    int right_key;
    int jump_key;
    int speed;
};

extern const struct controllable_component controllable_component;