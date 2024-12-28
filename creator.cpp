#include "Creator.h"
#include "animal.h"
#include "drawer.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <iostream>

animal *CurrentAnimal = new animal(0, 0, 0, 0, 0, "white", 5);
Drawer drawer(*CurrentAnimal);

Creator::Creator(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *mainPart = new QHBoxLayout(this);

    QWidget *spacerWidget = new QWidget(this);

    creatureDisplay = new QLabel("", this);
    creatureDisplay->setAlignment(Qt::AlignCenter);
    creatureDisplay->setStyleSheet("background-color: #f4f4f4;");


    mainPart->addWidget(creatureDisplay, 2);

    QVBoxLayout *editorLayout = new QVBoxLayout();

    QVBoxLayout *colorPickerLayout = new QVBoxLayout(this);
    QLabel *colorPickerText = new QLabel("цвет", this);
    colorPickerText->setAlignment(Qt::AlignCenter);
    colorPickerText->adjustSize();

    colorPickerButton = new QPushButton("", this);
    colorPickerButton->setFixedSize(25, 25);
    colorPickerButton->setStyleSheet("background-color: white;");
    connect(colorPickerButton, &QPushButton::clicked, this, &Creator::onColorPickerClicked);

    colorPickerLayout->addWidget(colorPickerButton);
    colorPickerLayout->addWidget(colorPickerText);

    QWidget *colorPickerButtonWidget = new QWidget(this);
    colorPickerButtonWidget->setLayout(colorPickerLayout);

    colorPickerButtonWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    editorLayout->addWidget(colorPickerButtonWidget, 1);

    QVBoxLayout *bodyShapeLayout = new QVBoxLayout(this);
    QLabel *bodyShapeLabel = new QLabel("Форма тела", this);
    bodyShapeLabel->setAlignment(Qt::AlignCenter);
    bodyShapeLabel->adjustSize();

    bodyShapeSelector = new QComboBox(this);
    bodyShapeSelector->addItems({"тип 1", "тип 2"});
    connect(bodyShapeSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(onBodyChanged(int)));

    bodyShapeLayout->addWidget(bodyShapeSelector);
    bodyShapeLayout->addWidget(bodyShapeLabel);

    QWidget *bodyShapeWidget = new QWidget(this);
    bodyShapeWidget->setLayout(bodyShapeLayout);
    bodyShapeWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    editorLayout->addWidget(bodyShapeWidget, 1);

    QVBoxLayout *faceShapeLayout = new QVBoxLayout(this);
    QLabel *faceShapeLabel = new QLabel("тип морды", this);
    faceShapeLabel->setAlignment(Qt::AlignCenter);
    faceShapeLabel->adjustSize();

    faceShapeSelector = new QComboBox(this);
    faceShapeSelector->addItems({"тип 1", "тип 2", "тип 3"});
    connect(faceShapeSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(onFaceChanged(int)));

    faceShapeLayout->addWidget(faceShapeSelector);
    faceShapeLayout->addWidget(faceShapeLabel);

    QWidget *faceShapeWidget = new QWidget(this);
    faceShapeWidget->setLayout(faceShapeLayout);
    faceShapeWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    editorLayout->addWidget(faceShapeWidget, 1);

    QVBoxLayout *earShapeLayout = new QVBoxLayout(this);
    QLabel *earShapeLabel = new QLabel("тип ушей", this);
    earShapeLabel->setAlignment(Qt::AlignCenter);
    earShapeLabel->adjustSize();

    earShapeSelector = new QComboBox(this);
    earShapeSelector->addItems({"тип 1", "тип 2", "тип 3"});
    connect(earShapeSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(onEarChanged(int)));

    earShapeLayout->addWidget(earShapeSelector);
    earShapeLayout->addWidget(earShapeLabel);

    QWidget *earShapeWidget = new QWidget(this);
    earShapeWidget->setLayout(earShapeLayout);
    earShapeWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    editorLayout->addWidget(earShapeWidget, 1);

    QVBoxLayout *additionalLayout = new QVBoxLayout(this);
    QLabel *additionalLabel = new QLabel("Дополнительно", this);
    additionalLabel->setAlignment(Qt::AlignCenter);
    additionalLabel->adjustSize();

    QHBoxLayout *checkboxLayout = new QHBoxLayout();
    stripeOption = new QCheckBox("Полоски", this);
    bandanaOption = new QCheckBox("Бандана", this);
    connect(stripeOption, &QCheckBox::toggled, this, &Creator::onStripeChanged);
    connect(bandanaOption, &QCheckBox::toggled, this, &Creator::onBandanaChanged);

    checkboxLayout->addWidget(stripeOption);
    checkboxLayout->addWidget(bandanaOption);

    additionalLayout->addWidget(additionalLabel);
    additionalLayout->addLayout(checkboxLayout);

    QWidget *additionalWidget = new QWidget(this);
    additionalWidget->setLayout(additionalLayout);
    additionalWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    editorLayout->addWidget(additionalWidget, 1);

    saveButton = new QPushButton("Сохранить!", this);
    connect(saveButton, &QPushButton::clicked, this, &Creator::onSaveClicked);

    QPushButton *returnButton = new QPushButton("Вернуться", this);
    connect(returnButton, &QPushButton::clicked, this, &Creator::onReturnClicked);

    QHBoxLayout *saveButtonLayout = new QHBoxLayout(this);

    saveButtonLayout->addWidget(spacerWidget, 3);
    saveButtonLayout->addWidget(saveButton, 2);
    saveButtonLayout->addWidget(returnButton, 1);
    saveButtonLayout->addWidget(spacerWidget, 3);

    QWidget *SaveButtonWidget = new QWidget(this);
    SaveButtonWidget->setLayout(saveButtonLayout);

    mainPart->addLayout(editorLayout, 2);
    QWidget *mainPartWidet = new QWidget(this);
    mainPartWidet->setLayout(mainPart);

    mainLayout->addWidget(mainPartWidet, 8);

    mainLayout->addWidget(SaveButtonWidget, 1);

    drawer.updateAnimalImage(creatureDisplay);
}

void Creator::onColorPickerClicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Pick Creature Color");
    if (color.isValid()) {
        QString colorStyle = QString("background-color: %1;").arg(color.name());
        colorPickerButton->setStyleSheet(colorStyle);
        CurrentAnimal->setColor(color.name().toStdString());
    }
    drawer.UpdateSettings(*CurrentAnimal);
    drawer.updateAnimalImage(creatureDisplay);
}

void Creator::onBodyChanged(const int type)
{
    CurrentAnimal->setBody(type);
    drawer.UpdateSettings(*CurrentAnimal);
    drawer.updateAnimalImage(creatureDisplay);
}

void Creator::onFaceChanged(const int type)
{
    CurrentAnimal->setFace(type);
    drawer.UpdateSettings(*CurrentAnimal);
    drawer.updateAnimalImage(creatureDisplay);
}

void Creator::onEarChanged(const int type)
{
    CurrentAnimal->setEars(type);
    drawer.UpdateSettings(*CurrentAnimal);
    drawer.updateAnimalImage(creatureDisplay);
}

void Creator::onStripeChanged(bool checked)
{
    CurrentAnimal->setStripes(checked);
    drawer.UpdateSettings(*CurrentAnimal);
    drawer.updateAnimalImage(creatureDisplay);
}

void Creator::onBandanaChanged(bool checked)
{
    CurrentAnimal->setBandana(checked);
    drawer.UpdateSettings(*CurrentAnimal);
    drawer.updateAnimalImage(creatureDisplay);
}

void Creator::onSaveClicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO animals (face, body, stripes, ears, bandana, color, lifespan) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");

    query.addBindValue(CurrentAnimal->getFace());
    query.addBindValue(CurrentAnimal->getBody());
    query.addBindValue(CurrentAnimal->getStripes());
    query.addBindValue(CurrentAnimal->getEars());
    query.addBindValue(CurrentAnimal->getBandana());
    query.addBindValue(QString::fromStdString(CurrentAnimal->getColor()));
    query.addBindValue(CurrentAnimal->getLifespan());

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
    } else {
        qDebug() << "Query executed successfully";
    }
    emit CreatorClosed();
    emit PushBackAnimal(CurrentAnimal);
}

void Creator::onReturnClicked()
{
    emit CreatorClosed();
}
