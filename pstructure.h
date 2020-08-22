#ifndef PSTRUCTURE_H
#define PSTRUCTURE_H
typedef struct pos{
    double xPos;
    double yPos;
}pos;
typedef struct packet_info{
    int RSSI;
    pos anthenaLoction;
}packet_info;
#endif // PSTRUCTURE_H

