#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "httpmgr.h"


RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state","normal");
    repolish(ui->err_tip);

    QObject::connect(HttpMgr::getInstance().get(), &HttpMgr::sigRegisterFinished, this, &RegisterDialog::slotHttpFinished);

    initHttpHeaders();
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

// 接收http请求的返回结果
void RegisterDialog::slotHttpFinished(ReqId reqId, QString res, ErrorCode errorCode)
{
    if (errorCode != ErrorCode::CODE_SUCCESS)
    {
        showTip("get verify code failed", false);
        return;
    }
    // 解析为json
    QJsonDocument doc = QJsonDocument::fromJson(res.toUtf8());
    if (doc.isNull())
    {
        showTip("json parse failed", false);
        return;
    }
    if (!doc.isObject())
    {
        showTip("json parse failed", false);
        return;
    }
    QJsonObject jsonObj = doc.object();
    _handlers[reqId](jsonObj); // 调用对应的处理函数
    return;
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

// 注册获取验证码回包的逻辑
void RegisterDialog::initHttpHeaders()
{
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj) {
        int error = jsonObj["error"].toInt();
        if (error != 0)
        {
            showTip("参数错误", false);
            return;
        }
        QString email = jsonObj["email"].toString();
        showTip("验证码已发送至" + email + "，请注意查收", true);
        qDebug() << "验证码已发送至" << email;
    });
}
