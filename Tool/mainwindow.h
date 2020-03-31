#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <extend.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenButter_clicked();

private slots:
   void ReadData();
   void on_CheckButton_clicked();
   void AnalysisConfig(QString str);
   void on_savebutton_clicked();
    void Delay_MSec_Suspend(unsigned int msec);
   void on_Clear_clicked();

   void on_Extend_clicked();

signals:
    void DisPlay(QString);
    void ClearRev(bool);
private:
    Ui::MainWindow *ui;
private:
    Extend * extend;
};
#endif // MAINWINDOW_H
