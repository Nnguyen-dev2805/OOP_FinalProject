#pragma once
#include <iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
#include<cctype>
#define all(x) x.begin(), x.end()
using namespace std; 
// chuan hoa string



string standardize(string name) {
	if (name.empty()) return "";
	//transform(name.begin(), name.end(), name.begin(), ::tolower);
	stringstream ss(name); 
	string tmp; 
	string result = "";
	while (ss >> tmp) {
		for (int i = 0; i < tmp.size(); i++) {
			tmp[i] = tolower(tmp[i]);
		}
		result = result + tmp + " "; 
	}
	if (!result.empty()) {
		//result[0] = toupper(result[0]);
		result.erase(result.size() - 1);
	}
	return result;
}

// hàm lấy ngàyb hiện tại
std::tm getCurrentDate() {
	std::time_t t = std::time(nullptr); // lấy thời gian hiện tại dưới dạng time_t
	std::tm currentDate;
#ifdef _WIN32 // cách sử dụng với win
	localtime_s(&currentDate, &t);
#else // các hệ điều hành khác
	currentDate = *std::localtime(&t);
#endif
	return currentDate;
}

// hàm so sanh 2 ngày
int compareDate(const std::tm& date1, const std::tm date2) {
	std::tm date1Copy = date1;
	std::tm date2Copy = date2;
	// Đặt giờ, phút, giây thành 0 để chỉ tính đến phần ngày tháng năm
	date1Copy.tm_hour = 0;
	date1Copy.tm_min = 0;
	date1Copy.tm_sec = 0;
	date2Copy.tm_hour = 0;
	date2Copy.tm_min = 0;
	date2Copy.tm_sec = 0;
	std::time_t time1 = std::mktime(&date1Copy);
	std::time_t time2 = std::mktime(&date2Copy);
	if (time1 == -1 || time2 == -1) {
		std::cout << "Loi chuyen doi thoi gian!" << std::endl;
		return 0;
	}
	// Tính số giây chênh lệch, sau đó chuyển sang ngày
	double secondsDifference = std::difftime(time1, time2);
	int daysDifference = secondsDifference / (60 * 60 * 24);
	return daysDifference;
}

std::tm stringChangeDate(const string& time) {
	std::tm date;
	string day = time.substr(0, 2);
	string month = time.substr(3, 2);
	string year = time.substr(6, 4);
	date.tm_year = stoi(year) - 1900;
	date.tm_mon = stoi(month) - 1;
	date.tm_mday = stoi(day);
	return date;
}

void inputDate(std::tm& date) {
	string ngay;
	cout << "Nhap ngay giao dich dinh dang (DD/MM/YYYY): ";
	getline(cin, ngay);
	string day = ngay.substr(0, 2);
	string month = ngay.substr(3, 2);
	string year = ngay.substr(6, 4);
	date.tm_year = stoi(year) - 1900;
	date.tm_mon = stoi(month) - 1;
	date.tm_mday = stoi(day);
}


bool isValidDate(string& s) {
	s.erase(remove(all(s), ' '), s.end());
	auto valid = [](int day, int month, int year) {
		if (year < 1 || month < 1 || month > 12) return false;
		int daysInMonth = 31;
		if (month == 4 || month == 6 || month == 9 || month == 11) daysInMonth = 30;
		else if (month == 2) daysInMonth = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
		return day >= 1 && day <= daysInMonth;
		};

	//kiểm tra nếu tồn tại kí tự là chữ hoặc kí tự đặc biệt (trừ '/')
	auto hasSpecialOrAlphabet = [](string& S) {
		for (char c : S) if (!isdigit(c) && !isspace(c) && c != '/') return true;
		return false;
		};

	//tách string thành day-month-year và kiểm tra dự liệu
	auto check = [&](string& S) -> bool {
		if (count(all(S), '/') != 2 || hasSpecialOrAlphabet(S)) return false;
		vector<string> ret;
		stringstream ss(S);
		string token;
		while (getline(ss, token, '/')) {
			if (token.empty() || !all_of(token.begin(), token.end(), ::isdigit)) return false;
			ret.push_back(token);
		}
		if (ret.size() != 3) return false;
		return valid(stoi(ret[0]), stoi(ret[1]), stoi(ret[2]));
		};
	return (check(s) ? true : false);
}