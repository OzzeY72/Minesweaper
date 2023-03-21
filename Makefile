all:
	g++ -c Main.cpp -I/usr/lib/SFML/include
	g++ Main.o -o Minesweaper -L/usr/lib/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
