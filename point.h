#pragma once

class point
{    
public: 
    int x;
    int y;
    point(int x, int y ) :  x(x) , y(y){}

    bool operator == (const point &p) {
        return ( x == p.x &&  y == p.y) == true;
    }

    bool operator != (const point &p) {
        return ( x != p.x || y != p.y) == true;
    }
    point operator += (const point &p){
        x += p.x;
        y += p.y;
        point new_p = {x,y};
        return new_p;
    }
    point operator -= (const point &p){
        x -= p.x;
        y -= p.y;
        point new_p = {x,y};
        return new_p;
    }
    point operator + (const point &p){
        int x1 = x;
        int y1 = y;
        x1 += p.x;
        y1 += p.y;
        point new_p = {y1,y1};
        return new_p;
    }
    point operator - (const point &p){
        int x1 = x;
        int y1 = y;
        x1 -= p.x;
        y1 -= p.y;
        point new_p = {x1,y1};
        return new_p;
    }
};