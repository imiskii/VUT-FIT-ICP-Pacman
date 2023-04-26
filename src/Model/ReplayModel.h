#ifndef REPLAYMODEL_H
#define REPLAYMODEL_H

#include <QObject>
#include "../View/replaypage.h"

class ReplayModel : public QObject
{
    Q_OBJECT
public:
    explicit ReplayModel(QObject *parent = nullptr, replaypage *ReplayModel = nullptr);
    ~ReplayModel();


private:
    replaypage *_ReplayView;


signals:

};

#endif // REPLAYMODEL_H
