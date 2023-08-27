output:	Main.o Snake.o TwoPlayers.o OnePlayer.o 
	clang++ Main.o Snake.o TwoPlayers.o OnePlayer.o -o snake -std=c++17 -lncurses 
	rm *.o

Main.o: Main.cpp
	clang++ -c Main.cpp -std=c++17

Snake.o: Snake.cpp
	clang++ -c Snake.cpp -std=c++17

TwoPlayers.o: TwoPlayers.cpp 
	clang++ -c TwoPlayers.cpp -std=c++17

OnePlayer.o: OnePlayer.cpp 
	clang++ -c OnePlayer.cpp -std=c++17

clean: 
	rm *.o snake

