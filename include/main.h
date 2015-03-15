/************************ main.h ******************************************
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

#ifndef _GCAMP_MAIN
#define _GCAMP_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>

typedef struct room { 

    int height;
    int width;
    int originX;
    int originY;
    int comElemSize;
    int noComElemSize;
    char ** noCommaElem;
    char ** commaElem;
    int monsterCount;

} room;

typedef struct monster {

    int posY;
    int posX;

} monster;

typedef struct door {

    int posY;
    int posX;
    char wall;
    int room;

} door;

typedef struct hero {
     
    int posY;
    int posX;
    char inventory[100];
    int invCount;
    int showInv;
 
} hero;

#endif
