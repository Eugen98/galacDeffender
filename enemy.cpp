#include "Enemy.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QTimer>
#include <stdlib.h> // Для rand()

Enemy::Enemy(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    // Устанавливаем изображение врага
    QPixmap enemyPixmap("D:/galacDeff/images/enemyl.png");
    setPixmap(enemyPixmap);

    // Случайная начальная позиция врага
    int randomX = rand() % 700;
    setPos(randomX, 0);

    // Таймер для движения врага
    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemy::move);
    moveTimer->start(50);  // Движение каждые 50 мс

    // Таймер для стрельбы врага
    QTimer *shootTimer = new QTimer(this);
    connect(shootTimer, &QTimer::timeout, this, &Enemy::shoot);
    shootTimer->start(2000);  // Стрельба каждые 2 секунды
}

void Enemy::move() {
    // Движение врага вниз
    setPos(x(), y() + 5);

    // Удаляем врага, если он выходит за нижний край экрана
    if (pos().y() > 600) {
        scene()->removeItem(this);
        delete this;
    }
}

void Enemy::shoot() {
    // Создаём пулю и устанавливаем её позицию
    Bullet *bullet = new Bullet();
    bullet->setPos(x() + pixmap().width() / 2 - bullet->pixmap().width() / 2, y() + pixmap().height());
    bullet->setDirection(1);  // Устанавливаем направление пули вниз
    scene()->addItem(bullet);
}
