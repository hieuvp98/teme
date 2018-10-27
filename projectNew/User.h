#pragma once
#include "stdafx.h"
struct User
{

	string account;
	string password;
	string id;
	string name;
	string sdt;
	int gender; // 0 is female, 1 is male
	int age;
	int type; //  0 la hoc vien, 1 la giang vien, 2 la nhan vien
	string listCourse[3];
	int countCourse;
	////// function//////////
	void vietHoaTen();
	int addCourse(string);
	int xoaCourse(string);
	char* toString();
	string thongTin();
	string thongTinItHon();
	string courseTostring();
	User newUser(string,string,string,int,int,int,string,string);
	User getUser(char* c);
	void copyUser(User);
	int checkRegister(char test[]);
	int checkLogin(char acc[], char pass[]);
	int checkCourse(string);
	int checkPassword(char* pass);
}; 


char* User::toString()
{
	string val =  account+'|'+password+'|'+id+'|'+to_string(type)+'|'+to_string(gender)+'|'+to_string(age)+'|'+name+'|'+sdt+'|'+courseTostring()+'\n';
	char* c = new char[val.length()];
	
	for(int i =0; i < val.length();i++)
		c[i] = val[i];
	c[val.length()] = 0;
	return c;
}
string User::courseTostring()
{
	string val =  listCourse[0]+'&'+listCourse[1]+'&'+listCourse[2]+'&';
	return val;
}
void User::vietHoaTen()
{
	if (name[0] > 96 && name[0] < 123) name[0] -= 32;
	for (int i = 1; i < name.length() ; i++)
	{
		if (name[i] == ' ' && name[i + 1] > 96 && name[i + 1] < 123) name[i + 1] -= 32;
	}
}
User User::newUser(string acc = "",string password = "",string id="",int type=0, int gender = 0, int age = 0, string mname = "",string sdt = "")
{
	User user;
	user.account = acc;
	user.password = password;
	user.id = id;
	user.type = type;
	user.gender = gender;
	user.age = age;
	user.name = mname;	
	user.countCourse = 0;
	user.sdt = sdt;
	user.vietHoaTen();
	return user;
}
User User::getUser(char* c)  // tao ra user tu char*
{
	User user = user.newUser();	
	user.countCourse = 0;
	int i = 0;
	    while( c[i] != '|' ) { user.account += c[i++];}
		i++;
		while (c[i] != '|')  {user.password  += c[i++];}
		i++;
		while (c[i] != '|') {user.id += c[i++];}
		i++;
		user.type = c[i++] - '0';
		i++;
		user.gender = c[i++] - '0';
		i++;
		string tuoi;
		while (c[i] != '|') {tuoi += c[i++];}
		user.age = stoi(tuoi);
		i++;
		while (c[i] != '|' ) {user.name += c[i++];}
		i++;
		while (c[i] != '|') { user.sdt += c[i++]; }
		i++;
		for (int j =0; j < 3; j++)
		{
		while (c[i] != '&') {user.listCourse[j] += c[i++];}
		if(user.listCourse[j].length() > 0) user.countCourse++;
		i++;
		}	
	return user;
}
int User::addCourse(string course)
{
	if ( countCourse < 3) 
		{
			listCourse[countCourse++] = course;
			return 1;
	}
	else
		cout<<"So luong khoa hoc da day!\n";
	return 0;
}
int User::xoaCourse(string course)
{
	if (!listCourse[0].compare(course)) // kiem tra thang course o cho nao
	{
		listCourse[0] = listCourse[1];
		listCourse[1] = listCourse[2];
		listCourse[2] ="";
		countCourse--;
		return 1;
	}
	else if (!listCourse[1].compare(course))
	{
		listCourse[1] = listCourse[2];
		listCourse[2] ="";
		countCourse--;
		return 1;
	}
	else if(!listCourse[2].compare(course))
		{
			listCourse[2] = "";
			countCourse--;
		    return 1;
	}
	    return 0;
}
void User::copyUser(User src)
{
	account = src.account;
	password = src.password;
	id = src.id;
	type = src.type;
	gender = src.gender;
	age = src.age; 
	name = src.name;
}
int User::checkRegister(char* test)
{
	string test2 = string(test);
	return account.compare(test2);
}
int User::checkLogin(char acc[], char pass[])
{
	string acc1 = string(acc);
	string pass1 = string(pass);
	if ( !account.compare(acc1) && !password.compare(pass1))
		return 1;
	else return 0;
}
string User::thongTin()
{
	string chucVu;
	if (!type) chucVu = "Hoc Vien";
	else if(type == 1) chucVu = "Giang Vien";
	else chucVu = "Quan Ly";
	return chucVu+": "+name+" | SDT: "+sdt+" | Gioi tinh: "+(gender?"nam":"nu")+ " | tuoi: "+to_string(age)+" | password: "+password+" | id: "+id ;
}
string User::thongTinItHon()
{
	return "Ho va ten: " + name + " | SDT: " + sdt + " | Gioi tinh: " + (gender ? "nam" : "nu") + " | tuoi: " + to_string(age) + " | So khoa hoc: " + to_string(countCourse) + " | id: " + id;
}
int User::checkCourse(string course)
{
	for (int i = 0; i < countCourse; i++)
		if(!listCourse[i].compare(course)) return 0;
	return 1;
}
int User::checkPassword(char* pass)
{
	if (!password.compare(string(pass))) 
		return 1;
	return 0;
}
