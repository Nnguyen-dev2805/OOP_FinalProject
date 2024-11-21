//#pragma once
//#include<iostream>
//#include<string>
//#include<sstream>
//#include<ctime>
//#include<iomanip>
//#include<chrono>
//
//using namespace std;
//
//// hàm lấy ngàyb hiện tại
//std::tm getCurrentDate() {
//	std::time_t t = std::time(nullptr); // lấy thời gian hiện tại dưới dạng time_t
//	std::tm currentDate;
//#ifdef _WIN32 // cách sử dụng với win
//	localtime_s(&currentDate, &t); 
//#else // các hệ điều hành khác
//	currentDate = *std::localtime(&t);
//#endif
//	return currentDate;
//}
//
//// hàm so sanh 2 ngày
//int compareDate(const std::tm& date1, const std::tm date2) {
//	std::tm date1Copy = date1;
//	std::tm date2Copy = date2;
//	// Đặt giờ, phút, giây thành 0 để chỉ tính đến phần ngày tháng năm
//	date1Copy.tm_hour = 0;
//	date1Copy.tm_min = 0;
//	date1Copy.tm_sec = 0;
//	date2Copy.tm_hour = 0;
//	date2Copy.tm_min = 0;
//	date2Copy.tm_sec = 0;
//	std::time_t time1 = std::mktime(&date1Copy);
//	std::time_t time2 = std::mktime(&date2Copy);
//	if (time1 == -1 || time2 == -1) {
//		std::cout << "Loi chuyen doi thoi gian!" << std::endl;
//		return 0;
//	}
//	// Tính số giây chênh lệch, sau đó chuyển sang ngày
//	double secondsDifference = std::difftime(time1, time2);
//	int daysDifference = std::abs(secondsDifference / (60 * 60 * 24));
//	return daysDifference;
//}
//
//void inputDate(std::tm&date) {
//	string ngay;
//	cout << "Nhap ngay giao dich dinh dang (DD/MM/YYYY): ";
//	getline(cin, ngay);
//	string day = ngay.substr(0, 2);
//	string month = ngay.substr(3, 2);
//	string year = ngay.substr(6, 4);
//	date.tm_year = stoi(year) - 1900;
//	date.tm_mon = stoi(month) - 1;
//	date.tm_mday = stoi(day);
//}
//
//class giaodich {
//public: 
//	std::tm date; 
//	double amount;
//	giaodich() {
//		this->date = {}; 
//		this->amount = 0;
//	}
//	void input(); 
//	void display();
//	void setGiaodich(const std::tm& date, double amount); 
//private:
//	void printDate(); 
//};
//
//void giaodich::input() {
//	double data;
//	cout << "Nhap so tien giao dich: "; 
//	cin >> data;
//	string ngay; 
//	cout << "Nhap ngay giao dich dinh dang (DD/MM/YYYY): "; 
//	cin.ignore();
//	getline(cin, ngay);
//	this->amount = data; 
//	string day = ngay.substr(0, 2);
//	string month = ngay.substr(3, 2);
//	string year = ngay.substr(6, 4);
//		this->date.tm_year = stoi(year) - 1900;
//		this->date.tm_mon = stoi(month) - 1;
//		this->date.tm_mday = stoi(day);
//}
//void giaodich::display() {
//	printDate(); 
//	cout << " : " << this->amount << " VND"<<endl;
//}
//
//// hàm in ngày tháng theoi định dạng yyyy-mm--dd
//void giaodich::printDate() {
//	cout << std::put_time(&this->date, "%d/%m/%Y");
//}
//
//void giaodich::setGiaodich(const ::tm& date, double amount) {
//	this->date = date; 
//	this->amount = amount;
//}