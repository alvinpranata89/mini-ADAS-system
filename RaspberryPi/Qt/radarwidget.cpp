#include "radarwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QDateTime>

RadarWidget::RadarWidget(QWidget *parent)
    : QWidget(parent)
{
    carImage.load(":img/car.png");
    backgroundImage.load(":img/bckgnd.jpg");

}

void RadarWidget::setDistances(int fl, int fr, int rl, int rr)
{
    frontLeft = fl;
    frontRight = fr;
    rearLeft = rl;
    rearRight = rr;

    update(); // repaint widget
}

QColor getColor(int distance)
{
    if(distance > 60)
        return QColor(0,255,0);   // green
    else if(distance > 11)
        return QColor(255,200,0); // yellow
    else
        return QColor(255,0,0);   // red
}

void RadarWidget::setSteering(float angle)
{
    steeringAngle = angle;
    update();
}

void RadarWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

     w = width();
     h = height();

    // ---------- CAR SIZE ----------
     carH = h * 0.35;
     carW = carH * 0.5;

    QRect carRect(
        w/2 - carW/2,
        h/2 - carH/2,
        carW,
        carH
        );

    // ---------- BACKGROUND ----------
    p.drawPixmap(rect(), backgroundImage);

    // ---------- RADAR SIZE ----------
    int radarOuter = carH * 0.8;
    int radarMid   = carH * 0.4;
    // int radarInner = carH * 0.3;

    // ---------- FRONT LEFT ----------

    QRect fl1(w/2 - radarOuter, h/2 - radarOuter-90, radarOuter, radarOuter);
    QRect fl2(w/2 - radarMid,   h/2 - radarMid-90,   radarMid-40,   radarMid-40);

    // QRect fl3(w/2 - radarInner, h/2 - radarInner-40, radarInner-80, radarInner-80);
    //     QRect frontLeftArc(w/2 - 150, h/2 - 200, 150, 150);
    //     QRect frontLeftArc2(w/2 - 135, h/2 - 185, 110, 110);
    //     QRect frontLeftArc3(w/2 - 120, h/2 - 170, 70, 70);

    // QColor c = getColor(frontLeft);
    // c.setAlpha(120);
    // p.setPen(QPen(c,5));



    p.setPen(QPen(getColor(frontLeft), 5));
    p.drawArc(fl1, 90 * 16, 90 * 16);
    p.drawArc(fl2, 90 * 16, 90 * 16);
    
    // p.drawArc(fl3, 90 * 16, 90 * 16);

    // ---------- FRONT RIGHT ----------
    QRect fr1(w/2, h/2 - radarOuter-90, radarOuter, radarOuter);
    QRect fr2(w/2+40, h/2 - radarMid-90,   radarMid-40,   radarMid-40);
    // QRect fr3(w/2+80, h/2 - radarInner-40, radarInner-80, radarInner-80);
    //     QRect frontRightArc(w/2, h/2 - 200, 150, 150);
    //     QRect frontRightArc2(w/2 + 25, h/2 - 185, 110, 110);
    //     QRect frontRightArc3(w/2 + 50, h/2 - 170, 70, 70);

    p.setPen(QPen(getColor(frontRight), 5));
    p.drawArc(fr1, 0 * 16, 90 * 16);
    p.drawArc(fr2, 0 * 16, 90 * 16);
    // p.drawArc(fr3, 0 * 16, 90 * 16);

    // ---------- REAR LEFT ----------
    QRect rl1(w/2 - radarOuter, h/2+100, radarOuter, radarOuter);
    QRect rl2(w/2 - radarMid,   h/2+120, radarMid-40, radarMid-40);
    // QRect rl3(w/2 - radarInner, h/2+120, radarInner-80, radarInner-80);

    //     QRect rearLeftArc(w/2 - 150, h/2 + 50, 150, 150);
    //     QRect rearLeftArc2(w/2 - 135, h/2 + 75, 110, 110);
    //     QRect rearLeftArc3(w/2 - 120, h/2 + 100, 70, 70);

    p.setPen(QPen(getColor(rearLeft), 5));
    p.drawArc(rl1, 180 * 16, 90 * 16);
    p.drawArc(rl2, 180 * 16, 90 * 16);
    // p.drawArc(rl3, 180 * 16, 90 * 16);

    // ---------- REAR RIGHT ----------
    QRect rr1(w/2, h/2+100, radarOuter, radarOuter);
    QRect rr2(w/2+40, h/2+120, radarMid-40, radarMid-40);
    // QRect rr3(w/2+80, h/2+120, radarInner-80, radarInner-80);
    //     QRect rearRightArc(w/2, h/2 + 50, 150, 150);
    //     QRect rearRightArc2(w/2 + 25, h/2 + 75, 110, 110);
    //     QRect rearRightArc3(w/2 + 50, h/2 + 100, 70, 70);
    p.setPen(QPen(getColor(rearRight), 5));
    p.drawArc(rr1, 270 * 16, 90 * 16);
    p.drawArc(rr2, 270 * 16, 90 * 16);
    // p.drawArc(rr3, 270 * 16, 90 * 16);

    // ---------- DRAW CAR ----------
    p.drawPixmap(carRect, carImage);
    drawTrajectory(p);
    
    p.setPen(QPen(QColor(255,255,255,80),2));

    p.drawLine(w/2-200, h/2+200, w/2-200, h/2-200);
    p.drawLine(w/2+200, h/2+200, w/2+200, h/2-200);

    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 14));

    QString text = QString("Rear: %1 cm").arg(rearRight);

    p.drawText(
        w/2 - 60,
        h/2 + carH + 40,
        text
        );

    drawObstacle(p, frontLeft,  w/2 - 120, h/2 - 140);
    drawObstacle(p, frontRight, w/2 + 60,  h/2 - 140);
    drawObstacle(p, rearLeft,   w/2 - 120, h/2 + 100);
    drawObstacle(p, rearRight,  w/2 + 60,  h/2 + 100);
}
void RadarWidget::drawObstacle(QPainter &p, int dist, int x, int y)
{
    // ---- CONFIG ----
    int maxDist = 175;      // max sensor range (cm)
    int maxPixel = 160;     // max visual distance (pixel)
    int minPixel = 10;       // jarak minimum dari body mobil (biar ga nembus)

    // ---- NORMALIZE DISTANCE ----
     float normalized = (float)dist / maxDist;
    // if (normalized > 1.0f) normalized = 1.0f;
    // if (normalized < 0.0f) normalized = 0.0f;

     // ---- CONVERT TO PIXEL OFFSET ----
     int offset = minPixel + normalized * (maxPixel - minPixel);

    if (dist < 30) {
        offset = minPixel + (dist / 30.0f) * 40;   // merah (padat, dekat)
    }
    else if (dist < 100) {
        offset = minPixel + 40 + ((dist - 30) / 70.0f) * 80; // kuning (lebih jauh)
    }
    else {
        offset = minPixel + 120 + ((dist - 100) / 75.0f) * 40; // hijau (relaxed)
    }

    // Non-linear biar lebih realistis (optional tapi recommended)
    normalized = normalized * normalized;



    // ---- DETERMINE DIRECTION ----
    int dx = 0;
    int dy = 0;

    int centerX = width() / 2;
    int centerY = height() / 2;

    // tentuin arah berdasarkan posisi sensor relatif ke tengah mobil
    if (x < centerX) dx = -offset;  // kiri
    else             dx =  offset;  // kanan

    if (y < centerY) dy = -offset;  // depan (atas)
    else             dy =  offset;  // belakang (bawah)

    // ---- FINAL POSITION ----
    int drawX = x + dx;
    int drawY = y + dy;

    // ---- DRAW ----
    QColor c = getColor(dist);
    p.setBrush(c);
    p.setPen(Qt::NoPen);

    // ukuran titik makin dekat makin besar
    int size = 8 + (maxDist - dist) / 5;
    if (size < 6) size = 6;
    if (size > 15) size = 15;

    p.drawEllipse(drawX, drawY, size, size);
}

void RadarWidget::drawTrajectory(QPainter &p)
{
    QColor glowColor(255, 51, 51);
    QColor glowColorW(255, 153, 153);
    float t = QDateTime::currentMSecsSinceEpoch() / 1000.0;
    float pulse = (sin(t * 7.0) + 1.0) / 2.0; // 0 ? 1
    int radius = 400;
    int angle = -(steeringAngle);

    // QPointF pivot(w/3 + 17 + radius, h/2 - 350 + radius);
    // int lineLength = 500;  // panjang garis merah
    
    // QPainterPath path;
    // path.moveTo(pivot);
    // // path.lineTo(pivot.x(), pivot.y() - lineLength);  // garis lurus ke atas (0°)
    // path.moveTo(pivot.x(), pivot.y() + lineLength * 0.25);
    // path.lineTo(pivot.x(), pivot.y() - lineLength * 0.75);
    // // Rotasi dari titik pivot sesuai nilai steering
    // QTransform transform;
    // transform.translate(pivot.x(), pivot.y());
    // transform.rotate(angle);  // -60 sampai +60 misalnya
    // transform.translate(-pivot.x(), -pivot.y());

    // p.save();
    // p.setTransform(transform);
    // p.drawPath(path);
    // p.restore();
    int carX1 = w/2-80;
    int carX2 = w/2 + 75;   // garis kanan, sesuaikan jaraknya
    int carFrontY = h/2;
    float offset = angle * 250.0f; 
    float trajectoryLength = h * 2.5f;  // 60% tinggi widget, sesuaikan

    auto drawGlowTrajectory = [&](int startX) {
        QPointF start(startX, carFrontY);
        QPointF end(startX + offset, carFrontY - trajectoryLength);
        QPointF ctrl1(startX,                  carFrontY - trajectoryLength * 0.8f);
        QPointF ctrl2(startX + offset * 9.0f,  carFrontY - trajectoryLength * 0.2f);

        QPainterPath path;
        path.moveTo(start);
        path.cubicTo(ctrl1, ctrl2, end);

        // outer
        glowColor.setAlpha(40 + pulse * 40);
        p.setPen(QPen(glowColor, 12));
        p.drawPath(path);

        // mid
        glowColor.setAlpha(80 + pulse * 80);
        p.setPen(QPen(glowColor, 8));
        p.drawPath(path);

        // inner
        glowColor.setAlpha(150 + pulse * 80);
        p.setPen(QPen(glowColorW, 5));
        p.drawPath(path);

        // core
        glowColor.setAlpha(190 + pulse * 35);
        p.setPen(QPen(glowColorW, 2));
        p.drawPath(path);
    };

    drawGlowTrajectory(carX1);
    drawGlowTrajectory(carX2);

    update();
}
