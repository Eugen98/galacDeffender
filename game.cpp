#include "Enemy.h"
#include "Game.h"
#include "Bullet.h"
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QPixmap>
#include <QDebug>
#include <QTimer>

Game *Game::game1 = nullptr;
Game *Game::game2 = nullptr;

Game::Game(bool isPlayer1, QWidget *parent)
    : QGraphicsView(parent), score(0), currentLevel(1), isGameStarted(false) {

    startScene = new QGraphicsScene(this);
    setScene(startScene);
    setFixedSize(800, 600);
    startScene->setSceneRect(0, 0, 800, 600);

    if (isPlayer1) {
        player = new Player(true);
        player->setPos(200, 500);
        game1 = this;  // Присваиваем указатель глобальной переменной
    } else {
        player = new Player(false);
        player->setPos(600, 500);
        game2 = this;  // Присваиваем указатель глобальной переменной
    }

    musicPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl::fromLocalFile("D:/galacDeff/sound/start_music.wav"));
    audioOutput->setVolume(0.5);

    showStartScreen();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void Game::showStartScreen() {
    startScene = new QGraphicsScene(this);
    setScene(startScene);
    startScene->setSceneRect(0, 0, 800, 600);

    QPixmap background("D:/galacDeff/images/start_background.png");
    startScene->setBackgroundBrush(background);

    QGraphicsTextItem *titleText = new QGraphicsTextItem("Galactic Defender");
    QFont titleFont("Arial", 36);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(Qt::white);
    titleText->setPos(200, 250);
    startScene->addItem(titleText);

    QGraphicsTextItem *instructionText = new QGraphicsTextItem("Press Enter to Start");
    QFont instructionFont("Arial", 18);
    instructionText->setFont(instructionFont);
    instructionText->setDefaultTextColor(Qt::white);
    instructionText->setPos(250, 350);
    startScene->addItem(instructionText);

    // Воспроизводим музыку стартового экрана
    if (musicPlayer) {
        musicPlayer->play();
    }
}

void Game::startGame() {
    if (musicPlayer->playbackState() == QMediaPlayer::PlayingState) {
        musicPlayer->stop();
    }

    gameScene = new QGraphicsScene(this);
    setScene(gameScene);
    gameScene->setSceneRect(0, 0, 800, 600);

    QPixmap background("D:/galacDeff/images/game_background.png");
    gameScene->setBackgroundBrush(background);

    gameScene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scoreText = new QGraphicsTextItem("Score: 0");
    scoreText->setFont(QFont("Arial", 16));
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setPos(10, 10);
    gameScene->addItem(scoreText);

    levelText = new QGraphicsTextItem("Level: 1");
    levelText->setFont(QFont("Arial", 16));
    levelText->setDefaultTextColor(Qt::yellow);
    levelText->setPos(10, 30);
    gameScene->addItem(levelText);

    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &Game::spawnEnemy);
    spawnTimer->start(3000);

    isGameStarted = true;
}

void Game::spawnEnemy() {
    Enemy *enemy = new Enemy();
    enemy->setPos(rand() % 700 + 50, 0);
    gameScene->addItem(enemy);
    qDebug() << "Enemy spawned!";
}

void Game::shootBullet(Player *player) {
    if (!player) return;

    Bullet *bullet = new Bullet();
    bullet->setPos(player->x() + player->pixmap().width() / 2 - bullet->pixmap().width() / 2, player->y());
    gameScene->addItem(bullet);

    qDebug() << "Bullet shot from player at position:" << player->pos();
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (!isGameStarted) {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            startGame();
        }
        return;
    }

    if (player) {
        if (isPlayer1) {
            if (event->key() == Qt::Key_A && player->pos().x() > 0) {
                player->setPos(player->x() - 10, player->y());
            } else if (event->key() == Qt::Key_D && player->pos().x() + player->pixmap().width() < 800) {
                player->setPos(player->x() + 10, player->y());
            } else if (event->key() == Qt::Key_Space) {
                shootBullet(player);
            }
        } else {
            if (event->key() == Qt::Key_Left && player->pos().x() > 0) {
                player->setPos(player->x() - 10, player->y());
            } else if (event->key() == Qt::Key_Right && player->pos().x() + player->pixmap().width() < 800) {
                player->setPos(player->x() + 10, player->y());
            } else if (event->key() == Qt::Key_Return) {
                shootBullet(player);
            }
        }
    }
}

void Game::increaseScore() {
    score += 10;
    scoreText->setPlainText("Score: " + QString::number(score));

    if (score % 100 == 0) {
        currentLevel++;
        levelText->setPlainText("Level: " + QString::number(currentLevel));
        spawnTimer->setInterval(spawnTimer->interval() * 0.9);
    }
}

void Game::endGame() {
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem("Game Over\nScore: " + QString::number(score));
    QFont gameOverFont("Arial", 36);
    gameOverText->setFont(gameOverFont);
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setPos(200, 250);
    gameScene->addItem(gameOverText);

    isGameStarted = false;
    if (spawnTimer) {
        spawnTimer->stop();
    }
}
