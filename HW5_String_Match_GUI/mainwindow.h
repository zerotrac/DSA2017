#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <random>
#include <iostream>
#include <fstream>
#include "stringmatch.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::random_device rd;
    std::mt19937 gen;

public slots:
    void showTextHelp();
    void showMatchHelp();
    void showSigmaHelp();
    void generateText();
    void generateMatch();
    void start();
};

#endif // MAINWINDOW_H
