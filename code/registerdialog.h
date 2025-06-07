#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"

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
    void slotHttpFinished(ReqId reqId, QString res, ErrorCode errorCode);

private:
    void showTip(QString str, bool is_ok);
    Ui::RegisterDialog *ui;
    
    void initHttpHeaders();
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;

private:
};

#endif // REGISTERDIALOG_H
