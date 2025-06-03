#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginDialog = new LoginDialog();
    setCentralWidget(loginDialog);
    //loginDialog->show();

    registerDialog = new RegisterDialog();

    // 创建和注册消息链接
    connect(loginDialog, &LoginDialog::showRegisterDialog, this, &MainWindow::SlotSwitchReg);

}

MainWindow::~MainWindow()
{
    delete ui;
    if (loginDialog)
    {
        delete loginDialog;
        loginDialog = nullptr;
    }

    if (registerDialog)
    {
        delete registerDialog;
        registerDialog = nullptr;
    }
}

void MainWindow::SlotSwitchReg()
{
    loginDialog->hide();
    setCentralWidget(registerDialog);
    //registerDialog->show();

}
