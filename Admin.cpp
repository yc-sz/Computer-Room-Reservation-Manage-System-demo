#include "Admin.h"

void Admin::add_account_menu()
{
	cout << "----------- ��ѡ��Ҫ��ӵ��˺� -----------" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t1��ѧ���˺�\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t2����ʦ�˺�\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t3������Ա�˺�\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "------------------------------------------" << endl;
	cout << "���������ѡ��: ";
	int select;
	cin >> select;
	switch (select)
	{
	case 1:
	{
		string acc = "";
		string name = "";
		string passwd = "";
		cout << "---------�������ѧ���˺�---------" << endl;
		cout << "�������˺�: ";
		cin >> acc;
		cout << "����������: ";
		cin >> name;
		cout << "����������: ";
		cin >> passwd;
		if (acc.compare("") != 0 && passwd.compare("") != 0)
		{
			this->add_acc(STUFILE, acc, name, passwd);
		}
		else
		{
			cout << "��������ȷ���˺�����!" << endl;
		}
		break;
	}
	case 2:
	{
		string acc = "";
		string name = "";
		string passwd = "";
		cout << "---------������ӽ�ʦ�˺�---------" << endl;
		cout << "�������˺�: ";
		cin >> acc;
		cout << "����������: ";
		cin >> name;
		cout << "����������: ";
		cin >> passwd;
		if (acc.compare("") != 0 && passwd.compare("") != 0)
		{
			this->add_acc(TEAFILE, acc, name, passwd);
		}
		else
		{
			cout << "��������ȷ���˺�����!" << endl;
		}
		break;
	}
	case 3:
	{
		string acc = "";
		string name = "";
		string passwd = "";
		cout << "--------������ӹ���Ա�˺�--------" << endl;
		cout << "�������˺�: ";
		cin >> acc;
		cout << "����������: ";
		cin >> name;
		cout << "����������: ";
		cin >> passwd;
		if (acc.compare("") != 0 && passwd.compare("") != 0)
		{
			this->add_acc(ADMFILE, acc, name, passwd);
		}
		else
		{
			cout << "��������ȷ���˺�����!" << endl;
		}
		break;
	}
	default:
		break;
	}
}

void Admin::show_account_menu()
{
	cout << "--------- ��ѡ��Ҫ�鿴���˺���Ϣ ---------" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t1��ѧ���˺�\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t2����ʦ�˺�\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "|\t\t3������Ա�˺�\t\t|" << endl;
	cout << "|\t\t\t\t\t|" << endl;
	cout << "------------------------------------------" << endl;
	cout << "���������ѡ��: ";
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
	//��ȡroom.csv�ļ�
	ifstream ifs(ROOMFILE, ios::in);
	if (ifs.is_open())
	{
		char ch;
		ifs >> ch;
		if (!ifs.eof())
		{
			ifs.putback(ch);
			string buff;
			cout << "������Ϣ����:" << endl;
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
				cout << "���: " << num << " ����: " << capacity << " �� " << endl;
			}
		}
		else
		{
			cout << ROOMFILE << "�ļ�Ϊ�գ�" << endl;
		}
	}
	else
	{
		cout << ROOMFILE <<"�ļ���ʧ�ܻ򲻴��ڣ�" << endl;
	}
	ifs.close();
}

void Admin::clear_book()
{
	int select = 2;
	cout << "ȷ�����?��1��ȷ�� 2��ȡ����: ";
	cin >> select;
	if (select == 1)
	{
		this->bp.clear_record_audit();
		cout << "������" << endl;
	}
}

void Admin::load_acc(string PATH, bool &file_error, map<string, vector<string>> &all_acc)
{
	ifstream ifs(PATH, ios::in);
	if (ifs.is_open())		//�ļ��򿪳ɹ�
	{	
		char ch;
		ifs >> ch;
		if (!ifs.eof()) //�ļ��ǿ�
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
			cout << PATH << "�ļ�Ϊ�գ�" << endl;
		}
	}
	else
	{
		cout << PATH <<"�ļ���ʧ�ܻ��ļ������ڣ�" << endl;
	}
	ifs.close();
}

void Admin::show_acc(string PATH)
{
	string identity = "";
	if (PATH.compare(ADMFILE) == 0) 
	{
		identity = "����Ա";
	}
	else if (PATH.compare(TEAFILE) == 0) 
	{
		identity = "��ʦ";
	}
	else if (PATH.compare(STUFILE) == 0)
	{
		identity = "ѧ��";
	}
	bool file_error = true;
	map<string, vector<string>> all_acc;
	all_acc.clear();
	this->load_acc(PATH, file_error, all_acc);
	if (file_error) {
		return;
	}
	cout << identity <<"�˺���Ϣ����:" << endl;
	for (map<string, vector<string>>::const_iterator it = all_acc.begin(); it != all_acc.end(); it++)
	{
		cout << "�˺�: " << it->first << " ����: " << (it->second)[0] << " ����: " << (it->second)[1] << endl;
	}
	cout << "----------------------------------" << endl;
}

void Admin::add_acc(string PATH, string acc, string name, string passwd)
{
	ifstream ifs(PATH, ios::in);	//����ļ��Ƿ�򿪳ɹ�
	if (ifs.is_open())					
	{	//�򿪳ɹ�������˺��Ƿ��ظ�
		if (!this->acc_exist(ifs, acc))
		{	//�˺Ų�����
			ifs.close();
			ofstream ofs(PATH, ios::out | ios::app);	//׷�����
			ofs << acc << "," << name << "," << passwd << "," << endl;
			ofs.close();
			cout << "��ӳɹ�!" << endl;
		}
		else
		{
			cout << "�˺��Ѵ��ڣ�" << endl;
		}
	}
	else
	{	//��ʧ��
		ifs.close();
		ofstream ofs(PATH, ios::out | ios::trunc);	//�½��ļ����
		ofs << acc << "," << name << "," << passwd << "," << endl;
		ofs.close();
	}
}

bool Admin::acc_exist(ifstream& ifs, string acc)
{
	set<string> acc_in_file;
	string buff = "";
	//ֻ��ȡ�˺�
	while (ifs >> buff)
	{
		string temp_acc;
		int pos = -1;
		int start = 0;
		pos = buff.find(",", start);
		temp_acc = buff.substr(start, pos - start);
		acc_in_file.insert(temp_acc);
	}
	//����˺��Ƿ����
	if (acc_in_file.find(acc) == acc_in_file.end())
	{	
		//������
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
		cout << "\t\t��ã�" << this->get_name() << "��\t\t" << endl;
		cout << "------------------------------------------" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t1������˺�\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t2���鿴�˺�\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t3���鿴����\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t4�����ԤԼ\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t0��ע����¼\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "------------------------------------------" << endl;
		cout << "���������ѡ��: ";
		int select;
		cin >> select;
		switch (select)
		{
		case 0:
			cout << "ע���ɹ�!" << endl;
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
			cout << "��������ȷ��ѡ�" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
