/*
 * Enemy.h
 *
 *  Created on: 11 Dec 2017
 *      Author: apl
 */

#ifndef ENEMY_H_
#define ENEMY_H_
#include <ncurses.h>
#include <time.h>

class Enemy {
public:
	Enemy(WINDOW * win, int y, int x, int &score, int &losCond);
	void Kill();
	virtual ~Enemy();
	void mvdown();
	void display();

private:
	int spawnXLoc, spawnYLoc, xMax, yMax;
	char character;
	WINDOW * curwin;
};
#endif /* ENEMY_H_ */
