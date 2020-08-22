#ifndef CALCULATE_H
#define CALCULATE_H
#include "pstructure.h"
#include <math.h>
#define TX_POWER -82
double CalculateDistance(packet_info pinfo, int n);
pos CalculateLocation(double disA, double disB, double disC, double disBetween);
double DistanceBetween(pos p1, pos p2);
double CalculateRadius(double disA, double disB, double disC, double disBetween,
                       pos target_loc);
#endif // CALCULATE_H

