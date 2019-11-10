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
#include <QToolBar>
#include <QMenuBar>
#include <QAction>
using namespace std;

const std :: string path = "C:\\Coding\\Programms_C_C+\\\Kurs\\Test\\Base\\";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    const std :: string path = "C:\\Base\\";
    ui->setupUi(this);
    QMenu *file = menuBar()->addMenu("File");
    QMenu *Help = menuBar()->addMenu("Help");
    QMenu *Top = menuBar()->addMenu("Top");
    QAction *exit = new QAction(tr("Exit"),this);
    QAction *Back_to_menu = new QAction(tr("Back to menu"),this);
    QAction *new_game = new QAction(tr("New Game"),this);
    exit->setShortcut(tr("Ctrl+F"));
    file->addAction(new_game);
    file->addAction(Back_to_menu);
    file->addAction(exit);
    connect(new_game,SIGNAL(triggered()),this,SLOT(new_game()));
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

string MainWindow::weird_check (string user_city)
{
    int i;
    bool flag, flag1;
    flag1 = false;
    while (flag1 == false)
    {
        flag=true;
        for (i=0; i<user_city.size(); i++)
        {
            if (isdigit(user_city[i]))
                flag=false;
        }
        if (flag)
            flag1 = true;
        else
        {
            QMessageBox::about(this, "Information", "Enter correct city.");
            QString user_city = ui->user_city_1->text();
        }
    }
    return user_city;
}

string MainWindow::user_presence_check (char last_letter, string user_city, string way_pr)
{
    bool flag;
    char first_letter, b;
    string presence_city;
    flag = false;
    first_letter = user_city[0];
    b = tolower(first_letter);
    while ((b != last_letter) || (flag == false))
    {
        if (b != last_letter)
        {
            while (b != last_letter)
            {
                QMessageBox::about(this, "Information", "Enter correct city.");
                QString user_city = ui->user_city_1->text();
                //first_letter = user_city[0];
                b = tolower(first_letter);
            }
        }
        if (flag == false)
        {
            flag = true;
            ifstream a_pr(way_pr.c_str());
            while(getline(a_pr, presence_city))
            {
                if (user_city == presence_city)
                {
                    QMessageBox::about(this, "Information", "Such city has already been entered.");
                    QString user_city = ui->user_city_1->text();
                    flag = false;
                }
            }
        }
        first_letter = user_city [0];
        b = tolower(first_letter);
        if (b != last_letter)
        {
            QMessageBox::about(this, "Information", "Enter correct city.");
            QString user_city = ui->user_city_1->text();
            //first_letter = user_city[0];
            b = tolower(first_letter);
        }
    }
    return user_city;
}

int MainWindow::a_presence_check(string user_city, string way)
{
    string city;
    bool flag;
    ifstream a(way.c_str());
    flag=false;
    while(getline(a, city))
    {
        if (user_city == city)
        {
            flag = true;
        }
    }
    a.close();
    if (!flag)
        return 0;
    else
        return 1;
}

string MainWindow::add_city (string user_city, string way)
{
    QMessageBox::StandardButton proof = QMessageBox::question(this, "Information", "Are you sure?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (proof == QMessageBox::No)
    {
        QMessageBox::about(this, "Information", "Enter correct city.");
        QString user_city = ui->user_city_1->text();
    }
    ofstream a(way.c_str(), ios :: app);
    a << user_city << endl;
    a.close();
    return user_city;
}

string MainWindow::a_auto_city (string way, string way_pr)
{
    string new_city = "", presence_city;
    ifstream a(way.c_str());
    while (getline (a, new_city))
    {
        ifstream a_pr(way_pr.c_str());
        while(getline(a_pr, presence_city))
        {
            if (new_city == presence_city)
            {
                new_city = "";
                break;
            }
        }
        a_pr.close();
        if (new_city != "")
            break;
    }
    a.close();
    return new_city;
}

int MainWindow::a_new_presence(string user_city, string way_pr)
{
    string city;
    bool flag=false;
    ifstream a_pr(way_pr.c_str());
    while(getline(a_pr, city))
        if (user_city == city)
            flag = true;
    a_pr.close();
    if (!flag)
    {
        ofstream a_pr(way_pr.c_str(), ios :: app);
        a_pr << user_city << endl;
        a_pr.close();
    }
    return 0;
}

int MainWindow::add_score (string user_city)
{
    int sc;
    sc = user_city.size();
    return sc;
}

void MainWindow::on_pushButton_clicked()
{
    char first_letter, last_letter = 'ü';
    int c = 1, user_sc, comp_sc;
    string user_city, auto_city, way, way_pr, out;
    bool flag = false;
    while (c == 1)
    {
        if (flag == true)
        {
            QString user_city = ui->user_city_1->text();
        }
        if ((flag == true) && (user_city[0] == '\0'))
            break;
        if (flag == false)
        {
            QString user_city = ui->user_city_1->text();
            flag = true;
        }
        if (last_letter != 'ü')
        {
            way_pr = path + last_letter + "_presence.txt";
            user_city = user_presence_check(last_letter, user_city, way_pr);
        }
        else
            user_city = weird_check(user_city);
        first_letter = user_city[0];
        way_pr = path + first_letter + "_presence.txt";
        way = path + first_letter + ".txt";
        if (a_presence_check(user_city, way) == 0)
        {
            QMessageBox::about(this, "Information", "I don't know city like this.");
            user_city = add_city(user_city, way);
            break;
        }
        a_new_presence(user_city, way_pr);
        user_sc = user_sc + add_score(user_city);
        last_letter = user_city[(user_city.size() - 1)];
        if(last_letter == 'û' || last_letter == 'ü')
            last_letter = user_city[(user_city.size() - 2)];
        way_pr = path + last_letter + "_presence.txt";
        way = path + last_letter + ".txt";
        auto_city = a_auto_city(way, way_pr);
        user_city = auto_city;
        a_new_presence(user_city, way_pr);
        if (auto_city == "")
        {
            QMessageBox::about(this, "Information", "You win");
            break;
        }
        else
            //ui->auto_city_1->setText(QString auto_city);
        comp_sc = comp_sc + add_score(user_city);
        last_letter = auto_city[(auto_city.size() - 1)];
        if(last_letter == 'û' || last_letter == 'ü')
            last_letter = auto_city[(auto_city.size()- 2)];

    }
    ui->user_sc_1->setText(QString::number(user_sc));
    ui->comp_sc_1->setText(QString::number(comp_sc));
}
