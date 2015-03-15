/************************ draw.c ******************************************
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
****************************************************************************/

#include "main.h"
#include "utility.h"
#include "draw.h"

/*
Get room details are call draw functions.
IN: Array of room structs
OUT: N/A
*/
void drawRooms(room ** roomsArray) {
    int roomCount;
    int i;
    int nextX;
    int nextY;
    int secRowY;
    int rmWidth;
    int rmHeight;
    int middlePathCount;   

    roomCount = 6;
        
    move(3,3);
    getyx(stdscr,nextY,nextX);
    secRowY = 3;

    for (i = 0; i<roomCount; i++) {
        rmWidth = roomsArray[i]->width;
        rmHeight =  roomsArray[i]->height;
        
        if (rmHeight > secRowY) {
            secRowY = rmHeight;
        }
        
        move(nextY,nextX);
        getyx(stdscr,roomsArray[i]->originY,roomsArray[i]->originX);
        drawWalls(rmWidth,rmHeight,roomsArray[i]->originX,roomsArray[i]->originY);
        drawFloor(rmWidth,rmHeight,roomsArray[i]->originX,roomsArray[i]->originY);               

        if (i == ((roomCount/2)-1)) {
            nextX = 3;
            nextY = secRowY+3+5;
            middlePathCount = 1;
            while (middlePathCount < 92) {
                mvaddch(nextY-2,middlePathCount,'#');
                middlePathCount++;
            }
        } else {
            nextX = nextX + rmWidth + 5;
        }

    }  

}

/*
Draw first cell of hallway and call vertical hallway function.
IN: Array of door pointers and array of room pointers.
OUT: N/A
*/
void drawPaths(door ** doorsArray,room ** roomsArray) {
    int i,k;
    int doorCount;
    int doorY;
    int doorX;
    int wall;
    int room;

    doorCount = 0;

    for (i = 0; i<6; i++) {
        doorCount = roomsArray[i]->noComElemSize+1+doorCount;
    }

    for (k = 0; k<doorCount; k++) {
        doorY = doorsArray[k]->posY;
        doorX = doorsArray[k]->posX;
        wall = doorsArray[k]->wall;
        room = doorsArray[k]->room;
        if (room == 0 || room == 1 || room == 2) {
            if (wall == 'e') {
                mvaddch(doorY,doorX+1,'#');
                move(doorY,doorX+2);
                drawVerticalPath(1);
            } else if (wall == 'w') {
                mvaddch(doorY,doorX-1,'#');
                move(doorY,doorX-2);
                drawVerticalPath(1);
            } else if (wall == 's') {
                move(doorY+1,doorX);
                drawVerticalPath(1);
            } else if (wall == 'n') {
                drawNSPath('n',doorY,doorX);                
                drawVerticalPath(1);
            }
        } else if (room == 3 || room == 4 || room == 5) {
            if (wall == 'e') {
                mvaddch(doorY,doorX+1,'#');
                move(doorY,doorX+2);
                drawVerticalPath(-1);
            } else if (wall == 'w') {
                mvaddch(doorY,doorX-1,'#');
                move(doorY,doorX-2);
                drawVerticalPath(-1);
            } else if (wall == 's') {
                drawNSPath('s',doorY,doorX);
                drawVerticalPath(-1);
            } else if (wall == 'n') {
                move(doorY-1,doorX);
                drawVerticalPath(-1);   
            }
        }
    }
    
}

/*
Draw horizontal hallways for north and south outer walls.
IN: Wall door is in, and coordinates of door.
OUT: N/A
*/
void drawNSPath(char wall, int doorY, int doorX) {
    int toCorner;
    int cornerCounter;
    int drawY;
    int nextY;

    if (wall == 's') {
        drawY = doorY+1;
        nextY = doorY;
    } else {
        drawY = doorY-1;
        nextY = doorY;
    }

    toCorner = findSideWall(doorY,doorX);
    for (cornerCounter = 0; cornerCounter<=toCorner+1; cornerCounter++) {
        mvaddch(drawY,doorX+cornerCounter,'#');
    }
    move(nextY,doorX+cornerCounter-1);
}

/*
Find corner of wall to determine hallway length.
IN: Door coordinates.
OUT: Length to corner fromm door.
*/
int findSideWall(int y, int x) {
    char checker;
    int i;
    
    i = 1;
    move(y,x+i);
    checker = inch();
    
    while (checker != '|' && checker != ' ') {
        move(y,x+i);
        i++;
        checker = inch();
    }

    return i;
}

/*
Connect doors to central hallway.
IN: direction of hallway.
OUT: N/A
*/
void drawVerticalPath (int direction) {
    char pathCheck;
    int y,x;

    pathCheck = inch();
    
    while (pathCheck != '#') {
        getyx(stdscr,y,x);
        addch('#');
        move(y+direction,x);
        pathCheck = inch();
    }
    
}

/*
Draw room walls.
IN: Room dimensions and coordinates of top left corner.
OUT: N/A
*/
void drawWalls(int width, int height, int originX, int originY) {
   int i,k;
   int addiWidth;
   int addiHeight;

   addiHeight = 1;
   addiWidth = 1;

   for (i = 0; i<=width+addiWidth; i++) {
       mvaddch(originY,originX+i,'-');
   } 
   for (k = 0; k<=height+addiHeight; k++) {
       mvaddch(originY+k,originX+width+1,'|');
   }
   for (i = 0; i<=width+addiWidth-1; i++) {
       mvaddch(originY+height+1,originX+i,'-');
   }
   for (k = 0; k<=height+addiHeight; k++) {
      mvaddch(originY+k,originX,'|');
   }

}

/*
Draw room floor.
IN: Room dimensions and coordinates of top left corner.
OUT: N/A
*/
void drawFloor(int width, int height, int originX, int originY) {
   int i,k;

   for (i = 0; i<height; i++) {
       for (k = 0; k<width; k++) {
           mvaddch(originY+i+1,originX+k+1,'.');
       }
   }
}

/*
Draw elements that include commas in their parse string.
IN: Element character, room struct, and element coordinates.
OUT: N/A
*/
void drawElem(char type, room * activeRoom,  int yCoord, int xCoord) {
    int originY;
    int originX;
    int yHolder;
    int xHolder;
    int rmHeight;
    int rmWidth;
    char toDraw;
    int isFloor;
    int moveCounter;
    originY = activeRoom->originY;
    originX = activeRoom->originX;
    rmHeight = activeRoom->height;
    rmWidth = activeRoom->width;

    moveCounter = 0;

    if (type == 'g') {
        toDraw = '*';
    } else if (type == 'p') {
        toDraw = '!';
    } else if (type == 'm') {
        toDraw = '$';
    } else if (type =='w') {
        toDraw = ')';
    } else if (type == 'h') {
        toDraw = '@';
    } else if (type == 's') {
        toDraw = '%';
    } else {
        toDraw = type;
    }

    move(originY+yCoord+1,originX+xCoord+1);
    while ((isFloor = floorStatus()) != 1) {
        getyx(stdscr,yHolder,xHolder);
        if (xHolder >= originX+rmWidth+1 && yHolder >= originY+rmHeight+1) { 
            move(originY+rmHeight,originX+rmWidth);
        } else if (xHolder <= originX) {
            move(originY+yCoord+1,originX+xCoord+1+moveCounter);
        } else if (yHolder >= originY+rmHeight+1) {
            move(originY+yCoord+1-moveCounter,originX+xCoord+1);
        } else if (xHolder >= originX+rmWidth+1) {
            move(originY+yCoord+1,originX+xCoord+1-moveCounter);
        } else if (yHolder <= originY) {
            move(originY+yCoord+1+moveCounter,originX+xCoord+1);
        } else {
            move(originY+yCoord+1+moveCounter,originX+xCoord+1+moveCounter);
        }
        moveCounter++;

    }
    
    addch(toDraw);

}

/*
Draw door.
IN: N,E,S,W, char indicating the wall the door is in, how far from the n, or w wall and roomm struct.
OUT: pointer to door struct.
*/
door * drawDoor(char wall, int location, room * activeRoom) {
    int originY;
    int originX;
    int height;
    int width;
    door * doorToRtrn;

    doorToRtrn = malloc(sizeof(door));

    originY = activeRoom->originY;
    originX = activeRoom->originX;
    height = activeRoom->height;
    width = activeRoom->width;

    location = location; //+1 assuming the doors can have a delta of 0

    if (wall == 'n') {
        move(originY,originX+location);
        if (originX+location > originX+width) {
            move(originY,originX+location-1);    
        } else if (originX+location == originX) {
            move(originY,originX+location+1);
        }
        getyx(stdscr,doorToRtrn->posY,doorToRtrn->posX);
        doorToRtrn->wall = 'n';
        printw("+");
    } else if (wall == 's') {
        move(originY+height+1,originX+location);
        if (originX+location > originX+width) {
            move(originY+height+1,originX+location-1);
        } else if (originX+location == originX) {
            move(originY+height+1,originX+location+1);
        }
        getyx(stdscr,doorToRtrn->posY,doorToRtrn->posX);
        doorToRtrn->wall = 's';
        printw("+");
    } else if (wall == 'e') {
        move(originY+location,originX+width+1);
        if (originY+location > originY+height) {
            move(originY+location-1,originX+width+1);
        } else if (originY+location == originY) {
            move(originY+location+1,originX+width+1);
        }
        getyx(stdscr,doorToRtrn->posY,doorToRtrn->posX);
        doorToRtrn->wall = 'e';
        printw("+");
    } else if (wall == 'w') {
        move(originY+location,originX);
        if (originY+location > originY+height) {
            move(originY+location-1,originX);
        } else if (originY+location == originY) {
            move(originY+location+1,originX);
        }
        getyx(stdscr,doorToRtrn->posY,doorToRtrn->posX);
        doorToRtrn->wall = 'w';
        printw("+");
    }

    return doorToRtrn;    

}
