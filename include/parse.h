/************************ parse.h ******************************************
Student Name:Geofferson Camp    Student Number: 0658817 
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

#ifndef _GCAMP_PARSE
#define _GCAMP_PARSE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>

/*
Open room text file and parse room details into roomm structs.
IN: Path fromm argv.
OUT: Pointer to array of rooms.
*/
room ** getRooms(char path[50]);

/*
Initiate element parsing functions.
IN: Array of room structs, hero struct.
OUT: Pointer to array of door structs.
*/
void parseToDraw(room ** roomsArray, hero * activeHero, door ** doorsArray, monster ** monstersArray);

/*
Parse elements containing a comma within their position string.
IN: Pointers to elements character, containing room struct, hero struct, and array of monster structs.
OUT: N/A
*/
void parseComElem(char * element, room * activeRoom, hero * activeHero, monster ** monstersArray, int * monsterCount);//int originY, int originX);

/*
Parse door position string.
IN: Pointer to door position string and pointer to room struct.
OUT: Pointer to door struct.
*/
door * parseDoor(char * door, room * activeRoom);

#endif
