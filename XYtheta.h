//
// Created by 研究用 on 2017/08/24.
//

#ifndef FIRSTSEARCHPROGRAM_XYTHETA_H
#define FIRSTSEARCHPROGRAM_XYTHETA_H

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


class XYtheta {
private:
    int i,j,theta;

public:
    void setI(int i);
    void setJ(int j);
    void setTheta(int theta);
    void setIJTheta(int,int,int);
    void setIJ(int,int);

    XYtheta();

    XYtheta(int i, int j, int theta);

    int getI() const;

    int getJ() const;

    int getTheta() const;

};


#endif //FIRSTSEARCHPROGRAM_XYTHETA_H
