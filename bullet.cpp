#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

extern Game *game1;
extern Game *game2;

Bullet::Bullet(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), direction(0) {
    // Устанавливаем изображение для пули
    QPixmap bulletPixmap("D:/galacDeff/images/bullet.png");
    if (bulletPixmap.isNull()) {
        qDebug() << "Failed to load bullet image!";
    } else {
        setPixmap(bulletPixmap);
    }

    // Таймер для движения пули
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50);  // Движение каждые 50 мс
}

void Bullet::setDirection(int dir) {
    direction = dir;  // Устанавливаем направление пули
}

void Bullet::move() {
    if (!scene()) {
        qDebug() << "Bullet: No scene, skipping move";
        return;
    }

    // Проверяем столкновения
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (QGraphicsItem *item : colliding_items) {
        if (direction == 0) {  // Пуля игрока
            Enemy *enemy = dynamic_cast<Enemy *>(item);
            if (enemy) {
                qDebug() << "Bullet hit enemy! Removing enemy and bullet.";

                // Увеличиваем счет обоих игроков
                if (game1) {
                    game1->increaseScore();
                }
                if (game2) {
                    game2->increaseScore();
                }

                // Удаляем врага
                if (enemy->scene()) {
                    scene()->removeItem(enemy);
                    enemy->deleteLater();
                }

                // Удаляем пулю
                if (scene()) {
                    scene()->removeItem(this);
                    this->deleteLater();
                }
                return;
            }
        } else if (direction == 1) {  // Пуля врага
            Player *player = dynamic_cast<Player *>(item);
            if (player) {
                qDebug() << "Bullet hit player! Decreasing health.";

                player->decreaseHealth();

                // Удаляем пулю
                if (scene()) {
                    scene()->removeItem(this);
                    this->deleteLater();
                }
                return;
            }
        }
    }

    // Движение пули
    if (direction == 0) {
        setPos(x(), y() - 10);  // Пуля летит вверх
    } else if (direction == 1) {
        setPos(x(), y() + 10);  // Пуля летит вниз
    }

    // Удаление пули, если она выходит за пределы экрана
    if (pos().y() + pixmap().height() < 0 || pos().y() > scene()->height()) {
        qDebug() << "Bullet out of bounds, removing from scene.";
        if (scene()) {
            scene()->removeItem(this);
            this->deleteLater();
        }
    }
}
