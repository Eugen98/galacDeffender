#include <QApplication>
#include "Game.h"

// Глобальные указатели на две игры
Game *game1 = nullptr;
Game *game2 = nullptr;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Создаем объекты игры в куче
    game1 = new Game(true);
    game2 = new Game(false);

    // Устанавливаем положение окон (левое и правое)
    game1->move(0, 0);
    game2->move(900, 0);

    // Отображаем окна
    game1->show();
    game2->show();

    return a.exec();
}
