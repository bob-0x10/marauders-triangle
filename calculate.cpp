#include "calculate.h"
double CalculateDistance(packet_info pinfo, int n){
    int RSSI = pinfo.RSSI;
    double distance;
    distance = (double)(TX_POWER - RSSI) / (double)pow(10, n);
    distance = pow(10, distance);
    return distance;
}
pos CalculateLocation(double disA, double disB, double disC, double disBetween){
    pos location;
    double x, y;
    x = (pow(disA, 2) - pow(disB, 2)) / (double)(2 * disBetween) +
         disBetween / (double)(2);
    y = sqrt(abs(pow(disA, 2) - pow(x, 2)));
    location.xPos = x;
    location.yPos = y;
    return location;
}
double DistanceBetween(pos p1, pos p2){
    double dis = sqrt(pow((p1.xPos - p2.xPos), 2) + pow((p1.yPos - p2.yPos), 2));
    return dis;
}
double CalculateRadius(double disA, double disB, double disC, double disBetween,
                       pos target_loc){
    pos p1, p2, p3;
    p1.xPos = 0;
    p1.yPos = 0;
    p2.xPos = disBetween;
    p2.yPos = 0;
    p3.xPos = disBetween / (double)2;
    p3.yPos = p3.xPos * 1.7;
    double len1, len2, len3;
    len1 = DistanceBetween(p1, target_loc) - disA;
    len2 = DistanceBetween(p2, target_loc) - disB;
    len3 = DistanceBetween(p3, target_loc) - disC;

    int avg = (len1+len2+len3)/3;

    return (0 < avg) ? avg : 0;
}
