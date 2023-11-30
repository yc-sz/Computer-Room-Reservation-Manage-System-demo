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

	void add_account_menu();	//添加账号菜单
	void show_account_menu();	//查看账号菜单
	void show_compuroom();		//查看机房
	void clear_book();			//清空预约
	void load_acc(string, bool&, map<string, vector<string>>&);	//加载账号
	void show_acc(string);		//查看账号
	void add_acc(string, string, string, string);		//添加账号
	bool acc_exist(ifstream&, string);		//检测账号是否重复

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