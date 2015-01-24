/*
 * 作者：陈浩川
 * 创作时间：2014/9/17
 * 最后更新时间：2014/9/17
 * 最后修改版本：V0.1
 *
 * 本模块属于抢课系统的一部分。
 * 本程序采用Java的编程风格编写。
 */
#pragma once

#include <string>

/**
 * 包含学生信息的类，定义了课程名称、教务班号等信息。
 * 第一个版本本着能用为原则的目的进行敏捷开发，仅定义学号、密码、sID。
 */
class Student
{
    // 首先添加课程班号作为唯一字段，为了能用
private:
    // 学生学号
    std::string username;
    // 教务系统密码
    std::string password;
    // sID，sID为登陆后返回得到的临时身份ID，是在线时的唯一标示符，用于验证选课等内容
    std::string sID;
public:
    // 必须初始化用户的学号，密码，sID设为空访问互联网后进行获取
    Student(std::string username, std::string password);

    // 后期可能会移植到Java中，故不做处理
    ~Student() {}

    // 以下设计保持java bean风格

    // 获取学号
    std::string getUsername();

    // 修改学号
    void setUsername(std::string username);

    // 获取密码
    std::string getPassword();

    // 修改密码
    void setStudentID(std::string password);

    // 获取sID
    std::string getSID();

    // 修改sID
    void setSID(std::string sID);
};

