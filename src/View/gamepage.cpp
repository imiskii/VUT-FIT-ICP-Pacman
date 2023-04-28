/**
 * @file gamepage.cpp
 * @author Michal Ľaš (xlasmi00)
 * @brief Game View
 * 
 */

#include "gamepage.h"
#include "ui_gamepage.h"


gamepage::gamepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamepage)
{
    ui->setupUi(this);
    this->_scene = new QGraphicsScene(ui->GameGraphicsView);
}


gamepage::~gamepage()
{
    delete ui;
}


void gamepage::MoveOnPage(GVPageCode page)
{
    switch (page) {
    case GVPageCode::PLAY_GAME:
        ui->MessageLabel->clear();
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case GVPageCode::HOME:
        ui->MessageLabel->clear();
        emit GoOnHomePage();
        break;
    case GVPageCode::GAME_END:
    case GVPageCode::GAME_LOBBY:
        ui->stackedWidget->setCurrentIndex(0);
        break;
    default:
        break;
    }
}


void gamepage::AddMapName(QString mapName)
{
    ui->MapComboBox->addItem(mapName);
    ui->MapComboBox->setCurrentText(mapName);
}


void gamepage::ShowGameField(std::vector<std::vector<char>> &gameField)
{   
    int tmp = std::min(ui->GameGraphicsView->size().width(), ui->GameGraphicsView->size().height());

    int cellSize = (tmp-1)/10;

    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            QGraphicsRectItem* cell = new QGraphicsRectItem(col * cellSize, row * cellSize, cellSize, cellSize);
            cell->setPen(QPen(Qt::black));
            cell->setBrush(QBrush(Qt::white));
            this->_scene->addItem(cell);
        }
    }

    ui->GameGraphicsView->setScene(this->_scene);
}


void gamepage::ShowMessage(QString msg)
{
    ui->MessageLabel->setText(msg);
}


void gamepage::on_GameBackButton_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_BACK);
}


void gamepage::on_PlayButton_clicked()
{
    emit PlayButtonClicked(ui->MapComboBox->currentText());
}


void gamepage::on_GameExitButton_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_EXIT);
}


void gamepage::on_EndContinueButton_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_CONTINUE);
}


void gamepage::on_ChooseMapFileButton_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_CHOOSEMAP);
}


