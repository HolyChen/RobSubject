/*
 * ���ߣ��ºƴ�
 * ����ʱ�䣺2014/9/17
 * ������ʱ�䣺2014/9/17
 * ����޸İ汾��V0.1
 *
 * ��ģ����������ϵͳ��һ���֡�
 * ���������Java�ı�̷���д��
 */
#include "Student.h"

// �����ʼ���û���ѧ�ţ����룬sID��Ϊ�շ��ʻ���������л�ȡ
Student::Student(std::string username, std::string password) {
    this->username = username;
    this->password = password;
    this->sID = "";   // ����ʹ��NULL����ֹ���ⷢ��
}

// ������Ʊ���java bean���

// ��ȡѧ��
std::string Student::getUsername() {
    return this->username;
}

// �޸�ѧ��
void Student::setUsername(std::string username) {
    this->username = username;
}

// ��ȡ����
std::string Student::getPassword() {
    return this->password;
}

// �޸�����
void Student::setStudentID(std::string password) {
    this->password = password;
}

// ��ȡsID
std::string Student::getSID() {
    return this->sID;
}

// �޸�sID
void Student::setSID(std::string sID) {
    this->sID = sID;
}