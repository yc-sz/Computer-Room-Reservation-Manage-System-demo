#pragma once
#include"User.h"
#include"BookProcesser.h"
#include<vector>
#include<map>
#include<set>
#include<fstream>
#include<string>
#define ADMFILE "admin.csv"
#define TEAFILE "teacher.csv"
#define	STUFILE "student.csv"
#define ROOMFILE "room.csv"

class Admin :public User 
{
private:
	string adm_num;
	BookProcesser bp;

	void add_account_menu();	//����˺Ų˵�
	void show_account_menu();	//�鿴�˺Ų˵�
	void show_compuroom();		//�鿴����
	void clear_book();			//���ԤԼ
	void load_acc(string, bool&, map<string, vector<string>>&);	//�����˺�
	void show_acc(string);		//�鿴�˺�
	void add_acc(string, string, string, string);		//����˺�
	bool acc_exist(ifstream&, string);		//����˺��Ƿ��ظ�

public:
	Admin(string, string, string);
	~Admin();

	void set_num(string);
	string get_num();
	void set_name(string);
	string get_name();
	void set_passwd(string);
	string get_passwd();

	void operat_menu();
};