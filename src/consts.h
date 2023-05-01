/**
 * @file consts.h
 * @author Michal Ľaš (xlasmi00)
 * @brief definitions of constans for Pacman project
 * 
 */

#ifndef CONSTS_H
#define CONSTS_H


#define _RED_GHOST_PATH "../../examples/graphics/Red-Ghost.png"
#define _YELLOW_GHOST_PATH "../../examples/graphics/Yellow-Ghost.png"
#define _BLUE_GHOST_PATH "../../examples/graphics/Blue-Ghost.png"
#define _KEY_PATH "../../examples/graphics/Pacman-Key.png"
#define _TARGET_PATH "../../examples/graphics/Target-Point.png"


enum class direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

#endif // CONSTS_H
