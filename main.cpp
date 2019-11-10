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
#include <QTextCodec>
using namespace std;

const std :: string path = "C:\\Coding\\Programms_C_C+\\\Kurs\\Test\\Base\\";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    w.show();
    return a.exec();
}
