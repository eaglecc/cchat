#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include <QStyle>
#include <memory>
#include <iostream>
#include <mutex>
#include <QByteArray>
#include <QNetworkReply>


extern std::function<void(QWidget*)> repolish;

enum ReqId{
    ID_GET_VARIFY_CODE = 1001, // 获取验证码
    ID_REG_USER = 1002, // 注册用户
};

enum Modules{
    MODULE_REGISTER = 0, // 注册模块

};

enum ErrorCode {
    CODE_SUCCESS = 0, // 成功
    ERROR_CODE_JSON_PARSE_ERROR = 1, // JSON解析错误
    ERROR_CODE_NETWORK_ERROR = 2, // 网络错误
    ERROR_CODE_UNKNOWN_ERROR = 3, // 未知错误
};


#endif // GLOBAL_H
