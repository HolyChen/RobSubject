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
 * �����γ���Ϣ���࣬�����˿γ����ơ������ŵ���Ϣ��
 * ��һ���汾��������Ϊԭ���Ŀ�Ľ������ݿ�������ʹ�ÿγ̰�š�
 */
class Subject
{
    // ������ӿγ̰����ΪΨһ�ֶΣ�Ϊ������
private:
    // �γ̰��
    std::string kcbh;
public:
    // �����ʼ���γ̰�ţ���֧�ֿչ��캯����
    Subject(std::string kcbh);

    // �������캯��
    Subject(const Subject& sb);

    // ���ڿ��ܻ���ֲ��Java�У��ʲ�������
    ~Subject();

    // ������Ʊ���java bean���

    // ��ȡ�γ�kcbh
    std::string getKcbh();

    // �޸Ŀγ̰��
    void setKcbh(std::string kcbh);

};

