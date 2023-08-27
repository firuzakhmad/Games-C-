#include <iostream>
#include <ncurses.h>
#include <string>

#include "Headers/TwoPlayers.h"
#include "Headers/OnePlayer.h"
#include "Headers/ISnakePlayer.h"


#define MARGIN    	(10)
#define nullptr		(0)

#define STR_HELP	u8"Usage: ./ [<option>]\n"    \
					u8"Option\n"	\
					u8"-1: Snake game for one player\n"    \
					u8"-2: Snake game for two players\n"    \
					u8"-h: Show this help\n\n"    \
					u8"<No option>: Snake game for one player\n"


int showHelp();


int main(int argc, char* argv[]) {
	ISnakePlayer* tp = nullptr;

	switch (argc) {
		case 1:	tp = new OnePlayer;	break;
		case 2:
			if (!strcmp(argv[1], u8"-2"))
				tp = new TwoPlayers;
			else if (!strcmp(argv[1], u8"-1"))
				tp = new OnePlayer;
		// default:
		// 	return showHelp();
	}

	tp->Start();
	flushinp();
	timeout(-1);
	getch();
	delete tp;
	return 0;
}

int showHelp() {
	printf(STR_HELP);
	return 0;
}