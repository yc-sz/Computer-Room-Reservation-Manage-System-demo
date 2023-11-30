#include "Admin.h"

void Admin::add_account_menu()
{
	cout << "----------- 请选择要添加的账号 -----------" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t1、学生账号\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t2、教师账号\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t3、管理员账号\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "------------------------------------------" << endl;
	cout << "请输入你的选择: ";
	int select;
	cin >> select;
	switch (select)
	{
	case 1:
	{
		string acc = "";
		string name = "";
		string passwd = "";
		cout << "---------正在添加学生账号---------" << endl;
		cout << "请输入账号: ";
		cin >> acc;
		cout << "请输入姓名: ";
		cin >> name;
		cout << "请输入密码: ";
		cin >> passwd;
		if (acc.compare("") != 0 && passwd.compare("") != 0)
		{
			this->add_acc(STUFILE, acc, name, passwd);
		}
		else
		{
			cout << "请输入正确的账号密码!" << endl;
		}
		break;
	}
	case 2:
	{
		string acc = "";
		string name = "";
		string passwd = "";
		cout << "---------正在添加教师账号---------" << endl;
		cout << "请输入账号: ";
		cin >> acc;
		cout << "请输入姓名: ";
		cin >> name;
		cout << "请输入密码: ";
		cin >> passwd;
		if (acc.compare("") != 0 && passwd.compare("") != 0)
		{
			this->add_acc(TEAFILE, acc, name, passwd);
		}
		else
		{
			cout << "请输入正确的账号密码!" << endl;
		}
		break;
	}
	case 3:
	{
		string acc = "";
		string name = "";
		string passwd = "";
		cout << "--------正在添加管理员账号--------" << endl;
		cout << "请输入账号: ";
		cin >> acc;
		cout << "请输入姓名: ";
		cin >> name;
		cout << "请输入密码: ";
		cin >> passwd;
		if (acc.compare("") != 0 && passwd.compare("") != 0)
		{
			this->add_acc(ADMFILE, acc, name, passwd);
		}
		else
		{
			cout << "请输入正确的账号密码!" << endl;
		}
		break;
	}
	default:
		break;
	}
}

void Admin::show_account_menu()
{
	cout << "--------- 请选择要查看的账号信息 ---------" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t1、学生账号\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t2、教师账号\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t3、管理员账号\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "------------------------------------------" << endl;
	cout << "请输入你的选择: ";
	int select;
	cin >> select;
	switch (select)
	{
	case 1:
		this->show_acc(STUFILE);
		break;
	case 2:
		this->show_acc(TEAFILE);
		break;
	case 3:
		this->show_acc(ADMFILE);
		break;
	default:
		break;
	}
}

void Admin::show_compuroom()
{
	//读取room.csv文件
	ifstream ifs(ROOMFILE, ios::in);
	if (ifs.is_open())
	{
		char ch;
		ifs >> ch;
		if (!ifs.eof())
		{
			ifs.putback(ch);
			string buff;
			cout << "机房信息如下:" << endl;
			while (ifs >> buff)
			{
				string num;
				string capacity;
				int pos = -1;
				int start = 0;
				int count = 0;
				while (true)
				{
					if (count > 2)
					{
						break;
					}
					switch (count)
					{
					case 0:
						pos = buff.find(",", start);
						num = buff.substr(start, pos - start);
						start = pos + 1;
						break;
					case 1:
						pos = buff.find(",", start);
						capacity = buff.substr(start, pos - start);
						start = pos + 1;
						break;
					default:
						break;
					}
					count++;
				}
				cout << "编号: " << num << " 容量: " << capacity << " 人 " << endl;
			}
		}
		else
		{
			cout << ROOMFILE << "文件为空！" << endl;
		}
	}
	else
	{
		cout << ROOMFILE <<"文件打开失败或不存在！" << endl;
	}
	ifs.close();
}

void Admin::clear_book()
{
	int select = 2;
	cout << "确认清空?（1、确认 2、取消）: ";
	cin >> select;
	if (select == 1)
	{
		this->bp.clear_record_audit();
		cout << "清空完成" << endl;
	}
}

void Admin::load_acc(string PATH, bool &file_error, map<string, vector<string>> &all_acc)
{
	ifstream ifs(PATH, ios::in);
	if (ifs.is_open())		//文件打开成功
	{	
		char ch;
		ifs >> ch;
		if (!ifs.eof()) //文件非空
		{	
			ifs.putback(ch);
			string buff;
			while (ifs >> buff)
			{
				string acc;
				string name;
				string passwd;
				int pos = -1;
				int start = 0;
				int count = 0;
				while (true)
				{
					pos = buff.find(",", start);
					if (pos == -1)
					{
						break;
					}
					else
					{
						switch (count)
						{
						case 0:
							acc = buff.substr(start, pos - start);
							start = pos + 1;
							break;
						case 1:
							name = buff.substr(start, pos - start);
							start = pos + 1;
							break;
						case 2:
							passwd = buff.substr(start, pos - start);
							start = pos + 1;
							break;
						default:
							break;
						}
						count++;
					}
				}
				vector<string> name_passwd;
				name_passwd.push_back(name);
				name_passwd.push_back(passwd);
				all_acc.insert(make_pair(acc, name_passwd));
			}
			file_error = false;
		}
		else
		{
			cout << PATH << "文件为空！" << endl;
		}
	}
	else
	{
		cout << PATH <<"文件打开失败或文件不存在！" << endl;
	}
	ifs.close();
}

void Admin::show_acc(string PATH)
{
	string identity = "";
	if (PATH.compare(ADMFILE) == 0) 
	{
		identity = "管理员";
	}
	else if (PATH.compare(TEAFILE) == 0) 
	{
		identity = "教师";
	}
	else if (PATH.compare(STUFILE) == 0)
	{
		identity = "学生";
	}
	bool file_error = true;
	map<string, vector<string>> all_acc;
	all_acc.clear();
	this->load_acc(PATH, file_error, all_acc);
	if (file_error) {
		return;
	}
	cout << identity <<"账号信息如下:" << endl;
	for (map<string, vector<string>>::const_iterator it = all_acc.begin(); it != all_acc.end(); it++)
	{
		cout << "账号: " << it->first << " 姓名: " << (it->second)[0] << " 密码: " << (it->second)[1] << endl;
	}
	cout << "----------------------------------" << endl;
}

void Admin::add_acc(string PATH, string acc, string name, string passwd)
{
	ifstream ifs(PATH, ios::in);	//检测文件是否打开成功
	if (ifs.is_open())					
	{	//打开成功，检测账号是否重复
		if (!this->acc_exist(ifs, acc))
		{	//账号不存在
			ifs.close();
			ofstream ofs(PATH, ios::out | ios::app);	//追加输出
			ofs << acc << "," << name << "," << passwd << "," << endl;
			ofs.close();
			cout << "添加成功!" << endl;
		}
		else
		{
			cout << "账号已存在！" << endl;
		}
	}
	else
	{	//打开失败
		ifs.close();
		ofstream ofs(PATH, ios::out | ios::trunc);	//新建文件输出
		ofs << acc << "," << name << "," << passwd << "," << endl;
		ofs.close();
	}
}

bool Admin::acc_exist(ifstream& ifs, string acc)
{
	set<string> acc_in_file;
	string buff = "";
	//只读取账号
	while (ifs >> buff)
	{
		string temp_acc;
		int pos = -1;
		int start = 0;
		pos = buff.find(",", start);
		temp_acc = buff.substr(start, pos - start);
		acc_in_file.insert(temp_acc);
	}
	//检测账号是否存在
	if (acc_in_file.find(acc) == acc_in_file.end())
	{	
		//不存在
		return false;
	}
	return true;
}

Admin::Admin(string adm_num, string name, string passwd)
{
	this->adm_num = adm_num;
	this->name = name;
	this->password = passwd;
}

Admin::~Admin()
{
}

void Admin::set_num(string num)
{   
	this->adm_num = num;
}

string Admin::get_num()
{
	return this->adm_num;
}

void Admin::set_name(string name)
{
	this->name = name;
}

string Admin::get_name()
{
	return this->name;
}

void Admin::set_passwd(string passwd)
{
	this->password = passwd;
}

string Admin::get_passwd()
{
	return this->password;
}

void Admin::operat_menu()
{
	while (true)
	{
		cout << "\t\t你好，" << this->get_name() << "！\t\t" << endl;
		cout << "------------------------------------------" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t1、添加账号\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t2、查看账号\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t3、查看机房\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t4、清空预约\t\t|" << endl;
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
			this->add_account_menu();
			system("pause");
			system("cls");
			break;
		case 2:
			this->show_account_menu();
			system("pause");
			system("cls");
			break;
		case 3:
			this->show_compuroom();
			system("pause");
			system("cls");
			break;
		case 4:
			this->clear_book();
			system("pause");
			system("cls");
			break;
		default:
			cout << "请输入正确的选项！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
