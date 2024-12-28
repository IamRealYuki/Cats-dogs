#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "animal.h"
#include "creator.h"
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QResizeEvent>
#include <QColorDialog>
#include <QFile>
#include <vector>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    protected:
        void resizeEvent(QResizeEvent *event);
        void load_font(QString font_name);
        QWidget *top_panel_init();
        void bg_image_init(QString bg_name);
        void init_buy_panel();
        void togglePanelVisibility();
        void onBuildButtonClicked(int value);
        void onVolumeChanged(int value);
        void init_menu();
        void toggleMenuVisibility();
        void toggleScreen();
        void saveAndExit();
        void openCreator();
        void returnToMain();
        void chooseColor();
        void load_animals(std::vector<animal> &animal_list);
        void startSimulation();
        void startAnimalThread(animal &animal);
        void moveAnimals();
        void decreaseLife();
        bool reachedTarget(QLabel *animalLabel, int targetX);
        void hideCats();
        void showCats();

private:
    Ui::MainWindow *ui;
    QLayout *buyHousePanel;
    QWidget *buyHousePanelWidget;
    animal *CurrentAnimal;
    QSqlDatabase db;

public slots:
    void CreatorClosed();
    void AnimalCatch(animal *currentAnimal);
};

#endif // MAINWINDOW_H
