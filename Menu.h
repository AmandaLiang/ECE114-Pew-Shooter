/*
 * Menu.h
 *
 *  Created on: 8 Dec 2017
 *      Author: apl
 */
#include <iostream>
#include <ncurses.h>
#include <string>

#ifndef MENU_H_
#define MENU_H_

class Menu {
public:
	Menu(int options = 3
			);
	void Fill();
};

#endif /* MENU_H_ */
