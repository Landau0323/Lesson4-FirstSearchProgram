# Lesson4-FirstSearchProgram
Codes for the exercises in udacity program "Artificial Intelligence for Robotics" (4: Search). 

This is a program for path-finding on a plane.
There are two classes of problems:

1. Maze. In this problem, the robot does not have direction.
The cost is simply Manhattan distance.

2. Car. In this problem, the car has a direction, and left turn and right turn have different costs.
Usually, the cost for turning left is larger than the other one.
Going straight has the least cost.
By changing the cost for turning left, one will see that the optimal path changes from single left turn to three right turns.
