#include "instructions.h"
#include "ui_instructions.h"

Instructions::Instructions(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Instructions)
{
    ui->setupUi(this);
    padre=parent;
    connect(ui->iconoBack, SIGNAL(clicked()), this, SLOT(verify_button()));
}

Instructions::~Instructions()
{
    delete ui;

}

void Instructions::verify_button()
{
    button = qobject_cast<QPushButton*>(sender());

    if (button->objectName() == "iconoBack")
    {
        close();
        padre->show();
    }
}
