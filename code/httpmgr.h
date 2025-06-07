#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

class HttpMgr : public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
private:
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager _manager;
    void PostHttpReq(QUrl url, QJsonObject data, ReqId reqId, Modules module);

private slots:
    void slotHttpFinished(ReqId reqId, QString res, ErrorCode errorCode, Modules module);

signals:
    void sigHttpFinished(ReqId reqId, QString res, ErrorCode errorCode, Modules module);
    void sigRegisterFinished(ReqId reqId, QString res, ErrorCode errorCode);

public:
    ~HttpMgr();
    // void Get(const QString& url, const QJsonObject& data);
    // void Post(const QString& url, const QJsonObject& data);
    // void Put(const QString& url, const QJsonObject& data);
};

#endif // HTTPMGR_H
