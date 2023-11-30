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

	void apply_book();		//申请预约
	void show_my_book();	//查看自己的预约
	void show_all_book();	//查看所有预约
	void cancle_book();		//取消预约
	void get_room_status();	//获取教室预约状态
	void show_room_status();//显示教室预约状态

public:
	Student(string, string, string);	//有参构造
	~Student();

	void set_num(string);
	string get_num();
	void set_name(string);
	string get_name();
	void set_passwd(string);
	string get_passwd();

	void operat_menu();
};