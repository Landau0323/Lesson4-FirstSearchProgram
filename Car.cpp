//
// Created by 研究用 on 2017/08/24.
//

#include "Car.h"
#include "parameter.h"

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

Car::Car() {
    cout<<"Car!"<<endl;
    //install road
    int tate=5;
    int yoko=6;
    road.resize(tate);
    for(int i=0;i<tate;i++) road[i].resize(yoko);
    road[0][0]=1; road[0][1]=1; road[0][2]=1; road[0][3]=0; road[0][4]=0; road[0][5]=0;
    road[1][0]=1; road[1][1]=1; road[1][2]=1; road[1][3]=0; road[1][4]=1; road[1][5]=0;
    road[2][0]=0; road[2][1]=0; road[2][2]=0; road[2][3]=0; road[2][4]=0; road[2][5]=0;
    road[3][0]=1; road[3][1]=1; road[3][2]=1; road[3][3]=0; road[3][4]=1; road[3][5]=1;
    road[4][0]=1; road[4][1]=1; road[4][2]=1; road[4][3]=0; road[4][4]=1; road[4][5]=1;

    //goal and start position
    goal.setIJ(2,0);    //goal position
    goal.setTheta(1);
    start.setIJ(4,3);   //start position
    start.setTheta(0);

    //initialize situation table
    situation.resize(tate);
    for(int i=0;i<tate;i++) situation[i].resize(yoko);

    //initialize value table
    value_table.resize(tate);
    for(int i=0;i<tate;i++){
        value_table[i].resize(yoko);
        for(int j=0;j<yoko;j++) value_table[i][j].resize(4);
    }
    for(int i=0;i<tate;i++){
        for(int j=0;j<yoko;j++){
            for(int k=0;k<4;k++)    value_table[i][j][k]=INT_MAX;   //initial value is INT_MAX
            evaluate_block(i,j);  //set 999 to blocked tiles
        }
    }
    //direction is, 0:up, 1:left, 2:down, 3:right
    value_table[goal.getI()][goal.getJ()][1]=0; //value at goal is 0
    value_table[goal.getI()][goal.getJ()][0]=999;  //value at goal in other direction is 999
    value_table[goal.getI()][goal.getJ()][2]=999;
    value_table[goal.getI()][goal.getJ()][3]=999;
    value_table[start.getI()][start.getJ()][1]=999; //values at start in wrong directions are 999
    value_table[start.getI()][start.getJ()][2]=999;
    value_table[start.getI()][start.getJ()][3]=999;

    //initialize policy table in 3D
    policy_table_3d.resize(tate);
    for(int i=0;i<tate;i++) {
        policy_table_3d[i].resize(yoko);
        for(int j=0;j<yoko;j++){
            policy_table_3d[i][j].resize(4);
            for(int k=0;k<4;k++){
                if(i==goal.getI() && j==goal.getJ()) policy_table_3d[i][j][k]='*';
                else if(i==start.getI() && j==start.getJ()) policy_table_3d[i][j][k]='S';
                else policy_table_3d[i][j][k]=' ';
            }
        }
    }

    //initialize policy table
    policy_table.resize(tate);
    for(int i=0;i<tate;i++){
        policy_table[i].resize(yoko);
        for(int j=0;j<yoko;j++){
            if(i==goal.getI() && j==goal.getJ()) policy_table[i][j]='*';
            else if(i==start.getI() && j==start.getJ()) policy_table[i][j]='S';
            else policy_table[i][j]=' ';
        }
    }
}

//label the situation of each tile (straight road, corner, cross), and put 999 for impossible directions
void Car::evaluate_block(int i_input, int j_input) {
//cout<<"label the situation of the tiles"<<endl;
    //value at blocked tile is 999 for all directions
    if (road[i_input][j_input] == 1) {
        situation[i_input][j_input]="B";
        for (int k = 0; k < 4; k++) value_table[i_input][j_input][k] = 999;
        return;
    }

    //the corrdinates for the next tile
    int i_up=i_input-1;
    int i_down=i_input+1;
    int i_right,i_left;
    i_right=i_left=i_input;
    int j_left=j_input-1;
    int j_right=j_input+1;
    int j_up,j_down;
    j_up=j_down=j_input;

    //when the tile is not at the edge, judge whether the tile is corner or straight road
    if(0<i_input && i_input<road.size()-1 && 0<j_input && j_input<road[0].size()-1) {
        //case 1:straight
        //when tile is straight road in west-east direction
        if (road[i_up][j_up] == 1 && road[i_down][j_down] == 1
            && road[i_left][j_left] == 0 && road[i_right][j_right] == 0){
            value_table[i_input][j_input][0] =value_table[i_input][j_input][2] = 999;
            situation[i_input][j_input]="-";
        }
        //when tile is straight road in north-south direction
        else if(road[i_up][j_up] == 0 && road[i_down][j_down] == 0
                && road[i_left][j_left] == 1 && road[i_right][j_right] == 1){
            value_table[i_input][j_input][1] =value_table[i_input][j_input][3] = 999;
            situation[i_input][j_input]="|";
        }
        //case 2:corner
        //when tile is L-shape corner (forbid right and up directions)
        else if(road[i_up][j_up] == 0 && road[i_down][j_down] == 1
                && road[i_left][j_left] == 1 && road[i_right][j_right] == 0){
            value_table[i_input][j_input][0] =value_table[i_input][j_input][3] = 999;
            situation[i_input][j_input]="L";
        }
        //when tile is 「-shape corner (forbid right and down directions)
        else if(road[i_up][j_up] == 1 && road[i_down][j_down] == 0
                && road[i_left][j_left] == 1 && road[i_right][j_right] == 0){
            value_table[i_input][j_input][2] =value_table[i_input][j_input][3] = 999;
            situation[i_input][j_input]="「";
        }
        //when tile is -| -shape corner (forbid left and down directions)
        else if(road[i_up][j_up] == 1 && road[i_down][j_down] == 0
                && road[i_left][j_left] == 0 && road[i_right][j_right] == 1){
            value_table[i_input][j_input][1] =value_table[i_input][j_input][2] = 999;
            situation[i_input][j_input]="-|";
        }
        //when tile is 」-shape corner (forbid up and left directions)
        else if(road[i_up][j_up] == 0 && road[i_down][j_down] == 1
                && road[i_left][j_left] == 0 && road[i_right][j_right] == 1){
            value_table[i_input][j_input][0] =value_table[i_input][j_input][1] = 999;
            situation[i_input][j_input]="」";
        }
        //case 3:cross
        else if(road[i_up][j_up] == 0 && road[i_down][j_down] == 0
                && road[i_left][j_left] == 0 && road[i_right][j_right] == 0){
            situation[i_input][j_input]="+";
        }
    }

    //when the tile is on the edge
    if(i_input==0){
        //left-up corner
        if(j_input==0){
            if(road[i_right][j_right]==0 && road[i_down][j_down]==0){
                value_table[i_input][j_input][2] =value_table[i_input][j_input][3] = 999;
                situation[i_input][j_input]="「";
            }
        }
        //right-up corner
        else if(j_input==road[0].size()-1){
            if(road[i_down][j_down] == 0 && road[i_left][j_left] == 0){
                value_table[i_input][j_input][1] =value_table[i_input][j_input][2] = 999;
                situation[i_input][j_input]="-|";
            }
        }
        //upper edge
        else{
            //straight road
            if(road[i_down][j_down] == 1 && road[i_left][j_left] == 0 && road[i_right][j_right] == 0){
                value_table[i_input][j_input][0] =value_table[i_input][j_input][2] = 999;
                situation[i_input][j_input]="-";
            }
            //「-shape corner
            else if(road[i_right][j_right]==0 && road[i_down][j_down]==0 && road[i_left][j_left]==1){
                value_table[i_input][j_input][2] =value_table[i_input][j_input][3] = 999;
                situation[i_input][j_input]="「";
            }
            //-| -shape corner
            else if(road[i_down][j_down] == 0 && road[i_left][j_left] == 0 && road[i_right][j_right] == 1) {
                value_table[i_input][j_input][1] = value_table[i_input][j_input][2] = 999;
                situation[i_input][j_input]="-|";
            }
        }
    }
    else if(i_input==road.size()-1){
        //left-down corner
        if(j_input==0) {
            if (road[i_up][j_up] == 0 && road[i_right][j_right] == 0) {
                value_table[i_input][j_input][0] = value_table[i_input][j_input][3] = 999;
                situation[i_input][j_input]="L";
            }
        }
        //right-down corner
        else if(j_input==road[0].size()-1){
            if(road[i_up][j_up] == 0 && road[i_left][j_left] == 0 ){
                value_table[i_input][j_input][0] =value_table[i_input][j_input][1] = 999;
                situation[i_input][j_input]="」";
            }
        }
        //lower edge
        else{
            //straight road
            if (road[i_up][j_up] == 1 && road[i_left][j_left] == 0 && road[i_right][j_right] == 0){
                value_table[i_input][j_input][0] =value_table[i_input][j_input][2] = 999;
                situation[i_input][j_input]="-";
            }
            //L-shape corner (forbid right and up directions)
            else if(road[i_up][j_up] == 0 && road[i_left][j_left] == 1 && road[i_right][j_right] == 0){
                value_table[i_input][j_input][0] =value_table[i_input][j_input][3] = 999;
                situation[i_input][j_input]="L";
            }
            //」-shape corner (forbid up and left directions)
            else if(road[i_up][j_up] == 0 && road[i_left][j_left] == 0 && road[i_right][j_right] == 1){
                value_table[i_input][j_input][0] =value_table[i_input][j_input][1] = 999;
                situation[i_input][j_input]="」";
            }
            //dead end
            else if(road[i_up][j_up] == 0 && road[i_left][j_left] == 1 && road[i_right][j_right] == 1){
                situation[i_input][j_input]="|";
            }
        }
    }
    //left edge
    else if(j_input==0 && 0<i_input && i_input<road.size()-1){
        //straight road
        if(road[i_up][j_up] == 0 && road[i_down][j_down] == 0 && road[i_right][j_right] == 1){
            value_table[i_input][j_input][1] =value_table[i_input][j_input][3] = 999;
            situation[i_input][j_input]="|";
        }
        //L-shape corner (forbid right and up directions)
        else if(road[i_up][j_up] == 0 && road[i_down][j_down] == 1 && road[i_right][j_right] == 0){
            value_table[i_input][j_input][0] =value_table[i_input][j_input][3] = 999;
            situation[i_input][j_input]="L";
        }
        //「-shape corner (forbid right and down directions)
        else if(road[i_up][j_up] == 1 && road[i_down][j_down] == 0 && road[i_right][j_right] == 0){
            value_table[i_input][j_input][2] =value_table[i_input][j_input][3] = 999;
            situation[i_input][j_input]="「";
        }
        //dead end
        else if(road[i_up][j_up] == 1 && road[i_down][j_down] == 1 && road[i_right][j_right] == 0){
            situation[i_input][j_input]="-";
        }
    }
    //right edge
    else if(j_input==road[0].size()-1 && 0<i_input && i_input<road.size()-1){
        //straight road
        if(road[i_up][j_up] == 0 && road[i_down][j_down] == 0 && road[i_left][j_left] == 1){
            value_table[i_input][j_input][1] =value_table[i_input][j_input][3] = 999;
            situation[i_input][j_input]="|";
        }
        //-| -shape corner (forbid left and down directions)
        else if(road[i_up][j_up] == 1 && road[i_down][j_down] == 0 && road[i_left][j_left] == 0 ){
            value_table[i_input][j_input][1] =value_table[i_input][j_input][2] = 999;
            situation[i_input][j_input]="-|";
        }
        //」-shape corner (forbid up and left directions)
        else if(road[i_up][j_up] == 0 && road[i_down][j_down] == 1 && road[i_left][j_left] == 0 ){
            value_table[i_input][j_input][0] =value_table[i_input][j_input][1] = 999;
            situation[i_input][j_input]="」";
        }
    }

    //goal is dead end
    if(i_input==goal.getI() && j_input==goal.getJ()){
        situation[i_input][j_input]="G";
    }
    //start is dead end
    if(i_input==start.getI() && j_input==start.getJ()) {
        situation[i_input][j_input]="S";
    }
}

//judge whether value table is completely evaluated
bool Car::judge_evaluate_table_complete() {
    for (int i = 0; i <road.size(); i++) {
        for (int j = 0; j<road[0].size(); j++) {
            for(int k=0;k<4;k++) {
                if(value_table[i][j][k]==INT_MAX) return false;
            }
        }
    }
    return true;
}

//evaluate value table until it is completely evaluated
void Car::evaluate_value_table() {
    vector<vector<vector<int> > > temp;
    cout<<"evaluate value table"<<endl;
    int count=0;
    while(value_table!=temp) {
        count++;
        cout<<"count for loop:"<<count<<endl;
show_value_table();
show_situation();
        temp=value_table;
        //loop for all the tiles
        for (int i = 0; i <road.size(); i++) {
            for (int j = 0; j<road[0].size(); j++) {
                evaluate_value(i,j);
            }
        }
    }
}

bool Car::judge_evaluate_value(int i_input, int j_input, int k_input, int i_next, int j_next, int k_next, int value_atinput_temp) {
    if((value_table[i_input][j_input][k_input] == INT_MAX || value_table[i_input][j_input][k_input]>value_atinput_temp)
       && value_table[i_next][j_next][k_next] != INT_MAX && value_table[i_next][j_next][k_next] != 999) return true;
    else return false;
}

//evaluate value at the specified tile
void Car::evaluate_value(int i_input, int j_input) {
    //if the tile is blocked, already 999 is assigned, so do nothing.
    if(situation[i_input][j_input]=="B") return;
//cout<<"evaluate value at tile ("<<i_input<<" "<<j_input<<")"<<endl;

    int i_next,j_next,k_next,k_input;   //variables for the neighboring tiles
    int temp;

    //case 1:going straight
    //case 1-a:going left straightly
    k_next=1;   //direction is, 0:up, 1:left, 2:down, 3:right
    k_input=k_next;
    i_next=i_input;
    j_next=j_input-1;
    if(0<=j_next && j_next<=road[0].size()-1) { //condition for not located at the edges
            //--, +-, 「-, L-
        temp=value_table[i_next][j_next][k_next] + cost_straight;
        //input:tile on which we evaluate, next:tile with which we evaluate
        if (situation[i_input][j_input] == "-"
            && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='#';
        }
            //-+
        else if (situation[i_input][j_input] == "+" && situation[i_next][j_next] == "-"
                 &&judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='#';
        }
    }

    //case 1-b: going right straightly
    k_next=3;
    k_input=k_next;
    i_next=i_input;
    j_next=j_input+1;
    if(0<=j_next && j_next<=road[0].size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_straight;
        //--, -+, -」, --|
        if (situation[i_input][j_input] == "-"
            && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='#';
        }
            //+-
        else if (situation[i_input][j_input] == "+" && situation[i_next][j_next] == "-"
                 && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='#';
        }
    }
    //case 1-c: going up straightly
    k_next=0;
    k_input=k_next;
    i_next=i_input-1;
    j_next=j_input;
    if(0<=i_next && i_next<=road.size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_straight;
        //| +「 -|
        //| | |  |
        if (situation[i_input][j_input] == "|"
            && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='#';
        }
            //|
            //+
        else if (situation[i_input][j_input] == "+" && situation[i_next][j_next] == "|"
                 && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='#';
        }
        else if(situation[i_input][j_input] == "S"
                && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)){
            value_table[i_input][j_input][k_input] = temp;
        }
    }

    //case 1-d: going down straightly
    k_next=2;
    k_input=k_next;
    i_next=i_input+1;
    j_next=j_input;
    if(0<=i_next && i_next<=road.size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_straight;
        //| | | |
        //| + L 」
        if (situation[i_input][j_input] == "|"
            && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='#';
        }
            //+
            //|
        else if (situation[i_input][j_input] == "+" && situation[i_next][j_next] == "|"
                 && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_next] = temp;
            policy_table_3d[i_input][j_input][k_input]='#';
        }
    }

    //case 2: turn left
    //case 2-a: turn at the cross
    if(situation[i_input][j_input]=="+"){
        //case 2-a-1: -+
        k_input=0;  //direction is, 0:up, 1:left, 2:down, 3:right
        k_next=1;
        i_next=i_input;
        j_next=j_input-1;
        if(0<=j_next && j_next<=road[0].size()-1) {
            temp=value_table[i_next][j_next][k_next] + cost_leftturn;
            if (judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
                value_table[i_input][j_input][k_input] = temp;
                policy_table_3d[i_input][j_input][k_input]='L';
            }
        }
        //case 2-a-2: |
        //            +
        k_input=3;
        k_next=0;
        i_next=i_input-1;
        j_next=j_input;
        if(0<=i_next && i_next<=road.size()-1) {
            temp=value_table[i_next][j_next][k_next] + cost_leftturn;
            if (judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
                value_table[i_input][j_input][k_input] = temp;
                policy_table_3d[i_input][j_input][k_input]='L';
            }
        }
        //case 2-a-3: +-
        k_input=2;
        k_next=3;
        i_next=i_input;
        j_next=j_input+1;
        if(0<=j_next && j_next<=road[0].size()-1) {
            temp=value_table[i_next][j_next][k_next] + cost_leftturn;
            if (judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
                value_table[i_input][j_input][k_input] = temp;
                policy_table_3d[i_input][j_input][k_input]='L';
            }
        }
        //case 2-a-4: +
        //            |
        k_input=2;
        k_next=3;
        i_next=i_input+1;
        j_next=j_input;
        if(0<=i_next && i_next<=road.size()-1) {
            temp=value_table[i_next][j_next][k_next] + cost_leftturn;
            if (judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
                value_table[i_input][j_input][k_input] = temp;
                policy_table_3d[i_input][j_input][k_input]='L';
            }
        }
    }

    //case 2-b: turn at the corner
    //case 2-b-1:L-
    k_input=2;
    k_next=3;
    i_next=i_input;
    j_next=j_input+1;
    if(0<=j_next && j_next<=road[0].size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_leftturn;
        if (situation[i_input][j_input] == "L"
            && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='L';
        }
    }
    //case 2-b-2: 「
    //             |
    k_input=1;
    k_next=2;
    i_next=i_input+1;
    j_next=j_input;
    if(0<=i_next && i_next<=road.size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_leftturn;
        if (situation[i_input][j_input] == "「"
            &&judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='L';
        }
    }
    //case 2-b-3: |
    //            」
    k_input=3;
    k_next=0;
    i_next=i_input-1;
    j_next=j_input;
    if(0<=i_next && i_next<=road.size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_leftturn;
        if (situation[i_input][j_input] == "」"
            && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='L';
        }
    }
    //case 2-b-4: --|
    k_input=0;
    k_next=1;
    i_next=i_input;
    j_next=j_input-1;
    if(0<=j_next && j_next<=road[0].size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_leftturn;
        if (situation[i_input][j_input] == "-|"
            && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='L';
        }
    }

    //case 3: turn right
    //case 3-a: turn at the cross
    if(situation[i_input][j_input]=="+"){
        //case 3-a-1: -+
        k_input=2;   //direction is, 0:up, 1:left, 2:down, 3:right
        k_next=1;
        i_next=i_input;
        j_next=j_input-1;
        if(0<=j_next && j_next<=road[0].size()-1) {
            temp=value_table[i_next][j_next][k_next] + cost_rightturn;
            if (judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
                value_table[i_input][j_input][k_input] = temp;
                policy_table_3d[i_input][j_input][k_input]='R';
            }
        }
        //case 3-a-2: |
        //            +
        k_input=1;
        k_next=0;
        i_next=i_input-1;
        j_next=j_input;
        if(0<=i_next && i_next<=road.size()-1) {
            temp=value_table[i_next][j_next][k_next] + cost_rightturn;
            if (judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
                value_table[i_input][j_input][k_input] = temp;
                policy_table_3d[i_input][j_input][k_input]='R';
            }
        }
        //case 3-a-3: +-
        k_input=0;
        k_next=3;
        i_next=i_input;
        j_next=j_input+1;
        if(0<=j_next && j_next<=road[0].size()-1) {
            temp=value_table[i_next][j_next][k_next] + cost_rightturn;
            if (judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
                value_table[i_input][j_input][k_input] = temp;
                policy_table_3d[i_input][j_input][k_input]='R';
            }
        }
        //case 3-a-4: +
        //            |
        k_input=3;
        k_next=2;
        i_next=i_input+1;
        j_next=j_input;
        if(0<=i_next && i_next<=road.size()-1) {
            temp=value_table[i_next][j_next][k_next] + cost_rightturn;
            if (judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
                value_table[i_input][j_input][k_input] = temp;
                policy_table_3d[i_input][j_input][k_input]='R';
            }
        }
    }

    //case 3-b: turn at the corner
    //case 3-b-1: |
    //            L
    k_input=1;
    k_next=0;
    i_next=i_input-1;
    j_next=j_input;
    if(0<=i_next && i_next<=road.size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_rightturn;
        if (situation[i_input][j_input] == "L"
            && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='R';
        }
    }
    //case 3-b-2: 「-
    k_input=0;
    k_next=3;
    i_next=i_input;
    j_next=j_input+1;
    if(0<=j_next && j_next<=road[0].size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_rightturn;
        if (situation[i_input][j_input] == "「"
            && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='R';
        }
    }
    //case 3-b-3: -」
    k_input=2;
    k_next=1;
    i_next=i_input;
    j_next=j_input-1;
    if(0<=j_next && j_next<=road[0].size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_rightturn;
        if (situation[i_input][j_input] == "」"
            &&judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='R';
        }
    }
    //case 3-b-4: -|
    //             |
    k_input=3;
    k_next=2;
    i_next=i_input+1;
    j_next=j_input;
    if(0<=i_next && i_next<=road.size()-1) {
        temp=value_table[i_next][j_next][k_next] + cost_rightturn;
        if (situation[i_input][j_input] == "-|"
            && judge_evaluate_value(i_input,j_input,k_input,i_next,j_next,k_next,temp)) {
            value_table[i_input][j_input][k_input] = temp;
            policy_table_3d[i_input][j_input][k_input]='R';
        }
    }
}

void Car::evaluate_policy() {
    cout<<"evaluate policy table in 2D"<<endl;
    XYtheta position=start;
    while(policy_table_3d[position.getI()][position.getJ()][position.getTheta()]!='*'){
        int action;
        if(policy_table_3d[position.getI()][position.getJ()][position.getTheta()]=='#') {
            action=0;
            policy_table[position.getI()][position.getJ()]='#';
        }
        else if(policy_table_3d[position.getI()][position.getJ()][position.getTheta()]=='L') {
            action=1;
            policy_table[position.getI()][position.getJ()]='L';
        }
        else if(policy_table_3d[position.getI()][position.getJ()][position.getTheta()]=='R'){
            action=-1;
            policy_table[position.getI()][position.getJ()]='R';
        }
        position=proceed(position,action);
    }

}

XYtheta Car::proceed(XYtheta original,int action) {
    //direction
    int theta=original.getTheta()+action;
    if(theta>=4) theta-=4;
    else if(theta<0) theta+=4;

    //position
    int i,j;
    i=original.getI();
    j=original.getJ();
    if(theta==0) i+=-1;
    else if(theta==1) j+=-1;
    else if(theta==2) i+=1;
    else if(theta==3) j+=1;

    XYtheta result(i,j,theta);
    return result;
}

////////////////////interface///////////////////
void Car::show_value_table() {
    cout << "show value table" << endl;
    cout << "Up" << endl;
    for (int i = 0; i < road.size(); i++) {
        for (int j = 0; j < road[0].size(); j++) cout << value_table[i][j][0] << " ";
        cout << endl;
    }
    cout << "Left" << endl;
    for (int i = 0; i < road.size(); i++) {
        for (int j = 0; j < road[0].size(); j++) cout << value_table[i][j][1] << " ";
        cout << endl;
    }
    cout << "Down" << endl;
    for (int i = 0; i < road.size(); i++) {
        for (int j = 0; j < road[0].size(); j++) cout << value_table[i][j][2] << " ";
        cout << endl;
    }
    cout << "Right" << endl;
    for (int i = 0; i < road.size(); i++) {
        for (int j = 0; j < road[0].size(); j++) cout << value_table[i][j][3] << " ";
        cout << endl;
    }
}

void Car::show_policy_table() {
    cout<<"show policy table"<<endl;
    for(int i=0;i<road.size();i++){
        for(int j=0;j<road[0].size();j++) cout<<policy_table[i][j]<<" ";
        cout<<endl;
    }
}

void Car::show_road() {
    cout<<"show road"<<endl;
    for(int i=0;i<road.size();i++){
        for(int j=0;j<road[0].size();j++) cout<<road[i][j]<<" ";
        cout<<endl;
    }
}

void Car::show_situation() {
    cout<<"show situation"<<endl;
    for(int i=0;i<road.size();i++){
        for(int j=0;j<road[0].size();j++) cout<<situation[i][j]<<" ";
        cout<<endl;
    }
}

void Car::show_policy_table_3d() {
    cout<<"show policy table in 3D"<<endl;
    cout << "Up" << endl;
    for (int i = 0; i < road.size(); i++) {
        for (int j = 0; j < road[0].size(); j++) cout << policy_table_3d[i][j][0] << " ";
        cout << endl;
    }
    cout << "Left" << endl;
    for (int i = 0; i < road.size(); i++) {
        for (int j = 0; j < road[0].size(); j++) cout << policy_table_3d[i][j][1] << " ";
        cout << endl;
    }
    cout << "Down" << endl;
    for (int i = 0; i < road.size(); i++) {
        for (int j = 0; j < road[0].size(); j++) cout << policy_table_3d[i][j][2] << " ";
        cout << endl;
    }
    cout << "Right" << endl;
    for (int i = 0; i < road.size(); i++) {
        for (int j = 0; j < road[0].size(); j++) cout << policy_table_3d[i][j][3] << " ";
        cout << endl;
    }
}








