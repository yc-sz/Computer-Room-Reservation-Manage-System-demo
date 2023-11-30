#include"ManagerSystem.h"

void ManagerSystem::show_menu() 
{
	cout << "---------- ��ӭʹ�û���ԤԼϵͳ ----------" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t1��ѧ����¼\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t2����ʦ��¼\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t3������Ա��¼\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t0���˳�ϵͳ\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "------------------------------------------" << endl;
}

void ManagerSystem::exit_system() 
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void ManagerSystem::stu_login()
{
	this->load_accounts(STUFILE, this->stu_acc_passwd);	//��ѧ�����˺�������ļ��ж���
	string stu_num = "";
	string passwd = "";
	cout << "���������ѧ��: ";
	cin >> stu_num;
	cout << "�������������: ";
	cin >> passwd;
	map<string, string>::iterator it = this->stu_acc_passwd.find(stu_num);
	if ( it != this->stu_acc_passwd.end())			//ѧ�Ŵ���
	{
		if ((it->second).compare(passwd) == 0)		//������ȷ
		{
			string name = this->acc_name[it->first];
			Student stu(it->first, name, it->second);
			system("cls");
			stu.operat_menu();
		}
		else
		{
			cout << "�������" << endl;
		}
	}
	else											//ѧ�Ų�����
	{
		cout << "ѧ�Ų����ڣ�" << endl;
	}
	system("pause");
	system("cls");
}

void ManagerSystem::tea_login()
{
	this->load_accounts(TEAFILE, this->tea_acc_passwd);	//����ʦ�˺�������ļ�����
	string tea_num = "";
	string passwd = "";
	cout << "���������ְ����: ";
	cin >> tea_num;
	cout << "�������������: ";
	cin >> passwd;
	map<string, string>::iterator it = this->tea_acc_passwd.find(tea_num);
	if (it != this->tea_acc_passwd.end())		//ѧ����ȷ
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
			cout << "�������" << endl;
		}
	}
	else
	{
		cout << "�ʺŲ����ڣ�" << endl;
	}
	system("pause");
	system("cls");
}

void ManagerSystem::admin_login()
{
	this->load_accounts(ADMFILE, this->adm_acc_passwd);	//������Ա�˺�������ļ����� 
	string adm_num = "";
	string passwd = "";
	cout << "��������Ĺ���Ա�ʺ�: ";
	cin >> adm_num;
	cout << "�������������: ";
	cin >> passwd;
	map<string, string>::const_iterator it = this->adm_acc_passwd.find(adm_num);
	if (it != this->adm_acc_passwd.end())		//�ʺ���ȷ
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
			cout << "�������" << endl;
		}
	}
	else
	{
		cout << "�ʺŲ����ڣ�" << endl;
	}
	system("pause");
	system("cls");
}

void ManagerSystem::load_accounts(string PATH, map<string, string> &acc_passwd)	//�����ļ�·����<�˺ţ���������>
{
	ifstream ifs(PATH, ios::in);
	if (!ifs.is_open())	//���ļ���ʧ��
	{
		//cout << "�ļ���ʧ�ܻ��ļ������ڣ�" << endl;
	}
	else				//�ļ��򿪳ɹ�
	{
		char ch;
		ifs >> ch;
		if (!ifs.eof()) //���ļ���Ϊ�� 
		{	
			ifs.putback(ch);
			string buf;
			while (ifs >> buf)
			{
				string acc;
				string name;
				string passwd;

				int pos = -1;   //","������
				int start = 0;  //��ʼ�����Ӵ�����
				int count = 0;  //��������С�ڵ���2
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
