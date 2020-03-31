#ifndef EXTEND_H
#define EXTEND_H

#include <QMainWindow>

namespace Ui {
class Extend;
}

class Extend : public QMainWindow
{
    Q_OBJECT

public:
    explicit Extend(QWidget *parent = nullptr);
    ~Extend();
public:

    static bool extendflag;
    static QByteArray RevBuff;
private:
    Ui::Extend * ui;

private slots:
    void DisplagRevData(QString);
    void ClearRevData(bool);
};



#endif // EXTEND_H
