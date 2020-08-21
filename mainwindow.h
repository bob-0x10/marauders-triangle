#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
