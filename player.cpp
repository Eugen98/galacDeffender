#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

Player::Player(bool isPlayer1) : isPlayer1(isPlayer1) {
    // Загружаем текстуру в зависимости от игрока
    QPixmap playerPixmap(isPlayer1 ? "D:/galacDeff/images/playerl.png" : "D:/galacDeff/images/player2.png");

    if (playerPixmap.isNull()) {
        qDebug() << "Failed to load player image!";
    } else {
        qDebug() << "Player image loaded successfully.";
        setPixmap(playerPixmap);
    }

    // Инициализация звука для выстрела
    shootSound = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    shootSound->setAudioOutput(audioOutput);

    // Установка пути к звуковому файлу
    QString soundPath = isPlayer1 ? "D:/galacDeff/sound/shoot1.wav" : "D:/galacDeff/sound/shoot2.wav";
    shootSound->setSource(QUrl::fromLocalFile(soundPath));
    audioOutput->setVolume(0.5);

    // Проверка пути к звуковому файлу
    if (shootSound->source().isEmpty()) {
        qDebug() << "Failed to load shoot sound!";
    } else {
        qDebug() << "Shoot sound loaded from:" << soundPath;
    }
}

// Обработчик клавиш для движения и выстрела
void Player::keyPressEvent(QKeyEvent *event) {
    if (!scene()) return;

    qDebug() << "Key pressed:" << event->key();

    if (isPlayer1) {
        // Управление Игрока 1
        if (event->key() == Qt::Key_A && pos().x() > 0) {
            setPos(x() - 10, y());
            qDebug() << "Player 1 moved left.";
        } else if (event->key() == Qt::Key_D && pos().x() + pixmap().width() < 800) {
            setPos(x() + 10, y());
            qDebug() << "Player 1 moved right.";
        } else if (event->key() == Qt::Key_Space) {
            shoot();
        }
    } else {
        // Управление Игрока 2
        if (event->key() == Qt::Key_Left && pos().x() > 0) {
            setPos(x() - 10, y());
            qDebug() << "Player 2 moved left.";
        } else if (event->key() == Qt::Key_Right && pos().x() + pixmap().width() < 800) {
            setPos(x() + 10, y());
            qDebug() << "Player 2 moved right.";
        } else if (event->key() == Qt::Key_Return) {
            shoot();
        }
    }
}

// Функция для выстрела
void Player::shoot() {
    if (!scene()) return;

    qDebug() << "Shooting!";
    Bullet *bullet = new Bullet();
    bullet->setPos(x() + pixmap().width() / 2 - bullet->pixmap().width() / 2, y());
    scene()->addItem(bullet);
    qDebug() << "Bullet created at position:" << bullet->pos();

    // Воспроизведение звука выстрела
    if (shootSound->playbackState() == QMediaPlayer::PlayingState) {
        shootSound->stop();
    }
    shootSound->play();

    if (shootSound->error() != QMediaPlayer::NoError) {
        qDebug() << "Sound playback error:" << shootSound->errorString();
    } else {
        qDebug() << "Shoot sound played successfully.";
    }
}

// Функция уменьшения здоровья
void Player::decreaseHealth() {
    health--;
    qDebug() << "Player health decreased. Current health:" << health;

    if (health <= 0) {
        qDebug() << "Player died!";
        scene()->removeItem(this);
        delete this;
    }
}

// Функция спавна врагов
void Player::spawn() {
    Enemy *enemy = new Enemy();
    scene()->addItem(enemy);
    qDebug() << "Enemy spawned at position:" << enemy->pos();
}
