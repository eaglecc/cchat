#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state","normal");
    repolish(ui->err_tip);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_verify_btn_clicked()
{
    auto email = ui->email_edit->text();
    // 邮箱格式检查
    if (!QRegExp("^[a-zA-Z0-9_.-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)*\\.[a-zA-Z]{2,6}$").exactMatch(email)) {
        showTip("email error", false);
        return;
    }
    // 获取验证码
    showTip("get success", true);
}

void RegisterDialog::showTip(QString str, bool is_ok)
{
    if (is_ok) {
        ui->err_tip->setProperty("state","normal");
    }
    else {
        ui->err_tip->setProperty("state","error");
    }
    ui->err_tip->setText(str);
    repolish(ui->err_tip);
}

