#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
#include<iomanip>
#include<chrono>
#include"function.h"
using namespace std;


class Transaction {
public:
	string nameBank;
	std::tm date;
	double amount;
	double balance; // so du tai khoan
	string purpose;
	string note;
	Transaction() {

		this->nameBank = "";
		this->date = {};
		this->amount = 0;
		this->balance = 0;
		this->purpose = "";
		this->note = "";
	}
	void inputTransaction();
	void displayTransaction();
	void setTransaction(const string &nameBank,const std::tm& date,const double &amount,const double &balance,const string &purpose);
	void setTransaction(const std::tm& date, const double& amount, const double& balance, const string& purpose);
	//void setTransaction(const string& nameBank, const std::tm& date, const double& amount,double const& sodu, const string& purpose);
	void dispalyForManage(); // dung cho manage  
private:
	void printDate();
};


void Transaction::dispalyForManage() {
	cout << this->nameBank << " ";
	if (this->amount >=0) cout << "+";
	cout << this->amount << "VND  SD: "<<this->balance<<"VND ";
	printDate();
	cout<<" "<< this->purpose << " ";
	if (!this->note.empty()) cout << " ( " << this->note << " )";
	cout << endl;
}

void Transaction::inputTransaction() {
	double data;
	cout << "Nhap so tien giao dich: ";
	cin >> data;
	string ngay;
	cout << "Nhap ngay giao dich dinh dang (DD/MM/YYYY): ";
	cin.ignore();
	getline(cin, ngay);
	this->amount = data;
	string day = ngay.substr(0, 2);
	string month = ngay.substr(3, 2);
	string year = ngay.substr(6, 4);
	this->date.tm_year = stoi(year) - 1900;
	this->date.tm_mon = stoi(month) - 1;
	this->date.tm_mday = stoi(day);
}

void Transaction::displayTransaction() {
	printDate();
	cout << " : ";
	if (this->amount>=0) cout << "+";
	cout << this->amount << " VND" <<" SD: " << this->balance<< "VND " << this->purpose;
	if (!this->note.empty()) cout << " ( " << this->note << " )"; 
	cout << endl;
}



// hàm in ngày tháng theoi định dạng yyyy-mm--dd
void Transaction::printDate() {
	cout << std::put_time(&this->date, "%d/%m/%Y");
}

void Transaction::setTransaction(const string& nameBank, const std::tm& date, const double& amount, const double& balance, const string& purpose) {
	this->nameBank = nameBank;
	this->date = date;
	this->amount = amount;
	this->balance = balance;
	this->purpose = purpose;
	if(this->purpose.size()>=1) this->purpose = standardize(this->purpose);
}


void Transaction::setTransaction(const ::tm& date, const double& amount, const double& balance, const string& purpose) {
	this->date = date;
	this->amount = amount;
	this->balance = balance;
	this->purpose = purpose;
	if (this->purpose.size() >= 1) this->purpose = standardize(this->purpose);
}