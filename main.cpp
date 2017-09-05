#include <iostream>
#include "Maze.h"
#include "Car.h"

using namespace std;

int main() {
    /*
    cout<<"Solve maze problem"<<endl;
    cout<<"Choose the method (0:normal, 1:Astar, 2:dynamic programming)"<<endl;
    int case_number;
    cin>>case_number;

    //search all the paths
    if(case_number==0) {
        Maze maze;
        maze.show_maze();
        cout << endl;

        maze.proceed();
//    maze.show_checked();
        maze.show_result_g();

        maze.show_expand_table();
        maze.find_path();
        maze.show_path();
        cout << endl;
    }

    //search with A*
    else if(case_number==1) {
        Maze maze_Astar;
        maze_Astar.show_maze();
        maze_Astar.proceed_Astar();
//    maze_Astar.show_checked();
        maze_Astar.show_result_g();

        maze_Astar.show_expand_table();
        maze_Astar.find_path();
        maze_Astar.show_path();
        cout << endl;
    }

    //dynamic programming
    else if(case_number==2) {
        Maze maze_dynamic;
        maze_dynamic.show_maze();
        maze_dynamic.show_value_table();
        maze_dynamic.evaluate_value_table();
        maze_dynamic.show_value_table();
        maze_dynamic.evaluate_policy_table();
        maze_dynamic.show_policy_table();
        cout << endl;
    }
*/
    //solve Car problem with dynamic programming
    Car car;
    car.show_road();
    car.show_situation();
    cout<<"value table at initial state"<<endl;
    car.show_value_table();

    car.evaluate_value_table();
    car.show_value_table();

    car.show_policy_table_3d();
    car.evaluate_policy();
    car.show_policy_table();

    return 0;
}