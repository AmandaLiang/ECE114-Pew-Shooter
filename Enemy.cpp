/*
 * Enemy.cpp
 *
 *  Created on: 11 Dec 2017
 *      Author: apl
 */

#include "Enemy.h"
#include "Player.h"
#include <ncurses.h>
#include <time.h>

Enemy::Enemy(WINDOW * win, int y, int x, int &score, int &losCond) {
	character = '0';
	curwin = win;
	spawnYLoc = y;
	spawnXLoc = x;
	getmaxyx(curwin, yMax, xMax); //gets dimensions of curwin and assigns to var yMax and var xMax
}

void Enemy::mvdown(){
		mvwaddch(curwin, spawnYLoc, spawnXLoc, ' ');
		spawnYLoc++;
			if(spawnYLoc > yMax - 2){
				Enemy::~Enemy();
			}
			else{
				usleep(30000);
				wrefresh(curwin);
				display();
			}
		}

void Enemy::getmv(){
	mvdown();
	display();
}

void Enemy::display(){
	mvwaddch(curwin, spawnYLoc, spawnXLoc, character);
	wrefresh(curwin);
	mvdown();
}

Enemy::~Enemy() {
}

