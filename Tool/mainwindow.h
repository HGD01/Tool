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

private slots:
    void on_OpenButter_clicked();

private slots:
   void ReadData();
   void on_CheckButton_clicked();
   void AnalysisConfig(QString str);
   void on_savebutton_clicked();

   void on_Clear_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
