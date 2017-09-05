//
// Created by 研究用 on 2017/08/22.
//

#ifndef FIRSTSEARCHPROGRAM_MAZE_H
#define FIRSTSEARCHPROGRAM_MAZE_H

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "XY.h"
#include "GXY.h"

using namespace std;

class Maze {
private:
    vector<vector<int> > maze,expand_table,h,value_table;
    vector<vector<char> > maze_path,policy_table;
    XY goal;
    vector<GXY> list,checked;
    int g;
    int count,count_block;

public:
    Maze();
    ///////////interface//////////
    void show_maze();
    void show_expand_table();
    void show_value_table();
    void show_policy_table();
    void show_path();
    void show_list();
    void show_checked();
    void show_result_g();

    void proceed();
    void proceed_Astar();
    void expand_next();
    void expand_next_Astar();
    void expand(int,int,int);
    bool judge();
    void find_path();
    void evaluate_value_table();
    void evaluate_value(int,int);
    void evaluate_policy_table();
    void evaluate_policy(int,int);
    bool judge_evaluate_table_complete();


};


#endif //FIRSTSEARCHPROGRAM_MAZE_H
