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
#include <unistd.h>
#include "calculate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int xValue{0}, yValue{0}, xPosition{0}, yPosition{0}, boundValue{0}, xCorrection{0}, yCorrection{0};

private slots:
    void reset_variables();

    void paintEvent(QPaintEvent* event);

    int return_RSSI(const char *filename);

    void on_enterButton_clicked();

    void on_xAxisCorrectionSlidebar_valueChanged(int value);

    void on_yAxisCorrectionSlidebar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
