#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>

constexpr int FIELD_WIDTH  = 10;
constexpr int FIELD_HEIGHT = 10;

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
};

point START_POSITION = {0,1};
point END_POSITION = {9,8};


void generationField(int field[FIELD_HEIGHT][FIELD_WIDTH])
{

    for (int x = 0; x != FIELD_WIDTH; x++) {
        for (int y = 0; y != FIELD_HEIGHT; y++){
            if (x == 0 || x == FIELD_WIDTH-1 || y == 0 || y == FIELD_HEIGHT-1)
                field[y][x] = 1;
            if (START_POSITION.x == x && START_POSITION.y == y)
                field[y][x] = 0;

            if (END_POSITION.x == x && END_POSITION.y == y)
                field[y][x] = 0;
        }
    }

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

std::vector<point> findRandomPath(){
    std::vector<point> path;
    point position_now = START_POSITION;
    point last_position = {0,0};
    while (position_now != END_POSITION)
    {
        int seed = std::rand()%4;
        if (FIELD[position_now.y+1][position_now.x] != 1 && position_now != last_position && seed == 0) {
            last_position = position_now;
            path.push_back(position_now);
            position_now += {0,1};
        }
        else if (FIELD[position_now.y][position_now.x+1] != 1 && position_now != last_position && seed == 1) {
            last_position = position_now;
            path.push_back(position_now);
            position_now += {1,0};
        }
        else if (FIELD[position_now.y][position_now.x-1] != 1 && position_now != last_position && seed == 2) {
            last_position = position_now;
            path.push_back(position_now);
            position_now -= {1,0};
        }
        else if (FIELD[position_now.y-1][position_now.x] != 1 && position_now != last_position&& seed == 3) {
            last_position = position_now;
            path.push_back(position_now);
            position_now -= {0,1};
        }
    }
    path.push_back(position_now);
    return path;
}

std::vector<point> cleanPath(std::vector<point> &path){
    std::vector<point> clean_path;
    auto begin = clean_path.cbegin();

    for(point pos: path)
        if (!count(clean_path.begin(), clean_path.end(), pos))
            clean_path.push_back(pos);


    return clean_path;
}

std::vector<point> minRandomPath(std::vector<point> &path,int niterations = 10000){
    std::vector<point> min_path = path;
    for(int i = 0; i != niterations; i++){
        std::vector<point> random_path = findRandomPath();
        if (min_path.size() > random_path.size())
            min_path = random_path;
    }
    return min_path;
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

int main(){
    generationField(FIELD);
    // FIELD[2][2] = 1;
    // FIELD[3][2] = 1;
    printField();

    std::srand(time(NULL));

    std::vector<point> path = findRandomPath();
    printPath(path);
    std::vector<point> minpath = minRandomPath(path);
    printPath(minpath);
    std::vector<point> cleanpath = cleanPath(minpath);
    printPath(cleanpath);
    printField(cleanpath);
    // int c = findPathLength({0,1},{0,0},counter);
    return 0;
}