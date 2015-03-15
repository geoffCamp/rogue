/************************ utility.h ******************************************
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
*********************************************************************************/

#ifndef _GCAMP_UTILITY
#define _GCAMP_UTILITY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>

/*
Determine number of elements in room.
IN: String of element positions.
OUT: Number of elements.
*/
int elemSize(char * elemString);

/*
Free room memory.
IN: Array of room structs.
OUT: N/A
*/
void freeRooms(room ** roomsArray);

/*
Free array of Doors
IN: Array of door and room pointer;
OUT: N/A
*/
void freeDoors(door ** doorsArray, room ** roomsArray);

/*
Free array of monsters
IN: Array of doors and room pointers
OUT: N/A
*/
void freeMonsters(monster ** monstersArray, room ** roomsArray);

/*
Free hero struct.
IN: Hero struct pointer.
OUT: N/A
*/
void freeHero(hero * activeHero);

/*
Print parsed room information for testing purposes.
IN: Pointer to array of room structs.
OUT: N/A
*/
void testPrint(room ** roomsArray);

/*
Remove first letter fromm element position strings.
IN: Elements position string and size of new string.
OUT: Pointer to new position string.
*/
char * removeLetter(char * element, int quant);

/*
Check if current cursor location if a wall or a monsterto prevent walking over them.
IN: Hero coodinates.
OUT: In wall status.
*/
int checkWall(int y, int x);

/*
Check if the cursor is over a floor filled cell.
IN: N/A
OUT: N/A
*/
int floorStatus();

/*
Print system messages.
IN: Message code and hero struct.
OUT: N/A
*/
void message(hero * activeHero, int msgCode);     

#endif
