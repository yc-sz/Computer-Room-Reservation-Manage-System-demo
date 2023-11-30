#pragma once
#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<vector>
#define STATUSFILE "room_status.csv"//存放机房预约状态	每3行一个机房状态，第一行机房编号，第二行每天上午的状态，第三行每天下午的状态，0表示空闲，1表示占用
#define RECORDFILE "record.csv"		//存放所有审核后的记录 申请人账号,申请人姓名,审核人账号,审核人姓名,机房号,日期,时段,审核结果,	0表示不通过审核，1表示通过审核，-2表示已取消
#define AUDITFILE "audit.csv"		//存放待审核的记录 申请人账号,申请人姓名,申请机房号,申请日期,申请时段,审核状态		//-1表示待审核，-2表示已取消
#define ROOMFILE "room.csv"			//存放机房信息
using namespace std;

class BookProcesser
{
private:
	int*** room_status;					//存储教室预约状态的三维数组，教室编号，天，时段
	map<int, int> room_num_capacity;	//记录教室编号，容量
	map<int, vector<string>> m_audit;	//存储编号，待审核记录
	
	int room_num = 3;
	int day_num = 5;
	int time_num = 2;

	void load_status();			//加载文件中保存的教室状态
	void save_status();			//保存教室状态到文件
	void init_status();			//创建并初始化教室状态数组
	void load_room_capacity();   //加载教室数、天数、时间段数
	void record_apply(string, string, string, string, string, string, string, int);	//记录审核后的结果到record.csv

public:
	BookProcesser();
	~BookProcesser();

	int*** get_room_status();
	int get_room_num();
	int get_day_num();
	int get_time_num();
	int get_room_capacity(int);
	void apply_receive(string, string, int, int, int);	//学生预约接收器
	void apply_audit(string, string, int, int);			//教师审核接收器
	vector<vector<string>> get_personl_apply(string);	//获取个人预约记录
	map<int, vector<string>> get_all_audit();			//获取所有待审核记录
	map<int, vector<string>> get_all_record();			//获取所有审核后的记录
	void clear_record_audit();							//清空所有预约信息，包含待审核信息
	bool cancel_personal_book(vector<string>);			//取消个人预约
};