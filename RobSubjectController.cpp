/*
 * 作者：陈浩川
 * 创作时间：2014/9/17
 * 最后更新时间：2014/9/18
 * 最后修改版本：V0.3
 *
 * 本模块属于抢课系统的一部分。
 * 本程序采用Java的编程风格编写。
 */
#include <time.h>

#include "RobSubjectController.h"

// 单例类，请通过getInstance对实例进行获取
RobSubjectController::RobSubjectController() {
    student = NULL;
    connection = JwxtConnection::getInstance();
    toElectCount = 0;
}

// 析构函数
RobSubjectController::~RobSubjectController() {
    if (this->student != NULL) {
        delete student;
        JwxtConnection::clear();
    }
}

// 输入用户名密码
void RobSubjectController::inputUsernameAndPassword() {
    std::string username, password;
    std::cout << "学号：";
    std::cin >> username;
    std::cout << "密码：";
    std::cin >> password;
    if (student != NULL) {
        delete student;
        student = NULL;
    }
    this->student = new Student(username, password);
}

// 登陆同时获取SID
bool RobSubjectController::login() {
    bool logined = false;
    if (student != NULL) {
        logined = connection->login(*student);
        /*
         * 获取SID。之所以集成在这里，是因为SID失效后需要立即获取SID
         * 为了避免代码重复，所以放在这里。
         * V0.3 添加判断logined，防止崩溃。
         */
        if (logined) {
            instance->student->setSID(instance->connection->separateSID());
        }
    }
    return logined;
}

// 输入选课列表
void RobSubjectController::inputSubjects() {
    std::string jxbh = "";
    Subject sb = Subject("");

    // 输入待选课门数
    std::cout << "要选课的门数（别太贪心）：";
    std::cin >> toElectCount;

    for (int i = 1; i <= toElectCount; i++) {
        std::cout << "第" << i << "门的教学班号：";
        std::cin >> jxbh;
        sb.setKcbh(jxbh);
        subjects.push_back(sb);
    }
}

// 判断选课是否全部完成
bool RobSubjectController::electComplete() {
    // 因为每选上一门课会删除掉一个
    return toElectCount == 0;
}

// Java风格Main函数
void RobSubjectController::myMain() {
    bool logined = false;

    // 初始化
    getInstance();

    // 输出提示信息
    outputInfo();

    // 输入用户名密码
    while (!logined) {
        instance->inputUsernameAndPassword();
        logined = instance->login();
        if (!logined) {
            std::cout << "登录失败，用户名或密码错误" << std::endl;
        }
        else {
            std::cout << "登陆成功" << std::endl;
        }
    }

    // 输入课程信息
    instance->inputSubjects();

    std::list<Subject>::iterator iter = instance->subjects.begin();
    ELECT_RESULT_CODE result;
    // 选课次数
    int times = 0;
    // 每次选课延迟5秒
    int delay = 5000;

    while (iter != instance->subjects.end() && !(instance->electComplete())) {
        times++;
        std::cout << "正在第" << times << "次选课..." << std::endl;
        result = instance->connection->elect(instance->student->getSID(),
            iter->getKcbh());
        // 选课成功
        if (result == SUCCESS) {
            std::cout << "课程" << iter->getKcbh() << "选课成功" << std::endl;
            // 选课成功，代选课程-1
            instance->toElectCount--;
            // 删除之
            instance->subjects.erase(iter);
            // 防止指针悬空
            iter = instance->subjects.begin();
        }
        // SID失效
        else if (result == SID_INVALID) {
            std::cout << "登陆超时，正在重新登录" << std::endl;
            // 重新登录
            instance->login();
        }
        else {
            std::cout << "课程" << iter->getKcbh() << "没选上，" << (delay / 1000) << "秒后再抢"
                << std::endl;
            iter++;
            if (iter == instance->subjects.end()) {
                iter = instance->subjects.begin();
            }
        }
        // 延迟delay,暂定为5秒
        _sleep(delay);
    }
}
// --------- 静态方法 ---------

// 获取实例
RobSubjectController* RobSubjectController::getInstance() {
    if (instance == NULL) {
        initiaInstance();
    }
    return instance;
}

// 初始化实例
void RobSubjectController::initiaInstance() {
    RobSubjectController::instance = new RobSubjectController();
}

// 清理实例
void RobSubjectController::clear() {
    delete instance;
    instance = NULL;
}

// 输出提示信息
void RobSubjectController::outputInfo() {
    std::cout << "\t\t\t    中山大学抢课助手  V0.3" << std::endl << std::endl
        << "\t作者：陈浩川（厚礼）\t←软院狗\t微博：sysu_厚_礼" << std::endl
        << std::endl << std::endl
        << "    输入学号、教务系统密码登陆系统，然后输入按照提示输入你要抢课的教学班号，"
        << "教学班号点开选课系统的课程名称可以看到。然后挂机抢就好了，别人一退课，就是你的了。" << std::endl
        << "做得比较烂，要喷请轻声喷。" << std::endl << std::endl
        << "感谢C++开源库CURL。本软件不用于商业目的。" << std::endl
        << "本软件不会记录账号密码，稍后会把源码放到Github（虽然写的好烂）。" << std::endl << std::endl
        << "\t感谢你的使用（原本说做图形界面，后来被内存污染问题虐到五点，还是算了）" << std::endl << std::endl;
}

RobSubjectController* RobSubjectController::instance = NULL;