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
	void printDate(); 
	void loadFromFile(istream& file);
	void WriteToFile(ostream& file);
};

void Transaction::WriteToFile(ostream& file) {
	file << this->nameBank << endl;
	file << this->amount << " " << this->balance << " ";
	file << std::put_time(&this->date, "%d/%m/%Y");
	file << " " << standardize(this->purpose) << " " << endl;
}

void Transaction::loadFromFile(istream& file) {
	string time;
	//file.ignore();
	if (!getline(file, this->nameBank)) {
		throw std::runtime_error("Error reading history nameBankHistory");
	}
	double sodu;
	file >> this->amount >> this->balance >> time;
	getline(file, this->purpose);
	this->date = stringChangeDate(time);
}

void Transaction::dispalyForManage() {
	/*cout <<left<<setw(15)<< this->nameBank << " ";
	if (this->amount >=0) cout << "+";
	cout << this->amount << "VND  SD: "<<this->balance<<"VND ";
	printDate();
	cout<<" "<< this->purpose << " ";
	if (!this->note.empty()) cout << " ( " << this->note << " )";
	cout << endl;*/
	string tmp = to_string(this->amount);
	tmp = tmp.substr(0, tmp.find('.') + 3);
	string ans = to_string(this->balance);
	ans = ans.substr(0, ans.find('.') + 3);
	cout << left << setw(20) << this->nameBank << " ";
	cout << setw(38)
		<< (this->amount > 0 ? "+" : "") + tmp + "VND "+ "SD:" + ans + "VND ";
	printDate();
	if (!standardize(this->purpose).empty()) cout << setw(20) << " " + standardize(this->purpose) << endl;
	else cout << endl;
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
	/*printDate();
	cout << " : ";
	if (this->amount>=0) cout << "+";
	cout << this->amount << " VND" <<" SD: " << this->balance<< "VND " << this->purpose;
	if (!this->note.empty()) cout << " ( " << this->note << " )"; 
	cout << endl;*/
	printDate();
	string tmp = to_string(this->amount);
	tmp = tmp.substr(0, tmp.find('.') + 3);
	string ans = to_string(this->balance);
	ans = ans.substr(0, ans.find('.') + 3);
	cout << "  ";
	cout << left;
	cout << left << setw(38)
		<< (this->amount > 0 ? "+" : "") + tmp+"VND SD:"+ans+"VND"
	    << setw(20) << this->purpose << endl;
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