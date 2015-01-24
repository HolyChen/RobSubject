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
#include <list>
#include <iostream>

#include "JwxtConnection.h"
#include "Student.h"
#include "Subject.h"

/**
 * 作为抢课系统控制器的类，对抢课流程进行控制。
 * 第一个版本本着能用为原则的目的进行敏捷开发。
 */
class RobSubjectController {
private:
    // 选课的学生
    Student *student;
    // 待选课列表
    std::list<Subject> subjects;
    // 与选课系统连接类
    JwxtConnection *connection;
    // 要选课的数量
    int toElectCount;

    // 单例类实例
    static RobSubjectController* instance;

    // 单例类，请通过getInstance对实例进行获取
    RobSubjectController();
public:
    // 析构函数
    ~RobSubjectController();

    // 输入用户名密码
    void inputUsernameAndPassword();

    // 登陆
    bool login();

    // 输入选课列表
    void inputSubjects();

    // 判断选课是否全部完成
    bool electComplete();

    // --------- 静态方法 ---------
    // Java风格Main函数
    static void myMain();

    // 获取实例
    static RobSubjectController* getInstance();

    // 初始化实例
    static void initiaInstance();

    // 清理实例
    static void clear();

    // 输出提示信息
    static void outputInfo();
};
