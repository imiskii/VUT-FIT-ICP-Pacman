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
    this->setFocus();

    this->_scene = new QGraphicsScene(ui->GameGraphicsView);
    //connect(this, &gamepage::resize, this, &gamepage::resizeEvent);

    this->_pacman = nullptr;
    this->_cellSize = 0;
}


gamepage::~gamepage()
{
    delete ui;
    foreach(QGraphicsItem *item, this->_scene->items())
    {
        this->_scene->removeItem(item);
        delete item;
    }
    delete this->_scene;
}


void gamepage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    this->updateSceneItemsSize(size());
}


void gamepage::updateSceneItemsSize(const QSize &newSize)
{
    // get pointer to QGraphicsScene
    QGraphicsScene* scene = ui->GameGraphicsView->scene();


    if (scene != nullptr)
    {
        // iterate through items in scene and change thier sizes
        foreach(QGraphicsItem *item, scene->items())
        {
            item->setPos(item->pos().x() * newSize.width() / ui->GameGraphicsView->width(), item->pos().y() * newSize.height() / ui->GameGraphicsView->height());
            item->setScale(newSize.width() / ui->GameGraphicsView->width());
        }
    }
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
        ui->stackedWidget->setCurrentIndex(2);
        break;
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
    // Calculate size of one cell
    int sceneWidth = ui->GameGraphicsView->size().width();
    int sceneHeight = ui->GameGraphicsView->size().height();
    if (sceneWidth < sceneHeight) // adjust scene for width
    {
        this->_cellSize = (sceneWidth-1)/gameField.at(0).size(); // scene width / count columns
    }
    else // adjust scene for height
    {
        this->_cellSize = (sceneHeight-1)/gameField.size(); // scene height / count rows
    }
    // create array of ghosts
    std::vector<std::string> ghosts = {_RED_GHOST_PATH, _YELLOW_GHOST_PATH, _BLUE_GHOST_PATH};

    // Create items and add them to scene
    for (size_t row = 0; row < gameField.size(); row++)
    {
        for (size_t col = 0; col < gameField.at(row).size(); col++)
        {
            QPointF position = QPointF(col * this->_cellSize, row * this->_cellSize);
            if (gameField.at(row).at(col) == 'X')
            {
                this->_scene->addItem(new WallItem(position, this->_cellSize, this->_cellSize));
            }
            else
            {
                QPixmap PixmapItem;
                this->_scene->addItem(new PathItem(position, this->_cellSize, this->_cellSize));
                switch (gameField.at(row).at(col))
                {
                case 'G':
                    PixmapItem = QPixmap(ghosts.at((row)%3).c_str());
                    this->_ghosts.push_back(new GhostItem(PixmapItem, position, this->_cellSize, this->_cellSize));
                    this->_scene->addItem(this->_ghosts.back());
                    break;
                case 'K':
                    PixmapItem = QPixmap(_KEY_PATH);
                    this->_keys.push_back(new KeyItem(PixmapItem, position, this->_cellSize, this->_cellSize));
                    this->_scene->addItem(this->_keys.back());
                    break;
                case 'S':
                    this->_pacman = new PacmanItem(position, this->_cellSize, this->_cellSize);
                    connect(this->_pacman, &PacmanItem::moveFinished, this, &gamepage::PacmanMoveFinished);
                    this->_scene->addItem(this->_pacman);
                    break;
                case 'T':
                    PixmapItem = QPixmap(_TARGET_PATH);
                    this->_target = new TargetItem(PixmapItem, position, this->_cellSize, this->_cellSize);
                    this->_scene->addItem(this->_target);
                    break;
                default:
                    break;
                }
            }
        }
    }

    ui->GameGraphicsView->setScene(this->_scene);
}


void gamepage::ShowMessage(QString msg)
{
    ui->MessageLabel->setText(msg);
}


void gamepage::UpdatePacmanPosition(direction dr, int speed)
{
    switch (dr)
    {
    case direction::UP:
        this->_pacman->moveTo(this->_pacman->pos() + QPointF(0, -this->_cellSize), speed, dr);
        break;
    case direction::LEFT:
        this->_pacman->moveTo(this->_pacman->pos() + QPointF(-this->_cellSize, 0), speed, dr);
        break;
    case direction::DOWN:
        this->_pacman->moveTo(this->_pacman->pos() + QPointF(0, this->_cellSize), speed, dr);
        break;
    case direction::RIGHT:
        this->_pacman->moveTo(this->_pacman->pos() + QPointF(this->_cellSize, 0), speed, dr);
        break;
    default:
        break;
    }    
}


void gamepage::PacmanMovementFinished()
{
    emit PacmanMoveFinished();
}


void gamepage::deleteKeyFromMap(int index)
{
    auto *key = this->_keys.at(index);
    this->_scene->removeItem(key);
    delete key;
    this->_keys.erase(this->_keys.begin() + index);
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


void gamepage::on_ExitGameButton_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_EXIT);
}


void gamepage::on_NextGame_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_NEXTLEVEL);
}


void gamepage::on_ChooseMapFileButton_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_CHOOSEMAP);
}


void gamepage::deleteScene()
{
    foreach(QGraphicsItem *item, this->_scene->items())
    {
        this->_scene->removeItem(item);
        delete item;
    }
    this->_ghosts.clear();
    this->_keys.clear();
    this->_pacman = nullptr;
    this->_target = nullptr;
}


