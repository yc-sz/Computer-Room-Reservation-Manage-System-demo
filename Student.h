#pragma once
#include"User.h"
#include"BookProcesser.h"
#include<vector>
//#define	STUFILE "student.csv"

class Student :public User
{
private:
	string stu_num;
	BookProcesser bp;
	int*** room_status;
	int room_num;
	int day_num;
	int time_num;

	void apply_book();		//����ԤԼ
	void show_my_book();	//�鿴�Լ���ԤԼ
	void show_all_book();	//�鿴����ԤԼ
	void cancle_book();		//ȡ��ԤԼ
	void get_room_status();	//��ȡ����ԤԼ״̬
	void show_room_status();//��ʾ����ԤԼ״̬

public:
	Student(string, string, string);	//�вι���
	~Student();

	void set_num(string);
	string get_num();
	void set_name(string);
	string get_name();
	void set_passwd(string);
	string get_passwd();

	void operat_menu();
};