/*
 * Projectile.h
 *
 *  Created on: 9 Dec 2017
 *      Author: apl
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include <ncurses.h>
#include "Player.h"

class Projectile {
public:
	Projectile(WINDOW * win, int y, int x, char c, Player * p);
	void display();
	void mvup();
	void getmv();
	~Projectile();
private:
	int xLoc, yLoc, xMax, yMax;
	char character;
	WINDOW * curwin;
};

#endif /* PROJECTILE_H_ */
