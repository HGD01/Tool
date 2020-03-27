#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <string>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QFile>
#include <QDir>
QString filepath;

QSerialPort * serial;

QString Debug = "AT+DEBUG=";
QString At ="AT+";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //ui->groupBox_3->setStyleSheet("background:transparent;border:2px solid red;");
    filepath = QDir::currentPath();//+"/default.text";
    ui->comnum->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {

        ui->comnum->addItem(info.portName());
    }
    QSerialPort serial;

}

MainWindow::~MainWindow()
{
    QString path = filepath +"/default.text";
    QFile::remove(path);
    delete ui;
}
//读取接收到的消息
void MainWindow::ReadData()
{
    QByteArray buf;

    buf=serial->readAll();

    if(!buf.isEmpty())
    {
        QString  path = filepath +"/default.text";
        QFile defaultfile(path);
        if(false == defaultfile.open(QIODevice::WriteOnly| QIODevice::Text |QIODevice::Append))
        {
            QMessageBox::about(NULL,"提示","文件打开失败!");
        }
        defaultfile.write(buf);

        defaultfile.close();
        QString str = buf;
        int num =str.indexOf(Debug);
        if(num != -1)
        {
            QString debug = str.mid(num);
            ui->DebugText->append(debug);
            debug = str.mid(Debug.length());
            AnalysisConfig(debug);
        }
        else
        {
            int at =str.indexOf(At);
            if(at != -1)
            {
                QString debug = str.mid(at);
                ui->U9507E_AT_Text->append(debug);
            }
        }
    }
    serial->clear();
    buf.clear();
}

void MainWindow::on_OpenButter_clicked()
{


    if(ui->OpenButter->text() == "开启")
    {
        serial = new QSerialPort;

        serial->setPortName(ui->comnum->currentText());
        if(false == serial->open(QIODevice::ReadOnly)) //开启只读
        {
            QMessageBox::about(NULL,"提示","无法打开串口!");
            return ;
        }

        serial->setParity(QSerialPort::NoParity); //校验
        serial->setDataBits(QSerialPort::Data8); //数据位
        switch (ui->bond->currentIndex())
        {
        case 0 :
            serial->setBaudRate(QSerialPort::Baud115200);
        break;
        case 1 :
            serial->setBaudRate(QSerialPort::Baud9600);
        break;
        default:
            serial->setBaudRate(QSerialPort::Baud115200);
        }
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        ui->DebugText->setEnabled(true);
        ui->savebutton->setEnabled(true);
        ui->Clear->setEnabled(true);

        QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::ReadData);

        ui->OpenButter->setText("关闭");
    }
    else
    {
        serial->clear();
        serial->close();
        serial->deleteLater();
        ui->savebutton->setEnabled(false);
        ui->Clear->setEnabled(false);
        ui->OpenButter->setText("开启");
    }
}


void MainWindow::AnalysisConfig(QString str)
{

    QString name;
    QJsonParseError json_error;

    QJsonDocument parse_doucment = QJsonDocument::fromJson(str.toUtf8(), &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if (parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            if(obj.contains("cmd")) //
            {
                QJsonValue name_value = obj.take("cmd"); //解析命令
                if (name_value.isString())
                {
                    name = name_value.toString();
                    if(name == "login")
                    {
                        name_value = obj.take("b_m");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->b_m->setText(name);
                        }

                        name_value = obj.take("w_s");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->w_s->setText(name);
                        }

                        name_value = obj.take("l_d");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->l_d->setText(name);
                        }

                        name_value = obj.take("l_r");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->l_r->setText(name);
                        }

                        name_value = obj.take("c_b");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->c_b->setText(name);
                        }

                        name_value = obj.take("g_i");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->g_i->setText(name);
                        }

                        name_value = obj.take("l_g");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->l_g->setText(name);
                        }

                        name_value = obj.take("s_t");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->s_t->setText(name);
                        }

                        name_value = obj.take("e_d");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->e_d->setText(name);
                        }

                        name_value = obj.take("s_s");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->s_s->setText(name);
                        }

                        name_value = obj.take("s_o");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->s_o->setText(name);
                        }

                        name_value = obj.take("s_r");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->s_r->setText(name);
                        }

                        name_value = obj.take("s_d");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->s_d->setText(name);
                        }

                        name_value = obj.take("t_s");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->t_s->setText(name);
                        }

                        name_value = obj.take("t_r");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->t_r->setText(name);
                        }

                        name_value = obj.take("t_d");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->t_d->setText(name);
                        }

                        name_value = obj.take("c_s");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->c_s->setText(name);
                        }

                        name_value = obj.take("c_o");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->c_o->setText(name);
                        }

                        name_value = obj.take("c_r");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->c_r->setText(name);
                        }

                        name_value = obj.take("c_d");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->c_d->setText(name);
                        }

                        name_value = obj.take("t_oh");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->t_oh->setText(name);
                        }

                        name_value = obj.take("t_oz");
                        if (name_value.isDouble())
                        {
                            double name1 = name_value.toDouble();
                            name = QString::number(name1, 'f', 0);
                            ui->t_oz->setText(name);
                        }
                        name_value = obj.take("apn");
                        if (name_value.isString())
                        {
                            name = name_value.toString();
                            ui->apn->setText(name);
                        }
                    }
                    else if(name == "infor")
                    {
                        name_value = obj.take("ve");
                        if (name_value.isString())
                        {
                            name = name_value.toString();
                            ui->version->setText(name);
                        }

                        name_value = obj.take("im");
                        if (name_value.isString())
                        {
                            name = name_value.toString();
                            ui->imei->setText(name);
                        }
                        name_value = obj.take("sn");
                        if (name_value.isString())
                        {
                            name = name_value.toString();
                            ui->sn->setText(name);
                        }
                        name_value = obj.take("ic");
                        if (name_value.isString())
                        {
                            name = name_value.toString();
                            ui->iccid->setText(name);
                        }

                        name_value = obj.take("fu");
                        if (name_value.isDouble())
                        {
                            int name1 = (int)name_value.toDouble();
                            if(name1>>0 & 1)ui->Lsm6dsl->setCheckState(Qt::Checked);
                            else ui->Lsm6dsl->setCheckState(Qt::Unchecked);

                            if(name1>>1 & 1)ui->Log->setCheckState(Qt::Checked);
                            else ui->Log->setCheckState(Qt::Unchecked);

                            if(name1>>2 & 1)ui->RTC->setCheckState(Qt::Checked);
                            else ui->RTC->setCheckState(Qt::Unchecked);

                            ui->iccid->setText(name);
                        }
                    }
                    else if(name == "log")
                    {
                         name_value = obj.take("i_n");
                         if (name_value.isDouble())
                         {
                             double num = name_value.toDouble();
                             name = QString::number(num, 'f', 0);
                             ui->Important_Now->setText(name);
                         }
                         name_value = obj.take("i_t");
                         if (name_value.isDouble())
                         {
                             double num = name_value.toDouble();
                             name = QString::number(num, 'f', 0);
                             ui->Important_Total->setText(name);
                         }

                         name_value = obj.take("n_n");
                         if (name_value.isDouble())
                         {
                             double num = name_value.toDouble();
                             name = QString::number(num, 'f', 0);
                             ui->Normal_Now->setText(name);
                         }
                         name_value = obj.take("n_t");
                         if (name_value.isDouble())
                         {
                             double num = name_value.toDouble();
                             name = QString::number(num, 'f', 0);
                             ui->Normal_Total->setText(name);
                         }
                    }
                    else if(name == "euler")
                    {
                        name_value = obj.take("p");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();
                            name = QString::number(num, 'f', 0);
                            ui->pitch->setText(name);
                        }
                        name_value = obj.take("y");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();
                            name = QString::number(num, 'f', 0);
                            ui->yaw->setText(name);
                        }
                        name_value = obj.take("r");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();
                            name = QString::number(num, 'f', 0);
                            ui->roll->setText(name);
                        }
                    }
                    else if(name == "offset")
                    {
                        name_value = obj.take("p");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();
                            name = QString::number(num, 'f', 0);
                            ui->pitch_off->setText(name);
                        }
                        name_value = obj.take("y");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();
                            name = QString::number(num, 'f', 0);
                            ui->yaw_off->setText(name);
                        }
                        name_value = obj.take("r");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();
                            name = QString::number(num, 'f', 0);
                            ui->roll_off->setText(name);
                        }
                    }
                    else if(name == "status")
                    {
                        name_value = obj.take("c");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();

                            if(num)ui->carsh->setCheckState(Qt::Checked);
                            else ui->carsh->setCheckState(Qt::Unchecked);
                        }

                        name_value = obj.take("b");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();

                            if(num)ui->bluetooth->setCheckState(Qt::Checked);
                            else ui->bluetooth->setCheckState(Qt::Unchecked);
                        }

                        name_value = obj.take("l");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();

                            if(num)ui->lock->setCheckState(Qt::Checked);
                            else ui->lock->setCheckState(Qt::Unchecked);
                        }

                        name_value = obj.take("s");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();

                            if(num)ui->stop->setCheckState(Qt::Checked);
                            else ui->stop->setCheckState(Qt::Unchecked);
                        }

                        name_value = obj.take("r");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();

                            if(num)ui->recharge->setCheckState(Qt::Checked);
                            else ui->recharge->setCheckState(Qt::Unchecked);
                        }

                        name_value = obj.take("n");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();

                            if(num)ui->net->setCheckState(Qt::Checked);
                            else ui->net->setCheckState(Qt::Unchecked);
                        }

                        name_value = obj.take("p");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();
                            name = QString::number(num, 'f', 0);
                            ui->power->setText(name);
                        }
                        name_value = obj.take("q");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();
                            name = QString::number(num, 'f', 0);
                            ui->csq->setText(name);
                        }
                        name_value = obj.take("w");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();
                            name = QString::number(num, 'f', 0);
                            ui->zhuwang->setText(name);
                        }
                        name_value = obj.take("f");
                        if (name_value.isDouble())
                        {
                            double num = name_value.toDouble();
                            name = QString::number(num, 'f', 0);
                            ui->fsm->setText(name);
                        }

                        name_value = obj.take("t");
                        if (name_value.isString())
                        {
                            QString num = name_value.toString();
                            ui->time->setText(num);
                        }

                    }

                }
            }
        }

    }
}

void MainWindow::on_CheckButton_clicked()
{

}

void MainWindow::on_savebutton_clicked()
{
    QString savename = ui->savename->text();
    if(QString(savename).isEmpty())
    {
        QMessageBox::about(NULL,"提示","请输入一个文件名!");
        return ;
    }
    if(true == QFile::copy("default.text",savename))
    {
        QMessageBox::about(NULL,"提示","保存成功!");
        return ;
    }
    else
    {
        QMessageBox::about(NULL,"提示","保存失败!");
        return ;
    }
}

void MainWindow::on_Clear_clicked()
{
    ui->DebugText->document()->clear();
    ui->U9507E_AT_Text->document()->clear();
    QString path = filepath +"/default.text";
    QFile::remove(path);
}
