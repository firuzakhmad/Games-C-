#include <iostream>
#include <string>
#include <ncurses.h>

#include "Headers/OnePlayer.h"
#include "Headers/TwoPlayers.h"


#define MARGIN		(10)
#define nullptr		(0)

#define STR_HELP	u8"Usage: ./ [<option>]\n"    \
					u8"Option\n"	\
					u8"-1: Tetris game for one player\n"    \
					u8"-2: Tetris game for two players\n"    \
					u8"-h: Show this help\n\n"    \
					u8"<No option>: Tetris game for one player\n"


int showHelp();


int main(int argc, char* argv[]) {
	ITetrisPlayer*  tp = nullptr;

	switch (argc) {
		case 1:	tp = new OnePlayer(MARGIN, 1);	break;
		case 2:
			if (!strcmp(argv[1], u8"-2"))
				tp = new TwoPlayers;
			else if (!strcmp(argv[1], u8"-1"))
				tp = new OnePlayer(MARGIN, 1);
		// default:
		// 	return showHelp();
	}

	tp->play();
	tp->showEndMessage();
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