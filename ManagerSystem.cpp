#include"ManagerSystem.h"

void ManagerSystem::show_menu() 
{
	cout << "---------- 欢迎使用机房预约系统 ----------" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t1、学生登录\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t2、教师登录\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t3、管理员登录\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t0、退出系统\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "------------------------------------------" << endl;
}

void ManagerSystem::exit_system() 
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void ManagerSystem::stu_login()
{
	this->load_accounts(STUFILE, this->stu_acc_passwd);	//将学生的账号密码从文件中读出
	string stu_num = "";
	string passwd = "";
	cout << "请输入你的学号: ";
	cin >> stu_num;
	cout << "请输入你的密码: ";
	cin >> passwd;
	map<string, string>::iterator it = this->stu_acc_passwd.find(stu_num);
	if ( it != this->stu_acc_passwd.end())			//学号存在
	{
		if ((it->second).compare(passwd) == 0)		//密码正确
		{
			string name = this->acc_name[it->first];
			Student stu(it->first, name, it->second);
			system("cls");
			stu.operat_menu();
		}
		else
		{
			cout << "密码错误！" << endl;
		}
	}
	else											//学号不存在
	{
		cout << "学号不存在！" << endl;
	}
	system("pause");
	system("cls");
}

void ManagerSystem::tea_login()
{
	this->load_accounts(TEAFILE, this->tea_acc_passwd);	//将教师账号密码从文件读出
	string tea_num = "";
	string passwd = "";
	cout << "请输入你的职工号: ";
	cin >> tea_num;
	cout << "请输入你的密码: ";
	cin >> passwd;
	map<string, string>::iterator it = this->tea_acc_passwd.find(tea_num);
	if (it != this->tea_acc_passwd.end())		//学号正确
	{
		if ((it->second).compare(passwd) == 0)
		{
			string name = this->acc_name[it->first];
			Teacher tea(it->first, name, it->second);
			system("cls");
			tea.operat_menu();
		}
		else
		{
			cout << "密码错误！" << endl;
		}
	}
	else
	{
		cout << "帐号不存在！" << endl;
	}
	system("pause");
	system("cls");
}

void ManagerSystem::admin_login()
{
	this->load_accounts(ADMFILE, this->adm_acc_passwd);	//将管理员账号密码从文件读出 
	string adm_num = "";
	string passwd = "";
	cout << "请输入你的管理员帐号: ";
	cin >> adm_num;
	cout << "请输入你的密码: ";
	cin >> passwd;
	map<string, string>::const_iterator it = this->adm_acc_passwd.find(adm_num);
	if (it != this->adm_acc_passwd.end())		//帐号正确
	{
		if ((it->second).compare(passwd) == 0)
		{
			string name = this->acc_name[it->first];
			Admin adm(it->first, name, it->second);
			system("cls");
			adm.operat_menu();
		}
		else
		{
			cout << "密码错误！" << endl;
		}
	}
	else
	{
		cout << "帐号不存在！" << endl;
	}
	system("pause");
	system("cls");
}

void ManagerSystem::load_accounts(string PATH, map<string, string> &acc_passwd)	//传入文件路径，<账号，密码容器>
{
	ifstream ifs(PATH, ios::in);
	if (!ifs.is_open())	//若文件打开失败
	{
		//cout << "文件打开失败或文件不存在！" << endl;
	}
	else				//文件打开成功
	{
		char ch;
		ifs >> ch;
		if (!ifs.eof()) //若文件不为空 
		{	
			ifs.putback(ch);
			string buf;
			while (ifs >> buf)
			{
				string acc;
				string name;
				string passwd;

				int pos = -1;   //","的索引
				int start = 0;  //开始划分子串索引
				int count = 0;  //计数器，小于等于2
				while (true) 
				{
					pos = buf.find(",", start);
					if (pos == -1)
					{
						break;
					}
					else
					{   
						if (count > 2) 
						{
							break;
						}
						switch (count)
						{
						case 0:
							acc = buf.substr(start, pos - start);
							start = pos + 1;
							break;
						case 1:
							name = buf.substr(start, pos - start);
							start = pos + 1;
							break;
						case 2:
							passwd = buf.substr(start, pos - start);
							start = pos + 1;
							break;
						default:
							break;
						}
						count++;
					}
				}
				acc_passwd.insert(make_pair(acc, passwd));
				this->acc_name.insert(make_pair(acc, name));
			}
		}
	}
	ifs.close();
}
