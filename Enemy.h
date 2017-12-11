/*
 * Enemy.h
 *
 *  Created on: 11 Dec 2017
 *      Author: apl
 */

#ifndef ENEMY_H_
#define ENEMY_H_

class Enemy {
public:
	Enemy(WINDOW * win, int y, int x, char c);
	void Kill();
	virtual ~Enemy();
	void mvdown();
	void display();

private:
	int xLoc, yLoc, xMax, yMax;
	char character;
	WINDOW * curwin;
};
#endif /* ENEMY_H_ */
