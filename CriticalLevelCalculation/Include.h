#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "MakeString.h"
#include "Cell.h"
#include "OpenMP.h"

// List of Flight Numbers
typedef std::vector<int> FlightList;
// List of flights in specific cell on ProjectSpace
typedef std::unordered_map<Cell, FlightList> ControlPointsMap;
//
typedef std::unordered_map<int, FlightList> CriticalLevel;

#include "ControlPoint.h"

#include "Profiler.h"

#endif //INCLUDE_H_