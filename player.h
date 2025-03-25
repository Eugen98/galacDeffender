#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Player(bool isPlayer1);
    void decreaseHealth();
    void spawn();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void shoot();
    int health = 3;
    bool isPlayer1;

    // Звук для выстрела
    QMediaPlayer *shootSound;
    QAudioOutput *audioOutput;
};

#endif // PLAYER_H
