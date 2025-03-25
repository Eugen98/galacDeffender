#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include "Player.h"
#include "Enemy.h"  // Добавляем заголовок Enemy

class Game : public QGraphicsView {
    Q_OBJECT
public:
    explicit Game(bool isPlayer1, QWidget *parent = nullptr);

    void startGame();
    void increaseScore();
    void endGame();
    void showStartScreen();  // Добавляем объявление функции
    void shootBullet(Player *player);
    void spawnEnemy();

    static Game *game1;
    static Game *game2;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *gameScene;
    QGraphicsScene *startScene; // <-- Добавляем это
    Player *player;
    bool isPlayer1;
    int score;
    int currentLevel;
    bool isGameStarted;

    QGraphicsTextItem *scoreText;
    QGraphicsTextItem *levelText;

    QMediaPlayer *musicPlayer;
    QAudioOutput *audioOutput;

    QTimer *spawnTimer;
};

#endif // GAME_H
