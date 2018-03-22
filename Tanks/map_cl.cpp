/*
 * map_cl.cpp
 *
 *  Created on: Aug 13, 2016
 *      Author: timur
 */
#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
using namespace std;
BOOLEAN nanosleep(LONGLONG ns) {
	 	/* Declarations */
		HANDLE timer;	/* Timer handle */
	 	LARGE_INTEGER li;	/* Time defintion */
	 	/* Create timer */
		if (!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
			return FALSE;
	 	/* Set timer properties */
		 	li.QuadPart = -ns;
	 	if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)) {
		 		CloseHandle(timer);
		 		return FALSE;
		
	}
	 	/* Start & wait for timer */
		 	WaitForSingleObject(timer, INFINITE);
	 	/* Clean resources */
		 	CloseHandle(timer);
	 	/* Slept without problems */
		 	return TRUE;
	
}
static int k = 206;

void gotoXY(int y, int x,char c)
{
	//Initialize the coordinates
	COORD coord = { x, y };
	//Set the position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout<<c;
	return;
}

void ClearConsole()
{
	//Get the handle to the current output buffer...
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//This is used to reset the carat/cursor to the top left.
	COORD coord = { 0, 0 };
	//A return value... indicating how many chars were written
	//   not used but we need to capture this since it will be
	//   written anyway (passing NULL causes an access violation).
	DWORD count;
	//This is a structure containing all of the console info
	// it is used here to find the size of the console.
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	//Here we will set the current color
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//This fills the buffer with a given character (in this case 32=space).
		FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		//This will set our cursor position for the next print statement.
		SetConsoleCursorPosition(hStdOut, coord);
	}
	return;
}


map_cl::map_cl(){
		srand(time(NULL));
		xx = 49;
		yy = 20;
		for (int i = 0;i < 6;i++){
			map [i] = new unsigned char *[50];
			for (int x = 0; x < 50; x++){
				map[i][x] = new unsigned char [50];
			}
		}
		for (int i = 0; i < 6; i++){
			for (int x = 0; x < 50; x++){
				for(int y = 0; y < 50; y++){
					map[i][x][y] = (unsigned char)rand()%204;
					if((map[i][x][y]>10)&&(map[i][x][y] < 199))map[i][x][y] = 30;
				}
			}
		}
		map[0][25][25] = 29;
		map[0][25][26] = 29;
		map[0][25][27] = 29;
		map[0][26][25] = 29;
		map[0][26][26] = 208;
		map[0][26][27] = 29;
		map[0][27][25] = 29;
		map[0][27][26] = 29;
		map[0][27][27] = 29;
		map[0][xx][yy] = 'O';

}
map_cl::~map_cl(){
	for (int i = 0;i < 6;i++){
		for (int x = 0; x < 50; x++){
			delete map[i][x];
		}
		delete map[i];
	}

}
bool map_cl::update(){

	int c = 0;
	if(_kbhit())c = _getch();
	if (c == 27)return false;
	if(c == 'a'){
		if((yy > 0) && (map[0][xx][yy - 1] == 30)){
			if (map[0][xx][yy] == 'O')map[0][xx][yy] = 30;
			map[0][xx][yy - 1] = 'O';
			yy--;
		}
	}
	if(c == 'd'){
		if((yy < 49) && (map[0][xx][yy + 1] == 30)){
			if (map[0][xx][yy] == 'O')map[0][xx][yy] = 30;
			map[0][xx][yy + 1] = 'O';
	//		mvaddch(xx,yy,' ');
	//		mvaddch(xx,yy + 1,'O');
			yy++;
		}
	}
	if(c == 'w'){
		if(xx == 0){
			return false;
		}
		if((xx > 0) && (map[0][xx - 1][yy] == 30)){
			if (map[0][xx][yy] == 'O')map[0][xx][yy] = 30;
			map[0][xx - 1][yy] = 'O';
			xx--;

		}
	}
	if(c == 's'){
		if((xx < 49) && (map[0][xx + 1][yy] == 30)){
			if (map[0][xx][yy] == 'O')map[0][xx][yy] = 30;
			map[0][xx + 1][yy] = 'O';
			xx++;
		}
	}
	if (c == ' ') {
		map[0][xx - 1][yy] = 205;
	}
	bool game_over = false;
	switch (k) {
	case 206:
		k = 207;
		break;
	case 207:
		k = 206;
		break;
	default:
		break;
	}

	for (int x = 0; x < 50; x++) {
		for (int y = 0; y < 50; y++) {
			if (map[0][x][y] < 30)gotoXY(x, y, '*');
			if (map[0][x][y] == 0)map[0][x][y] = 30;
			if (map[0][x][y] == 205)gotoXY(x, y, '+');
			if (map[0][x][y] == 208)gotoXY(x, y, 'G');

			if (map[0][x][y] == 206)gotoXY(x, y, '-');
			if (map[0][x][y] == 207)gotoXY(x, y, '-');
			if (map[0][x][y] == 'O')gotoXY(x, y, 'O');

			if (map[0][x][y] == 30)gotoXY(x, y, ' ');

			if ((map[0][x][y] == 200) || (map[0][x][y] == 199)) {
				gotoXY(x, y, 'X');
				int t = 0;
				while (t < 50) {
					if ((map[0][t][y] == 'O') && (x < 49)) {
						map[0][x + 1][y] = k;
						break;
					}
					t++;
				}
				game_over = false;
				if ((x == xx) && (y == yy))return false;
				if ((y == 49) && (map[0][x][y] == 200)) {
					map[0][x][y] = 199;
					continue;
				}
				if ((y == 0) && (map[0][x][y] == 199)) {
					map[0][x][y] = 200;
					continue;
				}
				if (map[0][x][y] == 200) {
					if (map[0][x][y + 1] == 205) {
						map[0][x][y] = 30;
						continue;
					}
					if ((map[0][x][y + 1] == 30) || (map[0][x][y + 1] == 'O')) {
						map[0][x][y] = 30;
						map[0][x][y + 1] = 200;
						y++;
					}
					else map[0][x][y] = 199;
					continue;
				}
				if (map[0][x][y] == 199) {
					if (map[0][x][y - 1] == 205) {
						map[0][x][y] = 30;
						continue;
					}
					if ((map[0][x][y - 1] == 30) || (map[0][x][y - 1] == 'O')) {
						map[0][x][y] = 30;
						map[0][x][y - 1] = 199;
					}
					else map[0][x][y] = 200;
				}

			}
		}
	}
	for (int y = 0;y < 50; y++){
		for(int x = 0;x < 50;x++){
			if (map[0][x][y] == 205) {
				map[0][x][y] = 30;
				if ((x < 50) && (x > 0) && (map[0][x - 1][y] >= 30))map[0][x - 1][y] = 205;
				if ((x<50) && (x>0) && (map[0][x - 1][y] < 30)&& (map[0][x - 1][y] > 0))map[0][x - 1][y]--;
			}
			if (map[0][x][y] == k) {
				map[0][x][y] = 30;
				if ((x < 49) && (x > 0) && (map[0][x + 1][y] >= 30)&&(map[0][x+1][y]!=205)) {
					if (map[0][x + 1][y] == 'O')return false;
					if(k==206)map[0][x + 1][y] = 207;
					else map[0][x + 1][y] = 206;
				}
			}

			if((map[0][x][y] == 201)||(map[0][x][y] == 202)||(map[0][x][y] == 203)){
				gotoXY(x,y, 'X');
				game_over = false;
				if((x == xx)&&(y == yy))return false;
				if ((x == 49)&&(map[0][x][y] == 202)){
					map[0][x][y] = 101;
					continue;
				}
				if ((x == 0)&&(map[0][x][y] == 201)){
					map[0][x][y] = 102;
					continue;
				}
				if(map[0][x][y] == 202){
					if (map[0][x + 1][y] == 205) {
						map[0][x][y] = 30;
						continue;
					}
					if ((map[0][x + 1][y] == 30)||(map[0][x + 1][y] == 'O')){
						map[0][x][y] = 30;
						map[0][x + 1][y] = 202;
						x++;
					}
						else map[0][x][y] = 201;
					continue;
				}
				if(map[0][x][y] == 201){
					if (map[0][x - 1][y] == 205) {
						map[0][x][y] = 30;
						continue;
					}
					if((map[0][x - 1][y] == 30)||(map[0][x - 1][y] == 'O')){
						map[0][x][y] = 30;
						map[0][x - 1][y]= 201;
					}
						else map[0][x][y] = 202;
				}

			}
		}
	}
	nanosleep(1000);
	if (game_over)return false;
		else return true;
}
