/*
 * Projectile.cpp
 *
 *  Created on: 9 Dec 2017
 *      Author: apl
 */

#include "Projectile.h"
#include <ncurses.h>
#include <unistd.h>
#include "Player.h"

Player * p;
int x = 0;

Projectile::Projectile(WINDOW * win, int y, int x, char c, Player* player) {
		curwin = win;
		p = player;
		yLoc = y-1;
		xLoc = x;
		getmaxyx(curwin, yMax, xMax);
		character = c;
		mvwprintw(win, yLoc + 2, xLoc -1, "pew");
		wrefresh(win);
		usleep(8000);
		mvwprintw(win, yLoc + 2, xLoc - 1, "   ");
		Projectile::display();

}
void Projectile::mvup(){
		mvwaddch(curwin, yLoc, xLoc, ' ');
		yLoc--;
		if(yLoc < 1)
			Projectile::~Projectile();
		else{
			usleep(50000);
			wrefresh(curwin);
			display();
		}
	}

void Projectile::getmv(){
	mvup();
	display();
}

void Projectile::display(){
	mvwaddch(curwin, yLoc, xLoc, character);
	wrefresh(curwin);
if(x < 1000){
	x++;
	p->Player::display();
}
		mvup();

}

Projectile::~Projectile(){
}

