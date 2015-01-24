/*
 * ���ߣ��ºƴ�
 * ����ʱ�䣺2014/9/17
 * ������ʱ�䣺2014/9/17
 * ����޸İ汾��V0.1
 *
 * ��ģ����������ϵͳ��һ���֡�
 * ���������Java�ı�̷���д��
 */
#pragma once

#include <string>
#include <list>
#include <iostream>

#include "JwxtConnection.h"
#include "Student.h"
#include "Subject.h"

/**
 * ��Ϊ����ϵͳ���������࣬���������̽��п��ơ�
 * ��һ���汾��������Ϊԭ���Ŀ�Ľ������ݿ�����
 */
class RobSubjectController {
private:
    // ѡ�ε�ѧ��
    Student *student;
    // ��ѡ���б�
    std::list<Subject> subjects;
    // ��ѡ��ϵͳ������
    JwxtConnection *connection;
    // Ҫѡ�ε�����
    int toElectCount;

    // ������ʵ��
    static RobSubjectController* instance;

    // �����࣬��ͨ��getInstance��ʵ�����л�ȡ
    RobSubjectController();
public:
    // ��������
    ~RobSubjectController();

    // �����û�������
    void inputUsernameAndPassword();

    // ��½
    bool login();

    // ����ѡ���б�
    void inputSubjects();

    // �ж�ѡ���Ƿ�ȫ�����
    bool electComplete();

    // --------- ��̬���� ---------
    // Java���Main����
    static void myMain();

    // ��ȡʵ��
    static RobSubjectController* getInstance();

    // ��ʼ��ʵ��
    static void initiaInstance();

    // ����ʵ��
    static void clear();

    // �����ʾ��Ϣ
    static void outputInfo();
};
