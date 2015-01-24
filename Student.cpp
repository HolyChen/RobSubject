/*
 * 作者：陈浩川
 * 创作时间：2014/9/17
 * 最后更新时间：2014/9/17
 * 最后修改版本：V0.1
 *
 * 本模块属于抢课系统的一部分。
 * 本程序采用Java的编程风格编写。
 */
#include "Student.h"

// 必须初始化用户的学号，密码，sID设为空访问互联网后进行获取
Student::Student(std::string username, std::string password) {
    this->username = username;
    this->password = password;
    this->sID = "";   // 避免使用NULL，防止意外发生
}

// 以下设计保持java bean风格

// 获取学号
std::string Student::getUsername() {
    return this->username;
}

// 修改学号
void Student::setUsername(std::string username) {
    this->username = username;
}

// 获取密码
std::string Student::getPassword() {
    return this->password;
}

// 修改密码
void Student::setStudentID(std::string password) {
    this->password = password;
}

// 获取sID
std::string Student::getSID() {
    return this->sID;
}

// 修改sID
void Student::setSID(std::string sID) {
    this->sID = sID;
}