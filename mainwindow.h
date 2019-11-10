#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <ctype.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <QMessageBox>
#include <QDebug>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    int add_score(string user_city);
    int a_new_presence(string user_city, string way_pr);
    string a_auto_city (string way, string way_pr);
    string add_city (string user_city, string way);
    int a_presence_check(string user_city, string way);
    string user_presence_check (char last_letter, string user_city, string way_pr);
    string weird_check (string user_city);
    void action()
    {
        QApplication::quit();
    }
    void new_game()
    {
        int comp_sc = 0, user_sc = 0;
        ui->user_sc_1->setText(QString::number(user_sc));
        ui->comp_sc_1->setText(QString::number(comp_sc));
        ui->auto_city_1->setText("Архангельск");
    }
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
