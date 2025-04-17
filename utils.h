#pragma once

#include <random> 
#include <algorithm>
#include <vector>

#include "constant.h"


bool cheakPointInArr(point p,std::vector<point> &arr_p){
    return count(arr_p.begin(), arr_p.end(), p)>0;
}

int GetRandomInt(int start,int end,std::vector<int> bad_int = {}){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(start, end);
    int random_int = dis(gen);
    int c = 0;
    while (count(bad_int.begin(), bad_int.end(), random_int) > 0)
    {
        random_int = dis(gen);
        c+=1;
        if(c == 10) return -1;
    }
    return random_int;
}

void printField(){
    std::cout << "\n";
    for (int x = 0; x != FIELD_SIZE; x++){
        for (int y = 0; y != FIELD_SIZE; y++) {
            std::cout << FIELD[x][y];
        } 
        std::cout << "\n";
    }
    std::cout << "\n";

}

void printField(std::vector<point> &path){
    std::cout << "\n" << "\n";
    for (int x = 0; x != FIELD_SIZE; x++){
        for (int y = 0; y != FIELD_SIZE; y++) {
            int str = FIELD[x][y];
            for(point pos: path){
                if (pos.x == y && pos.y == x)
                str = 7;
            }
            std::cout << str;
        } 
        std::cout << "\n";
    }
    std::cout << "\n" << "\n";

}

void printPath(std::vector<point> &path){
    std::cout << "[ ";
    for (auto pos:path){
        std::cout << "(" << pos.x << "," << pos.y << "),";
        }
    std::cout << " ]" << std::endl;
    std::cout << "path size: "<< path.size() << std::endl;
}
