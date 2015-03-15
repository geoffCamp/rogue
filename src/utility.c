/************************ utility.c ******************************************
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

/*
Determine number of elements in room.
IN: String of element positions.
OUT: Number of elements.
*/
int elemSize(char * elemString) {
    int size;
    char * token;
  
    size = 0;
  
    token = strtok(elemString," ");
    while (token != NULL) {
        size++;
        token = strtok(NULL," ");
    }
  
    return size;
  
}

/*
Free room memory.
IN: Array of room structs.
OUT: N/A
*/
void freeRooms(room ** roomsArray) {
    int i,k,j;    
    int comSizeHolder;
    int noComSizeHolder;

    for (i = 0; i<6; i++) {
        comSizeHolder = roomsArray[i]->comElemSize;
        noComSizeHolder = roomsArray[i]->noComElemSize;
        for (k = 0; k<=comSizeHolder; k++) {
            free(roomsArray[i]->commaElem[k]);
        }
        free(roomsArray[i]->commaElem);
        for (j = 0; j<=noComSizeHolder; j++) {
            free(roomsArray[i]->noCommaElem[j]);
        }
        free(roomsArray[i]->noCommaElem);
        free(roomsArray[i]);
    }
    free(roomsArray);
}

/*
Free hero struct.
IN: Hero struct pointer.
OUT: N/A
*/
void freeHero(hero * activeHero) {
    free(activeHero);
 }

/*
Free array of Doors
IN: Array of door and room pointer;
OUT: N/A
*/
void freeDoors(door ** doorsArray, room ** roomsArray) {
    int i;
    int totalDoors;

    totalDoors = 0;

    for (i = 0; i<6; i++) {
        totalDoors = totalDoors + roomsArray[i]->noComElemSize;
    }

   for (i = 0; i<totalDoors; i++) {
       free(doorsArray[i]);
   }
   free(doorsArray);
}

/*
Free array of monsters
IN: Array of doors and room pointers
OUT: N/A
*/
void freeMonsters(monster ** monstersArray, room ** roomsArray) {
    int i;
    int totalMonsters;
    
    totalMonsters = 0;
    
    for (i = 0; i<6; i++) {
        totalMonsters = totalMonsters + roomsArray[i]->noComElemSize;
    }

   for (i = 0; i<totalMonsters; i++) {
       free(monstersArray[i]);
   }
   free(monstersArray);
}

/*
Print parsed room information for testing purposes.
IN: Pointer to array of room structs.
OUT: N/A
*/
void testPrint(room ** roomsArray) {
    for (int i=0; i<6; i++) {
        printw("%d-%d-%d-%d\n", roomsArray[i]->height,roomsArray[i]->width,roomsArray[i]->comElemSize, roomsArray[i]->noComElemSize);
                 
        for (int k = 0; k<=roomsArray[i]->comElemSize; k++) {
            printw("%s",roomsArray[i]->commaElem[k]);
        }
        printw("");
        for (int j = 0; j<=roomsArray[i]->noComElemSize; j++) {
            printw("%s",roomsArray[i]->noCommaElem[j]);
        }
        printw("\n");
    }  
}

/*
Remove first letter fromm element position strings.
IN: Elements position string and size of new string.
OUT: Pointer to new position string.
*/
char * removeLetter(char * element, int quant) {
    int origLen;
    int i;
    char * newStr;

    newStr = malloc(sizeof(char)*7);//freed in function returned to (parseComELem)
    origLen = strlen(element);

    for (i = quant; i<=origLen; i++) {
        newStr[i-quant] = element[i];
    }
    return newStr;
}

/*
Check if current cursor location if a wall or a monsterto prevent walking over them.
IN: Hero coodinates.
OUT: In wall status.
*/
int checkWall(int y, int x) {
    char charHolder;
    move(y,x);
  
    charHolder = inch();
    if (charHolder == '|' || charHolder == '-' || charHolder == 'M' || charHolder == ' ') {
        return 1;
    } else {
        return 2;
    }
}

/*
Check if the cursor is over a floor filled cell.
IN: N/A
OUT: N/A
*/
int floorStatus() {
    char charHolder = inch();
    if (charHolder == '.') {
        return 1;
    } else {
        return 0;
    }
}

/*
Print system messages.
IN: Message code and hero struct.
OUT: N/A
*/
void message(hero * activeHero, int msgCode) {
    int i;
    char itemHolder;
    int goldCount = 0;
    int weaponCount = 0;
    int magicCount = 0;
    int potionCount = 0;
     
    goldCount = 0;
    weaponCount = 0;
    magicCount = 0;
    potionCount = 0;
 
    move(0,0);
    clrtoeol();
    
    if (msgCode == 1) {
        if (activeHero->invCount == 0) {
            printw("Inventory empty");
        } else {
            
            for (i = 0; i<activeHero->invCount; i++) {
                itemHolder = activeHero->inventory[i];
                if (itemHolder == '*') {
                    goldCount++;
                } else if (itemHolder == '!') {
                    potionCount++;
                } else if (itemHolder == '$') {
                    magicCount++;
                } else if (itemHolder == ')') {
                    weaponCount++;
                }
            }
            printw("Inventory: ");
            printw("%dxPotion ",potionCount);
            printw("%dxGold ",goldCount);
            printw("%dxMagic ",magicCount);
            printw("%dxWeapon ",weaponCount);    
            
        }
    }

    move(activeHero->posY,activeHero->posX);
}

