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
	map<string, string> adm_acc_passwd;	//管理员账号 <账号，密码>
	map<string, string> stu_acc_passwd;	//学生账号
	map<string, string> tea_acc_passwd;	//教师账号
	map<string, string> acc_name;		//账号姓名对组

	void load_accounts(string, map<string, string>&);	//读取账号
public:
	void show_menu();	//显示菜单
	void exit_system();	//退出系统
	void stu_login();	//学生登录
	void tea_login();	//教师登录
	void admin_login();	//管理员登录
};