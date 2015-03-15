/************************ draw.h ******************************************
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

#ifndef _GCAMP_DRAW
#define _GCAMP_DRAW

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ncurses.h>

/*
Get room details are call draw functions.
IN: Array of room structs
OUT: N/A
*/
void drawRooms(room ** roomsArray);

/*
Draw first cell of hallway and call vertical hallway function.
IN: Array of door pointers and array of room pointers.
OUT: N/A
*/
void drawPaths(door ** doorsArray, room ** roomsArray);

/*
Draw horizontal hallways for north and south outer walls.
IN: Wall door is in, and coordinates of door.
OUT: N/A
*/
void drawNSPath(char wall, int doorY, int doorX);

/*
Find corner of wall to determine hallway length.
IN: Door coordinates.
OUT: Length to corner fromm door.
*/
int findSideWall(int y, int x);

/*
Connect doors to central hallway.
IN: direction of hallway.
OUT: N/A
*/
void drawVerticalPath(int direction);
 
/*
Draw room walls.
IN: Room dimensions and coordinates of top left corner.
OUT: N/A
*/
void drawWalls(int width, int height, int originX, int originY);

/*
Draw room floor.
IN: Room dimensions and coordinates of top left corner.
OUT: N/A
*/
void drawFloor(int width, int height, int originX, int originY);

/*
Draw elements that include commas in their parse string.
IN: Element character, room struct, and element coordinates.
OUT: N/A
*/
void drawElem(char type, room * activeRoom, int yCoord, int xCoord);

/*
Draw door.
IN: N,E,S,W, char indicating the wall the door is in, how far from the n, or w wall and roomm struct.
OUT: pointer to door struct.
*/
door * drawDoor(char wall, int location, room * activeRoom);//int originY, int originX);

#endif
