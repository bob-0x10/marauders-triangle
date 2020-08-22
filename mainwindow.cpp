#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"

#define MONITOR_ONE_X 90
#define MONITOR_ONE_Y 42
#define MONITOR_TWO_X 390
#define MONITOR_TWO_Y 42
#define MONITOR_THREE_X 240
#define MONITOR_THREE_Y 438

char filename;
char mac_add;
char pwr;
uint8_t my_mac[6];
int pwr_arr[1024];
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

int MainWindow::return_RSSI(const char* filename){
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(filename, error_buffer);
    char *device = "enp0s3";
    int total_packet_count = -1;
    u_char *my_arguments = NULL;
    device = pcap_lookupdev(error_buffer);
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

    xCorrection=0;
    yCorrection=0;

    MainWindow::update();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    xPosition = 10  + xValue + xCorrection;
    yPosition = 490 - yValue + yCorrection;

    QPainter painter;
    painter.begin(this);

    painter.setPen(Qt::yellow);
    painter.setBrush(QBrush(Qt::yellow));
    painter.drawEllipse(
                xPosition-boundValue/2,
                yPosition-boundValue/2,
                boundValue,
                boundValue);

    painter.setPen(Qt::red);
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(
                xPosition-1,
                yPosition-1,
                2,
                2);

    painter.setPen(Qt::blue);
    painter.setBrush(QBrush(Qt::blue));
    painter.drawEllipse(
                10  +   MONITOR_ONE_X   - 9,
                490 -   MONITOR_ONE_Y   - 9,
                18,
                18);
    painter.drawEllipse(
                10  +   MONITOR_TWO_X   - 9,
                490 -   MONITOR_TWO_Y   - 9,
                18,
                18);
    painter.drawEllipse(
                10  +   MONITOR_THREE_X   - 9,
                490 -   MONITOR_THREE_Y   - 9,
                18,
                18);
}

void MainWindow::on_enterButton_clicked()
{
    ui->enterButton->setEnabled(false);
    ui->enterButton->repaint();

    QString mac_temp = ui->macAddress->toPlainText();
    unsigned int a, b, c, d, e, f;
    int res = sscanf(mac_temp.toStdString().c_str(), "%02X:%02X:%02X:%02X:%02X:%02X", &a, &b, &c, &d, &e, &f);
    my_mac[0] = a;
    my_mac[1] = b;
    my_mac[2] = c;
    my_mac[3] = d;
    my_mac[4] = e;
    my_mac[5] = f;

    QString path1=ui->pcapPath_1->toPlainText();
    QString path2=ui->pcapPath_2->toPlainText();
    QString path3=ui->pcapPath_3->toPlainText();

    const char* p1 = path1.toStdString().c_str();
    const char* p2 = path2.toStdString().c_str();
    const char* p3 = path3.toStdString().c_str();

    int r1=return_RSSI(p1);
    int r2=return_RSSI(p2);
    int r3=return_RSSI(p3);

    packet_info pckt1,pckt2,pckt3;
    pckt1.RSSI=r1;
    pckt1.anthenaLoction.xPos=0;
    pckt1.anthenaLoction.yPos=0;
    pckt2.RSSI=r2;
    pckt2.anthenaLoction.xPos=300;
    pckt2.anthenaLoction.yPos=0;
    pckt3.RSSI=r3;
    pckt3.anthenaLoction.xPos=150;
    pckt3.anthenaLoction.yPos=255;
    double disA, disB, disC;

    disA = CalculateDistance(pckt1, 2);
    disB = CalculateDistance(pckt2, 2);
    disC = CalculateDistance(pckt3, 2);

    struct pos resultLocation = CalculateLocation(disA, disB, disC, 2);
    xValue=resultLocation.xPos*150+90;
    yValue=resultLocation.yPos*150+42;
    int diff=abs(pckt2.anthenaLoction.xPos-pckt1.anthenaLoction.xPos);
    boundValue=CalculateRadius(disA, disB, disC, diff,resultLocation);

    sleep(3);

    ui->enterButton->setEnabled(true);
    ui->enterButton->repaint();
    MainWindow::update();
}

void MainWindow::on_xAxisCorrectionSlidebar_valueChanged(int value)
{
    xCorrection = value;

    MainWindow::update();
}

void MainWindow::on_yAxisCorrectionSlidebar_valueChanged(int value)
{
    yCorrection = value;

    MainWindow::update();
}
