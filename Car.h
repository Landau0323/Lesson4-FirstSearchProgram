//
// Created by 研究用 on 2017/08/24.
//

#ifndef FIRSTSEARCHPROGRAM_CAR_H
#define FIRSTSEARCHPROGRAM_CAR_H

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "XYtheta.h"
#include "XY.h"

using namespace std;


class Car {
private:
    vector<vector<int> > road;  //situation of road
    vector<vector<vector<int> > > value_table;  //table of value function at each point
    vector<vector<vector<char> > > policy_table_3d;
    vector<vector<char> > policy_table; //table of policy ateach point
    vector<vector<string> > situation;  //table of situation at each point

    XYtheta goal,start;

public:
    Car();
    void evaluate_block(int,int);
    void evaluate_value_table();
    void evaluate_value(int,int);
    void evaluate_policy();
    XYtheta proceed(XYtheta,int);

    bool judge_evaluate_table_complete();
    bool judge_evaluate_value(int,int,int,int,int,int,int);

    void show_value_table();
    void show_policy_table();
    void show_policy_table_3d();
    void show_road();
    void show_situation();

};

#endif //FIRSTSEARCHPROGRAM_CAR_H
