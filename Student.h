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

/**
 * ����ѧ����Ϣ���࣬�����˿γ����ơ������ŵ���Ϣ��
 * ��һ���汾��������Ϊԭ���Ŀ�Ľ������ݿ�����������ѧ�š����롢sID��
 */
class Student
{
    // ������ӿγ̰����ΪΨһ�ֶΣ�Ϊ������
private:
    // ѧ��ѧ��
    std::string username;
    // ����ϵͳ����
    std::string password;
    // sID��sIDΪ��½�󷵻صõ�����ʱ���ID��������ʱ��Ψһ��ʾ����������֤ѡ�ε�����
    std::string sID;
public:
    // �����ʼ���û���ѧ�ţ����룬sID��Ϊ�շ��ʻ���������л�ȡ
    Student(std::string username, std::string password);

    // ���ڿ��ܻ���ֲ��Java�У��ʲ�������
    ~Student() {}

    // ������Ʊ���java bean���

    // ��ȡѧ��
    std::string getUsername();

    // �޸�ѧ��
    void setUsername(std::string username);

    // ��ȡ����
    std::string getPassword();

    // �޸�����
    void setStudentID(std::string password);

    // ��ȡsID
    std::string getSID();

    // �޸�sID
    void setSID(std::string sID);
};

