exefile: ttt tictactoe.c
	./ttt

tictactoe: tictactoe.c
	gcc -o ttt tictactoe.c `pkg-config --libs --cflags gtk+-2.0`



