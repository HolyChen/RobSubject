/*
 * 作者：陈浩川
 * 创作时间：2014/9/17
 * 最后更新时间：2014/9/17
 * 最后修改版本：V0.1
 *
 * 本模块属于抢课系统的一部分，并使用C开源库cURL 7.38.0版本，编译环境为VS2013。
 * 本程序采用Java的编程风格编写。
 */
#pragma once

#include "Student.h"
#include "Subject.h"
#include <curl/curl.h>

// 表征选课结果的枚举量
enum ELECT_RESULT_CODE {
    // 选课成功
    SUCCESS,
    // 选课失败
    FAILED,
    // SID已经失效
    SID_INVALID
};


/**
 * 用于与教务系统建立连接。
 * 第一个版本本着能用为原则的目的进行敏捷开发。
 */
class JwxtConnection {
private:
    // CURL 连接
    CURL *curl;
    // 选课结果的输出缓冲，为了提升性能，统一在此设置
    char *buffer;


    // 这是一个单例类，不允许显式创建对象
    JwxtConnection();
    // 单例实例，初始值为NULL
    static JwxtConnection *instance;

public:
    ~JwxtConnection();

    /**
     * 根据提供的student信息，进行登录
     * @Para:
     *      student Student   进行选课的学生
     * @Return
     *      如果登陆成功返回true，反之false。
     */
    bool login(Student student);

    // 从登陆后的有效地址中分离sid
    std::string separateSID();

    /**
     * 根据sid和kcbh进行选课。
     * @para:
     *      sid std::string  学生的临时身份认证sid
     *      kcbh std::string 选课的教学班号
     * @return:
     *      选课成功返回true，反之false。
     */
    ELECT_RESULT_CODE elect(std::string sid, std::string jxbh);

    // 将选课返回的结果写入临时变量中。接口参见CURL定义
    static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);

    // --------- 静态方法 ---------

    // 获取实例
    static JwxtConnection* getInstance();

    // 初始化实例
    static void initiaInstance();

    // 清理实例
    static void clear();

    // --------- 公共常量 ---------

    // 选课系统基url
    static const std::string url_jxwtBase;
    // 选课系统登陆url
    static const std::string url_login;
    // 选课系统选课url
    static const std::string url_elect;
};
