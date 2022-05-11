#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <tablero.h>
#include <instructions.h>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->iconoPlay, SIGNAL(clicked()), this, SLOT(verify_button()));
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(verify_button()));
    connect(ui->iconoInstructions, SIGNAL(clicked()), this, SLOT(verify_button()));
    connect(ui->instructionsButton, SIGNAL(clicked()), this, SLOT(verify_button()));
    connect(ui->iconoExit, SIGNAL(clicked()), this, SLOT(verify_button()));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(verify_button()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::verify_button()
{
    button = qobject_cast<QPushButton*>(sender());

    if (button->objectName() == "iconoPlay" || button->objectName() == "playButton")
    {
        tablero= new Tablero(this);
        tablero->setFixedSize(1020,540);
        hide();
        tablero->show();
    }

    if (button->objectName() == "iconoInstructions" || button->objectName() == "instructionsButton")
    {
        instructions= new Instructions(this);
        instructions->setFixedSize(1020,540);
        hide();
        instructions->show();
    }

    if (button->objectName() == "iconoExit" || button->objectName() == "exitButton")
    {
        QMessageBox msgBox;
        msgBox.setText("Do you really want to stop the fun?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int result = msgBox.exec();
        switch (result)
        {
            case QMessageBox::Yes:
                close();
                break;
            case QMessageBox::No:
                break;
        }
    }
}
