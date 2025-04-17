#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <windows.h>
#include "generationField.h"
#include "findPath.h"

int main(){
    RandomGenerationField();
    printField();
    int start = GetTickCount();
    std::vector<point> path = findPath(100);
    int end=GetTickCount();
    std::cout<<(end-start)/1000.0<<std::endl;
    printField(path);
    return 0;
}