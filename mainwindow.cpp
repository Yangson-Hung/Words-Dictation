#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("单词听写V1.1");
    this->setWindowIcon(QIcon(":/new/prefix1/ico.ico"));
    button = new QPushButton(this);
    button->setText("我是按钮");
}

MainWindow::~MainWindow()
{

}
