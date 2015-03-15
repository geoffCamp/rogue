/************************ hero.c ******************************************
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

#include "main.h"
#include "utility.h"
#include "hero.h"

/*
Communication between the Hero action and the status of the game.
IN: Hero struct, array of monster structs, array of room structs.
OUT: Game status.
*/
int heroAction(hero * activeHero, room ** roomsArray, monster ** monstersArray) {
    int gameStatus;
    char action;
    char prevItem;

    noecho();
    prevItem = '.';

    while ((action = getch()) != 'q') {
        prevItem = moveHero(action,activeHero,prevItem,roomsArray,monstersArray);
    }
    
    gameStatus = 2;
    return gameStatus;
}

/*
Handles hero movement and other game interaction.
IN: User input, hero struct, contents of cell before hero overwrote it, array of monster structs, array of room structs.
OUT: Contents of cell.
*/
char moveHero(char action, hero * activeHero, char prevItem, room ** roomsArray, monster ** monstersArray) {
    int currentY;
    int currentX;
    char  itemHolder;

    currentY = activeHero->posY;
    currentX = activeHero->posX;    

    if (action == 'w') {
        if (checkWall(currentY-1,currentX)==2) {
            itemHolder = item(activeHero);
            move(currentY,currentX);
            printHero(currentY-1,currentX,currentY,currentX,prevItem);
            getyx(stdscr,activeHero->posY,activeHero->posX);
            moveMonster(monstersArray,roomsArray,activeHero);
        } else {
            itemHolder = prevItem;
        }
    } else if (action == 's') {
        if (checkWall(currentY+1,currentX)==2) {
            itemHolder = item(activeHero);
            move(currentY,currentX);
            printHero(currentY+1,currentX,currentY,currentX,prevItem);
            getyx(stdscr,activeHero->posY,activeHero->posX);
            moveMonster(monstersArray,roomsArray,activeHero);
        } else {
            itemHolder = prevItem;
        }
    } else if (action == 'a') {
        if (checkWall(currentY,currentX-1)==2) {
            itemHolder = item(activeHero);
            move(currentY,currentX);
            printHero(currentY,currentX-1,currentY,currentX,prevItem);
            getyx(stdscr,activeHero->posY,activeHero->posX);
            moveMonster(monstersArray,roomsArray,activeHero);
        } else {
            itemHolder = prevItem;
        }
    } else if (action == 'd') {
        if (checkWall(currentY,currentX+1)==2) {
            itemHolder = item(activeHero);
            move(currentY,currentX);
            printHero(currentY,currentX+1,currentY,currentX,prevItem);
            getyx(stdscr,activeHero->posY,activeHero->posX);
            moveMonster(monstersArray,roomsArray,activeHero);
        } else {
            itemHolder = prevItem;
        }
    } else if (action == 'i') {
        if (activeHero->showInv == 0) {
            message(activeHero,1);
            activeHero->showInv = 1;
        } else {
            message(activeHero,0);
            activeHero->showInv = 0;
        }
        itemHolder = prevItem;
    } else {
        itemHolder = prevItem;
    }

    return itemHolder;

}

/*
Retrieves contents of cell before hero symbol overwrites it.
IN: hero struct.
OUT: character previously in cell.
*/
char item(hero * activeHero) {
    char onGround;
    
    onGround = inch();
    if (onGround != '.' && onGround != '%' && onGround != 'M' && onGround != ' ' && onGround != '+' && onGround != '#') {  
    
        activeHero->inventory[activeHero->invCount] = onGround;
        activeHero->invCount = activeHero->invCount + 1;
        if (activeHero->showInv == 1) {
            message(activeHero,1);
        }
    }

    return onGround;

}

/*
Moves and prints hero location.
IN: Current, and future hero coordinates and future location cell contents.
OUT: N/A
*/
void printHero(int y, int x, int oldY, int oldX, char itemHolder) {
    char toPrint;    

    mvaddch(y,x,'@');
    if (itemHolder == '%') {
        toPrint = '%';
    } else if (itemHolder == '+' || itemHolder == '-' || itemHolder == '|') {
        toPrint = '+';
    } else if (itemHolder == '#' || itemHolder == '^') {
        toPrint = '#';
    } else {
        toPrint = '.';
    }
    mvaddch(oldY,oldX,toPrint);
    move(y,x);

}

/*
Move all monsters 1 unit when the hero moves.
IN: List of monster structs, room structs, and the hero struct.
OUT: N/A
*/
void moveMonster(monster ** monstersArray, room ** roomsArray, hero * activeHero) {
    int i;
    int totalMonsters;
    int random;
    int monsterX;
    int monsterY;
    int floorCheck;

    srand(time(NULL));
        
    totalMonsters = roomsArray[5]->monsterCount;  

    for (i = 0; i<totalMonsters; i++) {

        monsterY = monstersArray[i]->posY;
        monsterX = monstersArray[i]->posX;
        
        random = (rand()%(5-1))+1;
        if (random == 1) {
            move(monsterY,monsterX+1);
            floorCheck = floorStatus();
            if (floorCheck == 1) { 
                addch('M');
                mvaddch(monsterY,monsterX,'.');
                monstersArray[i]->posY = monsterY;
                monstersArray[i]->posX = monsterX+1;
            }
            
        } else if (random == 2) {
            move(monsterY,monsterX-1);
            floorCheck = floorStatus();
            if (floorCheck == 1) { 
                addch('M');
                mvaddch(monsterY,monsterX,'.');
                monstersArray[i]->posY = monsterY;
                monstersArray[i]->posX = monsterX-1;
            }
        } else if (random == 3) {
            move(monsterY+1,monsterX);
            floorCheck = floorStatus();
            if (floorCheck == 1) { 
                addch('M');
                mvaddch(monsterY,monsterX,'.');
                monstersArray[i]->posY = monsterY+1;
                monstersArray[i]->posX = monsterX;
            }
        } else if (random == 4) {
            move(monsterY-1,monsterX);
            floorCheck = floorStatus();
            if (floorCheck == 1) { 
                addch('M');
                mvaddch(monsterY,monsterX,'.');
                monstersArray[i]->posY = monsterY-1;
                monstersArray[i]->posX = monsterX;
            }
        }
        
    }
    move(activeHero->posY,activeHero->posX);   

}
