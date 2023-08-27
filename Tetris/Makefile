tetris:	Main.o Tetris.o OnePlayer.o TwoPlayers.o
	clang++ Main.o Tetris.o OnePlayer.o TwoPlayers.o  -o tetris -std=c++17 -lncurses
	rm *.o
	
Main.o: Main.cpp
	clang++ -c Main.cpp -std=c++17

Tetris.o: Tetris.cpp
	clang++ -c Tetris.cpp -std=c++17

OnePlayer.o: OnePlayer.cpp
	clang++ -c OnePlayer.cpp -std=c++17

TwoPlayers.o: TwoPlayers.cpp
	clang++ -c TwoPlayers.cpp -std=c++17

clean: 
	rm *.o tetris

