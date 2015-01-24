/*
 * 作者：陈浩川
 * 创作时间：2014/9/17
 * 最后更新时间：2014/9/17
 * 最后修改版本：V0.2
 *
 * 本模块属于抢课系统的一部分，并使用C开源库cURL 7.38.0版本，编译环境为VS2013。
 * 本程序采用Java的编程风格编写。
 */
#include "JwxtConnection.h"
#include <cstring>

// 这是一个单例类，不允许显式创建对象
JwxtConnection::JwxtConnection() {
    this->curl = NULL;
    // 因为有返回溢出控制机制，因此1000已经可以使用
    buffer = new char[1000];

    // Curl全局初始化
    curl_global_init(CURL_GLOBAL_ALL);
    // curl初始化
    curl = curl_easy_init();
}

JwxtConnection::~JwxtConnection() {
    // 清理curl
    curl_easy_cleanup(curl);
    // CURL 全局清理
    curl_global_cleanup();
    delete[] buffer;
}

/**
* 根据提供的student信息，进行登录
* @Para:
*      student Student   进行选课的学生
* @Return
*      如果登陆成功返回true，反之false。
*/
bool JwxtConnection::login(Student student) {
    CURLcode res;
    bool isOK = false;
    // 检测curl是否进行了初始化
    if (curl) {
        // 重置以释放内存
        curl_easy_reset(curl);

        // 注意，为了方便起见，不加入?作为开头
        std::string query = "username=" + student.getUsername() + "&" + "password=" + student.getPassword();
        std::string url = url_jxwtBase + url_login;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // 因为登陆界面会重定向，因此允许重定向
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // 定义POST操作数据，即账号密码
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
        // 设置将返回结果写入字符串缓冲区，避免回显
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        // 设置字符串缓冲区为字段buffer
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        // 启动Cookie引擎
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
        // 执行curl的访问操作，返回值为访问结果
        res = curl_easy_perform(curl);
        // 检查是否有误
        isOK = res == CURLE_OK;

        // 获取curl最后访问的url即登陆后重定向的url，末36位为SID
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &buffer);
        // 如果含有"login"说明登陆返回到了登陆界面，失败了
        if (strstr(buffer, "login") != NULL) {
            isOK = false;
        }
    }
    return isOK;
}

// 从登陆后的有效地址中分离sid
std::string JwxtConnection::separateSID() {
    std::string sid = "";
    // 获取curl最后访问的url即登陆后重定向的url，末36位为SID
    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &buffer);
    // 转回string型，便于操作。因为仅使用一次，不需要考虑性能。
    std::string data = std::string(buffer);
    sid = data.substr(data.length() - 36, data.length());
    return sid;
}

/**
 * 根据sid和kcbh进行选课。
 * @para:
 *      sid std::string  学生的临时身份认证sid
 *      kcbh std::string 选课的教学班号
 * @return:
 *      选课成功返回true，反之false。
 */
ELECT_RESULT_CODE JwxtConnection::elect(const std::string sid, const std::string jxbh) {
    CURLcode res;

    ELECT_RESULT_CODE returnCode = FAILED;

    // 选课的query字符串
    std::string query = std::string("jxbh=" + jxbh + "&sid=" + sid);
    // 选课的url
    std::string url = std::string(url_jxwtBase + url_elect);

    // 重置以释放内存
    curl_easy_reset(curl);

    // 因为会被CURL释放，因此不作处理
    char *returnJson = new char[1000];

    // 因为登陆界面会重定向，因此允许重定向
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // 设置将返回结果写入字符串缓冲区，避免回显
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    // 设置字符串缓冲区为字段returnJson
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &returnJson);
    // 设置访问URL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    // 设置查询字符串
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());

    // 执行选课
    try {
        res = curl_easy_perform(curl);
    }
    catch (...) {
        delete[] returnJson;
        return SID_INVALID;
    }
    // err:0 表示选课成功
    if (strstr(returnJson, "{&#034;err&#034;:{&#034;code&#034;:0") != NULL) {
        returnCode = SUCCESS;
    }
    // SID失效
    if (strstr(returnJson, "SID Invalid") != NULL) {
        returnCode = SID_INVALID;
    }
    return returnCode;
}

// 将选课返回的结果写入临时变量中。接口参见CURL定义
size_t JwxtConnection::write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    char *s = (char*)ptr;
    // 选课结果是一个JSON字符串，过长则代表页面跳转，说明用户名密码失效
    if (nmemb > 160) {
        strcpy(*((char **)stream), "SID Invalid");
        return nmemb;
    }
    strcpy(*((char **)stream), (char *)ptr);
    return nmemb;
}

// --------- 静态方法 ---------

// 获取实例
JwxtConnection* JwxtConnection::getInstance() {
    if (instance == NULL) {
        initiaInstance();
    }
    return instance;
}

// 初始化实例
void JwxtConnection::initiaInstance() {
    JwxtConnection::instance = new JwxtConnection();
}

// 清理实例
void JwxtConnection::clear() {
    delete instance;
    instance = NULL;
}

// 为I方便使用起见，结尾均不加/
const std::string JwxtConnection::url_jxwtBase = "http://uems.sysu.edu.cn/elect";
const std::string JwxtConnection::url_login = "/login";
const std::string JwxtConnection::url_elect = "/s/elect";

JwxtConnection* JwxtConnection::instance = NULL;