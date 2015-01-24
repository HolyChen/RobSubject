/*
 * ���ߣ��ºƴ�
 * ����ʱ�䣺2014/9/17
 * ������ʱ�䣺2014/9/18
 * ����޸İ汾��V0.3
 *
 * ��ģ����������ϵͳ��һ���֡�
 * ���������Java�ı�̷���д��
 */
#include <time.h>

#include "RobSubjectController.h"

// �����࣬��ͨ��getInstance��ʵ�����л�ȡ
RobSubjectController::RobSubjectController() {
    student = NULL;
    connection = JwxtConnection::getInstance();
    toElectCount = 0;
}

// ��������
RobSubjectController::~RobSubjectController() {
    if (this->student != NULL) {
        delete student;
        JwxtConnection::clear();
    }
}

// �����û�������
void RobSubjectController::inputUsernameAndPassword() {
    std::string username, password;
    std::cout << "ѧ�ţ�";
    std::cin >> username;
    std::cout << "���룺";
    std::cin >> password;
    if (student != NULL) {
        delete student;
        student = NULL;
    }
    this->student = new Student(username, password);
}

// ��½ͬʱ��ȡSID
bool RobSubjectController::login() {
    bool logined = false;
    if (student != NULL) {
        logined = connection->login(*student);
        /*
         * ��ȡSID��֮���Լ������������ΪSIDʧЧ����Ҫ������ȡSID
         * Ϊ�˱�������ظ������Է������
         * V0.3 ����ж�logined����ֹ������
         */
        if (logined) {
            instance->student->setSID(instance->connection->separateSID());
        }
    }
    return logined;
}

// ����ѡ���б�
void RobSubjectController::inputSubjects() {
    std::string jxbh = "";
    Subject sb = Subject("");

    // �����ѡ������
    std::cout << "Ҫѡ�ε���������̫̰�ģ���";
    std::cin >> toElectCount;

    for (int i = 1; i <= toElectCount; i++) {
        std::cout << "��" << i << "�ŵĽ�ѧ��ţ�";
        std::cin >> jxbh;
        sb.setKcbh(jxbh);
        subjects.push_back(sb);
    }
}

// �ж�ѡ���Ƿ�ȫ�����
bool RobSubjectController::electComplete() {
    // ��Ϊÿѡ��һ�ſλ�ɾ����һ��
    return toElectCount == 0;
}

// Java���Main����
void RobSubjectController::myMain() {
    bool logined = false;

    // ��ʼ��
    getInstance();

    // �����ʾ��Ϣ
    outputInfo();

    // �����û�������
    while (!logined) {
        instance->inputUsernameAndPassword();
        logined = instance->login();
        if (!logined) {
            std::cout << "��¼ʧ�ܣ��û������������" << std::endl;
        }
        else {
            std::cout << "��½�ɹ�" << std::endl;
        }
    }

    // ����γ���Ϣ
    instance->inputSubjects();

    std::list<Subject>::iterator iter = instance->subjects.begin();
    ELECT_RESULT_CODE result;
    // ѡ�δ���
    int times = 0;
    // ÿ��ѡ���ӳ�5��
    int delay = 5000;

    while (iter != instance->subjects.end() && !(instance->electComplete())) {
        times++;
        std::cout << "���ڵ�" << times << "��ѡ��..." << std::endl;
        result = instance->connection->elect(instance->student->getSID(),
            iter->getKcbh());
        // ѡ�γɹ�
        if (result == SUCCESS) {
            std::cout << "�γ�" << iter->getKcbh() << "ѡ�γɹ�" << std::endl;
            // ѡ�γɹ�����ѡ�γ�-1
            instance->toElectCount--;
            // ɾ��֮
            instance->subjects.erase(iter);
            // ��ָֹ������
            iter = instance->subjects.begin();
        }
        // SIDʧЧ
        else if (result == SID_INVALID) {
            std::cout << "��½��ʱ���������µ�¼" << std::endl;
            // ���µ�¼
            instance->login();
        }
        else {
            std::cout << "�γ�" << iter->getKcbh() << "ûѡ�ϣ�" << (delay / 1000) << "�������"
                << std::endl;
            iter++;
            if (iter == instance->subjects.end()) {
                iter = instance->subjects.begin();
            }
        }
        // �ӳ�delay,�ݶ�Ϊ5��
        _sleep(delay);
    }
}
// --------- ��̬���� ---------

// ��ȡʵ��
RobSubjectController* RobSubjectController::getInstance() {
    if (instance == NULL) {
        initiaInstance();
    }
    return instance;
}

// ��ʼ��ʵ��
void RobSubjectController::initiaInstance() {
    RobSubjectController::instance = new RobSubjectController();
}

// ����ʵ��
void RobSubjectController::clear() {
    delete instance;
    instance = NULL;
}

// �����ʾ��Ϣ
void RobSubjectController::outputInfo() {
    std::cout << "\t\t\t    ��ɽ��ѧ��������  V0.3" << std::endl << std::endl
        << "\t���ߣ��ºƴ�������\t����Ժ��\t΢����sysu_��_��" << std::endl
        << std::endl << std::endl
        << "    ����ѧ�š�����ϵͳ�����½ϵͳ��Ȼ�����밴����ʾ������Ҫ���εĽ�ѧ��ţ�"
        << "��ѧ��ŵ㿪ѡ��ϵͳ�Ŀγ����ƿ��Կ�����Ȼ��һ����ͺ��ˣ�����һ�˿Σ���������ˡ�" << std::endl
        << "���ñȽ��ã�Ҫ���������硣" << std::endl << std::endl
        << "��лC++��Դ��CURL���������������ҵĿ�ġ�" << std::endl
        << "����������¼�˺����룬�Ժ���Դ��ŵ�Github����Ȼд�ĺ��ã���" << std::endl << std::endl
        << "\t��л���ʹ�ã�ԭ��˵��ͼ�ν��棬�������ڴ���Ⱦ����Ű����㣬�������ˣ�" << std::endl << std::endl;
}

RobSubjectController* RobSubjectController::instance = NULL;