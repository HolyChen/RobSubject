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
 * 包含课程信息的类，定义了课程名称、教务班号等信息。
 * 第一个版本本着能用为原则的目的进行敏捷开发，仅使用课程班号。
 */
class Subject
{
    // 首先添加课程班号作为唯一字段，为了能用
private:
    // 课程班号
    std::string kcbh;
public:
    // 必须初始化课程班号，不支持空构造函数。
    Subject(std::string kcbh);

    // 拷贝构造函数
    Subject(const Subject& sb);

    // 后期可能会移植到Java中，故不做处理
    ~Subject();

    // 以下设计保持java bean风格

    // 获取课程kcbh
    std::string getKcbh();

    // 修改课程班号
    void setKcbh(std::string kcbh);

};

