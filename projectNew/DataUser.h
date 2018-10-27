#pragma once
#include "stdafx.h"
#include "User.h"

struct DataUser
{
   User* listUser;
   int countUser;
   DataUser newDataUser();
   void loadUserFromFile(char*);
   void saveUserToFile(char*);
   void addUser(User);
   void deleteUser(int position);
   void fixUser(User,int position);
   void xoaCourse(string);
   int checkLogin(char acc[], char pass[]);
   int checkRegister(char acc[]);
   int checkId(string);
   User getUserFromId(string );

};
DataUser DataUser::newDataUser()
{
	DataUser dataUser;
	dataUser.countUser = 0;
	dataUser.listUser = new User[0];
	return dataUser;
}
void DataUser::addUser(User user)
{
	User* temp = new User[countUser];  // mang user tam thoi
	for ( int i = 0; i < countUser; i++)
		temp[i]=listUser[i];
	listUser = new User[countUser+1]; // tang them mot o nho
	for ( int i = 0; i < countUser; i++)
		listUser[i]=temp[i];
	listUser[countUser]= user;  // them vao cuoi mang
	countUser++;
	delete[] temp;
}
void DataUser::deleteUser(int position)
{
	User* temp = new User[countUser];  // mang user tam thoi
	for ( int i = 0; i < countUser; i++)
		temp[i]=listUser[i];
	listUser = new User[countUser-1]; // xoa cmn mot o nho
	for (int i = 0, j =0 ; i < countUser ; i++)
	{
		if(i != position) // khong lay thang temp[position] 
		listUser[j++]=temp[i];                         
	}
	countUser--;
	delete[] temp;
}
void DataUser::fixUser(User newUser, int position)
{
	listUser[position]= newUser;
}
void DataUser::xoaCourse(string course)
{
	for (int i =0; i < countUser; i++)
	{
		  listUser[i].xoaCourse(course);
	}
}
void DataUser::loadUserFromFile(char* fileLocation)
{   
	FILE* file;
	errno_t arr;
	User user = user.newUser();
	arr = fopen_s(&file,fileLocation,"r");
	if (!arr)
	{
		countUser = 0;
		char buff[100];
		fgets(buff, 100, file);
		if (buff == 0)
		{
			fputc('!', file); // dat ky tu '!' o cuoi file
		}
		else
		{
			while (strcmp(buff, "!"))
			{
				user = user.getUser(buff);
				addUser(user);
				fgets(buff, 100, file);
			}
		}
	}
	if(file)
		arr = fclose(file);		
}
void DataUser::saveUserToFile(char* fileLocation)
{
	FILE* file;
	errno_t arr;
	arr = fopen_s(&file,fileLocation,"w");
	if(!arr)
	{
	  for ( int i = 0; i < countUser; i++)
		  fputs(listUser[i].toString(),file);
	  fputc('!',file);
	}
	if(file)
		arr = fclose(file);
}
int DataUser::checkRegister(char* acc)
{
	for (int i =0; i < countUser; i++)
		if (!listUser[i].checkRegister(acc)) return 0; // 0 la da bi trung
	return 1; // 1 la ok
}
int DataUser::checkLogin(char acc[], char pass[])
{
	for (int i =0; i < countUser; i++)
		if (listUser[i].checkLogin(acc,pass)) return i; // tai khoan thu i
	return -1; // -1 la chua dang ky
}
int DataUser::checkId(string id)
{
	for (int i = 0; i < countUser; i++)
		if (!listUser[i].id.compare(id)) return 0; // 0 la bi trung 
	return 1; // ok
}
User DataUser::getUserFromId(string id)
{
	for (int i = 0; i < countUser;i++)
	{
		if (!((listUser[i].id).compare(id))) 
			return listUser[i];	
	}
}