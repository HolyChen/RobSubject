/*
 * ���ߣ��ºƴ�
 * ����ʱ�䣺2014/9/17
 * ������ʱ�䣺2014/9/17
 * ����޸İ汾��V0.1
 *
 * ��ģ����������ϵͳ��һ���֡�
 * ���������Java�ı�̷���д��
 */
#include "Subject.h"

// �����ʼ���γ̰�ţ���֧�ֿչ��캯����
Subject::Subject(std::string kcbh) {
    this->kcbh = kcbh;
}

// �������캯��
Subject::Subject(const Subject& sb) {
    this->kcbh = sb.kcbh;
}

// ���ڿ��ܻ���ֲ��Java�У��ʲ�������
Subject::~Subject() {}

// ������Ʊ���java bean���

// ��ȡ�γ�kcbh
std::string Subject::getKcbh() {
    return this->kcbh;
}

// �޸Ŀγ̰��
void Subject::setKcbh(std::string kcbh) {
    this->kcbh = kcbh;
}
