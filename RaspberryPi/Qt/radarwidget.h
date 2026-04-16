#ifndef RADARWIDGET_H
#define RADARWIDGET_H
#include <QWidget>
#include <QPixmap>

class RadarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RadarWidget(QWidget *parent = nullptr);

    void setDistances(int fl, int fr, int rl, int rr);
    void setSteering(float angle);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int frontLeft = 100;
    int frontRight = 100;
    int rearLeft = 100;
    int rearRight = 100;
    int steeringAngle;

    int w;
    int h;
    int carW;
    int carH;

    void drawObstacle(QPainter &p, int dist, int x, int y);
    void drawTrajectory(QPainter &p);
    QPixmap carImage;
    QPixmap backgroundImage;
};
#endif// RADARWIDGET_H
