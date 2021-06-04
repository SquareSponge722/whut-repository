#pragma once

constexpr auto TIMELENGTH = 20;
constexpr auto WRITEFILE = false;

//��״̬
constexpr auto USING = 1; //�ϻ�
constexpr auto UNUSE = 2; //�»�
constexpr auto PAUSED = 3; //ע��

//�������
constexpr auto SUCCESS = 11;
constexpr auto FAILURE = 12;
constexpr auto EXISTED = 13;

//INFO������ʶ
constexpr auto INFO_NEW = 21; //����
constexpr auto INFO_PAUSE = 22; //����
constexpr auto INFO_CHARGE = 23; //��ֵ
constexpr auto INFO_FEEBACK = 24; //�˷�
constexpr auto INFO_CUNSUME = 25; //����

//���ó���
constexpr auto UNIT = 5; //��С�շѵ�Ԫ(����)
constexpr auto FEE = 500; //ÿ�շѵ�Ԫ����(Ԫ)
constexpr auto LIMIT = 0.5; //���������(Ԫ)

//Ĭ�����
constexpr auto SPLITELINE = "----------" ;
constexpr auto ERRORLINE = "������������";
constexpr auto DOWNLINE = "____";
constexpr auto HINT_CANCEL = "��ȡ�����β���...\n";
constexpr auto HINT_REINPUT = "�Ƿ��������룿��y/n��";
constexpr auto HINT_REWRITE = "�Ƿ���ģ���y/n��";
constexpr auto HINT_PAUSED = "������ע����\n";
constexpr auto HINT_USING = "�������ϻ���\n";
constexpr auto HINT_UNUSED = "�������»���\n";
constexpr auto HINT_ASK_UNUSE = "�뽫���»����ٲ�����\n";
constexpr auto HINT_ASK_USING = "�뽫���ϻ����ٲ�����\n";
constexpr auto HINT_ASK_QUIT = "���˳���ϵͳ��Ӧ�������ã�\n";
constexpr auto HINT_ASK_PATH = "��������·����";
constexpr auto HINT_ASK_VALUE = "��������ֵ��";
constexpr auto HINT_BALANCE_SHORTAGE = "�����㣡\n";
constexpr auto HINT_SUCCESS = "�����ɹ���\n";
constexpr auto HINT_NULL_RESAULT = "��ѯ���Ϊ�գ�\n";

//Ĭ��·��
constexpr auto CARDPATH = "D:\\card.txt";
constexpr auto INFOPATH = "D:\\info.txt";
constexpr auto LOGPATH = "D:\\log.txt";
constexpr auto SETTINGPATH = "D:\\setting.txt";