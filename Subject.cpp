/*
 * 作者：陈浩川
 * 创作时间：2014/9/17
 * 最后更新时间：2014/9/17
 * 最后修改版本：V0.1
 *
 * 本模块属于抢课系统的一部分。
 * 本程序采用Java的编程风格编写。
 */
#include "Subject.h"

// 必须初始化课程班号，不支持空构造函数。
Subject::Subject(std::string kcbh) {
    this->kcbh = kcbh;
}

// 拷贝构造函数
Subject::Subject(const Subject& sb) {
    this->kcbh = sb.kcbh;
}

// 后期可能会移植到Java中，故不做处理
Subject::~Subject() {}

// 以下设计保持java bean风格

// 获取课程kcbh
std::string Subject::getKcbh() {
    return this->kcbh;
}

// 修改课程班号
void Subject::setKcbh(std::string kcbh) {
    this->kcbh = kcbh;
}
