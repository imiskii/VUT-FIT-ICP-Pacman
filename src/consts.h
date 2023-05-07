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

#define _MAP_REPLAY_FILE_EXT "txt"
#define _MAP_FILES "../../examples/maps/"

#define MAX_GAME_LEVEL 5
#define LEVEL_1_SPEED 350
#define LEVEL_DIFF 30

#define RANDOM_SEED 123


/**
 * @brief The direction enum possible movement directions
 * Opposite directions are assigned opposite numbers
 */
enum direction
{
    UP = -2,
    LEFT = -1,
    NONE = 0,
    RIGHT = 1,
    DOWN = 2,
};

#endif // CONSTS_H


/* END OF FILE */
