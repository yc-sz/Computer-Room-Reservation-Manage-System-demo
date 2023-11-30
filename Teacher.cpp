#include "Teacher.h"

void Teacher::show_all_book()
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
		cout << "申请人账号\t申请人姓名\t申请机房号\t申请日期\t申请时段" << endl;
		for (map<int, vector<string>>::iterator it = m_temp.begin(); it != m_temp.end(); it++)
		{
			cout << it->second[0] << "\t\t"
				<< it->second[1] << "\t\t"
				<< it->second[2] << "\t\t"
				<< "周" << it->second[3] << "\t\t"
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
		cout << "申请人账号\t申请人姓名\t审核人账号\t审核人姓名\t申请机房号\t申请日期\t申请时段\t审核结果" << endl;
		for (map<int, vector<string>>::iterator it = m_temp.begin(); it != m_temp.end(); it++)
		{
			cout << it->second[0] << "\t\t"
				<< it->second[1] << "\t\t"
				<< it->second[2] << "\t\t"
				<< it->second[3] << "\t\t"
				<< it->second[4] << "\t\t"
				<< "周" << it->second[5] << "\t\t"
				<< (it->second[6].compare("1") == 0 ? "上午" : "下午") << "\t\t"
				<< (it->second[7].compare("1") == 0 ? "通过" : "不通过")
				<< endl;
		}
	}
	
	system("pause");
	system("cls");
}

void Teacher::audit_book()
{
	map<int, vector<string>> m_audit;
	m_audit = this->bp.get_all_audit();
	if (m_audit.size() > 0) {
		cout << "待审核记录如下:" << endl;
		for (map<int, vector<string>>::iterator it = m_audit.begin(); it != m_audit.end(); it++)
		{
			cout << "编号: " << it->first
				<< " 申请人账号: " << it->second[0]
				<< " 申请人姓名: " << it->second[1]
				<< " 申请机房号: " << it->second[2]
				<< " 申请日期: 周" << it->second[3]
				<< " 申请时段: " << (it->second[4].compare("1") == 0 ? "上午" : "下午")
				<<  "审核状态: " << (it->second[5].compare("-1") == 0 ? "待审核" : "已审核")
				<< endl;
		}
		int num;
		cout << "请输入要审核的记录的编号:";
		cin >> num;
		int result;
		cout << "请输入审核结果（0、不通过 1、通过）: ";
		cin >> result;
		this->bp.apply_audit(this->tea_num, this->name, num, result);
		cout << "审核完成!" << endl;
	}
	else
	{
		cout << "暂无待审核的预约申请!" << endl;
	}
	system("pause");
	system("cls");
}

Teacher::Teacher(string tea_num, string name, string passwd)
{
	this->tea_num = tea_num;
	this->name = name;
	this->password = passwd;
}

Teacher::~Teacher()
{
}

void Teacher::set_num(string tea_num)
{
	this->tea_num = tea_num;
}

string Teacher::get_num()
{
	return this->tea_num;
}

void Teacher::set_name(string name)
{
	this->name = name;
}

string Teacher::get_name()
{
	return this->name;
}

void Teacher::set_passwd(string passwd)
{
	this->password = passwd;
}

string Teacher::get_passwd()
{
	return this->password;
}

void Teacher::operat_menu()
{
	while (true)
	{
		cout << "\t\t你好，" << this->get_name() << "！\t\t" << endl;
		cout << "------------------------------------------" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t1、查看所有预约\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t2、审核预约\t\t|" << endl;
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
			this->show_all_book();
			break;
		case 2:
			this->audit_book();
			break;
		default:
			cout << "请输入正确的选项！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
