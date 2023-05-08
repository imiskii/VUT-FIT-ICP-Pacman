##
# Makefile
# Authors: Adam Lazík (xlazik00), Michal Ľaš (xlasmi00)
# Date: 23.04.2023
#

TOPACK=Makefile README.txt doc examples src/build src/Controller src/Model src/View src/ICP-pacman.pro src/main.cpp src/consts.h logs/.gitkeep
TOCLEAN=src/build/* src/build/.qmake.stash src/build/.qtc_clangd *.zip doc/html
POINTS_DISTRIBUTION=30-70

all: compile
	cd src/build && make


compile: src/ICP-pacman.pro
	qmake src/ICP-pacman.pro -o src/build/Makefile


run: all
	cd src/build && ./ICP-pacman


doxygen:
	cd doc/ && doxygen Doxyfile


clean:
	rm -rf $(TOCLEAN)


pack: clean
	zip -r xlazik00_xlasmi00-$(POINTS_DISTRIBUTION) $(TOPACK)
