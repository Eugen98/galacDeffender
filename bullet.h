#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Bullet(QGraphicsItem *parent = nullptr);  // Конструктор
    void setDirection(int dir);  // Установка направления

public slots:
    void move();  // Движение пули

private:
    int direction;  // Направление пули (0 - вверх, 1 - вниз)
};

#endif // BULLET_H
