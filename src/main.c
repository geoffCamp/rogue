/************************ main.c ******************************************
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

#include "main.h"
#include "utility.h"
#include "parse.h"
#include "draw.h"
#include "hero.h"

int main (int argc, char ** argv) {
   
    if (argc != 2) {
        exit(1);
    }

    room ** roomsArray;
    door ** doorsArray;
    monster ** monstersArray; 
    int gameStatus;
    hero * activeHero;
 
    activeHero = malloc(sizeof(hero));
    activeHero->invCount = 0;
    activeHero->showInv = 0;

    doorsArray = malloc(sizeof(door*)*24);
    monstersArray = malloc(sizeof(monster*)*24);

    roomsArray = getRooms(argv[1]);

    initscr();
    wresize(stdscr,100,100);
    curs_set(0);    

    parseToDraw(roomsArray,activeHero,doorsArray,monstersArray);
    move(activeHero->posY,activeHero->posX);

    gameStatus = 1;  

    while (gameStatus==1) {
        gameStatus = heroAction(activeHero,roomsArray,monstersArray);
    }
   
    erase(); 
    message(activeHero,1);
    mvprintw(2,0,"Press any key to quit.");
    getch();

    freeDoors(doorsArray,roomsArray);
    freeMonsters(monstersArray,roomsArray);
    freeRooms(roomsArray);
    freeHero(activeHero);
    endwin();
  
    return 0; 
    
}
