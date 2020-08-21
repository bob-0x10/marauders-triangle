#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <stdio.h>
#include <pcap.h>
#include <pcap/pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <math.h>
#define TX_POWER -82

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct pos{
    double xPos;
    double yPos;
}pos;
typedef struct packet_info{
    int RSSI;
    pos anthenaLoction;
}packet_info;


typedef struct radiotap_header {
        uint8_t        it_version;     /* set to 0 */
        uint8_t        it_pad;
        uint16_t       it_length;         /* entire length */
        uint64_t       it_present_flags;     /* fields present */
        uint8_t        it_flags;
        uint8_t        it_data_Rate;
        uint16_t       it_channel_frequency;
        uint16_t       it_channel_flags;
        uint8_t        it_antenna_signal;
        uint8_t        it_null;
        uint16_t       it_RX_flags;
        uint8_t        it_antenna_signal_2;
        uint8_t        it_null_2;
}radiotap_header;

typedef struct ieee80211_header {
        uint8_t        type_subtype;
        uint8_t        flags;
        uint16_t       duration;
        uint8_t 	mac_add_destination[6];
        uint8_t 	mac_add_source[6];
        uint8_t 	BSSID[6];
        uint16_t    fragment_sequence;
}ieee80211_header;

static void my_packet_handler( u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
double CalculateDistance(packet_info pinfo, int n);
pos CalculateLocation(double disA, double disB, double disC, double disBetween);
double DistanceBetween(pos p1, pos p2);
double CalculateRadius(double disA, double disB, double disC, double disBetween,
                       pos target_loc);
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int xValue{0}, yValue{0}, xPosition{0}, yPosition{0}, boundValue{0};

private slots:
    void reset_variables();

    void paintEvent(QPaintEvent* event);

    int return_RSSI(const char *filename);

    void on_enterButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
