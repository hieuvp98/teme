#pragma once
#include "stdafx.h"
#include "DataCourse.h"
#include "DataUser.h"
#include "dohoa.h"
 void header()
 {
	 clrscr();
	 char title[] = "QUAN LY HOC VIEN";
	 SetColor(13);
	 cout<<"\t\t\t\t\t\t";
	 for ( int i = 0; i < sizeof(title); i++ )
	 {
		 cout<<title[i];
		 Sleep(20);
	 }
	 cout<<endl<<endl;
	 cout<<"-----------------------------------------------------------------------------------------------------------------------\n";
	 SetColor(0);
	 
 }
struct MainWindow
{
	DataCourse dataCourse;
	DataUser dataUser;
	User logedUser;
	int loged; // vi tri cua user da dang nhap
	MainWindow newMainWindow(char * fileUser, char* fileCourse);
	char* fileUser;
	char* fileCourse;
	void mainMenu(int);
	void loadData();
	void saveData();
	void firstWindow();
	void loginWindow();
	void registerWindow();
	void profileWindow();
	void showCourses(int);
	void myCourse(int);
	void themKhoaHoc();
	void suaKhoaHoc(int);
	void xoaKhoaHoc(int);
	void quanLyKhoaHoc();
	void danhSachHocVien(int);
	void quanLyUser();
	void dangKyKhoaHoc();
	void dangKyLopDay();
	void fixProfile();
	void changePassword();
	void doanhThu();
	void headerMain();
	void line();
	int getResult();
};
MainWindow MainWindow::newMainWindow(char* fileUser, char* fileCourse)
{
	 SetBGColor(7);
	 SetColor(0);
    MainWindow main;
	main.fileUser = fileUser;
	main.fileCourse = fileCourse;
	main.loadData();
	return main;
}
void MainWindow::loadData()
{
	dataCourse = dataCourse.newDataCourse();
	dataCourse.loadCourseFromFile(fileCourse);
	dataUser = dataUser.newDataUser();
	dataUser.loadUserFromFile(fileUser);
}
void MainWindow::saveData()
{
	dataCourse.saveCourseToFile(fileCourse);
	dataUser.saveUserToFile(fileUser);
}
void MainWindow::firstWindow()
{
	header();
	printf_s("%90s","1. Dang ky                 2. Dang nhap                3. Thoat\n");
	line();
	switch (getResult())
	{
	case 1:
	{
			  registerWindow();
			  break;
	}
	case 2:
	{
			  loginWindow();
			  break;
	}
	default:
		break;
	}
}
void MainWindow::registerWindow()
{
	header();
	cout<<"DANG KY TAI KHOAN\n";	
	line();
	int check1 = 1, check2 = 1;
	char acc[16];
	do
   {
	printf("Nhap username: (toi da 16 ky tu )  ");
	gets_s(acc,16);
	if(!dataUser.checkRegister(acc)) 
	{
		printf("Username da ton tai, vui long nhap lai\n");
		check1 = 1;
	}
	else check1 = 0;
    }
    while(check1);
	fflush(stdin);
	char pass1[16],pass2[16];
	do
	{
	printf("Nhap password: (toi da 16 ky tu)  ");
	gets_s(pass1,16);
	printf("Nhap lai password: ");
	gets_s(pass2,16);
	if(strcmp(pass1,pass2)) 
		printf("nhap lai password khong chinh xac\n");
	else check2 = 0;
	}
	while (check2);
	char name[40];
	cout<<"Nhap ten cua ban: ";
	gets_s(name,40);
	fflush(stdin);
	char sdt[11];
	cout << "Nhap so dien thoai: ";
	gets_s(sdt, 11);
	int type,gender,age;
	cout<<"Ban la: \n";
	cout<<"0. Hoc Vien\n1. Giang Vien\n2.Quan Ly\n";
	type = getResult();
	cout<<"Nhap gioi Tinh: \n";
	cout<<"0. Nu\n1. Nam\n";
	gender = getResult();
	cout<<"Nhap so tuoi: ";
	cin>>age;
	fflush(stdin);
	string id;
	srand(time(NULL));
	do
	{
	id = to_string(rand()); // tao id random
	}
	while(!dataUser.checkId(id)); // kiem tra id da co chua
	User user = user.newUser(string(acc),string(pass1),id,type,gender,age,string(name),string(sdt));
	dataUser.addUser(user);
	dataUser.saveUserToFile(fileUser);
	cout<<"Dang ky tai khoan "<<user.account<<" thanh cong!\n";
	cout<<"Nhan phim bat ky de tiep tuc.";
	getchar();
	firstWindow();
}
void MainWindow::loginWindow()
{
	int check = 1;
	header();
	cout<<"DANG NHAP\n";
	line();
	char acc[16],pass[16];
	do
	{
	cout<<"USERNAME: ";
	gets_s(acc,16);
	cout<<"PASSWORD: ";
	gets_s(pass,16);
	if (dataUser.checkLogin(acc,pass) > -1)
		check = 0;
	else cout<<"Tai khoan hoac mat khau khong dung.\n";
	}
	while(check);	
	loged = dataUser.checkLogin(acc,pass); // vi tri cua user da dang nhap
	logedUser = dataUser.listUser[loged];
	cout<<"LOGGING...";
	Sleep(1000);
	mainMenu(logedUser.type);
}
void MainWindow::profileWindow()
{
	loadData();
	headerMain();
	cout<<"THONG TIN CA NHAN\n\n";
	line();
    cout<<dataUser.listUser[loged].thongTin()<<endl<<endl;
	line();
	cout<<"1. Chinh sua thong tin\n";
	cout<<"2. Doi mat khau\n";
	cout<<"0. Quay lai\n";
	switch(getResult())
	{
	case 1:
		{
			fixProfile();
			break;
		}
	case 2:
		{
			changePassword();
			break;
		}
	case 0:
		  {
			  mainMenu(logedUser.type);
			  break;
		  }
	default: break;
	}

}
void MainWindow::mainMenu(int type)
{
	headerMain();
	switch(type)
	{
	case 0:
		{
			cout<<"1. Thong tin ca nhan"<<endl;
			cout<<"2. Khoa hoc da dang ky"<<endl;
			cout<<"3. Dang ky khoa hoc"<<endl;
			cout<<"0. Dang xuat"<<endl;
			line();
			switch (getResult())
			{
			case 1:
				{
					profileWindow();
					break;
				}
			case 2:
				{
					myCourse(logedUser.type);
					break;
				}
			case 3:
				{
					dangKyKhoaHoc();
					break;
				}							
			default:
				{
				   firstWindow();
				   break;
				}
			}
			break;
		}
	case 1:
		{
		    cout<<"1. Thong tin ca nhan"<<endl;
			cout<<"2. Cac lop dang day"<<endl;
			cout<<"3. Dang ky lop day"<<endl;
			cout<<"0. Dang xuat"<<endl;
			line();
			switch (getResult())
			{
			case 1:
				{
					profileWindow();
					break;
				}
			case 2:
				{
					myCourse(logedUser.type);
					break;
				}
			case 3:
				{
					dangKyLopDay();
					break;
				}							
			default:
				{
				   firstWindow();
				}
			}
			break;
			break;
		}
	case 2:
		{
		    cout<<"1. Thong tin ca nhan"<<endl;
			cout<<"2. Quan ly hoc vien, giang vien"<<endl;
			cout<<"3. Quan ly khoa hoc"<<endl;
			cout<<"4. Thong ke doanh thu"<<endl;
			cout<<"0. Dang xuat"<<endl;
			line();
			switch (getResult())
			{
			case 1:
				{
					profileWindow();
					break;
				}
			case 2:
				{
					quanLyUser();
					break;
				}
			case 3:
				{
					quanLyKhoaHoc();
					break;
				}	
			case 4:
				{
					doanhThu();
					break;
				}
			case 0:
			{
					  firstWindow();
					  break;
			}
			default:
				{
				   mainMenu(logedUser.type);
				   break;
				}
			}
			break;
		}
	default: break;
	}
}
void MainWindow::showCourses(int type)
{
	loadData();
	line();
	if (dataCourse.countCourse > 0)
	{
		for (int i = 0; i < dataCourse.countCourse; i++)
		{
			cout<<i+1<<". ";
			if (type)
			cout<<dataCourse.listCourse[i].fullThongTin(dataUser)<<endl;
			else cout<<dataCourse.listCourse[i].thongTin(dataUser)<<endl;
			cout<<"---------------------------------------------------------------------\n";
		}
	}
	else 
		{
			cout<<"Chua co khoa hoc nao!"<<endl;
	line();
	}
}
void MainWindow::quanLyKhoaHoc()
{
	headerMain();
	loadData();
	line();
	cout<<"QUAN LY KHOA HOC"<<endl;
	showCourses(logedUser.type);
	cout<<"\n1. Them khoa hoc\n";
	cout<<"2. Chinh sua khoa hoc\n";
	cout<<"3. Xoa Khoa Hoc\n";
	cout << "4. Hoc vien da dang ky\n";
	cout<<"0. Quay lai\n";
	switch (getResult())
	{
	case 1:
		{
			themKhoaHoc();
			break;
		}
	case 2:
		{
			line();
			cout<<"Nhap STT khoa hoc: ";
			int position;
			cin>>position;
			fflush(stdin);
			suaKhoaHoc(position-1);
			break;
		}
	case 3:
		{
			line();
			cout<<"Nhap STT khoa hoc: ";
			int position;
			cin>>position;
			fflush(stdin);
			xoaKhoaHoc(position-1);
			break;
		}
	case 4:
	{
			  line();
			  cout << "Nhap STT khoa hoc: ";
			  int position;
			  cin >> position;
			  fflush(stdin);
			  danhSachHocVien(position - 1);
			  break;
	}
	case 0:
		{
			mainMenu(logedUser.type);
			break;
		}
	default:
		break;
	}
}
void MainWindow::danhSachHocVien(int position)
{
	headerMain();
	loadData();
	cout << "DANH SACH HOC VIEN" << endl;
	line();
	Course course = dataCourse.listCourse[position];
	User user;
	for (int i = 0; i < course.hocVienDaDangky; i++)
	{
		user = dataUser.getUserFromId(course.idHocVien[i]);
		cout << i + 1 << ". " << user.name <<" sdt: "<<user.sdt<<endl;
		line();
	}
	cout << "0. Quay Lai\n";
	switch (getResult())
	{
		
	default:
	{
			   quanLyKhoaHoc();
			   break;
	}
	}

}
void MainWindow::quanLyUser()
{
   headerMain();
   cout<<"QUAN LY GIANG VIEN, HOC VIEN\n";
   loadData();
   line();
   cout<<"                      Giang vien\n";
   cout<<"-----------------------------------------------------------------------------\n";
   for ( int i =0, j=1 ; i < dataUser.countUser; i++)
	   if (dataUser.listUser[i].type == 1)
	   cout<<j++<<". "+dataUser.listUser[i].thongTinItHon()<<endl;
   line();
   cout<<"                      Hoc vien\n";
   cout<<"-----------------------------------------------------------------------------\n";
   for ( int i =0, j=1 ; i < dataUser.countUser; i++)
	   if (!dataUser.listUser[i].type)
	   cout<<j++<<". "+dataUser.listUser[i].thongTinItHon()<<endl;
   line();
   cout<<"0. Quay lai.\n";
	   if (!getResult()) mainMenu(logedUser.type);
}
void MainWindow::themKhoaHoc()
{
	headerMain();
	cout<<"THEM KHOA HOC\n";
	line();
	char ten[30],thoiGian[30],khaiGiang[30];
	double hocPhi,luong;
	int soBuoi,soLuong;
	cout<<"Nhap ten khoa hoc: ";
	gets_s(ten,30);
	cout<<"Nhap lich hoc: ";
	gets_s(thoiGian,30);
	cout<<"Nhap ngay khai giang: ";
	gets_s(khaiGiang,30);
	fflush(stdin);
	cout<<"Nhap so buoi: ";
	cin>>soBuoi;
	cout<<"Nhap so luong hoc vien toi da: ";
	cin>>soLuong;
	cout<<"Nhap hoc phi: ";
	cin>>hocPhi;
	cout<<"Nhap luong giang vien: ";
	cin>>luong;
	srand(time(NULL));
	string maKhoaHoc = to_string(rand());
	Course course = course.newCourse(maKhoaHoc,ten,thoiGian,khaiGiang,hocPhi,luong,soLuong,soBuoi);
	dataCourse.addCourse(course);
	dataCourse.saveCourseToFile(fileCourse);
	dataCourse.loadCourseFromFile(fileCourse);
	quanLyKhoaHoc();
}
void MainWindow::suaKhoaHoc(int position)
{
    headerMain();
	cout<<"CHINH SUA KHOA HOC\n";
	line();
	char ten[30],thoiGian[30],khaiGiang[30];
	double hocPhi,luong;
	int soBuoi,soLuong;
	cout<<"Nhap ten khoa hoc: ";
	gets_s(ten,30);
	cout<<"Nhap lich hoc: ";
	gets_s(thoiGian,30);
	cout<<"Nhap ngay khai giang: ";
	gets_s(khaiGiang,30);
	fflush(stdin);
	cout<<"Nhap so buoi: ";
	cin>>soBuoi;
	cout<<"Nhap so luong hoc vien toi da: ";
	cin>>soLuong;
	cout<<"Nhap hoc phi: ";
	cin>>hocPhi;
	cout<<"Nhap luong giang vien: ";
	cin>>luong;
	Course course = course.newCourse(dataCourse.listCourse[position].maKhoaHoc,ten,thoiGian,khaiGiang,hocPhi,luong,soLuong,soBuoi);
	course.idGiangVien = dataCourse.listCourse[position].idGiangVien;
	course.hocVienDaDangky = dataCourse.listCourse[position].hocVienDaDangky;
	dataCourse.fixCourse(course,position);
	saveData();
	quanLyKhoaHoc();
}
void MainWindow::xoaKhoaHoc(int position)
{
	dataUser.xoaCourse(dataCourse.listCourse[position].maKhoaHoc);
	dataCourse.deleteCourse(position);
	saveData();
	quanLyKhoaHoc();
}
void MainWindow::dangKyKhoaHoc()
{
	headerMain();
	cout<<"DANG KY KHOA HOC (toi da 3 lop ) \n";
	showCourses(logedUser.type);
	cout<<"\n1.Chon khoa hoc\n0.Quay lai\n";
	switch (getResult())
	{
	case 1:
		{
			cout<<"Nhap STT cua khoa hoc: ";
			int val;
			cin>>val;
			if (dataUser.listUser[loged].checkCourse(dataCourse.listCourse[val - 1].maKhoaHoc)) // kiem tra da dang ky chua
			{
				if ((dataUser.listUser[loged]).addCourse(dataCourse.listCourse[val - 1].maKhoaHoc)) // kiem tra da du 3 khoa chua
				{
					if (dataCourse.listCourse[val - 1].hocVienDaDangky < dataCourse.listCourse[val - 1].soLuongHocVien)
					{
						dataCourse.listCourse[val - 1].themHocVien(logedUser.id);
						saveData();
						loadData();
						myCourse(logedUser.type);
					}
					else
					{
						cout << "Lop da day\n";
						cout << "Nhan phim bat ky de tiep tuc\n";
						fflush(stdin);
						getchar();
						dangKyKhoaHoc();
					}
				}
				else
				{
					cout << "Ban da dang ky 3 khoa hoc\n";
					cout << "Nhan phim bat ky de tiep tuc\n";
					fflush(stdin);
					getchar();
					dangKyKhoaHoc();
				}
			}
			else
				{
					cout<<"Ban da dang ky khoa hoc nay\n";
					cout<<"Nhan phim bat ky de tiep tuc\n";
					getchar();
					dangKyKhoaHoc();
			}
			
			
			break;
		}
	case 0:
			{
				mainMenu(logedUser.type);
				break;
			}
	default:
		{
			dangKyKhoaHoc();
		    break;
		}
	}
}
void MainWindow::dangKyLopDay()
{
	headerMain();
	cout<<"DANG KY LOP DAY ( toi da 3 lop )\n";
	showCourses(logedUser.type);
	cout<<"\n1.Chon khoa hoc\n0.Quay lai\n";
	switch (getResult())
	{
	case 1:
		{
			cout<<"Nhap STT cua khoa hoc: ";
			int val;
			cin>>val;
			string ma = dataCourse.listCourse[val-1].maKhoaHoc;
			if ( !dataCourse.listCourse[val-1].idGiangVien.compare("")) // kiem tra da dang ky lop chua
			{
			   if ((dataUser.listUser[loged]).addCourse(ma))  // kiem tra da du 3 lop chua
			   {
			   dataCourse.listCourse[val-1].idGiangVien = logedUser.id;
			   saveData();
			   myCourse(logedUser.type);
			   }
			   else
			   {
				 cout << "Ban da dang ky 3 lop\n";
				 cout << "Nhan phim bat ky de tiep tuc\n";
				 fflush(stdin);
				 getchar();
				 dangKyLopDay();
			   }
			}
			else
			{
				cout << "Ban da khong the dang ky lop nay\n";
				cout << "Nhan phim bat ky de tiep tuc\n";
				fflush(stdin);
				getchar();
				dangKyLopDay();

			}
			break;
		}
	case 0:
			{
				mainMenu(logedUser.type);
				break;
			}
	default:
		{
			dangKyLopDay();
		    break;
		}
	}
}
void MainWindow::myCourse(int type)
{
	logedUser = dataUser.listUser[loged];
	headerMain();
	cout<<"KHOA HOC CUA TOI\n";
	loadData();
	line();
	if (logedUser.countCourse > 0)
	{
		for (int i = 0; i < logedUser.countCourse; i++)
		{
			cout<<i+1<<". ";
			if (type)
			cout<<(dataCourse.getCourseFromId(logedUser.listCourse[i])).fullThongTin(dataUser)<<endl;
			else cout<<(dataCourse.getCourseFromId(logedUser.listCourse[i])).thongTin(dataUser)<<endl;
			line();
		}
	}
	else 
		{
			cout<<"Chua co khoa hoc nao!"<<endl;
			line();
	}
	cout<<"1. Huy dang ky khoa hoc\n";
	cout<<"0. Quay lai\n";
	switch (getResult())
	{
	case 1:
		{
			cout<<"Nhap STT khoa hoc muon huy: ";
			int val;
			cin>>val;
			string ma = dataUser.listUser[loged].listCourse[val-1];
			if (type)
				dataCourse.xoaGiangVien(ma);
			else
				dataCourse.huyDangKy(ma, dataUser.listUser[loged].id);
			dataUser.listUser[loged].xoaCourse(ma);
			saveData();
			myCourse(logedUser.type);
		}
	default:
		mainMenu(logedUser.type);
	}
}
void MainWindow::changePassword()
{
	headerMain();
	cout<<"DOI MAT KHAU\n";
	line();
	int check = 1;
	char oldPass[16];
	do
	{
		cout<<"Nhap mat khau cu: ";
		gets_s(oldPass,16);
		if (dataUser.listUser[loged].checkPassword(oldPass))
			check = 0;
		else check = 1;
		if (check)
			cout<<"Mat khau cu khong dung.\n";
	}
	while(check);
	cout<<"Nhap mat khau moi (khong qua 16 ky tu ): ";
	gets_s(oldPass,16);
	dataUser.listUser[loged].password = string(oldPass);
	saveData();
	profileWindow();
}
void MainWindow::fixProfile()
{
	headerMain();
	cout<<"DOI THONG TIN CA NHAN\n";
	line();
	char name[30];
	int age,gender;
	cout<<"Nhap ten moi: ";
	gets_s(name,30);
	fflush(stdin);
	cout<<"Nhap tuoi: ";
	cin>>age;
	cout<<"Nhap gioi tinh\n";
	cout<<" 0. Nu\n 1. Nam\n";
	cin>>gender;
	fflush(stdin);
	cout << "Nhap so dien thoai: \n";
	char sdt[11];
	gets_s(sdt, 11);
	dataUser.listUser[loged].name = string(name);
	dataUser.listUser[loged].age = age;
	dataUser.listUser[loged].gender = gender;
	dataUser.listUser[loged].sdt = sdt;
	saveData();
	profileWindow();
}
void MainWindow::doanhThu()
{
	headerMain();
	cout<<"THONG KE DOANH THU\n";
	line();
	printf_s("Tong doanh thu: %lf \n",dataCourse.doanhThu());
	line();
	printf_s("Tong tien lai: %lf \n",dataCourse.tienLai());
	line();
	cout<<"0. Quay lai.\n";
	switch (getResult())
	{
	
	default:
		{
			mainMenu(logedUser.type);
		break;
		}
	}
}
int MainWindow::getResult()
{
	SetColor(13);
	cout<<">>>>>> Nhap lua chon: ";
	int choice;
	scanf_s("%d",&choice);
	SetColor(0);
	fflush(stdin);
	return choice;
}
void MainWindow::headerMain()
{
	header();
	SetColor(10);
	printf("%54s %s \n","Hello",(logedUser.name).c_str());
	SetColor(0);
	line();
}
void MainWindow::line()
{
	cout<<"-----------------------------------------------------------------------------------------------------------------------\n";
}
