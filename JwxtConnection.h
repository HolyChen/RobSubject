/*
 * ���ߣ��ºƴ�
 * ����ʱ�䣺2014/9/17
 * ������ʱ�䣺2014/9/17
 * ����޸İ汾��V0.1
 *
 * ��ģ����������ϵͳ��һ���֣���ʹ��C��Դ��cURL 7.38.0�汾�����뻷��ΪVS2013��
 * ���������Java�ı�̷���д��
 */
#pragma once

#include "Student.h"
#include "Subject.h"
#include <curl/curl.h>

// ����ѡ�ν����ö����
enum ELECT_RESULT_CODE {
    // ѡ�γɹ�
    SUCCESS,
    // ѡ��ʧ��
    FAILED,
    // SID�Ѿ�ʧЧ
    SID_INVALID
};


/**
 * ���������ϵͳ�������ӡ�
 * ��һ���汾��������Ϊԭ���Ŀ�Ľ������ݿ�����
 */
class JwxtConnection {
private:
    // CURL ����
    CURL *curl;
    // ѡ�ν����������壬Ϊ���������ܣ�ͳһ�ڴ�����
    char *buffer;


    // ����һ�������࣬��������ʽ��������
    JwxtConnection();
    // ����ʵ������ʼֵΪNULL
    static JwxtConnection *instance;

public:
    ~JwxtConnection();

    /**
     * �����ṩ��student��Ϣ�����е�¼
     * @Para:
     *      student Student   ����ѡ�ε�ѧ��
     * @Return
     *      �����½�ɹ�����true����֮false��
     */
    bool login(Student student);

    // �ӵ�½�����Ч��ַ�з���sid
    std::string separateSID();

    /**
     * ����sid��kcbh����ѡ�Ρ�
     * @para:
     *      sid std::string  ѧ������ʱ�����֤sid
     *      kcbh std::string ѡ�εĽ�ѧ���
     * @return:
     *      ѡ�γɹ�����true����֮false��
     */
    ELECT_RESULT_CODE elect(std::string sid, std::string jxbh);

    // ��ѡ�η��صĽ��д����ʱ�����С��ӿڲμ�CURL����
    static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);

    // --------- ��̬���� ---------

    // ��ȡʵ��
    static JwxtConnection* getInstance();

    // ��ʼ��ʵ��
    static void initiaInstance();

    // ����ʵ��
    static void clear();

    // --------- �������� ---------

    // ѡ��ϵͳ��url
    static const std::string url_jxwtBase;
    // ѡ��ϵͳ��½url
    static const std::string url_login;
    // ѡ��ϵͳѡ��url
    static const std::string url_elect;
};
