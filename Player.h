/*
 * player.h
 *
 *  Created from ncurses tutorial 8 - Basic top down player movement
 *  from Casual Coder on YouTube.
 *
 *  Adapted by Amanda Liang.
 *  The only change I made was I added a pew function.
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <ncurses.h>
#include <string>

class Player {
public:
	Player(WINDOW * win, int y, int x, char c);
	void mvup();
	void mvdown();
	void mvleft();
	void mvright();
	int getmv(int move);
	void display();
	void pew(); // Mine
	int getLocX();
	int getLocY();
private:
	int xLoc, yLoc, xMax, yMax;
	char character;
	WINDOW * curwin;
};


#endif /* PLAYER_H_ */
