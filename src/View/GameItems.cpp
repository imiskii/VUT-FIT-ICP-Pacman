/**
 * @file GameItems.cpp
 * @author Michal Ľaš (xlasmi00)
 * @brief Items graphical presented in game field/map
 */

#include "GameItems.h"


WallItem::WallItem(QPointF position, qreal &width, qreal &height) : QGraphicsRectItem(position.x(), position.y(), width, height)
{
    this->setPen(QPen(Qt::black));
    this->setBrush(QBrush(QColor("#355070")));
}


WallItem::~WallItem()
{

}


/***************************************************************/


PathItem::PathItem(QPointF position, qreal &width, qreal &height) : QGraphicsRectItem(position.x(), position.y(), width, height)
{
    this->setPen(QPen(Qt::NoPen));
    this->setBrush(QBrush(QColor("#7FB069")));
}


PathItem::~PathItem()
{


}


/***************************************************************/


PacmanItem::PacmanItem(QPointF position, qreal &width, qreal &height) : QObject(), QGraphicsEllipseItem(position.x(), position.y(), width, height)
{
    // Pacman is moving object so it has to be on top of game field objects
    this->setZValue(1);
    // body
    this->setPen(QPen(Qt::NoPen));
    this->setBrush(QBrush(QColor("#F7D002")));
    this->setSpanAngle(270 * 16);
    this->setStartAngle(45 * 16);
    // mouth animation / death animation
    this->_mouthStartAnimation = new QPropertyAnimation(this, "startAngle");
    this->_mouthStartAnimation->setEasingCurve(QEasingCurve::Linear);
    this->_mouthSpanAnimation = new QPropertyAnimation(this, "spanAngle");
    this->_mouthSpanAnimation->setEasingCurve(QEasingCurve::Linear);
    // First set it for mouth animation
    this->_mouthStartAnimation->setStartValue(this->startAngle());
    this->_mouthStartAnimation->setEndValue(0);
    this->_mouthSpanAnimation->setStartValue(this->spanAngle());
    this->_mouthSpanAnimation->setEndValue(360 * 16);
    // move animation
    this->_moveAnimation = new QPropertyAnimation(this, "pos");
    this->_moveAnimation->setEasingCurve(QEasingCurve::Linear);
    // rotation
    this->setTransformOriginPoint(QPointF(this->rect().center().x(), this->rect().center().y()));

    connect(this->_moveAnimation, &QPropertyAnimation::finished, this, &PacmanItem::moveAnimationFinished);
}


PacmanItem::~PacmanItem()
{
    delete this->_moveAnimation;
    delete this->_mouthStartAnimation;
    delete this->_mouthSpanAnimation;
}

void PacmanItem::moveTo(QPointF destPos, int speed, direction dr)
{
    static int movementProgress; // store animation time that remains to complete the full pacman step
    // Change direction during movement
    if (this->_moveAnimation->state() == QAbstractAnimation::Running)
    {
        // Change only if it is different direction
        if (dr != this->_PacmanDirection)
        {
            // if it is NORT <-> SOUTH or WEST <-> EAST (diagonal movement is not alowed)
            if ((this->_prevPos.x() == destPos.x()) || (this->_prevPos.y() == destPos.y()))
            {
                // stop current animation
                this->_moveAnimation->stop();
                // set animation speed to time of progress that previous animation has done
                movementProgress += this->_moveAnimation->currentTime();
                this->_moveAnimation->setDuration(movementProgress);

                this->_moveAnimation->setEndValue(this->_prevPos);
                // change next and prev position values
                std::swap(this->_nextPos, this->_prevPos);
                // flip movement progress for possible next direction change
                movementProgress = speed - movementProgress;
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    // Pacman is not moving
    else
    {
        movementProgress = 0; // reset animation time
        this->_prevPos = this->pos();
        this->_nextPos = destPos;
        this->_moveAnimation->setDuration(speed);
        this->_moveAnimation->setEndValue(destPos);
    }
    this->_rotatePacman(dr);
    this->_moveAnimation->start();
    this->_mouthAnimation(speed);
}

void PacmanItem::moveAnimationFinished()
{
    emit moveFinished();
}


void PacmanItem::_mouthAnimation(int speed)
{
    speed = speed/2;
    this->_mouthStartAnimation->setDuration(speed);
    this->_mouthSpanAnimation->setDuration(speed);
    this->_mouthStartAnimation->setDirection(QAbstractAnimation::Forward);
    this->_mouthSpanAnimation->setDirection(QAbstractAnimation::Forward);

    this->_mouthStartAnimation->start();
    this->_mouthSpanAnimation->start();

    QTimer::singleShot(speed, this, [=](){
        this->_mouthStartAnimation->setDirection(QAbstractAnimation::Backward);
        this->_mouthSpanAnimation->setDirection(QAbstractAnimation::Backward);
        this->_mouthStartAnimation->start();
        this->_mouthSpanAnimation->start();
    });
}

void PacmanItem::deathAnimation()
{
    _moveAnimation->stop();
    _mouthStartAnimation->stop();
    _mouthSpanAnimation->stop();
    this->_mouthStartAnimation->setEndValue(180 *16);
    this->_mouthSpanAnimation->setEndValue(0);
    _mouthStartAnimation->setDirection(QAbstractAnimation::Forward);
    _mouthSpanAnimation->setDirection(QAbstractAnimation::Forward);

    this->_mouthStartAnimation->setDuration(this->DEATH_ANIMATION_SPEED);
    this->_mouthSpanAnimation->setDuration(this->DEATH_ANIMATION_SPEED);
    this->_mouthStartAnimation->start();
    this->_mouthSpanAnimation->start();

    // restore animation direction and values
    this->_mouthStartAnimation->setDirection(QAbstractAnimation::Backward);
    this->_mouthSpanAnimation->setDirection(QAbstractAnimation::Backward);
    this->_mouthStartAnimation->setEndValue(0);
    this->_mouthSpanAnimation->setEndValue(360 * 16);
}


void PacmanItem::_rotatePacman(direction dr)
{
    switch (dr) {
    case direction::RIGHT:
        this->setRotation(0);
        break;
    case direction::UP:
        this->setRotation(270);
        break;
    case direction::LEFT:
        this->setRotation(180);
        break;
    case direction::DOWN:
        this->setRotation(90);
        break;
    default:
        break;
    }
    this->_PacmanDirection = dr;
}


/***************************************************************/


GhostItem::GhostItem(QPixmap &pixmap, QPointF position, qreal &width, qreal &height, QGraphicsPixmapItem *parent) : QObject(), QGraphicsPixmapItem(pixmap, parent)
{
    // Ghost is moving object so it has to be on top of game field objects and also above pacman
    this->setZValue(2);
    // set position and size
    this->setPos(position);
    this->setScale(qMin(width / pixmap.width(), height / pixmap.height()));
    // move animation
    this->_moveAnimation = new QPropertyAnimation(this, "pos");
    this->_moveAnimation->setEasingCurve(QEasingCurve::Linear);
}


GhostItem::~GhostItem()
{
    delete _moveAnimation;
}


void GhostItem::moveTo(QPointF destPos, int speed)
{
    if (this->_moveAnimation->state() == QAbstractAnimation::Running)
    {
        return;
    }
    this->_moveAnimation->setDuration(speed);
    this->_moveAnimation->setEndValue(destPos);
    this->_moveAnimation->start();
}

void GhostItem::freeze()
{
    _moveAnimation->stop();
}

/***************************************************************/


KeyItem::KeyItem(QPixmap &pixmap, QPointF position, qreal &width, qreal &height, QGraphicsPixmapItem *parent) : QGraphicsPixmapItem(pixmap, parent)
{
    // set position and size
    this->setPos(position);
    this->setScale(qMin(width / pixmap.width(), height / pixmap.height()));
}


KeyItem::~KeyItem()
{

}


/***************************************************************/


TargetItem::TargetItem(QPixmap &pixmap, QPointF position, qreal &width, qreal &height, QGraphicsPixmapItem *parent) : QGraphicsPixmapItem(pixmap, parent)
{
    // set position and size
    this->setPos(position);
    this->setScale(qMin(width / pixmap.width(), height / pixmap.height()));
}


TargetItem::~TargetItem()
{

}

/* END OF FILE */
