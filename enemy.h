#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Enemy(QGraphicsItem *parent = nullptr);

public slots:
    void move();  // Движение врага
    void shoot(); // Стрельба врага
};

#endif // ENEMY_H
