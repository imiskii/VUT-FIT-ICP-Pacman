/**
 * @file GameModel.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for GameModel.cpp
 * 
 */

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QFileDialog>
#include "../View/gamepage.h"
#include "FileLoader.h"

class GameModel : public QObject
{
    Q_OBJECT

public:
    explicit GameModel(QObject *parent = nullptr, gamepage *GameView = nullptr);
    ~GameModel();


private:
    gamepage *_GameView; //< Game View


signals:
    /**
     * @brief AddMapNameToCombobox notify View to update combobox with available maps
     * @param mapFile name of map
     */
    void AddMapNameToCombobox(QString mapFile);


public slots:
    /**
     * @brief SelectMapFile open File Dialog to choose map file and notify view to display it
     */
    void SelectMapFile();

};

#endif // GAMEMODEL_H
