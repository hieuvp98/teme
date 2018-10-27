#pragma once
#include "stdafx.h"
#include "DataUser.h"
struct Course
{
	string maKhoaHoc;
	string tenKhoaHoc;
	string thoiGian;  // lich hoc
	string khaiGiang;  // dd/mm/yyyy
	double hocPhi;
	double luongGiangVien;
	int soLuongHocVien;
	int hocVienDaDangky;
	int soBuoi;
	string idGiangVien;
	string* idHocVien;
	////// function /////
	void themHocVien(string);
	void xoaHocVien(string);
	string idHocVienToString();
	Course newCourse(string,string,string,string,double,double,int,int,string);
	double tienLai();
	double doanhThu();
	char* toString();
	Course getCourse(char*);
	string thongTin(DataUser);
	string fullThongTin(DataUser);	
};
Course Course::newCourse(string maKhoaHoc, string tenKhoaHoc, string thoiGian, string khaiGiang,
						 double hocPhi,double luongGiangVien,int soLuongHocVien,int soBuoi,string idGiangVien = "")
{
	Course course;
	course.maKhoaHoc = maKhoaHoc;
	course.tenKhoaHoc = tenKhoaHoc;
	course.thoiGian = thoiGian;
	course.khaiGiang = khaiGiang;
	course.hocPhi = hocPhi;
	course.luongGiangVien = luongGiangVien;
	course.soLuongHocVien = soLuongHocVien;
	course.soBuoi = soBuoi;
	course.idGiangVien = idGiangVien;
	course.hocVienDaDangky = 0;
	course.idHocVien = new string[0];
	return course;
}
double Course::tienLai()
{
	return hocVienDaDangky*hocPhi-luongGiangVien;
}
double Course::doanhThu()
{
	return hocVienDaDangky*hocPhi;
}
char* Course::toString()
{
	string val = maKhoaHoc+'|'+tenKhoaHoc+'|'+thoiGian+'|'+khaiGiang+'|'+to_string(hocPhi)+
		'|'+to_string(luongGiangVien)+'|'+to_string(soLuongHocVien)+'|'+to_string(hocVienDaDangky)+'|'+ to_string(soBuoi)+'|'+idGiangVien+'|'+idHocVienToString()+'|'+'\n';
	char* c = new char[val.length()];
	
	for(int i =0; i < val.length();i++)
		c[i] = val[i];
	c[val.length()] = 0;
	return c;
}
string Course::idHocVienToString()
{
	string sum = "";
	for (int i = 0; i < hocVienDaDangky; i++)
	{
		sum += idHocVien[i];
		sum += '#';
	}
	return sum;
}
void Course::themHocVien(string add)
{
	string* temp = new string[hocVienDaDangky];
	for (int i = 0; i < hocVienDaDangky; i++)
		temp[i] = idHocVien[i];
	idHocVien = new string[hocVienDaDangky+1];
	for (int i = 0; i < hocVienDaDangky ; i++)
		idHocVien[i] = temp[i];
	idHocVien[hocVienDaDangky] = add;
	hocVienDaDangky++;
}
void Course::xoaHocVien(string del)
{
	int position = 0;
	for (int i = 0; i < hocVienDaDangky; i++)
	if (!idHocVien[i].compare(del)) position = i;
	string* temp = new string[hocVienDaDangky];
	for (int i = 0; i < hocVienDaDangky; i++)
		temp[i] = idHocVien[i];
	idHocVien = new string[hocVienDaDangky-1];
	for (int i = 0; i < position; i++)
		idHocVien[i] = temp[i];
	for (int j = position; j < hocVienDaDangky - 1; j++)
		idHocVien[j] = temp[j + 1];
	hocVienDaDangky--;

}
Course Course::getCourse(char* c)
{
    Course course;	
	int i = 0;
	    while( c[i] != '|' ) { course.maKhoaHoc += c[i++];}
		i++;
		while (c[i] != '|')  {course.tenKhoaHoc  += c[i++];}
		i++;
		while (c[i] != '|') {course.thoiGian += c[i++];}
		i++;
		while (c[i] != '|') {course.khaiGiang += c[i++];}
		i++;
		string hocphi;
		while (c[i] != '|') {hocphi += c[i++];}
		course.hocPhi = stod(hocphi);
		i++;
		string luong;
		while (c[i] != '|') {luong += c[i++];}
		course.luongGiangVien = stod(luong);
		i++;
		string soluong;
		while (c[i] != '|') {soluong += c[i++];}
		course.soLuongHocVien = stoi(soluong);
		i++;
		string daDangKy;
		while (c[i] != '|') {daDangKy += c[i++];}
		course.hocVienDaDangky = stoi(daDangKy);
		i++;
		string sobuoi;
		while (c[i] != '|') {sobuoi += c[i++];}
		course.soBuoi = stoi(sobuoi);
		i++;
		string idgv;
		while (c[i] != '|') { idgv+= c[i++];}
		course.idGiangVien = idgv;
		i++;
		string* id = new string[course.hocVienDaDangky];					
			for (int j = 0; j < course.hocVienDaDangky; j++)
			{
				while (c[i] != '#') { id[j] += c[i++]; }
				i++;
			}
		course.idHocVien = id;
		return course;
}
string Course::thongTin(DataUser dataUser)
{
	string tenGiangVien;
	if (!idGiangVien.compare(""))  tenGiangVien = "chua co";
	else 
	{
		User giangVien = dataUser.getUserFromId(idGiangVien);
		tenGiangVien = giangVien.name;
	}
	return " Khoa hoc: "+tenKhoaHoc+" | Thoi Gian: "+thoiGian+" | Khai Giang: "+khaiGiang+" | So buoi: "+to_string(soBuoi)
		+"\n     | Hoc Phi: "+to_string(hocPhi)+" |Hoc vien: "
		+to_string(hocVienDaDangky)+'/'+to_string(soLuongHocVien)+" | Giang vien: "+tenGiangVien; 
}
string Course::fullThongTin(DataUser dataUser)
{
	string tenGiangVien;
	if (!idGiangVien.compare(""))  tenGiangVien = "chua co";
	else 
	{
		User giangVien = dataUser.getUserFromId(idGiangVien);
		tenGiangVien = giangVien.name;
	}
	return " Khoa hoc: "+tenKhoaHoc+" | Thoi Gian: "+thoiGian+" | So buoi: "+to_string(soBuoi)+" | Khai giang: "+khaiGiang
		+"\n      Hoc Phi: "+to_string(hocPhi)+" | Luong giang vien: "+to_string(luongGiangVien)+" | Hoc vien: "
		+to_string(hocVienDaDangky)+'/'+to_string(soLuongHocVien)+" | Giang vien: "+tenGiangVien; 
}

//////////////////////////////////////

