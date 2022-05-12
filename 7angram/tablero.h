#ifndef TABLERO_H
#define TABLERO_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QMessageBox>

namespace Ui {
class Tablero;
}

class Tablero : public QMainWindow
{
    Q_OBJECT
    QPushButton *button;
    bool mdrag;
    QPoint lastPoint;

public:
    explicit Tablero(QMainWindow *parent = nullptr);
    QTimer *timer=new QTimer();
    QTime time;
    int remainingPieces;
    int levelNumber=1;
    QMessageBox msgBox;


    void mousePressEvent(QMouseEvent *ev) override;
    void dragEnterEvent(QDragEnterEvent *ev) override;
    void dragMoveEvent(QDragMoveEvent *ev) override;
    void dropEvent(QDropEvent *ev) override;


    ~Tablero();
public slots:
    void verify_button();
    void update_status();
    void update_stopwatch();
    void define_result();
    void start_game();
    void show_solution();
    void hide_solution();

private:
    Ui::Tablero *ui;
    QMainWindow *padre;
};

#endif // TABLERO_H
