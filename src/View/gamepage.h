#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>

namespace Ui {
class gamepage;
}

class gamepage : public QWidget
{
    Q_OBJECT

public:
    explicit gamepage(QWidget *parent = nullptr);
    ~gamepage();

private slots:
    void on_GameBackButton_clicked();

    void on_PlayButton_clicked();

    void on_GameExitButton_clicked();

    void on_EndContinueButton_clicked();

private:
    Ui::gamepage *ui;


signals:
    void GoOnHomePage();

};

#endif // GAMEPAGE_H
