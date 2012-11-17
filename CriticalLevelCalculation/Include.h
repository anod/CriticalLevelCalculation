#ifndef INCLUDE_H_
#define INCLUDE_H_

/**
 * Include standard c++ libraries
 */
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

/**
 * Include helpers
 */
#include "MakeString.h"
#include "OpenMP.h"
#include "Profiler.h"

/**
 * Project classes/defenitions
 */
#include "Cell.h"
#include "Flight.h"
#include "ProjectInfo.h"

/**
 * List of flights
 */
typedef std::vector<int> FlightList;
/**
 * List of flights in specific cell on ProjectSpace
 */
typedef std::unordered_map<Cell, FlightList> ControlPointsMap;
/**
 * Critical Level (CL) of the object at the specific moment:
 * the number of objects that do not see this object at the given moment. 
 */
typedef std::unordered_map<int, FlightList> CriticalLevel;

#include "ControlPoint.h"


#endif //INCLUDE_H_