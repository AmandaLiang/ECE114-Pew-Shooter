/*
 * Main.cpp
 *
 *  Created on: 4 Dec 2017
 *      Author: Amanda Liang
 *      Course: ECE 114
 *
 *		Resources Used: New Curses Library and accompanying documentation.
 *		http://www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html
 *		http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html
 *
 *      Compilation instructions:
 *      Mac terminal command
 *      gcc -lncurses -lstdc++ Main.cpp Player.cpp Projectile.cpp Enemies.cpp
 *
 *      Optimal size for play is terminal size 100x40.
 */

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <ncurses.h>
#include <string>
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"

int main() {

	//Seed Random for enemy spawner.
	srand((unsigned)time(NULL));

 	initscr(); //initializes and allocates memory for a 24x80 screen.
 	curs_set(0); // Set cursor to invisible
  	clear(); //clears screen.
	cbreak(); // character input in real time, no linebreak character needed.
 	noecho(); // Makes it so that user input does not get printed.
 	keypad(stdscr, TRUE); //Enable use of special keystrokes including the arrow keys.

	printw("PRESS ANY KEY..."); // Print string.
	getch();  // Wait until the user press a key
  	printw("\nFor ECE 114.");
  	halfdelay(10);
  	refresh(); //refreshes window by pulling from previously alloted memory.
 	getch();

 	clear();
 	refresh();

 	//Dimensions
 	int screenY, screenX;
 	getmaxyx(stdscr, screenY, screenX); //saves screen dimensions as a value.

 	//Prints title and author
 	mvprintw(screenY/2-5, screenX/2-11, "'Pew' Shooter");
 	refresh();
  	getch();
 	mvprintw(screenY/2-4, screenX/2-10, "By Amanda Liang");
 	refresh();
 	getch();

	//Initialize score variables.
	int score = 0;
	int highscore = 0;

 	//PRESENTS START MENU
 	mvprintw(screenY - 8, screenX - 29, "PRESS ENTER TO SELECT");
	WINDOW * menuwin = newwin(5, screenX - 12 , screenY - 7, 5 ); //creates new window
	box(menuwin, 0 , 0); //puts default boarders around window.
	refresh(); //refresh
	wrefresh(menuwin); //refresh window.
	keypad(menuwin, true); //activates keypad for new window.

	cbreak();

	//MENU CONTENTS
	std::string choices[3] = {
								"PLAY",
								"ABOUT",
								"EXIT TO TERMINAL"
							};

	int choice;
	int highlight = 0;


		while (1){
			while (1){
			 	mvprintw(screenY - 8, screenX - 29, "PRESS ENTER TO SELECT"); // Reprint the menu
			 	refresh();
				box(menuwin, 0 , 0); //puts default boarders around window.
			for (int i = 0; i < 3; i++){
				if (i == highlight){
					wattron(menuwin, A_BLINK);
					wattron(menuwin, A_REVERSE);//window attribute, reverse foreground and background color
				}
					mvwprintw(menuwin, i+1, 1, choices[i].c_str());
					wattroff(menuwin, A_BLINK);
					wattroff(menuwin, A_REVERSE);
			}
			choice = wgetch(menuwin);

			switch(choice){
			case KEY_UP:
				highlight--;
				if (highlight == -1)
					highlight = 0;
				break;
			case KEY_DOWN:
				highlight++;
				if (highlight == 3)
					highlight = 3 - 1;
				break;
			default:
				break;
			}
			//10 is the number attributed to the enter key.
			if (choice == 10)
				break;
			}
			if(highlight == 0) { //User selects play.

						//Kill the manu window and the PRESS ENTER TO SELECT.
						wclear(menuwin);
						wrefresh(menuwin);
						mvprintw(screenY - 8, screenX - 29, "                     ");
						refresh();

						//wait
						halfdelay(3);
						getch();

						//Create Score Window, border and display.
						WINDOW * scorewin = newwin(16,20,screenY/2-8,3);
						box(scorewin, 0,0);
						mvwprintw(scorewin, 4,6, "SCORE: %d", score);
						mvwprintw(scorewin, 6, 2, "HIGHSCORE: %d", highscore);
						wrefresh(scorewin);

						//Create Play Window, border and Display
						WINDOW * playwin = newwin(screenY,51,0, screenX/2-25);
						box(playwin, 0,0);
						wrefresh(playwin); //refresh window


						getch(); //wait 0.3 seconds or for input.
						getch(); //0.3 more seconds or input

						//Instruction window pop up.
						WINDOW * instructwin = newwin(20, 40, (screenY/2)-10 ,screenX/2-20 );
						box(instructwin, 0,0);
						mvwprintw(instructwin, 9, 8, "PRESS ANY KEY TO EXIT...");
						mvwprintw(instructwin, 2, 14, "INSTRUCTIONS");
						mvwprintw(instructwin, 4, 9, "USE ARROW KEYS TO MOVE.");
						mvwprintw(instructwin, 5, 10, "USE SPACEBAR TO SHOOT.");
						mvwprintw(instructwin, 6, 11, "USE ESCAPE TO EXIT.");
						refresh();
						wrefresh(instructwin);

						cbreak();
						getch(); //Wait anykey to continue.

						halfdelay(1);

						//kill instruction window
						wclear(instructwin);
						wrefresh(instructwin);
						delwin(instructwin); //free memory.
						wrefresh(playwin);

						refresh(); //refresh standard screen.

						int loss = 0; // initialize loss condition variable.
						Player * player = new Player(playwin, screenY-3 ,25, 'x'); // Create Player Object.

				//MAIN GAME LOOP
						do {
							player->display();
							wrefresh(playwin);
							score += 1;
							mvwprintw(scorewin, 4,6, "SCORE: %d", score);
							wrefresh(scorewin);
							Enemy * enemy = new Enemy(playwin,(rand()%10)+2,(rand()%24)*2 + 2, score, loss);
							enemy->display();
							wrefresh(playwin);
						} while (player->getmv()!=27 && loss == 0); //while player doesn't press escape key and hasn't lost.

				//ENDGAME
							mvwprintw(playwin, screenY/2 - 3, 21, "GAME OVER");
							wrefresh(playwin);
							halfdelay(5);
							wgetch(playwin);
							if(score > highscore){
								highscore = score;
								mvwprintw(playwin, screenY/2 - 1, 8, "CONGRATULATIONS! NEW HIGH SCORE: %d", highscore);
								mvwprintw(scorewin, 6, 2, "HIGHSCORE: %d", highscore);
								wrefresh(playwin);
								wrefresh(scorewin);
								getch();
								mvwprintw(playwin, screenY/2 + 1, 15, "PRESS ANY KEY TO EXIT");
								wrefresh(playwin);
								cbreak();
								getch();
							} else {
								mvwprintw(playwin, screenY/2 - 1, 15, "PRESS ANY KEY TO EXIT");
								wrefresh(playwin);
								cbreak();
								getch();
							}
							score = 0;
							mvwprintw(scorewin, 4,6, "SCORE: %d    ", score);
							wrefresh(scorewin);
							wclear(playwin);
							wrefresh(playwin);
			}

			if (highlight==1){ //User selects about.
						//wclear(stdscr); //Aesthetic decision. Keeps aboutscr overlayed on the rest of the menu.
						WINDOW * aboutwin = newwin(screenY,50,0, screenX/2-25);
						mvwprintw(aboutwin, 1, 14, "PRESS ANY KEY TO EXIT");
						mvwprintw(aboutwin, 3,1, " Hello! \n    My name is Amanda and I'm currently an ECE      major at the U of R.\n\n    This is a simple shooter game I built in C++\n  for my ECE 114 class with a fun little twist.\n  It utilizes the ncurses library and is mostly     just for amusement/academic purposes.");
						box(aboutwin, 0,0);
						refresh(); //refresh
						wrefresh(aboutwin); //refresh window.
						wgetch(aboutwin);
						keypad(aboutwin, true); //activates keypad for new window.
						wclear(aboutwin); //replace all points of the window with a space.
						mvprintw(screenY - 8, screenX - 29, "PRESS ENTER TO SELECT"); //reprint to compensate for clear
						wrefresh(aboutwin);
			}

			if (highlight == 2){ //User selects exit to terminal.
				break;
			}
		}// goes back to menu loop.

					endwin(); // deallocate memory, ends ncurses

		 	return 0;
		}
