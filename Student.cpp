#include "Student.h"

void Student::apply_book()
{
	
	this->show_room_status();
	int room = -1;
	int day = -1;
	int time = -1;
	cout << "----------请输入你要预约的机房----------" << endl;
	cout << "机房号: ";
	cin >> room;
	cout << "周: ";
	cin >> day;
	cout << "时段(1、上午 2、下午): ";
	cin >> time;
	this->bp.apply_receive(this->stu_num, this->name, room, day, time);
	cout << "预约提交成功，等待审核中..." << endl;
}

void Student::show_my_book()
{
	cout << "----------您的个人预约如下----------" << endl;
	vector<vector<string>> v_temp;
	v_temp = this->bp.get_personl_apply(this->stu_num);
	if (v_temp.size() != 0)
	{
		for (vector<vector<string>>::const_iterator it_line = v_temp.begin(); it_line != v_temp.end(); it_line++)
		{
			string status;
			if ((*it_line)[5].compare("-1") == 0)
			{
				status = "待审核";
			}
			else if ((*it_line)[5].compare("0") == 0)
			{
				status = "审核不通过";
			}
			else if ((*it_line)[5].compare("1") == 0)
			{
				status = "审核通过";
			}
			else if ((*it_line)[5].compare("-2") == 0)
			{
				status = "已取消";
			}
			cout << "申请人账号: " << (*it_line)[0]
				<< " | 申请人姓名: " << (*it_line)[1]
				<< " | 申请机房号: " << (*it_line)[2]
				<< " | 日期: 周" << (*it_line)[3]
				<< " | 时间段: " << ((*it_line)[4].compare("1") == 0 ? "上午" : "下午")
				<< " | 审核结果: " << status 
				<< endl;
		}
	}
	else
	{
		cout << "无个人预约记录!" << endl;
	}
}

void Student::show_all_book()
{
	map<int, vector<string>> m_temp;
	m_temp = this->bp.get_all_audit();
	cout << "-------所有预约记录如下-------" << endl;
	if (m_temp.size() == 0)
	{
		cout << "暂无待审核记录!" << endl;
	}
	else
	{
		cout << "-------待审核记录-------" << endl;
		cout << "申请人账号    申请人姓名    申请机房号    申请日期    申请时段" << endl;
		for (map<int, vector<string>>::iterator it = m_temp.begin(); it != m_temp.end(); it++)
		{
			cout << it->second[0] << "    "
				<< it->second[1] << "    "
				<< it->second[2] << "    "
				<< "周" << it->second[3] << "    "
				<< (it->second[4].compare("1") == 0 ? "上午" : "下午")
				<< endl;
		}
	}

	m_temp = this->bp.get_all_record();
	if (m_temp.size() == 0)
	{
		cout << "暂无已审核记录!" << endl;
	}
	else
	{
		cout << "-------已审核记录-------" << endl;
		cout << "申请人账号    申请人姓名    审核人账号    审核人姓名    申请机房号    申请日期    申请时段    审核结果" << endl;
		for (map<int, vector<string>>::iterator it = m_temp.begin(); it != m_temp.end(); it++)
		{
			string status;
			if (it->second[7].compare("0") == 0)
			{
				status = "未通过";
			}
			else if (it->second[7].compare("-2") == 0)
			{
				status = "已取消";
			}
			else if (it->second[7].compare("1") == 0)
			{
				status = "已通过";
			}

			cout << it->second[0] << "    "
				<< it->second[1] << "    "
				<< it->second[2] << "    "
				<< it->second[3] << "    "
				<< it->second[4] << "    "
				<< "周" << it->second[5] << "    "
				<< (it->second[6].compare("1") == 0 ? "上午" : "下午")
				<< status
				<< endl;
		}
	}

	system("pause");
	system("cls");
}

void Student::cancle_book()
{
	int i = 0;
	vector<vector<string>> v_temp;
	v_temp = this->bp.get_personl_apply(this->stu_num);
	if (!v_temp.empty())
	{
		cout << "---------审核中或预约成功的记录如下----------" << endl;
		cout << "编号\t申请人账号\t申请人姓名\t申请机房号\t申请日期\t申请时段\t审核状态" << endl;
		for (vector<vector<string>>::iterator it = v_temp.begin(); it != v_temp.end(); it++)
		{
			string status;
			if (v_temp[i][5].compare("-1") == 0)
			{
				status = "待审核";
			}
			else if (v_temp[i][5].compare("-2") == 0)
			{
				status = "已取消";
			}
			else if (v_temp[i][5].compare("1") == 0)
			{
				status = "已通过";
			}
			else if (v_temp[i][5].compare("0") == 0)
			{
				status = "未通过";
			}

			cout << i + 1 << "\t"												//编号
				<< v_temp[i][0] << "\t\t"										//申请人账号
				<< v_temp[i][1] << "\t\t"										//申请人姓名
				<< v_temp[i][2] << "\t\t"										//申请机房号
				<< "周" << v_temp[i][3] << "\t\t"								//申请日期
				<< (v_temp[i][4].compare("1") == 0 ? "上午" : "下午") << "\t\t"	//申请时段
				<< status														//审核状态
				<< endl;
			i++;
		}
		int num;
		cout << "请输入要取消的申请编号: ";
		cin >> num;
		bool flag = this->bp.cancel_personal_book(v_temp[num - 1]);
		if (flag)
		{
			cout << "取消成功!" << endl;
		}
		else
		{
			cout << "取消失败!" << endl;
		}
	}
	else
	{
		cout << "无预约记录!" << endl;
	}
}

void Student::get_room_status()
{
	this->room_status = this->bp.get_room_status();
}

void Student::show_room_status()
{
	this->get_room_status();
	for (int room = 0; room < this->room_num; room++)
	{
		cout << "----------" << room + 1 << "号机房信息如下" << "----------" << endl;
		cout << "----------容量: " << this->bp.get_room_capacity(room + 1) << "人----------" << endl;
		cout << "     周一    周二    周三    周四    周五" << endl;
		for (int time = 0; time < this->time_num; time++)
		{
			if (time == 0)
			{
				cout << "上午: ";
			}
			else
			{
				cout << "下午: ";
			}
			for (int day = 0; day < this->day_num; day++)
			{
				cout << (this->room_status[room][day][time] == 0 ? "空闲" : "占用") << "    ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

Student::Student(string stu_num, string name, string passwd)
{
	this->stu_num = stu_num;
	this->name = name;
	this->password = passwd;
	this->get_room_status();
	this->room_num = this->bp.get_room_num();
	this->day_num = this->bp.get_day_num();
	this->time_num = this->bp.get_time_num();
}

Student::~Student()
{
}

void Student::set_num(string num)
{
	this->stu_num = num;
}

string Student::get_num()
{
	return this->stu_num;
}

void Student::set_name(string name)
{
	this->name = name;
}

string Student::get_name()
{
	return this->name;
}

void Student::set_passwd(string passwd)
{
	this->password = passwd;
}

string Student::get_passwd()
{
	return this->password;
}

void Student::operat_menu()
{
	while (true)
	{
		cout << "\t\t你好，" << this->get_name() << "！\t\t" << endl;
		cout << "------------------------------------------" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t1、申请预约\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t2、查看自己的预约\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t3、查看所有预约\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t4、取消预约\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t0、注销登录\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "------------------------------------------" << endl;
		cout << "请输入你的选择: ";
		int select;
		cin >> select;
		switch (select)
		{
		case 0:
			cout << "注销成功!" << endl;
			return;
			break;
		case 1:
			this->apply_book();
			break;
		case 2:
			this->show_my_book();
			break;
		case 3:
			this->show_all_book();
			break;
		case 4:
			this->cancle_book();
			break;
		default:
			cout << "请输入正确的选项！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
