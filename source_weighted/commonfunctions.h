#ifndef COMMONFUNCTIONS
#define COMMONFUNCTIONS

#include <ctime>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <list>

void putProcess(double procedure, double time_used);

std::stringstream timeFormatting(double microSeconds);

unsigned long long currentTime();

#endif