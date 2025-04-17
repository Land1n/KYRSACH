#pragma once

#include "utils.h"

void baseGenerationField(std::vector<point> Maze = {}){
    for (int x = 0; x != FIELD_SIZE; x++) {
        for (int y = 0; y != FIELD_SIZE; y++){
            point now_position = {x,y};
            if (Maze.size()){
                bool flag = false;
                for (point pos :Maze){
                    if (now_position == pos)
                        flag = true;
                }
                if (flag)
                    FIELD[y][x] = 0;
                else{
                    FIELD[y][x] = 1;
                }
            }
            if (x == 0 || x == FIELD_SIZE-1 || y == 0 || y == FIELD_SIZE-1)
                FIELD[y][x] = 1;
            if (now_position == START_POSITION || now_position == END_POSITION)
                FIELD[y][x] = 0;
        }
    }
}


void RandomGenerationField(){
    std::vector<point> Maze;
    for( int y = 0; y < FIELD_SIZE;y+=2){
        for( int x = 0; x != FIELD_SIZE;x++){
            FIELD[y][x] = 1;
        }
        int nrandom = GetRandomInt(1,round(FIELD_SIZE/2));
        for( int n = 0; n != nrandom;n++){
            int xrandom = GetRandomInt(1,FIELD_SIZE-1);
            FIELD[y][xrandom] = 0;
        }
    }

    for( int x = 0; x != FIELD_SIZE;x++){
        FIELD[START_POSITION.y][x] = 0;
        FIELD[END_POSITION.y][x] = 0;

    }   
    baseGenerationField(Maze);
}