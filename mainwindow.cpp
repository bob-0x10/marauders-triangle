#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"

#define MONITOR_ONE_X 42
#define MONITOR_ONE_Y 90
#define MONITOR_TWO_X 42
#define MONITOR_TWO_Y 390
#define MONITOR_THREE_X 438
#define MONITOR_THREE_Y 240

char filename;
char mac_add;
char pwr;
uint8_t my_mac[6];
int pwr_arr[20];
int k = 0;

static void my_packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    struct radiotap_header *radio_hdr;
    struct ieee80211_header *ieee_hdr;

    radio_hdr = (struct radiotap_header *)packet;
    ieee_hdr = (struct ieee80211_header *)(packet + radio_hdr->it_length);
    pwr = radio_hdr->it_antenna_signal;

    if (memcmp(my_mac, ieee_hdr->mac_add_source, 6) == 0){
        pwr_arr[k++] = pwr;
    }
    return;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    reset_variables();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::return_RSSI(char* filename, char* mac_add){
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(filename, error_buffer);
    char *device; //= "enp0s3";
    int total_packet_count = -1;
    u_char *my_arguments = NULL;
    device = pcap_lookupdev(error_buffer);

    char *str = mac_add;
    char t[4];

    for(int i=0; i<6; i++){
        memcpy(t, (str+i*3), 3);
        t[3] = '\0';
        *(my_mac +i) = (uint8_t)strtoul(t, NULL, 16);
    }

    pcap_loop(handle, total_packet_count, my_packet_handler, my_arguments);

    int temp;

    for(int i = 0; i < k ; i++){
        for(int j = 0; j < k-1; j++){
            if(pwr_arr[j] > pwr_arr[i]){
                temp = pwr_arr[j];
                pwr_arr[j] = pwr_arr[j+1];
                pwr_arr[j+1] = temp;
            }
        }
    }

    int mid_signal = pwr_arr[k/2];

    return mid_signal;
}

void MainWindow::reset_variables()
{
    xValue=240;
    yValue=240;
    xPosition=0;
    yPosition=0;
    boundValue=1;

    MainWindow::update();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    xPosition = 490 - xValue;
    yPosition = 10  + yValue;

    QPainter painter;
    painter.begin(this);

    painter.setPen(Qt::yellow);
    painter.setBrush(QBrush(Qt::yellow));
    painter.drawEllipse(
                yPosition-boundValue/2,
                xPosition-boundValue/2,
                boundValue,
                boundValue);

    painter.setPen(Qt::red);
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(
                yPosition-1,
                xPosition-1,
                2,
                2);

    painter.setPen(Qt::blue);
    painter.setBrush(QBrush(Qt::blue));
    painter.drawEllipse(
                10  +   MONITOR_ONE_Y   - 9,
                490 -   MONITOR_ONE_X   - 9,
                18,
                18);
    painter.drawEllipse(
                10  +   MONITOR_TWO_Y   - 9,
                490 -   MONITOR_TWO_X   - 9,
                18,
                18);
    painter.drawEllipse(
                10  +   MONITOR_THREE_Y - 9,
                490 -   MONITOR_THREE_X - 9,
                18,
                18);
}
