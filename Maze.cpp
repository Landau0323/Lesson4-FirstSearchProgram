//
// Created by 研究用 on 2017/08/22.
//

#include "Maze.h"

using namespace std;

Maze::Maze() {
    count=0;
    count_block=0;

    //install maze
    maze.clear();
    cout<<"Choose the maze(0-8):"<<endl;
    int case_number;
    cin>>case_number;
    int tate,yoko;
    if(case_number!=7 && case_number!=8){
        tate=5;
        yoko=6;
    }
    else{
        tate=6;
        yoko=6;
    }
    maze.resize(tate);
    for(int i=0;i<tate;i++) maze[i].resize(yoko);
    if(case_number==0){
        maze[0][0]=0; maze[0][1]=0; maze[0][2]=1; maze[0][3]=0; maze[0][4]=0; maze[0][5]=0;
        maze[1][0]=0; maze[1][1]=0; maze[1][2]=1; maze[1][3]=0; maze[1][4]=0; maze[1][5]=0;
        maze[2][0]=0; maze[2][1]=0; maze[2][2]=0; maze[2][3]=0; maze[2][4]=1; maze[2][5]=0;
        maze[3][0]=0; maze[3][1]=0; maze[3][2]=1; maze[3][3]=1; maze[3][4]=1; maze[3][5]=0;
        maze[4][0]=0; maze[4][1]=0; maze[4][2]=0; maze[4][3]=0; maze[4][4]=1; maze[4][5]=0;
    }
    else if(case_number==1){
        maze[0][0]=0; maze[0][1]=0; maze[0][2]=1; maze[0][3]=0; maze[0][4]=0; maze[0][5]=0;
        maze[1][0]=0; maze[1][1]=0; maze[1][2]=0; maze[1][3]=0; maze[1][4]=0; maze[1][5]=0;
        maze[2][0]=0; maze[2][1]=0; maze[2][2]=0; maze[2][3]=0; maze[2][4]=1; maze[2][5]=0;
        maze[3][0]=0; maze[3][1]=0; maze[3][2]=1; maze[3][3]=1; maze[3][4]=1; maze[3][5]=0;
        maze[4][0]=0; maze[4][1]=0; maze[4][2]=0; maze[4][3]=0; maze[4][4]=1; maze[4][5]=0;
    }
    else if(case_number==2){
        maze[0][0]=0; maze[0][1]=0; maze[0][2]=1; maze[0][3]=0; maze[0][4]=0; maze[0][5]=0;
        maze[1][0]=0; maze[1][1]=0; maze[1][2]=1; maze[1][3]=0; maze[1][4]=0; maze[1][5]=0;
        maze[2][0]=0; maze[2][1]=0; maze[2][2]=1; maze[2][3]=0; maze[2][4]=1; maze[2][5]=0;
        maze[3][0]=0; maze[3][1]=0; maze[3][2]=1; maze[3][3]=0; maze[3][4]=1; maze[3][5]=0;
        maze[4][0]=0; maze[4][1]=0; maze[4][2]=0; maze[4][3]=0; maze[4][4]=1; maze[4][5]=0;
    }
    else if(case_number==3){    //in this case, search fails.
        maze[0][0]=0; maze[0][1]=0; maze[0][2]=1; maze[0][3]=0; maze[0][4]=0; maze[0][5]=0;
        maze[1][0]=0; maze[1][1]=0; maze[1][2]=1; maze[1][3]=0; maze[1][4]=0; maze[1][5]=0;
        maze[2][0]=0; maze[2][1]=0; maze[2][2]=1; maze[2][3]=0; maze[2][4]=1; maze[2][5]=0;
        maze[3][0]=0; maze[3][1]=0; maze[3][2]=1; maze[3][3]=0; maze[3][4]=1; maze[3][5]=0;
        maze[4][0]=0; maze[4][1]=0; maze[4][2]=1; maze[4][3]=0; maze[4][4]=1; maze[4][5]=0;
    }
    else if(case_number==4){
        maze[0][0]=0; maze[0][1]=0; maze[0][2]=1; maze[0][3]=0; maze[0][4]=0; maze[0][5]=0;
        maze[1][0]=0; maze[1][1]=0; maze[1][2]=0; maze[1][3]=0; maze[1][4]=0; maze[1][5]=0;
        maze[2][0]=0; maze[2][1]=0; maze[2][2]=1; maze[2][3]=0; maze[2][4]=1; maze[2][5]=0;
        maze[3][0]=0; maze[3][1]=0; maze[3][2]=1; maze[3][3]=0; maze[3][4]=1; maze[3][5]=0;
        maze[4][0]=0; maze[4][1]=0; maze[4][2]=1; maze[4][3]=0; maze[4][4]=1; maze[4][5]=0;
    }
    else if(case_number==5){
        maze[0][0]=0; maze[0][1]=1; maze[0][2]=0; maze[0][3]=0; maze[0][4]=0; maze[0][5]=0;
        maze[1][0]=0; maze[1][1]=1; maze[1][2]=0; maze[1][3]=0; maze[1][4]=0; maze[1][5]=0;
        maze[2][0]=0; maze[2][1]=1; maze[2][2]=0; maze[2][3]=0; maze[2][4]=0; maze[2][5]=0;
        maze[3][0]=0; maze[3][1]=1; maze[3][2]=0; maze[3][3]=0; maze[3][4]=0; maze[3][5]=0;
        maze[4][0]=0; maze[4][1]=0; maze[4][2]=0; maze[4][3]=0; maze[4][4]=1; maze[4][5]=0;
    }
    else if(case_number==6){
        maze[0][0]=0; maze[0][1]=1; maze[0][2]=0; maze[0][3]=0; maze[0][4]=0; maze[0][5]=0;
        maze[1][0]=0; maze[1][1]=1; maze[1][2]=0; maze[1][3]=0; maze[1][4]=0; maze[1][5]=0;
        maze[2][0]=0; maze[2][1]=1; maze[2][2]=0; maze[2][3]=0; maze[2][4]=0; maze[2][5]=0;
        maze[3][0]=0; maze[3][1]=1; maze[3][2]=0; maze[3][3]=0; maze[3][4]=0; maze[3][5]=0;
        maze[4][0]=0; maze[4][1]=0; maze[4][2]=0; maze[4][3]=0; maze[4][4]=0; maze[4][5]=0;
    }
    else if(case_number==7){
        maze[0][0]=0; maze[0][1]=0; maze[0][2]=1; maze[0][3]=0; maze[0][4]=0; maze[0][5]=0;
        maze[1][0]=0; maze[1][1]=0; maze[1][2]=1; maze[1][3]=0; maze[1][4]=0; maze[1][5]=0;
        maze[2][0]=0; maze[2][1]=0; maze[2][2]=1; maze[2][3]=0; maze[2][4]=0; maze[2][5]=0;
        maze[3][0]=0; maze[3][1]=0; maze[3][2]=0; maze[3][3]=0; maze[3][4]=1; maze[3][5]=0;
        maze[4][0]=0; maze[4][1]=0; maze[4][2]=1; maze[4][3]=1; maze[4][4]=1; maze[4][5]=0;
        maze[5][0]=0; maze[5][1]=0; maze[5][2]=0; maze[5][3]=0; maze[5][4]=1; maze[5][5]=0;
    }
    else if(case_number==8){
        maze[0][0]=0; maze[0][1]=0; maze[0][2]=0; maze[0][3]=0; maze[0][4]=0; maze[0][5]=0;
        maze[1][0]=0; maze[1][1]=0; maze[1][2]=1; maze[1][3]=0; maze[1][4]=0; maze[1][5]=0;
        maze[2][0]=0; maze[2][1]=0; maze[2][2]=1; maze[2][3]=0; maze[2][4]=0; maze[2][5]=0;
        maze[3][0]=0; maze[3][1]=0; maze[3][2]=0; maze[3][3]=0; maze[3][4]=1; maze[3][5]=0;
        maze[4][0]=0; maze[4][1]=0; maze[4][2]=1; maze[4][3]=1; maze[4][4]=1; maze[4][5]=0;
        maze[5][0]=0; maze[5][1]=0; maze[5][2]=0; maze[5][3]=0; maze[5][4]=1; maze[5][5]=0;
    }

    //install goal
    goal.setIJ(tate-1,yoko-1);

    //initialize list
    GXY initial;
    initial.setIJ(0,0);
    initial.setG(0);
    list.clear();
    list.push_back(initial);

    //initialize expand
    expand_table.clear();
    expand_table.resize(tate);
    for(int i=0;i<tate;i++){
        expand_table[i].resize(yoko);
        for(int j=0;j<yoko;j++) expand_table[i][j]=-1;
    }
    expand_table[list[0].getI()][list[0].getJ()]=count;

    //initialize path map
    maze_path.resize(tate);
    for(int i=0;i<tate;i++){
        maze_path[i].resize(yoko);
        for(int j=0;j<yoko;j++) maze_path[i][j]=' ';
    }
    maze_path[goal.getI()][goal.getJ()]='*';
    
    //install h-value
    h.resize(tate);
    for(int k=0;k<tate;k++) h[k].resize(yoko);
    h[0][0]=9; h[0][1]=8; h[0][2]=7; h[0][3]=6; h[0][4]=5; h[0][5]=4;
    h[1][0]=8; h[1][1]=7; h[1][2]=6; h[1][3]=5; h[1][4]=4; h[1][5]=3;
    h[2][0]=7; h[2][1]=6; h[2][2]=5; h[2][3]=4; h[2][4]=3; h[2][5]=2;
    h[3][0]=6; h[3][1]=5; h[3][2]=4; h[3][3]=3; h[3][4]=2; h[3][5]=1;
    h[4][0]=5; h[4][1]=4; h[4][2]=3; h[4][3]=2; h[4][4]=1; h[4][5]=0;

    //initialize value table
    value_table.resize(tate);
    for(int k=0;k<tate;k++) value_table[k].resize(yoko);
    for(int n=0;n<tate;n++){
        for(int m=0;m<yoko;m++){
            if(maze[n][m]==1) {
                value_table[n][m]=99;
                count_block++;
            }
            else value_table[n][m]=INT_MAX;
        }
    }
    value_table[goal.getI()][goal.getJ()]=0;

    //initialize policy table
    policy_table.resize(tate);
    for(int k=0;k<tate;k++) policy_table[k].resize(yoko);
    for(int n=0;n<tate;n++){
        for(int m=0;m<yoko;m++){
            if(maze[n][m]==1) policy_table[n][m]=' ';
        }
    }
    policy_table[goal.getI()][goal.getJ()]=' ';
}

    //Until it reaches at the goal, iterate.
void Maze::proceed() {
    cout<<"solve the maze problem with normal algorithm"<<endl;
    bool condition;
    while(1){
//        show_list();
        //if it reaches at the goal, stop the loop
        condition=judge();
        if(condition==true){
            cout<<"Search successful!"<<endl;
            break;
        }
        //if list is empty, the search fails
        if(list.empty()){
            cout<<"Fail!"<<endl;
            break;
        }
        expand_next();      //if it is not at the goal, expand the list
    }
}

//solve the problem with A* algorithm
void Maze::proceed_Astar() {
    cout<<"solve the maze problem with A* algorithm"<<endl;
    bool condition;
    while(1){
//        show_list();
        //if it reaches at the goal, stop the loop
        condition=judge();
        if(condition==true) break;
        //if list is empty, the search fails
        if(list.empty()){
            cout<<"Fail!"<<endl;
            break;
        }
        expand_next_Astar();      //if it is not at the goal, expand the list
    }
}

void Maze::expand_next() {
    //choose the point with the least g-value
    int g_min=INT_MAX;
    int temp_id;
    for(int i=0;i<list.size();i++){
        if(list[i].getG()<g_min) {
            g_min=list[i].getG();
            temp_id=i;
        }
    }
    int i=list[temp_id].getI();
    int j=list[temp_id].getJ();
    list.erase(list.begin()+temp_id);   //erase the point with the least g-value
    GXY temp;
    temp.setG(g_min);
    temp.setIJ(i,j);
    checked.push_back(temp);

    //expand from this point
    //case 1: up
    int i_next=i-1;
    int j_next=j;
    expand(g_min,i_next,j_next);

    //case 2:down
    i_next=i+1;
    j_next=j;
    expand(g_min,i_next,j_next);

    //case 3:right
    i_next=i;
    j_next=j+1;
    expand(g_min,i_next,j_next);

    //case 4:left
    i_next=i;
    j_next=j-1;
    expand(g_min,i_next,j_next);
}

void Maze::expand_next_Astar() {
    //choose the point with the least f-value
    int f_min=INT_MAX;
    int g_min;
    int temp_id;
    for(int i=0;i<list.size();i++){
        int f_temp=list[i].getG()+h[list[i].getI()][list[i].getJ()];
//list[i].show();
//cout<<"f-value:"<<f_temp<<endl;
        if(f_temp<f_min) {
            f_min=f_temp;
            g_min=list[i].getG();
            temp_id=i;
        }
    }
//cout<<"expand this: f-value is "<<f_min<<", ";
//list[temp_id].show();

    int i=list[temp_id].getI();
    int j=list[temp_id].getJ();

    //erase the point with the least f-value
    list.erase(list.begin()+temp_id);

    GXY temp;
    temp.setG(g_min);
    temp.setIJ(i,j);
    checked.push_back(temp);    //put the point to the checked list

    //expand from this point (without choosing the neighbor with the least f-value)
    int i_next,j_next;
    //case 1: up
    i_next=i-1;
    j_next=j;
    expand(g_min,i_next,j_next);

    //case 2:down
    i_next=i+1;
    j_next=j;
    expand(g_min,i_next,j_next);

    //case 3:right
    i_next=i;
    j_next=j+1;
    expand(g_min,i_next,j_next);

    //case 4:left
    i_next=i;
    j_next=j-1;
    expand(g_min,i_next,j_next);
}

//Expand the specified tile with incremented g-value (if possible)
void Maze::expand(int g_input, int i_input,int j_input) {
    GXY temp;
    int tate=maze.size();
    int yoko=maze[0].size();

    bool condition=true;
    for(int k=0;k<checked.size();k++){
        if(checked[k].getI()==i_input && checked[k].getJ()==j_input) condition=false;
    }
    for(int k=0;k<list.size();k++){
        if(list[k].getI()==i_input && list[k].getJ()==j_input) condition=false;
    }
    if(0<=i_input && i_input<tate && 0<=j_input && j_input<yoko //condition 1:Is it inside the maze?
       && maze[i_input][j_input]==0 //condition 2:Is it unblocked tile?
       && condition==true)        //condition 3:Is it already checked or in the list?
    {
        temp.setG(g_input+1);
        temp.setIJ(i_input,j_input);
        list.push_back(temp);
        count++;
//cout<<"count becomes "<<count<<", and the expanded tile is "<<i_input<<" "<<j_input<<endl;
        expand_table[i_input][j_input]=count;
    }
}

//judge whether it reaches at the goal
bool Maze::judge() {
    for(int i=0;i<list.size();i++){
        if(list[i].getI()==goal.getI() && list[i].getJ()==goal.getJ()) return true;
    }
    return false;
}

//find path. Start from the goal to the starting point
void Maze::find_path() {
    //pick up the goal position
    int i,j,g_result;
    for(int n=0;n<list.size();n++){
        if(list[n].getG()==g){
            i=list[n].getI();
            j=list[n].getJ();
            g_result=g;
        }
    }
    //count down from g-value at the goal
    for(int n=g_result;n>=0;n--){
        //pick up from the checked tiles
        for(int m=checked.size();m>=0;m--){
            if(checked[m].getG()==g-1){
                if(checked[m].getI()==i-1 && checked[m].getJ()==j){
                    maze_path[i-1][j]='v';
                    g--;
                    i--;
                }
                else if(checked[m].getI()==i+1 && checked[m].getJ()==j){
                    maze_path[i+1][j]='^';
                    g--;
                    i++;
                }
                else if(checked[m].getI()==i && checked[m].getJ()==j-1){
                    maze_path[i][j-1]='>';
                    g--;
                    j--;
                }
                else if(checked[m].getI()==i && checked[m].getJ()==j+1){
                    maze_path[i][j+1]=',';
                    g--;
                    j++;
                }
            }
        }
    }
}

bool Maze::judge_evaluate_table_complete() {
    for(int i=0;i<maze.size();i++){
        for(int j=0;j<maze[0].size();j++){
            if(value_table[i][j]==INT_MAX) return false;
        }
    }
    return true;
}

void Maze::evaluate_value_table() {
    cout<<"evaluate value table"<<endl;
    while(judge_evaluate_table_complete()==false) {
        for (int i = maze.size() - 1; i >= 0; i--) {
            for (int j = maze[0].size() - 1; j >= 0; j--) {
                evaluate_value(i, j);
            }
        }
    }
}

void Maze::evaluate_value(int i_input, int j_input) {
    if(value_table[i_input][j_input]!=INT_MAX) return;

    //case 1:up
    int i=i_input-1;
    int j=j_input;
    if(0<=i && i<maze.size()) {
        if (value_table[i][j] != INT_MAX && value_table[i][j] != 99) {
            value_table[i_input][j_input] = value_table[i][j] + 1;
            return;
        }
    }
    //case 2:down
    i=i_input+1;
    j=j_input;
    if(0<=i && i<maze.size()) {
        if (value_table[i][j] != INT_MAX && value_table[i][j] != 99) {
            value_table[i_input][j_input] = value_table[i][j] + 1;
            return;
        }
    }
    //case 3:left
    i=i_input;
    j=j_input-1;
    if(0<=j && j<maze[0].size()) {
        if (value_table[i][j] != INT_MAX && value_table[i][j] != 99) {
            value_table[i_input][j_input] = value_table[i][j] + 1;
            return;
        }
    }
    //case 4:right
    i=i_input;
    j=j_input+1;
    if(0 <= j && j < maze[0].size()) {
        if (value_table[i][j] != INT_MAX && value_table[i][j] != 99) {
            value_table[i_input][j_input] = value_table[i][j] + 1;
            return;
        }
    }
}

void Maze::evaluate_policy_table() {
    for(int i=0;i<maze.size();i++){
        for(int j=0;j<maze[0].size();j++) evaluate_policy(i,j);
    }
}

void Maze::evaluate_policy(int i_input, int j_input) {
    if(policy_table[i_input][j_input]==' ') return;
    //case 1:up
    int i=i_input-1;
    int j=j_input;
    if(0<=i && i<maze.size()) {
        if (value_table[i][j]< value_table[i_input][j_input]) {
            policy_table[i_input][j_input] = '^';
            return;
        }
    }
    //case 2:down
    i=i_input+1;
    j=j_input;
    if(0<=i && i<maze.size()) {
        if (value_table[i][j]< value_table[i_input][j_input]) {
            policy_table[i_input][j_input] = 'v';
            return;
        }
    }
    //case 3:left
    i=i_input;
    j=j_input-1;
    if(0<=j && j<maze[0].size()) {
        if (value_table[i][j]< value_table[i_input][j_input]) {
            policy_table[i_input][j_input] = '<';
            return;
        }
    }
    //case 4:right
    i=i_input;
    j=j_input+1;
    if(0 <= j && j < maze[0].size()) {
        if (value_table[i][j]< value_table[i_input][j_input]) {
            policy_table[i_input][j_input] = '>';
            return;
        }
    }



}

//print the resultant g-value
void Maze::show_result_g() {
    cout<<"Resultant g-value:";
    for(int i=list.size()-1;i>=0;i--){
        if(list[i].getI()==goal.getI() && list[i].getJ()==goal.getJ()){
            g=list[i].getG();
            cout<<g<<endl;
        }
    }
    cout<<"goal position:["<<goal.getI()<<", "<<goal.getJ()<<"]"<<endl;
}

void Maze::show_list() {
    cout<<"Show list"<<endl;
    for(int i=0;i<list.size();i++) list[i].show();
    cout<<endl;
}

void Maze::show_checked() {
    cout<<"Show checked list"<<endl;
    for(int i=0;i<checked.size();i++) checked[i].show();
}

void Maze::show_maze() {
    cout<<"Show maze"<<endl;
    for(int i=0;i<maze.size();i++){
        for(int j=0;j<maze[i].size();j++) cout<<maze[i][j]<<" ";
        cout<<endl;
    }
}

void Maze::show_expand_table() {
    cout<<"Show expand table"<<endl;
    for(int i=0;i<maze.size();i++){
        for(int j=0;j<maze[i].size();j++) cout<<expand_table[i][j]<<" ";
        cout<<endl;
    }
}

void Maze::show_path() {
    cout<<"Show path"<<endl;
    for(int i=0;i<maze.size();i++){
        for(int j=0;j<maze[i].size();j++) cout<<maze_path[i][j]<<" ";
        cout<<endl;
    }

}

void Maze::show_value_table() {
    cout<<"show value table"<<endl;
    for(int i=0;i<maze.size();i++){
        for(int j=0;j<maze[0].size();j++) cout<<value_table[i][j]<<" ";
        cout<<endl;
    }
}

void Maze::show_policy_table() {
    cout << "show policy table" << endl;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].size(); j++) cout << policy_table[i][j] << " ";
        cout << endl;
    }
}