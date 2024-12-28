#ifndef Creator_H
#define Creator_H

#include "animal.h"
#include <QWidget>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QSpacerItem>

class Creator : public QWidget
{
    Q_OBJECT

public:
    explicit Creator(QWidget *parent = nullptr);
    void onReturnClicked();

signals:
    void CreatorClosed();
    void PushBackAnimal(animal *CurrentAnimal);

private slots:
    void onColorPickerClicked();
    void onBodyChanged(const int newBody);
    void onFaceChanged(const int newFace);
    void onEarChanged(const int newEar);
    void onStripeChanged(bool checked);
    void onBandanaChanged(bool checked);
    void onSaveClicked();

private:
    QLabel *creatureDisplay;
    QColorDialog *colorDialog;
    QComboBox *bodyShapeSelector;
    QComboBox *faceShapeSelector;
    QComboBox *earShapeSelector;
    QCheckBox *stripeOption;
    QCheckBox *bandanaOption;
    QPushButton *colorPickerButton;
    QPushButton *saveButton;
};

#endif
