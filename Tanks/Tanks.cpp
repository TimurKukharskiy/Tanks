// Tanks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "map_cl.h"
int main() {
	map_cl map_obj;
//	initscr();
//	raw();
//	nodelay(stdscr, TRUE);
	//	cbreak();
//	noecho();
//	keypad(stdscr, TRUE);
	//	WINDOW *win = new win(50,50, 0,0);
	while (map_obj.update());
//	endwin();
	//	delete win;
	return 0;
}



