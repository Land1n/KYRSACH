#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <thread>
#include <random> 
#include <mutex>
#include<windows.h>

constexpr int FIELD_WIDTH  = 11;
constexpr int FIELD_HEIGHT = 11;

int FIELD[FIELD_HEIGHT][FIELD_WIDTH];

std::mutex mtx;

class point
{    
public: 
    int x;
    int y;
    point(int x, int y ) :  x(x) , y(y){}

    bool operator == (const point &p) {
        if( x == p.x &&  y == p.y)
            return true;
        return false;
    }

    bool operator != (const point &p) {
        if( x != p.x || y != p.y)
            return true;
        return false;
    }
    point operator += (const point &p){
        if ((x + p.x) <= FIELD_WIDTH && (x + p.x) >= 0)
            x += p.x;

        if ((y + p.y)  <= FIELD_HEIGHT &&  (y + p.y) >= 0)
            y += p.y;
        point new_p = {x,y};
        return new_p;
    }
    point operator -= (const point &p){
        if ((x - p.x) <= FIELD_WIDTH && (x - p.x) >= 0)
            x -= p.x;

        if ((y - p.y)  <= FIELD_HEIGHT &&  (y - p.y) >= 0)
            y -= p.y;
            
        point new_p = {x,y};
        return new_p;
    }
    point operator + (const point &p){
        int x1 = x;
        int y1 = y;
        if ((x1 + p.x) <= FIELD_WIDTH && (x1 + p.x) >= 0)
            x1 += p.x;

        if ((y1 + p.y)  <= FIELD_HEIGHT &&  (y1 + p.y) >= 0)
            y1 += p.y;
        point new_p = {y1,y1};
        return new_p;
    }
    point operator - (const point &p){
        int x1 = x;
        int y1 = y;
        if ((x1 - p.x) <= FIELD_WIDTH && (x1 - p.x) >= 0)
            x1 -= p.x;

        if ((y1 - p.y)  <= FIELD_HEIGHT &&  (y1 - p.y) >= 0)
            y1 -= p.y;
            
        point new_p = {x1,y1};
        return new_p;
    }
};

point START_POSITION = {0,1};
point END_POSITION = {FIELD_WIDTH-1,FIELD_HEIGHT-2};

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
    for (int x = 0; x != FIELD_WIDTH; x++){
        for (int y = 0; y != FIELD_HEIGHT; y++) {
            std::cout << FIELD[x][y];
        } 
        std::cout << "\n";
    }
    std::cout << "\n";

}

void printField(std::vector<point> &path){
    std::cout << "\n" << "\n";
    for (int x = 0; x != FIELD_WIDTH; x++){
        for (int y = 0; y != FIELD_HEIGHT; y++) {
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

std::vector<point> findRandomPath(point &start = START_POSITION,point &end = END_POSITION){
    std::vector<point> path;
    std::vector<point> temp_path;
    point position_now = start;
    int bad_iteration = 0;
    while (position_now != end)
    {   
        std::system("cls");
        temp_path.push_back(position_now);
        std::cout << temp_path.size();
        if (count(temp_path.begin(), temp_path.end(),point(2,1))>5 || count(temp_path.begin(), temp_path.end(),point(1,1))>5){
            path.clear();
            break;
        }
            

        int start_seed = 0;
        int end_seed = 3;
        std::vector<int> bad_int;
        if (FIELD[position_now.y+1][position_now.x] == 1 || cheakPointInArr(position_now + point(0,1),path)) 
            bad_int.push_back(0);
        if (FIELD[position_now.y][position_now.x+1] == 1 || cheakPointInArr(position_now + point(1,0),path)) 
            bad_int.push_back(1);
        if (FIELD[position_now.y][position_now.x-1] == 1 || cheakPointInArr(position_now - point(1,0),path)) 
            bad_int.push_back(2);
        if (FIELD[position_now.y-1][position_now.x] == 1 || cheakPointInArr(position_now - point(0,1),path)) 
            bad_int.push_back(3);

        int seed = GetRandomInt(start_seed,end_seed,bad_int);
        if (seed == -1){
            position_now = start;
            path.clear();
            bad_int.clear();
            continue;
        }

        if (seed == 0) {
            path.push_back(position_now);
            position_now += {0,1};
            bad_iteration = 0;
        }
        else if (seed == 1) {
            path.push_back(position_now);
            position_now += {1,0};
            bad_iteration = 0;
        }
        else if (seed == 2) {
            path.push_back(position_now);
            position_now -= {1,0};
            bad_iteration = 0;
        }
        else if (seed == 3) {
            path.push_back(position_now);
            position_now -= {0,1};
            bad_iteration = 0;
        }
        else bad_iteration+=1;
        if (bad_iteration > FIELD_HEIGHT*FIELD_WIDTH){
            path.clear();
            bad_int.clear();
            position_now = start;
            
            continue;
        }
        printField(path);
    }
    if (path.size() > 0)
        path.push_back(position_now);

    return path;
}

std::vector<point> cleanPath(std::vector<point> path){
    std::vector<point> temp_path;
    std::vector<point> clean_path;
    std::vector<int> temp_position;
    for (size_t i = 0;i != path.size();i++){
        if (!count(temp_path.begin(), temp_path.end(), path[i])){
            temp_path.push_back(path[i]);
        } else {
            temp_position.push_back(i);
        }
    }
    temp_path.clear();
    std::reverse(temp_position.begin(),temp_position.end());
    for (int pos : temp_position){
        auto begin = path.cbegin();
        path.erase(begin+pos-1,begin+pos);
    }
    for (size_t i = 0;i != path.size();i++)
        if (!count(clean_path.begin(), clean_path.end(), path[i]))
            clean_path.push_back(path[i]);

    return clean_path;
}

std::vector<point> minRandomPath(int niterations = 1,point &start = START_POSITION,point &end = END_POSITION){
    std::vector<point> min_path = findRandomPath(start,end);

    // auto functionFindRandomPath = [&min_path,&start,&end](){
        while (min_path.size() == 0)
        {
            min_path = findRandomPath(start,end);
        }
    // };
    
    // std::thread ThreadFindRandomPath1(functionFindRandomPath);
    // std::thread ThreadFindRandomPath2(functionFindRandomPath);
    // std::thread ThreadFindRandomPath3(functionFindRandomPath);
    // std::thread ThreadFindRandomPath4(functionFindRandomPath);
    // std::thread ThreadFindRandomPath5(functionFindRandomPath);

    // ThreadFindRandomPath1.join();
    // ThreadFindRandomPath2.join();
    // ThreadFindRandomPath3.join();
    // ThreadFindRandomPath4.join();
    // ThreadFindRandomPath5.join();


    for(int i = 0; i != niterations; i++){
        std::vector<point> random_path = findRandomPath(start,end);
        if (min_path.size() > random_path.size() && random_path.size() != 0)
            min_path = random_path;
    }
    return min_path;
}

std::vector<point> findPath(int niterations = 10000, point &start = START_POSITION, point &end = END_POSITION){
    std::vector<point> min_path = minRandomPath(niterations,start,end);
    std::vector<point> clean_path = cleanPath(min_path);
    if (clean_path.back() != end)
        clean_path.clear();
    return clean_path;
}


void baseGenerationField(std::vector<point> Maze = {}){
    for (int x = 0; x != FIELD_WIDTH; x++) {
        for (int y = 0; y != FIELD_HEIGHT; y++){
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
            if (x == 0 || x == FIELD_WIDTH-1 || y == 0 || y == FIELD_HEIGHT-1)
                FIELD[y][x] = 1;
            if (now_position == START_POSITION || now_position == END_POSITION)
                FIELD[y][x] = 0;
        }
    }
}


void RandomGenerationField(){
    std::vector<point> Maze;
    for( int y = 0; y < FIELD_HEIGHT;y+=2){
        for( int x = 0; x != FIELD_WIDTH;x++){
            FIELD[y][x] = 1;
        }
        int nrandom = GetRandomInt(1,round(FIELD_WIDTH/2));
        for( int n = 0; n != nrandom;n++){
            int xrandom = GetRandomInt(1,FIELD_WIDTH-1);
            FIELD[y][xrandom] = 0;
        }
    }

    for( int x = 0; x != FIELD_WIDTH;x++){
        FIELD[START_POSITION.y][x] = 0;
        FIELD[END_POSITION.y][x] = 0;

    }   
    baseGenerationField(Maze);
}

int main(){
    RandomGenerationField();
    // for(int i =0; i!=FIELD_WIDTH;i++)
    //     FIELD[2][i] = 1;
    printField();
    int start = GetTickCount();
    std::vector<point> path = minRandomPath(100);
    int end=GetTickCount();
    std::cout<<(end-start)/1000.0<<std::endl;
    printField(path);
    
    // AllRandomGenerationField(3);
    // baseGenerationField();
    // std::vector<point> path = minRandomPath(1000);
    // std::vector<point> path = findPath(100000);
    // std::cout << std::endl;

    // std::cout << path.size() << std::endl;
    // std::cout << std::thread::hardware_concurrency();
    return 0;
}