#pragma once
#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<vector>
#define STATUSFILE "room_status.csv"//��Ż���ԤԼ״̬	ÿ3��һ������״̬����һ�л�����ţ��ڶ���ÿ�������״̬��������ÿ�������״̬��0��ʾ���У�1��ʾռ��
#define RECORDFILE "record.csv"		//���������˺�ļ�¼ �������˺�,����������,������˺�,���������,������,����,ʱ��,��˽��,	0��ʾ��ͨ����ˣ�1��ʾͨ����ˣ�-2��ʾ��ȡ��
#define AUDITFILE "audit.csv"		//��Ŵ���˵ļ�¼ �������˺�,����������,���������,��������,����ʱ��,���״̬		//-1��ʾ����ˣ�-2��ʾ��ȡ��
#define ROOMFILE "room.csv"			//��Ż�����Ϣ
using namespace std;

class BookProcesser
{
private:
	int*** room_status;					//�洢����ԤԼ״̬����ά���飬���ұ�ţ��죬ʱ��
	map<int, int> room_num_capacity;	//��¼���ұ�ţ�����
	map<int, vector<string>> m_audit;	//�洢��ţ�����˼�¼
	
	int room_num = 3;
	int day_num = 5;
	int time_num = 2;

	void load_status();			//�����ļ��б���Ľ���״̬
	void save_status();			//�������״̬���ļ�
	void init_status();			//��������ʼ������״̬����
	void load_room_capacity();   //���ؽ�������������ʱ�����
	void record_apply(string, string, string, string, string, string, string, int);	//��¼��˺�Ľ����record.csv

public:
	BookProcesser();
	~BookProcesser();

	int*** get_room_status();
	int get_room_num();
	int get_day_num();
	int get_time_num();
	int get_room_capacity(int);
	void apply_receive(string, string, int, int, int);	//ѧ��ԤԼ������
	void apply_audit(string, string, int, int);			//��ʦ��˽�����
	vector<vector<string>> get_personl_apply(string);	//��ȡ����ԤԼ��¼
	map<int, vector<string>> get_all_audit();			//��ȡ���д���˼�¼
	map<int, vector<string>> get_all_record();			//��ȡ������˺�ļ�¼
	void clear_record_audit();							//�������ԤԼ��Ϣ�������������Ϣ
	bool cancel_personal_book(vector<string>);			//ȡ������ԤԼ
};