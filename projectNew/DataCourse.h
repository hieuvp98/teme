#pragma once
#include "stdafx.h"
#include "Course.h"

struct DataCourse
{
    Course* listCourse;
	int countCourse;
	DataCourse newDataCourse();
	void loadCourseFromFile(char*);
	void saveCourseToFile(char*);
	void addCourse(Course);
	void deleteCourse(int);
	void huyDangKy(string,string);
	void cancleCourse(string);
	void xoaGiangVien(string);
	void fixCourse(Course,int);
	double doanhThu();
	double tienLai();
	Course getCourseFromId(string);
	
};
DataCourse DataCourse::newDataCourse()
{
	DataCourse dataCourse;
	dataCourse.listCourse = new Course[0];
	dataCourse.countCourse = 0;
	return dataCourse;
}
void DataCourse::addCourse(Course course)
{
	Course* tempo = new Course[countCourse];  // mang  tam thoi
	for ( int i = 0; i < countCourse; i++)
		tempo[i] = listCourse[i];
	listCourse = new Course[countCourse+1]; // tang them mot o nho
	for ( int i = 0; i < countCourse; i++)
		listCourse[i] = tempo[i];
	listCourse[countCourse] = course;  // them vao cuoi mang
	countCourse++;
	delete[] tempo;
}
void DataCourse::deleteCourse(int position)
{
	Course* temp = new Course[countCourse];  // mang  tam thoi
	for ( int i = 0; i < countCourse; i++)
		temp[i] = listCourse[i];
	listCourse = new Course[countCourse-1]; // xoa di mot o nho
	for (int i = 0, j =0 ; i < countCourse ; i++)
	{
		if(i != position) // khong lay thang temp[position] 
		listCourse[j++]=temp[i];
	}
	countCourse--;
	delete[] temp;
}
void DataCourse::huyDangKy(string del,string id)
{
	for (int i = 0; i < countCourse; i++)
	if (!(listCourse[i].maKhoaHoc).compare(del))
		listCourse[i].xoaHocVien(id);
}
void DataCourse::cancleCourse(string ma)
{
	for ( int i = 0; i < countCourse; i++)
	{
		if (!(listCourse[i].maKhoaHoc).compare(ma))
			listCourse[i].hocVienDaDangky--;
	}
}
void DataCourse::xoaGiangVien(string ma)
{
	for ( int i = 0; i < countCourse; i++)
	{
		if (!(listCourse[i].maKhoaHoc).compare(ma))
			listCourse[i].idGiangVien = "";
	}
}
void DataCourse::fixCourse(Course newCourse, int position)
{
    listCourse[position] = newCourse;
}
double DataCourse::doanhThu()
{
	double sum = 0;
	for (int i =0; i < countCourse; i++)
		sum += listCourse[i].doanhThu();
	return sum;
}
double DataCourse::tienLai()
{
	double sum = 0 ;
	for (int i =0; i < countCourse; i++)
		sum += listCourse[i].tienLai();
	return sum;
}
void DataCourse::loadCourseFromFile(char* fileLocation)
{
	Course course;
    FILE* file;
	errno_t arr;
	arr = fopen_s(&file,fileLocation,"r");
	if (!arr){
		countCourse = 0;
		char buff[255];
		fgets(buff, 255, file);
		if (buff == 0)
		{
			fputc('!', file); // dat ky tu '!' o cuoi file
		}
		else{
			while (strcmp(buff, "!")) // dung lai o ki tu '!' dau dong
			{
				course = course.getCourse(buff);
				addCourse(course);
				fgets(buff, 255, file);
			}
		}
	}
	if(file)
		arr = fclose(file);
}
void DataCourse::saveCourseToFile(char* fileLocation)
{
	FILE* file;
	errno_t arr;
	arr = fopen_s(&file,fileLocation,"w");
	if(!arr){
	  for ( int i = 0; i < countCourse; i++)
		  fputs(listCourse[i].toString(),file);
	  fputc('!',file); // dat ky tu '!' o cuoi file
	}
	if(file)
		arr = fclose(file);
}
Course DataCourse::getCourseFromId(string id)
{
	for ( int i =0; i < countCourse; i++)
		if (!listCourse[i].maKhoaHoc.compare(id))
			return listCourse[i];
}
