#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class Instructions;
}

class Instructions : public QMainWindow
{
    Q_OBJECT
    QPushButton *button;

public:
    explicit Instructions(QMainWindow *parent = nullptr);
    ~Instructions();
public slots:
    void verify_button();

private:
    Ui::Instructions *ui;
    QMainWindow *padre;
};

#endif // INSTRUCTIONS_H
