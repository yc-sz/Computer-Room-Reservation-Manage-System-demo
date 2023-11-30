#pragma once
#include<iostream>
#include<string>
using namespace std;

class User 
{
protected:
	string name;
	string password;
public:
	virtual void set_name(string) = 0;
	virtual void set_passwd(string) = 0;
	virtual string get_name() = 0;
	virtual string get_passwd() = 0;
	virtual void operat_menu() = 0;

	virtual ~User() = 0;
};