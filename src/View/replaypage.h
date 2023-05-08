/**
 * @file replaypage.h
 * @author Michal Las (xlasmi00)
 * @brief header file for replaypage.cpp
 *
 */

#ifndef REPLAYPAGE_H
#define REPLAYPAGE_H

#include <QWidget>
#include "gamepage.h"
#include <iostream>

/**
 * @brief The RVPageCode enum application pages codes in ReplayView
 */
enum class RVPageCode
{
    HOME,           //< Home page
    REPLAY_GAME,    //< Replay page
    REPLAY_LOBBY    //< before replay lobby page
};


/**
 * @brief The RVActionCode enum user action codes in ReplayView
 */
enum class RVActionCode
{
    CLICKED_BUTTON_BACK,        //< Back button
    CLICKED_BUTTON_REPLAYGAME,  //< Replay button
    CLICKED_BUTTON_EXIT,        //< Exit button
    CLICKED_BUTTON_CHOOSEREPLAY //< Choose Replay button
};


namespace Ui {
class replaypage;
}

/**
 * @brief The replaypage class pacman Replay View
 */
class replaypage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief replaypage constructor
     * @param parent
     */
    replaypage(QWidget *parent = nullptr);
    ~replaypage();

private:
    Ui::replaypage *ui;
    QGraphicsScene *_scene;             ///< Game scene
    unsigned _mapRowCount;              ///< number of rows in map
    unsigned _mapColumnCount;           ///< number of columns in map
    PacmanItem *_pacman;                ///< Pacman view object
    std::vector<GhostItem*> _ghosts;    ///< Vector with ghost objects
    std::vector<KeyItem*> _keys;        ///< Vector with keys objects
    TargetItem *_target;                ///< Target item
    qreal _cellSize;                    ///< Size of one cell in GraphicView

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

signals:
    /**
     * @brief Notify controller about acctions in GameView
     * @param code code of action
     */
    void NotifyUserAction(RVActionCode code);

    /**
     * @brief GoOnHomePage signal to change page on home page
     */
    void GoOnHomePage();

    /**
     * @brief notify Model that pacman movement was finished
     */
    void PacmanMoveFinished();

    /**
     * @brief Notify controller that player wants to replay a game
     * @param choosenMap name of map selected by user
     */
    void ReplayButtonClicked(QString choosenMap);


public slots:
    /**
     * @brief Change page of application
     * @param page code of the page where apllication should move
     */
    void MoveOnPage(RVPageCode page);
    /**
     * @brief add new replay name to combobox
     * @param replayName name of new replay
     */
    void AddReplayName(QString replayName);
    /**
     * @brief Create new game field and add it to scene
     * @param gameField 2D array representing game field
     */
    void ShowGameField(std::vector<std::vector<char>> &gameField);


private slots:
    /**
     * @brief on_ReplayExitButton_clicked sends signal to Controller that 'Exit' button was clicked
     */
    void on_ReplayExitButton_clicked();
    /**
     * @brief on_ReplayButton_clicked sends signal to Controller that 'Replay' button was clicked
     */
    void on_ReplayButton_clicked();
    /**
     * @brief on_BackButton_clicked sends signal to Controller that 'Back' button was clicked
     */
    void on_BackButton_clicked();
    /**
     * @brief on_ChooseReplayFileButton_clicked sends signal to Controller that 'Choose Replay' button was clicked
     */
    void on_ChooseReplayFileButton_clicked();

    void PacmanMovementFinished();
};

#endif // REPLAYPAGE_H


/* END OF FILE */
