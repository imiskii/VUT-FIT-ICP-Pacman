# VUT-FIT-ICP-Pacman
The C++ Programming Language - Pacman project

# Authors
Adam Lazík (xlazik00)
Michal Ľaš (xlasmi00)

# Implemented functionality

- PacMan control using WASD
- Autonomous Ghost movement
- Logging - logs can be found in /logs directory
- Loading of maps from files in /examples/maps/ directory
- Interactive Element: Score
    * with each passed game, player score is incremented by one
    * score resets upon changing the map
- Interactive Element: Lives
    * Player starts with three lives
    * Upon encounter with ghost, player loses one life and the game is reset
    * Upon reaching zero lives, the player is reset
- Interactive Element: Levels
    * Upon completing a level and starting next level, both pacman and ghosts
    are faster

# Unimplemented functionality
- Game replaying
- Pacman movement using mouse

# Assigned tasks

asignee  | task                                     | status
xlasmi00 | create GUI, pages and navigation         | completed
xlasmi00 | create animations for pacman and ghosts  | completed
xlasmi00 | create map and model for displying maps  | completed
xlasmi00 | implement pacman movement using WASD     | completed
xlasmi00 | implement map loading from files         | completed
xlasmi00 | doxyfile                                 | completed
xlasmi00 | Makefile                                 | completed
xlazik00 | implement logging                        | completed
xlazik00 | implement ghost movement                 | completed
xlazik00 | implement lives and score                | completed
xlazik00 | implement game replay                    | not completed
xlazik00 | implement pacman movement using mouse    | not completed


# Files documentation

The author is listed in the header of each file. (automatically generated 
files do not have headers or the author is not mentioned in them). 
If both authors are listed in the header, one of the authors also lists the 
methods/functions he implemented (the other author developed everything else).


# Points distribution

We believe that it is fair to distribute points 30:70 in favor of xlasmi00
since xlazik00 did not implement his assigned tasks, including replaying games,
which is mandatory according to project assignment
