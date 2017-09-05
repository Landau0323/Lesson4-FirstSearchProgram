//
// Created by 研究用 on 2017/08/22.
//

#include "GXY.h"

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

void GXY::setG(int g) {
    GXY::g = g;
}
int GXY::getG() const {
    return g;
}

void GXY::show() {
    cout<<g<<" ["<<i<<", "<<j<<"]"<<endl;
}
