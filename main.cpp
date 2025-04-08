#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <cmath>

constexpr int FIELD_WIDTH  = 5;
constexpr int FIELD_HEIGHT = 5;

int FIELD[FIELD_HEIGHT][FIELD_WIDTH];

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

void printField(){
    for (int x = 0; x != FIELD_WIDTH; x++){
        for (int y = 0; y != FIELD_HEIGHT; y++) {
            std::cout << FIELD[x][y];
        } 
        std::cout << "\n";
    }
}

void printField(std::vector<point> &path){
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
}

void printPath(std::vector<point> &path){
    int x = 0;
    std::cout << "[ ";
    for (auto pos:path){
        x += 1;
        std::cout << "(" << pos.x << "," << pos.y << "),";
        }
    std::cout << " ]" << std::endl;
    std::cout << x << std::endl;
}

std::vector<point> findRandomPath(point &start = START_POSITION,point &end = END_POSITION){
    std::vector<point> path;
    point position_now = start;
    int c = 0;
    while (position_now != end)
    {
        int seed = std::rand()%4;

        if (FIELD[position_now.y+1][position_now.x] != 1 && seed == 0 && !cheakPointInArr(position_now + point(0,1),path)) {
            path.push_back(position_now);
            position_now += {0,1};
        }
        else if (FIELD[position_now.y][position_now.x+1] != 1  && seed == 1 && !cheakPointInArr(position_now + point(1,0),path)) {
            path.push_back(position_now);
            position_now += {1,0};
        }
        else if (FIELD[position_now.y][position_now.x-1] != 1  && seed == 2 && !cheakPointInArr(position_now - point(1,0),path)) {
            path.push_back(position_now);
            position_now -= {1,0};
        }
        else if (FIELD[position_now.y-1][position_now.x] != 1 && seed == 3 && !cheakPointInArr(position_now - point(0,1),path)) {
            path.push_back(position_now);
            position_now -= {0,1};

        }else{
            c+=1;
        }
        if (c > FIELD_HEIGHT*FIELD_WIDTH){
            path.clear();
            break;
        }
    }
    if (path.size() > 0 )
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

std::vector<point> minRandomPath(long long niterations = FIELD_WIDTH*FIELD_HEIGHT*FIELD_WIDTH*FIELD_HEIGHT,point &start = START_POSITION,point &end = END_POSITION){
    std::vector<point> min_path = findRandomPath(start,end);
    for(int i = 0; i != niterations; i++){
        std::vector<point> random_path = findRandomPath(start,end);
        if (min_path.size() > random_path.size())
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

void AllRandomGenerationField(int difficulty = 1)
{
    std::vector<point> temp_arr = {START_POSITION};
    std::vector<point> Maze;
    for(int y = 1; y != FIELD_HEIGHT;y++){
        int n = std::rand()%difficulty + 1;
        for(int i = 0; i!= n;i++){
            int x = std::rand()%FIELD_WIDTH + 1;
            point p = {x,y};
            temp_arr.push_back(p);
        }
    }
    temp_arr.push_back(END_POSITION);
    for(int i = 0; i != temp_arr.size()-1;i++){
        std::vector<point> path = findPath(100,temp_arr[i],temp_arr[i+1]);
        for (point pos :path){
            Maze.push_back(pos);
        }
    }
    baseGenerationField(Maze);
}


int main(){
    std::srand(time(NULL));

    // AllRandomGenerationField(1);
    baseGenerationField();
    std::vector<point> path = findRandomPath();
    printField(path);
    // std::vector<point> path = findPath(100000);
    // std::cout << std::endl;
    printPath(path);
    // std::cout << path.size() << std::endl;

    return 0;
}