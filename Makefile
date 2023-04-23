##
# Makefile
# Authors: Adam Lazík (xlazik00), Michal Ľaš (xlasmi00)
# Date: 23.04.2023
#

TOPACK=Makefile README.txt doc examples src/build src/Controller src/Model src/View src/ICP-pacman.pro src/main.cpp


all: compile
	cd src/build && make


compile: src/ICP-pacman.pro
	qmake src/ICP-pacman.pro -o src/build/Makefile


run: all
	src/build/ICP-pacman


clean:
	rm -rf src/build/* src/build/.qmake.stash src/build/.qtc_clangd *.zip


pack: clean
	zip -r xlazik00_xlasmi00 $(TOPACK)