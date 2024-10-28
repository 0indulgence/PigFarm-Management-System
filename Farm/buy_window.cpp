#include "buy_window.h"
#include "ui_buy_window.h"

buy_window::buy_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::buy_window)
{
    ui->setupUi(this);

}

buy_window::~buy_window()
{
    delete ui;
}
