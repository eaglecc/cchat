#include "httpmgr.h"

HttpMgr::HttpMgr() {
    connect(this, &HttpMgr::sigHttpFinished, this, &HttpMgr::slotHttpFinished);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject data, ReqId reqId, Modules module)
{
    QByteArray postData = QJsonDocument(data).toJson(); // JSON 序列化 -> 字节数组
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(postData.size()));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36");
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("Accept-Language", "zh-CN,zh;q=0.9");

    auto self = shared_from_this(); // 闭包：捕获当前对象的this指针
    QNetworkReply *reply = _manager.post(request, postData);
    QObject::connect(reply, &QNetworkReply::finished, this, [self, reply, reqId, module]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Network error: " << reply->errorString();
            emit self->sigHttpFinished(reqId, "", ErrorCode::ERROR_CODE_NETWORK_ERROR, module);
            delete reply;
            return;
        }
        QString response = reply->readAll();
        emit self->sigHttpFinished(reqId, response, ErrorCode::CODE_SUCCESS, module);
        delete reply;
        return;
    });
}

void HttpMgr::slotHttpFinished(ReqId reqId, QString res, ErrorCode errorCode, Modules module)
{
    if (module == Modules::MODULE_REGISTER)
    {
        emit sigRegisterFinished(reqId, res, errorCode);
    }
    
}

HttpMgr::~HttpMgr(){}
