#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    // 获取验证码
    void on_verify_btn_clicked();

private:
    void showTip(QString str, bool is_ok);
private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
