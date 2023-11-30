#pragma once
#include<iostream>
#include<map>
#include<fstream>
#include<string>
#include"Admin.h"
#include"Teacher.h"
#include"Student.h"
#define ADMFILE "admin.csv"
#define TEAFILE "teacher.csv"
#define	STUFILE "student.csv"
using namespace std;

class ManagerSystem {
private:
	map<string, string> adm_acc_passwd;	//����Ա�˺� <�˺ţ�����>
	map<string, string> stu_acc_passwd;	//ѧ���˺�
	map<string, string> tea_acc_passwd;	//��ʦ�˺�
	map<string, string> acc_name;		//�˺���������

	void load_accounts(string, map<string, string>&);	//��ȡ�˺�
public:
	void show_menu();	//��ʾ�˵�
	void exit_system();	//�˳�ϵͳ
	void stu_login();	//ѧ����¼
	void tea_login();	//��ʦ��¼
	void admin_login();	//����Ա��¼
};