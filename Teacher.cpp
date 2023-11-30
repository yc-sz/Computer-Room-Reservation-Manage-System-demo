#include "Teacher.h"

void Teacher::show_all_book()
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
		cout << "�������˺�\t����������\t���������\t��������\t����ʱ��" << endl;
		for (map<int, vector<string>>::iterator it = m_temp.begin(); it != m_temp.end(); it++)
		{
			cout << it->second[0] << "\t\t"
				<< it->second[1] << "\t\t"
				<< it->second[2] << "\t\t"
				<< "��" << it->second[3] << "\t\t"
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
		cout << "�������˺�\t����������\t������˺�\t���������\t���������\t��������\t����ʱ��\t��˽��" << endl;
		for (map<int, vector<string>>::iterator it = m_temp.begin(); it != m_temp.end(); it++)
		{
			cout << it->second[0] << "\t\t"
				<< it->second[1] << "\t\t"
				<< it->second[2] << "\t\t"
				<< it->second[3] << "\t\t"
				<< it->second[4] << "\t\t"
				<< "��" << it->second[5] << "\t\t"
				<< (it->second[6].compare("1") == 0 ? "����" : "����") << "\t\t"
				<< (it->second[7].compare("1") == 0 ? "ͨ��" : "��ͨ��")
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
		cout << "����˼�¼����:" << endl;
		for (map<int, vector<string>>::iterator it = m_audit.begin(); it != m_audit.end(); it++)
		{
			cout << "���: " << it->first
				<< " �������˺�: " << it->second[0]
				<< " ����������: " << it->second[1]
				<< " ���������: " << it->second[2]
				<< " ��������: ��" << it->second[3]
				<< " ����ʱ��: " << (it->second[4].compare("1") == 0 ? "����" : "����")
				<<  "���״̬: " << (it->second[5].compare("-1") == 0 ? "�����" : "�����")
				<< endl;
		}
		int num;
		cout << "������Ҫ��˵ļ�¼�ı��:";
		cin >> num;
		int result;
		cout << "��������˽����0����ͨ�� 1��ͨ����: ";
		cin >> result;
		this->bp.apply_audit(this->tea_num, this->name, num, result);
		cout << "������!" << endl;
	}
	else
	{
		cout << "���޴���˵�ԤԼ����!" << endl;
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
		cout << "\t\t��ã�" << this->get_name() << "��\t\t" << endl;
		cout << "------------------------------------------" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t1���鿴����ԤԼ\t\t|" << endl;
		cout << "|\t\t\t\t\t|" << endl;
		cout << "|\t\t2�����ԤԼ\t\t|" << endl;
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
			this->show_all_book();
			break;
		case 2:
			this->audit_book();
			break;
		default:
			cout << "��������ȷ��ѡ�" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
