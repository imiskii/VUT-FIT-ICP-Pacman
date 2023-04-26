#include "View/mainwindow.h"
#include "View/gamepage.h"
#include "View/replaypage.h"
#include "Controller/gamecontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gamepage *GameView = new gamepage();
    replaypage *ReplayView = new replaypage();
    MainWindow *MainView = new MainWindow(nullptr, GameView, ReplayView);
    // Init Model
    GameController *controller = new GameController(nullptr, MainView, GameView, ReplayView);

    MainView->show();
    return a.exec();
}
