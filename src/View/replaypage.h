#ifndef REPLAYPAGE_H
#define REPLAYPAGE_H

#include <QWidget>

namespace Ui {
class replaypage;
}

class replaypage : public QWidget
{
    Q_OBJECT

public:
    explicit replaypage(QWidget *parent = nullptr);
    ~replaypage();

private:
    Ui::replaypage *ui;


signals:
    void GoOnHomePage();

private slots:
    void on_pushButton_clicked();
    void on_PlayButton_clicked();
    void on_ReplayExitButton_clicked();
};

#endif // REPLAYPAGE_H
