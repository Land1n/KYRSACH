#pragma once

#include "utils.h"

std::vector<point> findRandomPath(point &start = START_POSITION,point &end = END_POSITION){
    std::vector<point> path;
    std::vector<point> temp_path;
    point position_now = start;
    int bad_iteration = 0;
    while (position_now != end)
    {   
        temp_path.push_back(position_now);
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
        if (bad_iteration > FIELD_SIZE*FIELD_SIZE){
            path.clear();
            bad_int.clear();
            position_now = start;
            
            continue;
        }




        if (DEBUG){
            std::system("cls");
            printField(path);
        }
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
    point new_start;
    point new_end;
    std::vector<point> path_before_new_start;
    std::vector<point> path_before_new_end;
    for (int x = start.x; x != FIELD_SIZE-1; x++)
    {
        point position_now = {x,start.y};
        if (FIELD[start.y-1][x] == 1 && FIELD[start.y+1][x] == 1)
            path_before_new_start.push_back(position_now);
        else{
            new_start = position_now;
            break;
        }
    }
    for (int x = end.x; x != 1; x--)
    {
        point position_now = {x,end.y};
        if (FIELD[end.y-1][x] == 1 && FIELD[end.y+1][x] == 1)
            path_before_new_end.push_back(position_now);
        else{
            new_end = position_now;
            break;
        }
    }
    for (int i = 0; i!=3;i++){
        path_before_new_start.push_back(point(0,i) + new_start);
        path_before_new_end.push_back(new_end - point(0,i));
    }
    new_start += {0,2};
    new_end -= {0,2};
    std::vector<point> min_path = minRandomPath(niterations,new_start,new_end);
    std::vector<point> clean_path = cleanPath(min_path);
    path_before_new_start.insert(path_before_new_start.end(),clean_path.begin(),clean_path.end());
    path_before_new_start.insert(path_before_new_start.end(),path_before_new_end.begin(),path_before_new_end.end());
    return path_before_new_start;
}