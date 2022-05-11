#ifndef TABLERO_H
#define TABLERO_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QTime>

namespace Ui {
class Tablero;
}

class Tablero : public QMainWindow
{
    Q_OBJECT
    QPushButton *button;
    QTimer *timer = new QTimer;
    QTime time;
    QString level;
    QPoint last_pos, actual_pos;
    int p;

public:
    explicit Tablero(QMainWindow *parent = nullptr);
    ~Tablero();

    void init();
    void result_end();

protected:


public slots:
    void verify_button();
    void actual_time();
    void actual_state();
    void game();

private:
    Ui::Tablero *ui;
    QMainWindow *padre;
};

#endif // TABLERO_H
