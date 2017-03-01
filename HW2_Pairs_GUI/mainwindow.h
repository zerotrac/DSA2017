#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <vector>
#include <cmath>

#define PII std::pair<int, int>
#define mp std::make_pair

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    std::vector<PII> points;
    std::vector<int> colors;
    int myColors[7] = {Qt::black, Qt::red, Qt::green, Qt::cyan, Qt::magenta, Qt::yellow, Qt::gray};

    int ptx = 0;
    int pty = 0;
    int dis = 999999999;


public:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

public slots:
    void clearPoints();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
