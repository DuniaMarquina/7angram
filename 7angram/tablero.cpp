#include "tablero.h"
#include "ui_tablero.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QDrag>
#include <QMimeData>
#include <QLabel>
#include <QPixmap>
#include <QPainter>

Tablero::Tablero(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Tablero)
{
    ui->setupUi(this);
    padre=parent;

    setAcceptDrops(true);

    connect(ui->iconoBack, SIGNAL(clicked()), this, SLOT(verify_button()));
    connect(ui->iconoLight, SIGNAL(pressed()), this, SLOT(show_solution()));
    connect(ui->iconoLight, SIGNAL(released()), this, SLOT(hide_solution()));
    connect(timer, SIGNAL(timeout()), this, SLOT(update_status()));
    start_game();
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
}

void Tablero::show_solution()
{
   ui->iconoFigureGray->setStyleSheet("#iconoFigureGray{ image: url(:/imagenes/Soluciones/"+QString::number(levelNumber-1)+".jpg);}");
}

void Tablero::hide_solution()
{
   ui->iconoFigureGray->setStyleSheet("#iconoFigureGray{ image: url(:/imagenes/FigurasGris/"+QString::number(levelNumber-1)+".png);}");
}

void Tablero::update_stopwatch()
{
    time=time.addSecs(-1);
    ui->time->setText(time.toString("m:ss"));
}

void Tablero::start_game()
{
    remainingPieces=7;
    time.setHMS(0,1,0);
    ui->time->setText(time.toString("m:ss"));
    timer->start(1000);
    ui->iconoFigure->setStyleSheet("#iconoFigure{ image: url(:/imagenes/Figuras/"+QString::number(levelNumber)+".png);}");
    ui->iconoFigureGray->setStyleSheet("#iconoFigureGray{ image: url(:/imagenes/FigurasGris/"+QString::number(levelNumber)+".png);}");
    ui->level->setText("LEVEL "+QString::number(levelNumber++));
}

void Tablero::define_result()
{
    msgBox.setWindowTitle("Tangram");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setEscapeButton(QMessageBox::No);

    if (remainingPieces==0){
        timer->stop();
        msgBox.setText("Completed Tangram.¡Congratulations!\n¿Next level?");
        if (QMessageBox::Yes == msgBox.exec()){
            start_game();
        }
        else{
            close();
            padre->show();
        }
    }
    else{
        if (time.toString()=="00:00:00"){
            timer->stop();
            ui->centralwidget->setEnabled(false);
            msgBox.setText(" ;( Game over\n Play again?");
            if (QMessageBox::Yes == msgBox.exec()){
                 close();
                padre->show();
            }
            else{
                close();
            }
        }
    }
}

void Tablero::update_status()
{
    update_stopwatch();
    define_result();
}

void Tablero::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button()==Qt::RightButton)
    {
        QLabel *child = static_cast<QLabel*>(childAt(ev->pos()));
        if(!child->inherits("QLabel")){
            return;
        }
        QPixmap pixmap = child->pixmap(Qt::ReturnByValue);
        QTransform trans;
        QLabel *newIcon = new QLabel(this);
        child->close();

        trans.rotate(45);
        newIcon->setPixmap(pixmap.transformed(trans));
        newIcon->setGeometry(0,0,pixmap.width(),pixmap.height());
        newIcon->move(ev->position().toPoint());
        newIcon->setScaledContents(true);
        newIcon->show();
    }
    if (ev->button()==Qt::LeftButton)
    {
        QLabel *child = static_cast<QLabel*>(childAt(ev->pos()));
        if(!child->inherits("QLabel")){
            return;
        }

        QPixmap pixmap = child->pixmap(Qt::ReturnByValue);
        QByteArray itemData;
        QDataStream dataStream(&itemData,QIODevice::WriteOnly);
        dataStream<<pixmap<<QPoint(ev->pos()-child->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata",itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(ev->pos()-child->pos());

        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.end();
        child->setPixmap(tempPixmap);
        child->setScaledContents(true);

        if(drag->exec(Qt::CopyAction|Qt::MoveAction,Qt::CopyAction) == Qt::MoveAction)
        {
            child->close();
        }else{
            child->show();
            child->setPixmap(pixmap);
        }
    }
}

void Tablero::dragEnterEvent(QDragEnterEvent *ev)
{
    if (ev->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (ev->source() == this)
        {
            ev->setDropAction(Qt::MoveAction);
            ev->accept();
         } else {
                ev->acceptProposedAction();
            }
        } else {
            ev->ignore();
    }
}

void Tablero::dragMoveEvent(QDragMoveEvent *ev)
{
    if (ev->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (ev->source() == this)
        {
            ev->setDropAction(Qt::MoveAction);
            ev->accept();
         } else {
                ev->acceptProposedAction();
            }
     } else {
         ev->ignore();
    }
}

void Tablero::dropEvent(QDropEvent *ev)
{
    if (ev->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        QByteArray itemData = ev->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->setGeometry(0,0,pixmap.width(),pixmap.height());
        newIcon->move(ev->position().toPoint() - offset);
        newIcon->setScaledContents(true);

        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (ev->source() == this)
        {
            ev->setDropAction(Qt::MoveAction);
            ev->accept();
        } else {
            ev->acceptProposedAction();
        }
    } else {
         ev->ignore();
    }
}
