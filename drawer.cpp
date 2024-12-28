#include "drawer.h"
#include <iostream>

const QString Drawer::basePath = ":/img/img/";

Drawer::Drawer(const animal &animal)
{
    bodyBorderImage = basePath + "body_border_" + QString::number(animal.getBody()) + ".png";
    bodyFillImage = basePath + "body_fill_" + QString::number(animal.getBody()) + ".png";
    faceImage = basePath + "face_" + QString::number(animal.getFace()) + ".png";
    earImage = basePath + "ears_" + QString::number(animal.getEars()) + ".png";
    if(animal.getStripes() != 0) {
        stripeImage = basePath + "stripes.png";
    }
    else {
        stripeImage = "";
    }
    if(animal.getBandana() != 0) {
        bandanaImage = basePath + "bandana.png";
    }
    else {
        bandanaImage = "";
    }
    color = QString::fromStdString(animal.getColor());
}

void Drawer::UpdateSettings(const animal &animal)
{
    bodyBorderImage = basePath + "body_border_" + QString::number(animal.getBody()) + ".png";
    bodyFillImage = basePath + "body_fill_" + QString::number(animal.getBody()) + ".png";
    faceImage = basePath + "face_" + QString::number(animal.getFace()) + ".png";
    earImage = basePath + "ears_" + QString::number(animal.getEars()) + ".png";
    if(animal.getStripes() != 0) {
        stripeImage = basePath + "stripes.png";
    }
    else {
        stripeImage = "";
    }
    if(animal.getBandana() != 0) {
        bandanaImage = basePath + "bandana.png";
    }
    else {
        bandanaImage = "";
    }
    color = QString::fromStdString(animal.getColor());
}

void Drawer::updateAnimalImage(QLabel *animalLabel)
{
    std::cout << "updating sprite" << std::endl;
    QPixmap finalImage(bodyBorderImage);

    QPainter painter(&finalImage);

    if (!color.isEmpty()) {
            QColor animalColor(color);
            painter.drawPixmap(0, 0, finalImage);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(finalImage.rect(), animalColor.darker(200));
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        }

    QPixmap border(bodyFillImage);
    QPainter bpainter(&border);
    bpainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    bpainter.fillRect(finalImage.rect(), QColor(color));
    bpainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, border);

    QPixmap facePix(faceImage);
    painter.drawPixmap(0, 0, facePix);

    QPixmap earPix(earImage);
    painter.drawPixmap(0, 0, earPix);

    if (!stripeImage.isEmpty()) {
        QPixmap stripePix(stripeImage);
        QPainter spainter(&stripePix);
        spainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        spainter.fillRect(finalImage.rect(), QColor(color).darker(200));
        spainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(0, 0, stripePix);
    }

    if (!bandanaImage.isEmpty()) {
        QPixmap bandanaPix(bandanaImage);
        painter.drawPixmap(0, 0, bandanaPix);
    }

    painter.end();
    animalLabel->clear();
    animalLabel->setPixmap(finalImage);
}
