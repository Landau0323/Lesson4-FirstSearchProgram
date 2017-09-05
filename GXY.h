//
// Created by 研究用 on 2017/08/22.
//

#ifndef FIRSTSEARCHPROGRAM_GXY_H
#define FIRSTSEARCHPROGRAM_GXY_H

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
#include "XY.h"

using namespace std;

class GXY:public XY {
private:
    int g;

public:
    void setG(int g);
    int getG() const;

    void show();

};


#endif //FIRSTSEARCHPROGRAM_GXY_H
