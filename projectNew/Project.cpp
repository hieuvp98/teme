// Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "User.h"
#include "DataUser.h"
#include "DataCourse.h"
#include "Course.h"
#include "MainWindow.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char fileUser[] = "D:\\user2.txt";
	char fileCourse[] = "D:\\course2.txt";
	MainWindow mainWindow = mainWindow.newMainWindow(fileUser,fileCourse);
	mainWindow.firstWindow();
	return 0;
}

