/**
 * @file replaypage.cpp
 * @author Adam Lazík (xlazik00)
 * @brief Replay view
 *
 */

#include "replaypage.h"
#include "ui_replaypage.h"

replaypage::replaypage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::replaypage)
{
    ui->setupUi(this);
    ui->ReplayGraphicsView->installEventFilter(this);

    this->_scene = new QGraphicsScene(ui->ReplayGraphicsView);

    this->_pacman = nullptr;
    this->_cellSize = 0;
}


bool replaypage::eventFilter(QObject* obj, QEvent* event)
{
    // check if the event is a key event
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        // filter out the event by returning true
        return true;
    }
    // process all other events normally
    return QWidget::eventFilter(obj, event);
}

replaypage::~replaypage()
{
    delete ui;
    delete _scene;
    if (_pacman != nullptr)
    {
        delete _pacman;
    }
}


void replaypage::MoveOnPage(RVPageCode page)
{
    switch (page) {
    case RVPageCode::REPLAY_GAME:
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case RVPageCode::HOME:
        emit GoOnHomePage();
        break;
    case RVPageCode::REPLAY_LOBBY:
        ui->stackedWidget->setCurrentIndex(0);
        break;
    default:
        break;
    }
}

void replaypage::AddReplayName(QString replayName)
{
    ui->ReplayComboBox->addItem(replayName);
    ui->ReplayComboBox->setCurrentText(replayName);
}


void replaypage::on_ReplayButton_clicked()
{
    emit ReplayButtonClicked(ui->ReplayComboBox->currentText());
}


void replaypage::on_ReplayExitButton_clicked()
{
    emit NotifyUserAction(RVActionCode::CLICKED_BUTTON_EXIT);
}


void replaypage::on_BackButton_clicked()
{
    emit NotifyUserAction(RVActionCode::CLICKED_BUTTON_BACK);
}


void replaypage::on_ChooseReplayFileButton_clicked()
{
    emit NotifyUserAction(RVActionCode::CLICKED_BUTTON_CHOOSEREPLAY);
}

void replaypage::ShowGameField(std::vector<std::vector<char>> &gameField)
{
    this->_mapRowCount = gameField.size();
    this->_mapColumnCount = gameField.at(0).size();
    // Calculate size of one cell
    if (this->_mapRowCount < this->_mapColumnCount) // adjust scene for width
    {
        this->_cellSize = (ui->ReplayGraphicsView->size().width()-1)/this->_mapColumnCount; // scene width / count columns
    }
    else // adjust scene for height
    {
        this->_cellSize = (ui->ReplayGraphicsView->size().height()-1)/this->_mapRowCount; // scene height / count rows
    }
    std::vector<std::string> ghosts = {_RED_GHOST_PATH, _YELLOW_GHOST_PATH, _BLUE_GHOST_PATH};

    // Create items and add them to scene
    for (size_t row = 0; row < this->_mapRowCount; row++)
    {
        for (size_t col = 0; col < this->_mapColumnCount; col++)
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
                    PixmapItem = QPixmap(ghosts.at(rand()%3).c_str());
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
                    connect(this->_pacman, &PacmanItem::moveFinished, this, &replaypage::PacmanMoveFinished);
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

    ui->ReplayGraphicsView->setScene(this->_scene);
}

void replaypage::UpdatePacmanPosition(direction dr, int speed)
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

void replaypage::PacmanMovementFinished()
{
    emit PacmanMoveFinished();
}

/* END OF FILE */
