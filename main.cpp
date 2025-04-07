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
    while (position_now != end)
    {
        int seed = std::rand()%4;
        if (FIELD[position_now.y+1][position_now.x] != 1 && seed == 0) {
            path.push_back(position_now);
            position_now += {0,1};
        }
        else if (FIELD[position_now.y][position_now.x+1] != 1  && seed == 1) {
            path.push_back(position_now);
            position_now += {1,0};
        }
        else if (FIELD[position_now.y][position_now.x-1] != 1  && seed == 2) {
            path.push_back(position_now);
            position_now -= {1,0};
        }
        else if (FIELD[position_now.y-1][position_now.x] != 1 && seed == 3) {
            path.push_back(position_now);
            position_now -= {0,1};
        }
    }
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

std::vector<point> minRandomPath(int niterations = 10000,point &start = START_POSITION,point &end = END_POSITION){
    std::vector<point> min_path = findRandomPath(start,end);
    for(int i = 0; i != niterations; i++){
        std::vector<point> random_path = findRandomPath(start,end);
        if (min_path.size() > random_path.size())
            min_path = random_path;
    }
    return min_path;
}

std::vector<point> findPath(){
    std::vector<point> min_path = minRandomPath();
    std::vector<point> clean_path = cleanPath(min_path);
    return clean_path;
}

int main(){
    generationField(FIELD);

    printField();

    std::srand(time(NULL));


    return 0;
}