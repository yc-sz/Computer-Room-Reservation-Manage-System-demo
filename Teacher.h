#pragma once
#include"User.h"
#include"BookProcesser.h"
//#define TEAFILE "teacher.csv"

class Teacher :public User
{
private:
	string tea_num;
	BookProcesser bp;

	void show_all_book();	//�鿴����ԤԼ
	void audit_book();		//���ԤԼ

public:
	Teacher(string, string, string);
	~Teacher();

	void set_num(string);
	string get_num();
	void set_name(string);
	string get_name();
	void set_passwd(string);
	string get_passwd();

	void operat_menu();
};