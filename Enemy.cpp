/*
 * Enemy.cpp
 *
 *  Created on: 11 Dec 2017
 *      Author: apl
 */

#include "Enemy.h"
#include <ncurses.h>

Enemy::Enemy(WINDOW * win, int &score, int &losCond) {
	character = '0';
	curwin = win;
	spawnYLoc = 0;
	spawnXLoc = 0;
	getmaxyx(curwin, yMax, xMax); //gets dimensions of curwin and assigns to var yMax and var xMax
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

