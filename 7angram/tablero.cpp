#include "tablero.h"
#include "ui_tablero.h"
#include <QMessageBox>
#include <QMouseEvent>


Tablero::Tablero(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Tablero)
{
    ui->setupUi(this);
    padre=parent;
    connect(ui->iconoBack, SIGNAL(clicked()), this, SLOT(verify_button()));
    connect(ui->iconoLight, SIGNAL(clicked()), this, SLOT(verify_button()));
    connect(timer, SIGNAL(timeout()), this, SLOT(actual_state()));

    level = "Level 1";

    init();
}

Tablero::~Tablero()
{
    delete ui;
}

void Tablero::verify_button()
{
    button = qobject_cast<QPushButton*>(sender());

    if (button->objectName() == "iconoBack")
    {
        close();
        padre->show();
    }
    else if (button->objectName() == "iconoLight")
    {
        ui->ayuda->setPixmap(QPixmap(":/imagenes/Tortuga.png"));
        ui->ayuda->move(330, 100);
        ui->ayuda->show();
        ui->ayuda->setAttribute(Qt::WA_DeleteOnClose);
        ui->ayuda->setEnabled(false);
    }
}

void Tablero::init(){

    ui->level->setText(level);

    p = 7;

    time.setHMS(0,1,0);

    ui->time->setText(time.toString("m:ss"));


    timer->start(1000);
}


void Tablero::actual_time(){
    time=time.addSecs(-1);
    ui->time->setText(time.toString("m:ss"));
}


void Tablero::actual_state(){
    actual_time();
    result_end();
}

void Tablero::result_end()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Tangram");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setEscapeButton(QMessageBox::No);

    if (p==0){
        timer->stop();
        msgBox.setText("Completed Tangram.¡Congratulations!\n¿Next level?");
        if (QMessageBox::Yes == msgBox.exec()){
            init();
        }
        else{
            close();
        }
    }
    else{
        if (time.toString()=="00:00:00"){
            timer->stop();
            ui->centralwidget->setEnabled(false);
            msgBox.setText(" ;( Game over\n Play again?");
            if (QMessageBox::Yes == msgBox.exec()){
                Tablero *tablero= new Tablero;
                tablero->setFixedSize(1020,540);
                hide();
                tablero->show();
            }
            else{
                close();
            }
        }
    }
}


void Tablero::game()
{
    if(actual_pos.x() > ui->ayuda->pos().x() & actual_pos.x() < ui->ayuda->pos().x()+ui->ayuda->width())
        if(actual_pos.y() > ui->ayuda->pos().y() & actual_pos.y() < ui->ayuda->pos().y()+ui->ayuda->height())
        {
          p--;
        }
}

