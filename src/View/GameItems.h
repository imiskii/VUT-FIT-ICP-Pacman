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

/**
 * @brief The WallItem class graphical item representing wall
 */
class WallItem : public QGraphicsRectItem
{
public:
    /**
     * @brief WallItem constructor
     * @param position position on graphics scene
     * @param width width of the object
     * @param height height of the object
     */
    WallItem(QPointF position, qreal &width, qreal &height);
    ~WallItem();
};


/**
 * @brief The PathItem class graphical item representing path
 */
class PathItem : public QGraphicsRectItem
{
public:
    /**
     * @brief PathItem constructor
     * @param position position on graphics scene
     * @param width width of the object
     * @param height height of the object
     */
    PathItem(QPointF position, qreal &width, qreal &height);
    ~PathItem();
};


/**
 * @brief The PacmanItem class graphical item representing pacman
 */
class PacmanItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int spanAngle READ spanAngle WRITE setSpanAngle)

public:
    /**
     * @brief PacmanItem constructor
     * @param position position on graphics scene
     * @param width width of the object
     * @param height height of the object
     */
    PacmanItem(QPointF position, qreal &width, qreal &height);
    ~PacmanItem();
    /**
     * @brief moveTo move pacman on given destination position on map
     * @param destPos destination position on map
     * @param speed speed of moving
     * @param dr direction of movement
     */
    void moveTo(QPointF destPos, int speed, direction dr);
    /**
     * @brief DEATH_ANIMATION_SPEED constant value representing speed of pacman death animation in miliseconds
     */
    static const int DEATH_ANIMATION_SPEED = 1500;
    /**
     * @brief deathAnimation starts pacman death animation
     */
    void deathAnimation();

private:
    QPropertyAnimation *_moveAnimation;          ///< instance of QPropertyAnimation class for pacman move animations
    QPropertyAnimation *_mouthStartAnimation;    ///< instance of QPropertyAnimation class for pacman mouth animation
    QPropertyAnimation *_mouthSpanAnimation;     ///< instance of QPropertyAnimation class for pacman mouth animations
    direction _PacmanDirection;                  ///< current direction of pacman movement
    QPointF _prevPos;                            ///< last position before movement
    QPointF _nextPos;                            ///< last position where pacman wanted to move
    /**
     * @brief _rotatePacman rotate pacman to given direction
     * @param dr direction
     */
    void _rotatePacman(direction dr);
    /**
     * @brief _mouthAnimation starts pacman mouth animation
     * @param speed speed of animation
     */
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


/**
 * @brief The GhostItem class graphical item representing ghost
 */
class GhostItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    /**
     * @brief GhostItem constructor
     * @param pixmap pixel map of the ghost image
     * @param position position on graphics scene
     * @param width width of the object
     * @param height height of the object
     * @param parent parent item
     */
    GhostItem(QPixmap &pixmap, QPointF position, qreal &width, qreal &height, QGraphicsPixmapItem *parent = nullptr);
    ~GhostItem();
    /**
     * @brief moveTo move ghost on given destination position on map
     * @param destPos destination position on map
     * @param speed speed of moving
     * @param dr direction of movement
     */
    void moveTo(QPointF desPos, int speed);

    void freeze();

private:
    QGraphicsPixmapItem *_ghostPixmapItem;  ///< pixel map of ghost image
    QPropertyAnimation *_moveAnimation;     ///< instance of QPropertyAnimation class for ghost move animation

};


/**
 * @brief The KeyItem class graphical item representing Key
 */
class KeyItem : public QGraphicsPixmapItem
{
public:
    /**
     * @brief KeyItem
     * @param pixmap pixel map of the Key image
     * @param position position on graphics scene
     * @param width width of the object
     * @param height height of the object
     * @param parent parent item
     */
    KeyItem(QPixmap &pixmap, QPointF position, qreal &width, qreal &height, QGraphicsPixmapItem *parent = nullptr);
    ~KeyItem();
};



/**
 * @brief The TargetItem class graphical item representing Target point
 */
class TargetItem : public QGraphicsPixmapItem
{
public:
    /**
     * @brief TargetItem
     * @param pixmap pixel map of the target point image
     * @param position position on graphics scene
     * @param width width of the object
     * @param height height of the object
     * @param parent parent item
     */
    TargetItem(QPixmap &pixmap, QPointF position, qreal &width, qreal &height, QGraphicsPixmapItem *parent = nullptr);
    ~TargetItem();
};

#endif // GAMEITEMS_H

/* END OF FILE */
