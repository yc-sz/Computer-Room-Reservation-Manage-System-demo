#include "Student.h"

void Student::apply_book()
{
	
	this->show_room_status();
	int room = -1;
	int day = -1;
	int time = -1;
	cout << "----------��������ҪԤԼ�Ļ���----------" << endl;
	cout << "������: ";
	cin >> room;
	cout << "��: ";
	cin >> day;
	cout << "ʱ��(1������ 2������): ";
	cin >> time;
	this->bp.apply_receive(this->stu_num, this->name, room, day, time);
	cout << "ԤԼ�ύ�ɹ����ȴ������..." << endl;
}

void Student::show_my_book()
{
	cout << "----------���ĸ���ԤԼ����----------" << endl;
	vector<vector<string>> v_temp;
	v_temp = this->bp.get_personl_apply(this->stu_num);
	if (v_temp.size() != 0)
	{
		for (vector<vector<string>>::const_iterator it_line = v_temp.begin(); it_line != v_temp.end(); it_line++)
		{
			string status;
			if ((*it_line)[5].compare("-1") == 0)
			{
				status = "�����";
			}
			else if ((*it_line)[5].compare("0") == 0)
			{
				status = "��˲�ͨ��";
			}
			else if ((*it_line)[5].compare("1") == 0)
			{
				status = "���ͨ��";
			}
			else if ((*it_line)[5].compare("-2") == 0)
			{
				status = "��ȡ��";
			}
			cout << "�������˺�: " << (*it_line)[0]
				<< " | ����������: " << (*it_line)[1]
				<< " | ���������: " << (*it_line)[2]
				<< " | ����: ��" << (*it_line)[3]
				<< " | ʱ���: " << ((*it_line)[4].compare("1") == 0 ? "����" : "����")
				<< " | ��˽��: " << status 
				<< endl;
		}
	}
	else
	{
		cout << "�޸���ԤԼ��¼!" << endl;
	}
}

void Student::show_all_book()
{
	map<int, vector<string>> m_temp;
	m_temp = this->bp.get_all_audit();
	cout << "-------����ԤԼ��¼����-------" << endl;
	if (m_temp.size() == 0)
	{
		cout << "���޴���˼�¼!" << endl;
	}
	else
	{
		cout << "-------����˼�¼-------" << endl;
		cout << "�������˺�    ����������    ���������    ��������    ����ʱ��" << endl;
		for (map<int, vector<string>>::iterator it = m_temp.begin(); it != m_temp.end(); it++)
		{
			cout << it->second[0] << "    "
				<< it->second[1] << "    "
				<< it->second[2] << "    "
				<< "��" << it->second[3] << "    "
				<< (it->second[4].compare("1") == 0 ? "����" : "����")
				<< endl;
		}
	}

	m_temp = this->bp.get_all_record();
	if (m_temp.size() == 0)
	{
		cout << "��������˼�¼!" << endl;
	}
	else
	{
		cout << "-------����˼�¼-------" << endl;
		cout << "�������˺�    ����������    ������˺�    ���������    ���������    ��������    ����ʱ��    ��˽��" << endl;
		for (map<int, vector<string>>::iterator it = m_temp.begin(); it != m_temp.end(); it++)
		{
			string status;
			if (it->second[7].compare("0") == 0)
			{
				status = "δͨ��";
			}
			else if (it->second[7].compare("-2") == 0)
			{
				status = "��ȡ��";
			}
			else if (it->second[7].compare("1") == 0)
			{
				status = "��ͨ��";
			}

			cout << it->second[0] << "    "
				<< it->second[1] << "    "
				<< it->second[2] << "    "
				<< it->second[3] << "    "
				<< it->second[4] << "    "
				<< "��" << it->second[5] << "    "
				<< (it->second[6].compare("1") == 0 ? "����" : "����")
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
		cout << "---------����л�ԤԼ�ɹ��ļ�¼����----------" << endl;
		cout << "���\t�������˺�\t����������\t���������\t��������\t����ʱ��\t���״̬" << endl;
		for (vector<vector<string>>::iterator it = v_temp.begin(); it != v_temp.end(); it++)
		{
			string status;
			if (v_temp[i][5].compare("-1") == 0)
			{
				status = "�����";
			}
			else if (v_temp[i][5].compare("-2") == 0)
			{
				status = "��ȡ��";
			}
			else if (v_temp[i][5].compare("1") == 0)
			{
				status = "��ͨ��";
			}
			else if (v_temp[i][5].compare("0") == 0)
			{
				status = "δͨ��";
			}

			cout << i + 1 << "\t"												//���
				<< v_temp[i][0] << "\t\t"										//�������˺�
				<< v_temp[i][1] << "\t\t"										//����������
				<< v_temp[i][2] << "\t\t"										//���������
				<< "��" << v_temp[i][3] << "\t\t"								//��������
				<< (v_temp[i][4].compare("1") == 0 ? "����" : "����") << "\t\t"	//����ʱ��
				<< status														//���״̬
				<< endl;
			i++;
		}
		int num;
		cout << "������Ҫȡ����������: ";
		cin >> num;
		bool flag = this->bp.cancel_personal_book(v_temp[num - 1]);
		if (flag)
		{
			cout << "ȡ���ɹ�!" << endl;
		}
		else
		{
			cout << "ȡ��ʧ��!" << endl;
		}
	}
	else
	{
		cout << "��ԤԼ��¼!" << endl;
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
		cout << "----------" << room + 1 << "�Ż�����Ϣ����" << "----------" << endl;
		cout << "----------����: " << this->bp.get_room_capacity(room + 1) << "��----------" << endl;
		cout << "     ��һ    �ܶ�    ����    ����    ����" << endl;
		for (int time = 0; time < this->time_num; time++)
		{
			if (time == 0)
			{
				cout << "����: ";
			}
			else
			{
				cout << "����: ";
			}
			for (int day = 0; day < this->day_num; day++)
			{
				cout << (this->room_status[room][day][time] == 0 ? "����" : "ռ��") << "    ";
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
		cout << "\t\t��ã�" << this->get_name() << "��\t\t" << endl;
		cout << "------------------------------------------" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t1������ԤԼ\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t2���鿴�Լ���ԤԼ\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t3���鿴����ԤԼ\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t4��ȡ��ԤԼ\t\t|" << endl;
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
			cout << "��������ȷ��ѡ�" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
