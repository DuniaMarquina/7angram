#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "tablero.h"
#include "instructions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

     QPushButton *button;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void verify_button();

private:
    Ui::MainWindow *ui;
    Tablero *tablero;
    Instructions *instructions;
};
#endif // MAINWINDOW_H
