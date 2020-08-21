#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"

#define MONITOR_ONE_X 42
#define MONITOR_ONE_Y 90
#define MONITOR_TWO_X 42
#define MONITOR_TWO_Y 390
#define MONITOR_THREE_X 438
#define MONITOR_THREE_Y 240

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

void MainWindow::on_xValue_valueChanged(int value)
{
    xValue = 240+value;

    MainWindow::update();
}

void MainWindow::on_yValue_valueChanged(int value)
{
    yValue = 240+value;

    MainWindow::update();
}

void MainWindow::on_boundValue_valueChanged(int value)
{
    boundValue = value*2;

    MainWindow::update();
}
