/*
 * player.cpp
 *
 *  Created from ncurses tutorial 8 - Basic top down player movement
 *  from Casual Coder on YouTube.
 *  Added one function. (pew)
 *  Added score update to display.
 *  Added get functions for locations.
 */

#include "Player.h"
#include <ncurses.h>
#include <string.h>
#include "Projectile.h"

Player::Player(WINDOW * win, int y, int x, char c){
	curwin = win;
	yLoc = y;
	xLoc = x;
	getmaxyx(curwin, yMax, xMax);
	keypad(curwin, true);
	character = c;
}

//fires projectile
void Player::pew(){
	// creates a projectile object from current location
	Projectile * pew = new Projectile(curwin, yLoc, xLoc, '|', this);
}


void Player::mvup(){
	mvwaddch(curwin, yLoc, xLoc, ' ');
	yLoc--;
	if(yLoc < 2)
		yLoc = 2;
}
void Player::mvdown(){
	mvwaddch(curwin, yLoc, xLoc, ' ');
	yLoc++;
		if(yLoc > yMax-3)
			yLoc = yMax-3;
}
void Player::mvleft(){
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc--;
	xLoc--;
	if(xLoc < 2)
		xLoc =2;
}
void Player::mvright(){
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc++;
	xLoc++;
		if(xLoc > xMax-3)
			xLoc = xMax-3;
}

int Player::getmv(int input){
	switch(input){
	case KEY_UP:
		mvup();
		break;
	case KEY_DOWN:
			mvdown();
			break;
	case KEY_LEFT:
			mvleft();
			break;
	case KEY_RIGHT:
			mvright();
			break;
	case 32://ascii value for whitespace
		Player::pew();
		break;
	default:
			break;
	}
	return input;
}

void Player::display(){
	mvwaddch(curwin, yLoc, xLoc, character);
	wrefresh(curwin);
}

int Player::getLocX(){
	return xLoc;
}

int Player::getLocY(){
	return yLoc;
	}

