/*
 * Enemy.cpp
 *
 *  Created on: 11 Dec 2017
 *      Author: apl
 */

#include "Enemy.h"
#include <ncurses.h>
#include <time.h>

Enemy::Enemy(WINDOW * win, int y, int x, int &score, int &losCond) {
	character = '0';
	curwin = win;
	spawnYLoc = y;
	spawnXLoc = x;
	getmaxyx(curwin, yMax, xMax); //gets dimensions of curwin and assigns to var yMax and var xMax
}

void Enemy::display(){
	mvwaddch(curwin, spawnYLoc, spawnXLoc, character);
	wrefresh(curwin);
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

