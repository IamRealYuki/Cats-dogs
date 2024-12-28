#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creator.h"
#include "drawer.h"
#include <QPixmap>
#include <QResizeEvent>
#include <QSpacerItem>
#include <QFontDatabase>
#include <iostream>
#include <QDebug>
#include <string>
#include <QSlider>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QStackedWidget>
#include <QImage>
#include <QPainter>
#include <QApplication>
#include <QMultimedia>
#include <QSqlQuery>
#include <QTimer>
#include <QThread>
#include <QPropertyAnimation>

bool aging = 0;
int houses = 0;
int max_pets = 1;
std::vector<animal> animal_list;
std::vector<QLabel*> animal_labels;
std::vector<int> targetCoordinates;

void MainWindow:: saveAndExit()
{
    std:: cout << "saved";
    close();
}
void MainWindow::load_font(QString font_name)
{
    QFontDatabase fontDatabase;
    int fontId = fontDatabase.addApplicationFont(":/font/fonts/" + font_name);
    if (fontId != -1) {
        QString fontFamily = fontDatabase.applicationFontFamilies(fontId).at(0);
        QFont pixelFont(fontFamily);
        pixelFont.setPixelSize(20);
        QApplication::setFont(fontFamily);
    } else {
        std::cout << "Font loading failed!";
    }

}

void MainWindow::load_animals(std::vector<animal> &animal_list)
{
    QSqlQuery query;
    query.exec("SELECT face, body, stripes, ears, bandana, color, lifespan FROM animals");

    while (query.next()) {
        int face = query.value(0).toInt();
        int body = query.value(1).toInt();
        bool stripes = query.value(2).toBool();
        int ears = query.value(3).toInt();
        bool bandana = query.value(4).toBool();
        QString color = query.value(5).toString();
        int lifespan = query.value(6).toInt();
        animal *loaded_animal = new animal(face, body, stripes, ears, bandana, color.toStdString(), lifespan);
        animal_list.push_back(*loaded_animal);
    }
}

QWidget *MainWindow::top_panel_init()
{
    QWidget *topPanelWidget = new QWidget(this);
    QHBoxLayout *topPanelLayout = new QHBoxLayout(this);
    QWidget *spacer = new QWidget(this);

    topPanelLayout->addWidget(ui->creatorbtn, 1);
    topPanelLayout->addWidget(ui->buildbtn, 1);
    topPanelLayout->addWidget(spacer, 3);
    topPanelLayout->addWidget(ui->menubtn, 1);
    topPanelWidget->setLayout(topPanelLayout);

    ui->creatorbtn->setStyleSheet("QPushButton {"
                                  "border: none;"
                                  "background: transparent;"
                                  "border-image: url(:/img/img/button_texture.jpg) stretch stretch;"
                                  "font-size: 30px;"
                                  "min-width: 180px;"
                                  "min-height: 50px;"
                                  "color: white;"
                                  "}");

    ui->buildbtn->setStyleSheet("QPushButton {"
                                  "border: none;"
                                  "background: transparent;"
                                  "border-image: url(:/img/img/button_texture.jpg) stretch stretch;"
                                  "font-size: 30px;"
                                  "min-width: 270px;"
                                  "min-height: 50px;"
                                  "color: white;"
                                  "}");

    ui->menubtn->setStyleSheet("QPushButton {"
                                  "border: none;"
                                  "background: transparent;"
                                  "border-image: url(:/img/img/button_texture.jpg) stretch stretch;"
                                  "font-size: 25px;"
                                  "min-width: 50px;"
                                  "min-height: 50px;"
                                  "color: white;"
                                  "}");
    return topPanelWidget;
}

void MainWindow::bg_image_init(QString bg_name)
{
    QPixmap pixmap(":/img/img/" + bg_name);
    ui->bg_label->setPixmap(pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding));
    ui->bg_label->setGeometry(0, 0, this->size().width(), this->size().height());
}

void MainWindow::onBuildButtonClicked(int value)
{
        QPixmap pixmap(":img/img/house" + QString::number(value));
        switch(houses)
        {
            case 0:
            {
                ui->house1->setVisible(true);
                ui->house1->setPixmap(pixmap);
                break;
            }
            case 1:
            {
                ui->house2->setVisible(true);
                ui->house2->setPixmap(pixmap);
                break;
            }

            case 2:
            {
                ui->house3->setVisible(true);
                ui->house3->setPixmap(pixmap);
                break;
            }
            case 3:
            {
                ui->house4->setVisible(true);
                ui->house4->setPixmap(pixmap);
                break;
            }
            case 4:
            {
                ui->house5->setVisible(true);
                ui->house5->setPixmap(pixmap);
                break;
            }
        }
        houses++;
        max_pets +=2;
}

void MainWindow::init_buy_panel()
{
    buyHousePanelWidget = new QWidget(this);
    QHBoxLayout *buyHousePanel = new QHBoxLayout();
    QVBoxLayout *firstLayout = new QVBoxLayout();

    QLabel *houseImageLabel1 = new QLabel(this);
    houseImageLabel1->setObjectName("houseImageLabel1");
    QPixmap housePixmap1(":/img/img/house1.png");
    if (housePixmap1.isNull()) {
        qDebug() << "Ошибка: Не удалось загрузить картинку домика!";
    }
    housePixmap1 = housePixmap1.scaled(this->size().width()/5, this->size().height()/5, Qt::KeepAspectRatio);
    houseImageLabel1->setPixmap(housePixmap1);
    houseImageLabel1->setAlignment(Qt::AlignCenter);
    houseImageLabel1->setAutoFillBackground(false);
    houseImageLabel1->setStyleSheet("background: transparent;");

    QPushButton *buildButton = new QPushButton("Построить", this);
    buildButton->setStyleSheet("QPushButton {"
                                  "border: none;"
                                  "background: transparent;"
                                  "border-image: url(:/img/img/button_texture.jpg) stretch stretch; "
                                  "font-size: 20px;"
                                  "color: white;"
                                  "}");
    buildButton->installEventFilter(this);
    connect(buildButton, &QPushButton::clicked, this, [this](){
            onBuildButtonClicked(1);
    });

    firstLayout->addWidget(houseImageLabel1);
    firstLayout->addWidget(buildButton);

    QVBoxLayout *secondLayout = new QVBoxLayout();

    QLabel *houseImageLabel2 = new QLabel(this);
    houseImageLabel2->setObjectName("houseImageLabel2");
    QPixmap housePixmap2(":/img/img/house2.png");
    if (housePixmap2.isNull()) {
        qDebug() << "Ошибка: Не удалось загрузить картинку домика!";
    }
    housePixmap2 = housePixmap2.scaled(this->size().width()/5, this->size().height()/5, Qt::KeepAspectRatio);
    houseImageLabel2->setPixmap(housePixmap2);
    houseImageLabel2->setAlignment(Qt::AlignCenter);
    houseImageLabel2->setAutoFillBackground(false);
    houseImageLabel2->setStyleSheet("background: transparent;");

    QPushButton *buildButton1 = new QPushButton("Построить", this);
    buildButton1->setStyleSheet("QPushButton {"
                                  "border: none;"
                                  "background: transparent;"
                                  "border-image: url(:/img/img/button_texture.jpg) stretch stretch; "
                                  "font-size: 20px;"
                                  "color: white;"
                                  "}");

    connect(buildButton1, &QPushButton::clicked, this, [this](){
            onBuildButtonClicked(2);
    });
    secondLayout->addWidget(houseImageLabel2);
    secondLayout->addWidget(buildButton1);

    QSpacerItem *spacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    buyHousePanel->addItem(spacer1);
    buyHousePanel->addLayout(firstLayout);
    QSpacerItem *spacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    buyHousePanel->addItem(spacer2);
    buyHousePanel->addLayout(secondLayout);
    QSpacerItem *spacer3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    buyHousePanel->addItem(spacer3);

    QPushButton *exitButton = new QPushButton(this);
    exitButton->setStyleSheet("QPushButton {"
                                  "border-image: url(:/img/img/cross.png) stretch stretch; "
                                  "}");
    exitButton->setFixedWidth(30);
    exitButton->setFixedHeight(30);

    connect(exitButton, &QPushButton::clicked, this, &MainWindow::togglePanelVisibility);
    buyHousePanel->addWidget(exitButton, 0, Qt::AlignTop);
    buyHousePanel->setStretch(0,4);
    buyHousePanel->setStretch(1,4);
    buyHousePanel->setStretch(2,4);
    buyHousePanel->setStretch(3,4);
    buyHousePanel->setStretch(4,4);
    buyHousePanel->setStretch(5,1);
    buyHousePanelWidget->setStyleSheet("background-image: url(:/img/img/panel_texture.jpg);"
                                       "background-position: center;");
    buyHousePanelWidget->setLayout(buyHousePanel);
    buyHousePanelWidget->setVisible(false);
    ui->centralWidget->layout()->setContentsMargins(0, 0, 0, 0);
    ui->centralWidget->layout()->addWidget(buyHousePanelWidget);
}

void MainWindow::init_menu()
{
QWidget* menuWidget = new QWidget(this);
menuWidget->setObjectName("menuWidget");


menuWidget->setFixedSize(this->size().width() / 4, this->size().height() / 3 + 50);


menuWidget->setStyleSheet("QWidget#menuWidget {"
                          "background-image: url(:/img/img/panel_texture.jpg);"
                          "background-position: center;"
                          "background-size: cover;"
                          "}");

QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);
menuLayout->setContentsMargins(20, 20, 20, 20);
menuLayout->setSpacing(15);

QSlider *volumeSlider = new QSlider(Qt::Horizontal, menuWidget);
volumeSlider->setRange(0, 100);
volumeSlider->setValue(50);
volumeSlider->setTickPosition(QSlider::TicksBelow);
volumeSlider->setTickInterval(10);

QWidget *sliderWidget = new QWidget(this);
QVBoxLayout *sliderLayout = new QVBoxLayout(this);
QLabel *sliderLabel = new QLabel("Громкость", this);
sliderLabel->setStyleSheet("color: white;");

sliderLayout->addWidget(sliderLabel);
sliderLayout->addWidget(volumeSlider);

sliderWidget->setLayout(sliderLayout);


connect(volumeSlider, &QSlider::valueChanged, this, &MainWindow::onVolumeChanged);

menuLayout->addWidget(sliderWidget);

QGroupBox *groupBox = new QGroupBox("", menuWidget);
groupBox->setStyleSheet("QGroupBox { border: none; }");
QVBoxLayout *checkboxLayout = new QVBoxLayout(groupBox);

QCheckBox *checkBox1 = new QCheckBox("Полный экран", groupBox);
QCheckBox *checkBox2 = new QCheckBox("Старение", groupBox);
connect(checkBox1, &QCheckBox::toggled, this, &MainWindow::toggleScreen);
connect(checkBox2, &QCheckBox::toggled, this, []() {
    aging = !aging;
    std::cout << "aging: " << aging << std::endl;
});
checkBox1->setChecked(false);
checkBox2->setChecked(false);
checkBox1->setStyleSheet("QCheckBox { color: lightgray; }");
checkBox2->setStyleSheet("QCheckBox { color: lightgray; }");

checkboxLayout->addWidget(checkBox1);
checkboxLayout->addWidget(checkBox2);
menuLayout->addWidget(groupBox);

QPushButton *saveExitButton = new QPushButton("Сохранить и выйти", menuWidget);
connect(saveExitButton, &QPushButton::clicked, this, &MainWindow::saveAndExit);
menuLayout->addWidget(saveExitButton);

menuWidget->move((this->width() - menuWidget->width()) / 2,
                 (this->height() - menuWidget->height()) / 2);
menuWidget->setVisible(false);
}



void MainWindow::toggleScreen()
{
    if(this->isFullScreen()){
        this->showNormal();
    }
    else {
        this->showFullScreen();
        QResizeEvent *event = new QResizeEvent(this->size(), this->size());
        resizeEvent(event);
        delete event;
    }
}

void MainWindow::onVolumeChanged(int value)
{
    qDebug() << "Изменена громкость: " << value;
}

void MainWindow::toggleMenuVisibility()
{
    QWidget* tmp = this->findChild<QWidget*>("menuWidget");
    if (tmp) {
        qDebug() << "Переключаем видимость панели.";
        tmp->setVisible(!tmp->isVisible());
    } else {
        qDebug() << "Ошибка: menuPanel не существует!";
    }
}

void MainWindow::togglePanelVisibility()
{
    if (buyHousePanel) {
        qDebug() << "Переключаем видимость панели.";
        if(!buyHousePanelWidget->isVisible())
        {
            hideCats();
        }
        else {
            showCats();
        }
        buyHousePanelWidget->setVisible(!buyHousePanelWidget->isVisible());
    } else {
        qDebug() << "Ошибка: buyHousePanelContainer не существует!";
    }
}

void MainWindow::startSimulation() {
    QTimer *lifeTimer = new QTimer(this);
    connect(lifeTimer, &QTimer::timeout, this, &MainWindow::decreaseLife);
    lifeTimer->start(5000);

    targetCoordinates.resize(animal_list.size());

    // Запускаем таймер для обновления позиции животных
    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &MainWindow::moveAnimals);
    moveTimer->start(1000 / 60); // Обновляем каждый кадр (60 раз в секунду)

    // Если вектор пустой, создаем лейблы для всех животных
    for (size_t i = 0; i < animal_list.size(); i++) {
        QLabel *animalLabel = nullptr;

        // Если лейбл для текущего животного не существует, создаем новый
        if (animal_labels.size() <= i) {
            animalLabel = new QLabel(this);
            animalLabel->setObjectName("animalLabel");
            animalLabel->setFixedSize(200, 200);

            // Отображаем изображение животного
            Drawer drawer(animal_list[i]);
            drawer.updateAnimalImage(animalLabel);
            animalLabel->setPixmap(animalLabel->pixmap()->scaled(animalLabel->size(), Qt::KeepAspectRatio));

            // Начальная случайная позиция
            int xPos = rand() % (ui->animalWidget->width() - 200);  // Учитываем ширину родительского виджета
            int yPos = this->size().height() * 75 / 100;  // Позиция по оси Y

            animalLabel->move(xPos, yPos);  // Устанавливаем позицию лейбла внутри родительского виджета
            animalLabel->show();  // Отображаем лейбл

            animal_labels.push_back(animalLabel);  // Добавляем лейбл в список
        } else {
            animalLabel = animal_labels[i];
        }

        // Изначальная случайная цель для животного
        targetCoordinates[i] = rand() % (ui->animalWidget->width() - 200);  // Обновляем для родительского виджета
    }
}

void MainWindow::moveAnimals() {
    int stepSize = 5;  // Шаг, с которым будет двигаться животное

    // Для каждого животного проверяем его движение
    for (size_t i = 0; i < animal_list.size(); ++i) {
        QLabel *animalLabel = nullptr;

        // Если лейбл для текущего животного не существует, создаем новый
        if (animal_labels.size() <= i) {
            animalLabel = new QLabel(this);
            animalLabel->setObjectName("animalLabel");
            animalLabel->setFixedSize(200, 200);

            // Отображаем изображение животного
            Drawer drawer(animal_list[i]);
            drawer.updateAnimalImage(animalLabel);
            animalLabel->setPixmap(animalLabel->pixmap()->scaled(animalLabel->size(), Qt::KeepAspectRatio));

            int xPos = rand() % (ui->animalWidget->width() - 200);
            int yPos = this->size().height() * 75 / 100;

            animalLabel->move(xPos, yPos);
            animalLabel->show();
            animal_labels.push_back(animalLabel);  // Добавляем лейбл в список
        } else {
            animalLabel = animal_labels[i];
        }

        QPoint currentPos = animalLabel->pos();
        int targetX = targetCoordinates[i];

        // Мягкая проверка на достижение цели
        if (abs(currentPos.x() - targetX) > stepSize) {
            if (currentPos.x() < targetX) {
                animalLabel->move(currentPos.x() + stepSize, currentPos.y());
            } else if (currentPos.x() > targetX) {
                animalLabel->move(currentPos.x() - stepSize, currentPos.y());
            }
        } else {
            // Когда цель почти достигнута, выбираем новую
            targetCoordinates[i] = rand() % (animalLabel->parentWidget()->width() - 200);  // Новая цель
        }
    }
}

void MainWindow::decreaseLife() {
    if(!aging)
      {
        std::cout << "Aging off. No death";
        return;
      }
    for (auto it = animal_list.begin(); it != animal_list.end(); ) {
        it->setLifespan(it->getLifespan() - 1);

        if (it->getLifespan() <= 0) {
            // Очищаем животное и его изображение
            delete animal_labels[std::distance(animal_list.begin(), it)];
            animal_labels.erase(animal_labels.begin() + std::distance(animal_list.begin(), it));

            it = animal_list.erase(it);
        } else {
            ++it;
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:/Qt-labs/kurs/CatsAndHomes/db.db");

        if (!db.open()) {
            std::cout << "Ошибка! Не удалось подключиться к базе данных!";
            exit(1);
        }

    load_font("Monocraft.otf");
    load_animals(animal_list);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(top_panel_init(), 2, Qt::AlignTop);
    centralWidget()->setLayout(mainLayout);

    bg_image_init("bg.jpg");
    init_buy_panel();
    init_menu();
    ui->house1->setVisible(false);
    ui->house2->setVisible(false);
    ui->house3->setVisible(false);
    ui->house4->setVisible(false);
    ui->house5->setVisible(false);
    if(animal_list.size() != 0)
        startSimulation();

    connect(ui->buildbtn, &QPushButton::clicked, this, &MainWindow::togglePanelVisibility);
    connect(ui->menubtn, &QPushButton::clicked, this, &MainWindow::toggleMenuVisibility);
    connect(ui->creatorbtn, &QPushButton:: clicked, this, &MainWindow::openCreator);
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->centralWidget->layout());
    if (!layout) {
        layout = new QVBoxLayout(ui->centralWidget);
        ui->centralWidget->setLayout(layout);
    }

    Creator *newCreatorWidget = new Creator(this);
    newCreatorWidget->setObjectName("CreatorWindow");
    newCreatorWidget->hide();
    newCreatorWidget->move(0, 0);
    newCreatorWidget->setGeometry(0, 0, this->width(), this->height());
    layout->addWidget(newCreatorWidget);
    connect(newCreatorWidget, &Creator::CreatorClosed, this, &MainWindow::CreatorClosed);
    connect(newCreatorWidget, &Creator::PushBackAnimal, this, &MainWindow::AnimalCatch);
}

void MainWindow::openCreator()
{
    ui->creatorbtn->hide();
    ui->menubtn->hide();
    ui->buildbtn->hide();
    ui->bg_label->hide();
    buyHousePanelWidget->setVisible(false);
    this->findChild<QWidget*>("menuWidget")->setVisible(false);
    this->findChild<Creator*>("CreatorWindow")->show();
    hideCats();
}

void MainWindow::CreatorClosed()
{
    ui->creatorbtn->show();
    ui->menubtn->show();
    ui->buildbtn->show();
    ui->bg_label->show();
    this->findChild<Creator*>("CreatorWindow")->hide();
    showCats();
}

void MainWindow::hideCats()
{
    QList<QLabel*> labels = this->findChildren<QLabel*>("animalLabel");
    for(int i = 0; i < animal_list.size(); i++)
    {
        labels[i]->hide();
    }
}

void MainWindow::showCats()
{
    QList<QLabel*> labels = this->findChildren<QLabel*>("animalLabel");
    for(int i = 0; i < animal_list.size(); i++)
    {
        labels[i]->show();
    }
}

void MainWindow::AnimalCatch(animal* animal)
{
    if(animal_list.size() == 0)
    {
        animal_list.push_back(*animal);
        startSimulation();
    }
    else {
        animal_list.push_back(*animal);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap pixmap(":/img/img/bg.jpg");
    ui->bg_label->setPixmap(pixmap.scaled(event->size(), Qt::KeepAspectRatioByExpanding));
    ui->bg_label->setGeometry(0, 0, this->width(), this->height());
    ui->bg_label->lower();
    ui->house1->move(this->width()*0, this->height()*7/10);
    ui->house2->move(width()/12*3, height()*75/100);
    ui->house3->move(width()/12*6, height()*7/10);
    ui->house4->move(width()/12*8, height()*7/10);
    ui->house5->move(width()/12*10, height()*75/100);
    ui->house1->setFixedSize(width()/6, height()/4);
    ui->house2->setFixedSize(width()/6, height()/5);
    ui->house3->setFixedSize(width()/5, height()/4);
    ui->house4->setFixedSize(width()/6, height()/4);
    ui->house5->setFixedSize(width()/7, height()/5);

    buyHousePanelWidget->setFixedSize(this->width(), this->height()*3/10);

    QPixmap label1pix(":/img/img/house1.png");
    QPixmap label2pix(":/img/img/house2.png");
    label1pix = label1pix.scaled(this->size().width()/5, this->size().height()/5, Qt::KeepAspectRatio);
    label2pix = label2pix.scaled(this->size().width()/5, this->size().height()/5, Qt::KeepAspectRatio);
    this->findChild<QLabel*>("houseImageLabel1")->setPixmap(label1pix);
    this->findChild<QLabel*>("houseImageLabel2")->setPixmap(label2pix);

    QWidget *menuWidget = this->findChild<QWidget*>("menuWidget");
    menuWidget->move((this->width() - this->size().width() / 4) / 2, (this->height() - this->size().height() / 3) / 2);
    menuWidget->setFixedSize(this->size().width() / 4, this->size().height() / 3);

    this->findChild<Creator*>("CreatorWindow")->setFixedSize(this->size());
    QList<QLabel*> labels = this->findChildren<QLabel*>("animalLabel");
    for (size_t i = 0; i < animal_list.size(); i++) {
        targetCoordinates[i] = rand() % (event->size().width() - 200);
        int yPos = this->size().height() * 75 / 100;  // Позиция по оси Y
        labels[i]->move(labels[i]->pos().x(), yPos);
    }
    QMainWindow::resizeEvent(event);
}
