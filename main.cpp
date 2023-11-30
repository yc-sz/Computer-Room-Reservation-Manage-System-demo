#include<iostream>
#include"ManagerSystem.h"
using namespace std;

int main() {
	ManagerSystem ms;
	while (true){
		ms.show_menu();
		int select;
		cout << "请输入你的选项:";
		cin >> select;
		switch (select) {
		case 1:		//学生登录
			ms.stu_login();
			break;
		case 2:		//教师登录
			ms.tea_login();
			break;
		case 3:		//管理员登录
			ms.admin_login();
			break;
		case 0:		//退出系统
			ms.exit_system();
			break;
		default:
			cout << "请输入正确的选项！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	return 0;
}