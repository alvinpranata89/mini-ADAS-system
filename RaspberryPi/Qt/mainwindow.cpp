#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include "radarwidget.h"
#include <QTimer>
#include <cstdlib>
#include <QtSerialBus/QCanBus>
#include <QtSerialBus/QCanBusFrame>
#include <QUdpSocket>

QUdpSocket *udpSocket;

void MainWindow::readUdpData()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());

        udpSocket->readDatagram(datagram.data(), datagram.size());

        float gyro = datagram.toFloat();

        // DEBUG dulu
        //qDebug() << "GYRO:" << gyro;

        // kirim ke radar
        radar->setSteering(gyro);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   // ui->setupUi(this);
    // resize(800,600);
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 12345);

    connect(udpSocket, &QUdpSocket::readyRead,
        this, &MainWindow::readUdpData);
        
    //showMaximized();
    showFullScreen();
    
    //RadarWidget *radar = new RadarWidget(this);
    //setCentralWidget(radar);

    radar = new RadarWidget(this);
    setCentralWidget(radar);

    canDevice = QCanBus::instance()->createDevice("socketcan", "can0");

    if (!canDevice) {
        qDebug() << "CAN device not created";
        return;
    }
    canDevice->setConfigurationParameter(
        QCanBusDevice::BitRateKey,
        QVariant()
        );
    if (!canDevice->connectDevice()) {
        qDebug() << "CAN connect failed";
        return;
    }

   /*  connect(canDevice, &QCanBusDevice::framesReceived, this, [=]() {
         while (canDevice->framesAvailable()) {

             QCanBusFrame frame = canDevice->readFrame();

             if (frame.frameId() == 0x129) {
                 QByteArray data = frame.payload();

                 if (data.size() >= 2) {
                     uint16_t distance =
                         ((uint8_t)data[0] << 8) |
                         (uint8_t)data[1];

                     qDebug() << "Distance:" << distance;

                     this->dist =
                         ((uint8_t)data[0] << 8) |
                         (uint8_t)data[1];

                     // update UI
                     ui->label->setText(QString::number(distance) + " cm");
                 }
             }
         }
     });

     QLabel *label = new QLabel("ADAS Parking Assist", this);
     label->setAlignment(Qt::AlignCenter);
     setCentralWidget(label);

     QTimer *timer = new QTimer(this);

     connect(timer, &QTimer::timeout, [=]() {

          int fl = rand() % 90;
         int fr = rand() % 200;
         int rl = rand() % 70;
         int rr = rand() % 100;

         radar->setDistances(fl, fr, rl, rr);

     });

     timer->start(1000);

     connect(canDevice, &QCanBusDevice::framesReceived, this, [=]() {
     int fl,fr,rl,rr;
         while (canDevice->framesAvailable()) {

             QCanBusFrame frame = canDevice->readFrame();

             QByteArray data = frame.payload();

             if (data.size() < 2) return;

             uint16_t dist =
                 ((uint8_t)data[0] << 8) |
                 (uint8_t)data[1];

             switch (frame.frameId()) {
             case 0x129: fl = dist; break;
             case 0x130: fr = dist; break;
             case 0x131: rl = dist; break;
             case 0x132: rr = dist; break;
             }

             radar->setDistances(fl, fr, rl, rr);
         }
     });*/

    connect(canDevice, &QCanBusDevice::framesReceived, this, [=]() {
    // int fl,fr,rl,rr;
        while (canDevice->framesAvailable()) {

            QCanBusFrame frame = canDevice->readFrame();

            QByteArray data = frame.payload();

            if (data.size() < 2)
                continue;

            uint16_t dist =
                ((uint8_t)data[0] << 8) |
                (uint8_t)data[1];

            // DEBUG (optional)
            qDebug() << "FRAME:"
                     << "ID=0x" + QString::number(frame.frameId(), 16).toUpper()
                     << "DIST=" << dist;

            // UPDATE STATE
            switch (frame.frameId()) {
            case 0x120: fl = dist; break;
            case 0x121: fr = dist; break;
            case 0x122: rl = dist; break;
            case 0x123: rr = dist; break;
            }
        }

        // 🔥 UPDATE UI SEKALI (setelah semua frame diproses)
        radar->setDistances(fl, fr, rl, rr);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

// #include "mainwindow.h"
// #include "./ui_mainwindow.h"
// #include <QLabel>

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
// {
//     QLabel *label = new QLabel("ADAS Parking Assist", this);
//     label->setAlignment(Qt::AlignCenter);
//     setCentralWidget(label);
// }
