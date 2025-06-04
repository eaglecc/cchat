#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginDialog = new LoginDialog(this);
    setCentralWidget(loginDialog);

    registerDialog = new RegisterDialog(this);

    // 创建和注册消息链接
    connect(loginDialog, &LoginDialog::showRegisterDialog, this, &MainWindow::SlotSwitchReg);
    
    // 设置无边框
    loginDialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint); 
    registerDialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    registerDialog->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    loginDialog->hide();
    setCentralWidget(registerDialog);
    registerDialog->show();

}
