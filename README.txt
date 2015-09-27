*******************************************************
Geofferson Camp
Rogue
March 2015
*******************************************************


************
Compilation
************

all:
        gcc -Wall -pedantic -std=c99 src/main.c src/parse.c src/utility.c src/draw.c src/hero.c -Iinclude -o bin/runMe -lncurses -lm

**********************
Enhancements
**********************

- Connecting doors with hallways.
- Monsters move randomly throughout the level.
- Accessible inventory tracking system.

***********************
Running the program(s)
***********************

- Include path to room.txt file when running.
- User moves around with w,s,a,d keys.
- User opens and closes of inventory with i key.
- User can quit with q key.

*****************
Known Limitations
*****************

- File path can be a maximum of 50 characters.
- nCurses window is set to 100x100.
- Coodinates can be a maximum of height or width minus one as the roomm dimensions start at 1 but floor dimensions start at 0.
- Room string can be a maximum of 150 characters
- Door offsets can not be greater than the height or width plus 1 or less than the coordinates of the top left corner.
- Window must be greater than everything drawn by at least one row or column.
- Monster randomness only changes per second.
- Program will not except empty or incorrectly formated files.
- Hero can store up to 100 items in inventory.

*****************
Testing Done
*****************

- See assets/test.txt.

*****************
Sources
*****************

- nCurses functions referenced from linux.die.net/man
