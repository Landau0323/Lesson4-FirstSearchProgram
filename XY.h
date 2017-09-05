//
// Created by 研究用 on 2017/08/22.
//

#ifndef FIRSTSEARCHPROGRAM_XY_H
#define FIRSTSEARCHPROGRAM_XY_H

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


class XY {
protected:
    int i,j;

public:
    int getI() const;
    int getJ() const;
    void setIJ(int,int);
};


#endif //FIRSTSEARCHPROGRAM_XY_H
