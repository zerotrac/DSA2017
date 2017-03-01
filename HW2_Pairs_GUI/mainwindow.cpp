#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(clearPoints()));
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPen pen;

    int radius = 5;
    for (int i = 0; i < (int)points.size(); ++i)
    {
        if (ptx != pty && (ptx == i || pty == i))
        {
            pen.setColor(Qt::blue);
            pen.setWidth(3);
        }
        else
        {
            pen.setColor(Qt::black);
            pen.setWidth(1);
        }
        painter.setPen(pen);

        int xx = points[i].first;
        int yy = points[i].second;
        painter.setBrush(Qt::GlobalColor(myColors[colors[i]]));
        painter.drawEllipse(xx - radius, yy - radius, radius * 2, radius * 2);
    }

    pen.setColor(Qt::blue);
    pen.setWidth(3);
    painter.setPen(pen);
    if (ptx != pty)
    {
        int dx = points[pty].first - points[ptx].first;
        int dy = points[pty].second - points[ptx].second;
        printf("%d %d %d\n", dx, dy, dis);
        dx = (int)((double)dx * 5.0 / sqrt(1.0 * dis) + 0.5);
        dy = (int)((double)dy * 5.0 / sqrt(1.0 * dis) + 0.5);
        printf("%d %d\n", dx, dy);
        painter.drawLine(points[ptx].first + dx, points[ptx].second + dy, points[pty].first - dx, points[pty].second - dy);
    }
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    int xx = event->pos().x();
    int yy = event->pos().y();
    points.push_back(mp(xx, yy));
    colors.push_back(rand() % 7);
    for (int i = 0; i < (int)points.size() - 1; ++i)
    {
        int dx = points[i].first - points[points.size() - 1].first;
        int dy = points[i].second - points[points.size() - 1].second;
        int d = dx * dx + dy * dy;
        if (d < dis)
        {
            ptx = i;
            pty = points.size() - 1;
            dis = d;
        }
    }
    repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearPoints()
{
    points.clear();
    colors.clear();
    ptx = 0;
    pty = 0;
    dis = 999999999;
    repaint();
}
