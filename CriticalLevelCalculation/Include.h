#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Cell.h"
#include "OpenMP.h"

typedef std::vector<int> FlightList;
typedef std::unordered_map<Cell, FlightList> ControlPointsMap;
typedef std::unordered_map<int, FlightList> CriticalLevel;

#include "ControlPoint.h"

#include "Profiler.h"

#endif //INCLUDE_H_