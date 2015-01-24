/*
 * ���ߣ��ºƴ�
 * ����ʱ�䣺2014/9/17
 * ������ʱ�䣺2014/9/17
 * ����޸İ汾��V0.2
 *
 * ��ģ����������ϵͳ��һ���֣���ʹ��C��Դ��cURL 7.38.0�汾�����뻷��ΪVS2013��
 * ���������Java�ı�̷���д��
 */
#include "JwxtConnection.h"
#include <cstring>

// ����һ�������࣬��������ʽ��������
JwxtConnection::JwxtConnection() {
    this->curl = NULL;
    // ��Ϊ�з���������ƻ��ƣ����1000�Ѿ�����ʹ��
    buffer = new char[1000];

    // Curlȫ�ֳ�ʼ��
    curl_global_init(CURL_GLOBAL_ALL);
    // curl��ʼ��
    curl = curl_easy_init();
}

JwxtConnection::~JwxtConnection() {
    // ����curl
    curl_easy_cleanup(curl);
    // CURL ȫ������
    curl_global_cleanup();
    delete[] buffer;
}

/**
* �����ṩ��student��Ϣ�����е�¼
* @Para:
*      student Student   ����ѡ�ε�ѧ��
* @Return
*      �����½�ɹ�����true����֮false��
*/
bool JwxtConnection::login(Student student) {
    CURLcode res;
    bool isOK = false;
    // ���curl�Ƿ�����˳�ʼ��
    if (curl) {
        // �������ͷ��ڴ�
        curl_easy_reset(curl);

        // ע�⣬Ϊ�˷��������������?��Ϊ��ͷ
        std::string query = "username=" + student.getUsername() + "&" + "password=" + student.getPassword();
        std::string url = url_jxwtBase + url_login;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // ��Ϊ��½������ض�����������ض���
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // ����POST�������ݣ����˺�����
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
        // ���ý����ؽ��д���ַ������������������
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        // �����ַ���������Ϊ�ֶ�buffer
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        // ����Cookie����
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
        // ִ��curl�ķ��ʲ���������ֵΪ���ʽ��
        res = curl_easy_perform(curl);
        // ����Ƿ�����
        isOK = res == CURLE_OK;

        // ��ȡcurl�����ʵ�url����½���ض����url��ĩ36λΪSID
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &buffer);
        // �������"login"˵����½���ص��˵�½���棬ʧ����
        if (strstr(buffer, "login") != NULL) {
            isOK = false;
        }
    }
    return isOK;
}

// �ӵ�½�����Ч��ַ�з���sid
std::string JwxtConnection::separateSID() {
    std::string sid = "";
    // ��ȡcurl�����ʵ�url����½���ض����url��ĩ36λΪSID
    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &buffer);
    // ת��string�ͣ����ڲ�������Ϊ��ʹ��һ�Σ�����Ҫ�������ܡ�
    std::string data = std::string(buffer);
    sid = data.substr(data.length() - 36, data.length());
    return sid;
}

/**
 * ����sid��kcbh����ѡ�Ρ�
 * @para:
 *      sid std::string  ѧ������ʱ�����֤sid
 *      kcbh std::string ѡ�εĽ�ѧ���
 * @return:
 *      ѡ�γɹ�����true����֮false��
 */
ELECT_RESULT_CODE JwxtConnection::elect(const std::string sid, const std::string jxbh) {
    CURLcode res;

    ELECT_RESULT_CODE returnCode = FAILED;

    // ѡ�ε�query�ַ���
    std::string query = std::string("jxbh=" + jxbh + "&sid=" + sid);
    // ѡ�ε�url
    std::string url = std::string(url_jxwtBase + url_elect);

    // �������ͷ��ڴ�
    curl_easy_reset(curl);

    // ��Ϊ�ᱻCURL�ͷţ���˲�������
    char *returnJson = new char[1000];

    // ��Ϊ��½������ض�����������ض���
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // ���ý����ؽ��д���ַ������������������
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    // �����ַ���������Ϊ�ֶ�returnJson
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &returnJson);
    // ���÷���URL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    // ���ò�ѯ�ַ���
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());

    // ִ��ѡ��
    try {
        res = curl_easy_perform(curl);
    }
    catch (...) {
        delete[] returnJson;
        return SID_INVALID;
    }
    // err:0 ��ʾѡ�γɹ�
    if (strstr(returnJson, "{&#034;err&#034;:{&#034;code&#034;:0") != NULL) {
        returnCode = SUCCESS;
    }
    // SIDʧЧ
    if (strstr(returnJson, "SID Invalid") != NULL) {
        returnCode = SID_INVALID;
    }
    return returnCode;
}

// ��ѡ�η��صĽ��д����ʱ�����С��ӿڲμ�CURL����
size_t JwxtConnection::write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    char *s = (char*)ptr;
    // ѡ�ν����һ��JSON�ַ��������������ҳ����ת��˵���û�������ʧЧ
    if (nmemb > 160) {
        strcpy(*((char **)stream), "SID Invalid");
        return nmemb;
    }
    strcpy(*((char **)stream), (char *)ptr);
    return nmemb;
}

// --------- ��̬���� ---------

// ��ȡʵ��
JwxtConnection* JwxtConnection::getInstance() {
    if (instance == NULL) {
        initiaInstance();
    }
    return instance;
}

// ��ʼ��ʵ��
void JwxtConnection::initiaInstance() {
    JwxtConnection::instance = new JwxtConnection();
}

// ����ʵ��
void JwxtConnection::clear() {
    delete instance;
    instance = NULL;
}

// ΪI����ʹ���������β������/
const std::string JwxtConnection::url_jxwtBase = "http://uems.sysu.edu.cn/elect";
const std::string JwxtConnection::url_login = "/login";
const std::string JwxtConnection::url_elect = "/s/elect";

JwxtConnection* JwxtConnection::instance = NULL;