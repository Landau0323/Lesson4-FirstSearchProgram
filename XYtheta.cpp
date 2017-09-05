//
// Created by 研究用 on 2017/08/24.
//

#include "XYtheta.h"

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

void XYtheta::setI(int i) {
    XYtheta::i = i;
}

void XYtheta::setJ(int j) {
    XYtheta::j = j;
}

void XYtheta::setTheta(int theta) {
    XYtheta::theta = theta;
}

void XYtheta::setIJTheta(int i_input, int j_input, int theta_input) {
    i=i_input;
    j=j_input;
    theta=theta_input;
}

void XYtheta::setIJ(int i_input, int j_input) {
    i=i_input;
    j=j_input;
}

int XYtheta::getI() const {
    return i;
}

int XYtheta::getJ() const {
    return j;
}

int XYtheta::getTheta() const {
    return theta;
}

XYtheta::XYtheta(int i, int j, int theta) : i(i), j(j), theta(theta) {}

XYtheta::XYtheta() {}
