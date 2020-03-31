#include "extend.h"
#include "ui_extend.h"
#include <string>
#include "mainwindow.h"
#include <QDebug>

bool Extend::extendflag = 0;
QByteArray Extend::RevBuff;
Extend::Extend(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Extend)
{
    ui->setupUi(this);
}


Extend::~Extend()
{
    Extend::extendflag == false;
    delete ui;
}
void Extend::DisplagRevData(QString)
{
    ui->RevText->append(Extend::RevBuff);
}
void Extend::ClearRevData(bool)
{
    ui->RevText->document()->clear();
}
