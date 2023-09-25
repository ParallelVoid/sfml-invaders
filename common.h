#ifndef COMMON_H
#define COMMON_H

const int CELL = 64;

const int RIGHT = 0;
const int LEFT = 1;
const int UP = 1;
const int DOWN = -1;
const int NONE = -1;

const int TOP = 0;
const int BOTTOM = 1;
const int SIDE1 = 2; //LEFT
const int SIDE2 = 3; //RIGHT

const int XCELLS = 13; 
const int YCELLS = 9;

const int WINDOW_HEIGHT = (YCELLS * CELL) + CELL/2;
#endif
