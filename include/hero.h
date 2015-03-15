/************************ hero.h ******************************************
Student Name:Geofferson Camp    
Date: March 13th, 2015         Course Name: cis2500

I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.

Sources:
- nCurses functions referenced from www.linux.die.net/man
****************************************************************************/


#ifndef _GCAMP_HERO
#define _GCAMP_HERO

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ncurses.h>
#include <time.h>

/*
Communication between the Hero action and the status of the game.
IN: Hero struct, array of monster structs, array of room structs.
OUT: Game status.
*/
int heroAction(hero * activeHero, room ** roomsArray, monster ** monstersArray);

/*
Handles hero movement and other game interaction.
IN: User input, hero struct, contents of cell before hero overwrote it, array of monster structs, array of room structs.
OUT: Contents of cell.
*/
char moveHero(char action, hero * activeHero, char prevItem, room ** roomsArray, monster ** monstersArray);

/*
Retrieves contents of cell before hero symbol overwrites it.
IN: hero struct.
OUT: character previously in cell.
*/
char item(hero * activeHero);

/*
Moves and prints hero location.
IN: Current, and future hero coordinates and future location cell contents.
OUT: N/A
*/
void printHero(int y, int x, int oldY, int oldX, char itemHolder);

/*
Move all monsters 1 unit when the hero moves.
IN: List of monster structs, room structs, and the hero struct.
OUT: N/A
*/
void moveMonster(monster ** monstersArray, room ** roomsArray, hero * activeHero);

#endif
