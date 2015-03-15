/************************ parse.c ******************************************
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
#include "draw.h"
#include "parse.h"

/*
Open room text file and parse room details into roomm structs.
IN: Path fromm argv.
OUT: Pointer to array of rooms.
*/
room ** getRooms(char path[50]) {
    FILE * fileStr;
    char roomStr[150];
    char roomStrHolder[150];
    char * token;
    char elemType;
    room ** allRooms;
    int size;
    int roomCount; 
    int commaCount;
    int noCommaCount;

    fileStr = fopen(path,"r");
    if (fileStr == NULL) {
        exit(1);
    }    

    allRooms = malloc(sizeof(room *)*6);

    roomCount = 0;
    
    while (fgets(roomStr,150,fileStr) != NULL) {
 
        strcpy(roomStrHolder,roomStr);
        commaCount = 0;
        noCommaCount = 0;   
  
        size = elemSize(roomStr);
 
        allRooms[roomCount] = malloc(sizeof(room));
        allRooms[roomCount]->commaElem = malloc(sizeof(char *)*size);
        allRooms[roomCount]->noCommaElem = malloc(sizeof(char *)*size);

        token = strtok(roomStrHolder,"X");
        allRooms[roomCount]->height = atoi(token);
        
        token = strtok(NULL," ");
        allRooms[roomCount]->width = atoi(token);

        token = strtok(NULL," ");
        while (token != NULL) {
            elemType = token[0];
            if (elemType == 'p' || elemType == 'h' || elemType == 'm' || elemType == 'M' || elemType == 'w' || elemType == 'g' || elemType == 's') {
                allRooms[roomCount]->commaElem[commaCount] = malloc(sizeof(char)*(strlen(token)+1));
                strcpy(allRooms[roomCount]->commaElem[commaCount], token);
                commaCount++;
            } else if (elemType == 'd' && noCommaCount < 100) {
                allRooms[roomCount]->noCommaElem[noCommaCount] = malloc(sizeof(char)*(strlen(token)+1));
                strcpy(allRooms[roomCount]->noCommaElem[noCommaCount], token);
                noCommaCount++;
            } 
            token = strtok(NULL," ");
        }
        allRooms[roomCount]->comElemSize = commaCount-1;
        allRooms[roomCount]->noComElemSize = noCommaCount-1;     
        roomCount++;
    }    
    
    fclose(fileStr);
    return allRooms;

}

/*
Initiate element parsing functions.
IN: Array of room structs, hero struct.
OUT: Pointer to array of door structs.
*/ 
void parseToDraw(room ** roomsArray, hero * activeHero, door ** doorsArray, monster ** monstersArray) {
    int roomCount;
    int doorCount;
    int * monsterCount;
    int i,k,j;
    int comElemSize; 
    int noComElemSize;

    drawRooms(roomsArray);
    
    roomCount = 6;
    doorCount = 0;
   
    monsterCount = malloc(sizeof(int));
    *monsterCount = 0;
 
    for (i = 0; i<roomCount; i++) {
        comElemSize = roomsArray[i]->comElemSize;
        noComElemSize = roomsArray[i]->noComElemSize;
                
        for (k = 0; k<=comElemSize; k++) {
           parseComElem(roomsArray[i]->commaElem[k],roomsArray[i],activeHero,monstersArray,monsterCount);
        }

        for (j = 0; j<=noComElemSize; j++) {
            doorsArray[doorCount] = parseDoor(roomsArray[i]->noCommaElem[j],roomsArray[i]);
            doorsArray[doorCount]->room = i; 
            doorCount++;
        }    
        roomsArray[i]->monsterCount = *monsterCount;
        
    }
    free(monsterCount);
    drawPaths(doorsArray,roomsArray);

}

/*
Parse elements containing a comma within their position string.
IN: Pointers to elements character, containing room struct, hero struct, and array of monster structs.
OUT: N/A
*/
void parseComElem (char * element, room * activeRoom, hero * activeHero, monster ** monstersArray, int * monsterCount) {//int originY, int originX) {
    char type;
    int xCoord;
    int yCoord;
    char * token;
    char * coordsStr;
    monster * activeMonster;

    type = element[0];
    coordsStr = removeLetter(element,1);
    token = strtok(coordsStr,",");
    if (token != NULL) {
        yCoord = atoi(token);
    }
    token = strtok(NULL,",");
    xCoord = atoi(token);
    free(coordsStr);    
   
    drawElem(type,activeRoom,yCoord,xCoord);
    if (type == 'h') {
        activeHero->posY = activeRoom->originY+yCoord+1;
        activeHero->posX = activeRoom->originX+xCoord+1;
    }
    if (type == 'M') {
        activeMonster = malloc(sizeof(monster)); 
        activeMonster->posY = yCoord+activeRoom->originY+1;
        activeMonster->posX = xCoord+activeRoom->originX+1;
        monstersArray[*monsterCount] = activeMonster;
        *monsterCount = *monsterCount + 1; 
    }
}

/*
Parse door position string.
IN: Pointer to door position string and pointer to room struct.
OUT: Pointer to door struct.
*/
door * parseDoor(char * doorStr, room * activeRoom) { //int originY, int originX) {
    char wall;
    int location;
    char * locHolder;
    door * doorToRtrn;

    wall = doorStr[1];

    locHolder = removeLetter(doorStr,2);
    location = atoi(locHolder);
    free(locHolder);
    doorToRtrn = drawDoor(wall,location,activeRoom);

    return doorToRtrn;
}

