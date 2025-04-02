#include <iostream>

constexpr int FIELD_WIDTH  = 5;
constexpr int FIELD_HEIGHT = 5;
constexpr int START_POSITION[] = {0,1};
constexpr int END_POSITION[] = {3,4};

int FIELD[FIELD_WIDTH][FIELD_HEIGHT];

void generationField(int field[FIELD_WIDTH][FIELD_HEIGHT])
{
    for (int x = 0; x != FIELD_WIDTH; x++){
        for (int y = 0; y != FIELD_HEIGHT; y++) {
            if (x == 0 || x == FIELD_WIDTH-1 || y == 0 || y == FIELD_HEIGHT-1)
                field[x][y] = 1;
        } 
        for (int y = 0; y != FIELD_HEIGHT; y++) {
            if (START_POSITION[0] == x && START_POSITION[1] == y)
                field[x][y] = 0;
            if (END_POSITION[0] == x && END_POSITION[1] == y)
                field[x][y] = 0;
        } 
    }

// просто идеи
    field[2][1] = 1;
    field[2][2] = 1;
}

void printField(int field[FIELD_WIDTH][FIELD_HEIGHT]){
    for (int x = 0; x != FIELD_WIDTH; x++){
        for (int y = 0; y != FIELD_HEIGHT; y++) {
            std::cout << field[x][y];
        } 
        std::cout << "\n";
    }
}

int searchhWay(int field[FIELD_WIDTH][FIELD_HEIGHT],int position[2], int last_position[2],int counter){

}

int main(){
    generationField(FIELD);
    printField(FIELD);
    return 0;
}