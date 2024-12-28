#ifndef DRAWER_H
#define DRAWER_H

#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include "animal.h"

class Drawer
{
public:
    Drawer(const animal &animal);

    void UpdateSettings(const animal &animal);

    void updateAnimalImage(QLabel *animalLabel);

private:
    static const QString basePath;

    QString bodyBorderImage;
    QString bodyFillImage;
    QString faceImage;
    QString earImage;
    QString stripeImage;
    QString bandanaImage;
    QString color;
};

#endif
