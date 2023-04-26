#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include "../View/gamepage.h"

class GameModel : public QObject
{
public:
    explicit GameModel(QObject *parent = nullptr, gamepage *GameView = nullptr);
    ~GameModel();


private:
    gamepage *_GameView;


signals:

};

#endif // GAMEMODEL_H
