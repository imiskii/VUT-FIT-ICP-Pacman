/**
 * @file GameItems.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for GameItems.cpp
 * 
 */

#ifndef GAMEITEMS_H
#define GAMEITEMS_H

#include <QPointF>
#include <QGraphicsAnchor>
#include <QBrush>
#include <QPropertyAnimation>
#include <QPen>
#include <QTimer>
#include <QPainter>
#include <utility>
#include "../consts.h"

class WallItem : public QGraphicsRectItem
{
public:
    WallItem(QPointF position, qreal &width, qreal &height);
    ~WallItem();
};


class PathItem : public QGraphicsRectItem
{
public:
    PathItem(QPointF position, qreal &width, qreal &height);
    ~PathItem();
};


class PacmanItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int spanAngle READ spanAngle WRITE setSpanAngle)


public:
    PacmanItem(QPointF position, qreal &width, qreal &height);
    ~PacmanItem();
    void moveTo(QPointF destPos, int speed, direction dr);
    static const int DEATH_ANIMATION_SPEED = 1500;
    void deathAnimation();


private:
    QPropertyAnimation *_moveAnimation;
    QPropertyAnimation *_mouthStartAnimation;
    QPropertyAnimation *_mouthSpanAnimation;
    direction _PacmanDirection;
    QPointF _prevPos;                            //< Store last position before movement
    QPointF _nextPos;                            //< Store last position where pacman wanted to move
    void _rotatePacman(direction dr);
    void _mouthAnimation(int speed);


signals:
    /**
     * @brief moveFinished signal to game view that pacman movement was finished
     */
    void moveFinished();


private slots:
    /**
     * @brief moveAnimationFinished handeling pacman movement animation
     */
    void moveAnimationFinished();

};


class GhostItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    GhostItem(QPixmap &pixmap, QPointF position, qreal &width, qreal &height, QGraphicsPixmapItem *parent = nullptr);
    ~GhostItem();
    void moveTo(QPointF desPos, int speed, direction dr);

private:
    QGraphicsPixmapItem *_ghostPixmapItem;
    QPropertyAnimation *_moveAnimation;

};


class KeyItem : public QGraphicsPixmapItem
{
public:
    KeyItem(QPixmap &pixmap, QPointF position, qreal &width, qreal &height, QGraphicsPixmapItem *parent = nullptr);
    ~KeyItem();
};



class TargetItem : public QGraphicsPixmapItem
{
public:
    TargetItem(QPixmap &pixmap, QPointF position, qreal &width, qreal &height, QGraphicsPixmapItem *parent = nullptr);
    ~TargetItem();
};

#endif // GAMEITEMS_H
