#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QUdpSocket>
#include <QMainWindow>
#include <QtSerialBus/QCanBusDevice>
#include "radarwidget.h" 

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readUdpData();

private:
    Ui::MainWindow *ui;
    QCanBusDevice *canDevice;    
    QUdpSocket *udpSocket;
    RadarWidget *radar;  
    int fl ;//= 100;
    int fr ;//= 100;
    int rl ;//= 100;
    int rr ;//=100;
};
#endif // MAINWINDOW_H
