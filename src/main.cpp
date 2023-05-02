#include "View/mainwindow.h"
#include "View/gamepage.h"
#include "View/replaypage.h"
#include "Controller/gamecontroller.h"
#include "Model/GameModel.h"
#include "Model/ReplayModel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Create Views
    gamepage *GameView = new gamepage();
    replaypage *ReplayView = new replaypage();
    MainWindow *MainView = new MainWindow(nullptr, GameView, ReplayView);
    // Create Models
    GameModel *GameM = new GameModel(nullptr, GameView);
    ReplayModel *ReplayM = new ReplayModel(nullptr, ReplayView);
    // Create Controller
    GameController *controller = new GameController(nullptr, MainView, GameView, ReplayView, GameM, ReplayM);

    MainView->show();
    return a.exec();
}

/* END OF FILE */