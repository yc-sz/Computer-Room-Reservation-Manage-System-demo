#include<iostream>
#include"ManagerSystem.h"
using namespace std;

int main() {
	ManagerSystem ms;
	while (true){
		ms.show_menu();
		int select;
		cout << "���������ѡ��:";
		cin >> select;
		switch (select) {
		case 1:		//ѧ����¼
			ms.stu_login();
			break;
		case 2:		//��ʦ��¼
			ms.tea_login();
			break;
		case 3:		//����Ա��¼
			ms.admin_login();
			break;
		case 0:		//�˳�ϵͳ
			ms.exit_system();
			break;
		default:
			cout << "��������ȷ��ѡ�" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	return 0;
}