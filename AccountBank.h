#pragma once
#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<fstream>
#include"Transaction.h"
#include"function.h"
using namespace std;

string destArr[10] = { "Giao duc","Suc khoe","Gia dinh","Mua sam","An uong","Dau tu","Khan cap","Du lich","Di chuyen","Khac" };

void print_purpose() {
	cout << "Muc Chi tieu\n";
	cout << "1. Giao duc\n"; 
	cout << "2. Suc khoe\n"; 
	cout << "3. Gia dinh\n";
	cout << "4. Mua sam\n"; 
	cout << "5. An uong\n"; 
	cout << "6. Dau tu\n"; 
	cout << "7. Khan cap\n"; 
	cout << "8. Du lich\n"; 
	cout << "9. Di chuyen\n"; 
	cout << "10. Khac\n";
}

class AccountBank {
public:
	string nameUserbank;
	string nameBank; 
	string accountNumber; 
	double balance;
	vector<Transaction>history;
	vector<double>purpose;

	AccountBank() : purpose(10,0){
		this->nameUserbank = "";
		this->nameBank = ""; 
		this->accountNumber = ""; 
		this->balance = 0;
	}
	AccountBank(const string &name,const string &number,const double &amount) : purpose(10,0){
		this->accountNumber = number; 
		this->balance = amount; 
		this->nameBank = name;
		this->nameUserbank = "";
	}
	double getBalance();
	bool updateBalance(const double &data);
	bool updateBalance(const double& data, Transaction &giaodich,int &indexPurpose);
	void printHistory();
	void EditBank();
	void printReport();
	void loadFromFile(istream &file);
	void WriteToFile(ostream& file);
	void saveToFile(const string& filename);
	void Transfer(const string &name,AccountBank &other );
	void filterTransaction(string purpose); // tra cuu lich su giao dich voi muc dich
	void filterTransaction(const std::tm timeStart, const std::tm timeEnd); // tra cuu gai dich trong konag thoi gian nhat dinh
	// cập nhật dữ liệu các lịch sử sau 2 hoặc 3 tháng sẽ bị xóa
	void printAccountBank();
	string getnameBank();
	string getAccountNumber(); 
	string getnameUserBank();
	bool checkBalance(); // kiem tra tài khoản có số du lớn hơn 20000 không , true nếu balance >
	//void ReadFromFile(); 
};

void AccountBank::WriteToFile(ostream& file) {
	file << this->nameBank << endl; // gh ten ngan hang 
	file << this->accountNumber << endl; // so tai khoan
	file << this->nameUserbank << endl; // ten chu so huu
	file << this->balance << endl; // so du tai khoan
	for (const auto& pur : this->purpose) {
		file << pur << " ";
	}
}

bool AccountBank::checkBalance() {
	return this->balance > 20000;
}

string AccountBank::getAccountNumber() {
	return this->accountNumber;
}

string AccountBank::getnameUserBank() {
	return this->nameUserbank;
}

string AccountBank::getnameBank() {
	return this->nameBank;
}

void AccountBank::printAccountBank() {
	cout << this->accountNumber << " " << this->nameBank << " SD:" << this->balance<<"VND "<<endl;
}

void AccountBank::filterTransaction(const std::tm timeStart, const std::tm timeEnd){
	if (this->history.size() == 0) cout << "Chua co giao dich\n";
	else {
		bool check = false;
		for (int i = 0; i < this->history.size(); i++) {
			// neu trong khoang timeStart vaf timeEnd thi xuat ra 
			if (compareDate(this->history[i].date, timeStart) >= 0 && compareDate(this->history[i].date, timeEnd) <= 0) {
				this->history[i].displayTransaction();
			}
		}
		if (check == false) cout << "Khong tim thay giao dich\n";
	}
}

void AccountBank::filterTransaction(string purpose) {
	if (this->history.size() == 0) cout << "Chua co giao dich\n";
	else {
		bool check = false;
		for (int i = 0; i < this->history.size(); i++) {
			if (this->history[i].purpose == purpose) {
				this->history[i].displayTransaction();
				check = true;
			}
		}
		if (check == false) cout << "Khong tim thay giao dich\n";
	}
}

void AccountBank::Transfer(const string& name,AccountBank &other) {
	int data; 
	cout << "Nhap so tien can chuyen: ";
	cin >> data; // data > 0
	while (data <= 0) {
		cout << "Loi! Yeu cau nhap so tien >0 : ";
		cin >> data;
		// lay ngay hien tai cho vao lich su
	}
	int x = this->balance - data;
	if (x < 0) {
		cout << "\nSo tien trong tai khoan khong du de thuc hien giao dich\n";
	}
	else {
		this->balance = x; 
		other.balance += data;
		std::tm timegiaodich = getCurrentDate(); 
		Transaction giaodich;
		string dest = other.nameBank + " " + other.accountNumber;
		string source = this->nameBank + " " + this->accountNumber;
		giaodich.setTransaction(timegiaodich, -data,this->balance,dest);
		this->history.push_back(giaodich);
		giaodich.setTransaction(timegiaodich, data,other.balance,source); 
		other.history.push_back(giaodich);
	}
}

void AccountBank::saveToFile(const string& filename) {
	ofstream file(filename);
	if (file.is_open()) {
		file << this->nameBank<<endl; 
		file << this->accountNumber << endl;
		file << this->balance << endl;
		for (int i = 0; i < 10; i++) {
		     file << this->purpose[i] << " ";
		}
		file << endl;
		file << this->history.size()<<endl; 
		for (int i = 0; i < this->history.size(); i++) {
			file << std::put_time(&this->history[i].date, "%d/%m/%Y") << " " << this->history[i].amount << " "<<this->history[i].purpose << endl;
		}
		file.close(); 
	}
	else {
		cout << "\nKhong the mo file du lieu\n"; 
	}
}

void AccountBank::loadFromFile(istream &file) {
	getline(file, this->nameBank); // ten ngan hang
	getline(file, this->accountNumber); // stk
	getline(file, this->nameUserbank); // ten nguoi dung
	file >> this->balance; // so du tai khoan
	this->purpose.resize(10);
	for (int j = 0; j < 10; j++) {
		file >> this->purpose[j]; // so tien bao cao cho muc dich
	}
}

void AccountBank::printReport() {
	cout << endl;
	cout << "Muc Chi tieu\n";
	cout << "1. Giao duc  : " << this->purpose[0] <<" VND" << '\n';
	cout << "2. Suc khoe  : " << this->purpose[1] <<" VND" << '\n';
	cout << "3. Gia dinh  : " << this->purpose[2] <<" VND" << '\n';
	cout << "4. Mua sam   : " << this->purpose[3] <<" VND" << '\n';
	cout << "5. An uong   : " << this->purpose[4] <<" VND" << '\n';
	cout << "6. Dau tu    : " << this->purpose[5] <<" VND" << '\n';
	cout << "7. Khan cap  : " << this->purpose[6] <<" VND" << '\n';
	cout << "8. Du lich   : " << this->purpose[7] <<" VND" << '\n';
	cout << "9. Di chuyen : " << this->purpose[8] <<" VND" << '\n';
	cout << "Khac         : " << this->purpose[9] <<" VND" << '\n';
}

void AccountBank::EditBank() {
	cout << "Nhap ten ngan hang: "; 
	getline(cin, this->nameBank); 
	cout << "Nhap so tai khoan ngan hang: "; 
	getline(cin, this->accountNumber); 
	cout << "Nhap ten tai khoan: ";
	getline(cin, this->nameUserbank);
	cout << "Cap nhat so tien: "; 
	cin >> this->balance;
}

void AccountBank::printHistory() {
	if (this->history.size() == 0) {
		cout << "\nChua co giao dich!\n";
	}
	else {
		cout << "\nLich su giao dich:\n";
		for (int i = 0; i < this->history.size(); i++) {
			this->history[i].displayTransaction();
		}
		cout << endl;
	}
}

bool AccountBank::updateBalance(const double &data) {
	if (data == 0) return false ;
	string nameB = this->accountNumber + this->nameBank;
	if (data > 0) {
		this->balance += data; 
		Transaction x;
		std::tm ngay = getCurrentDate();
		x.setTransaction(nameB,ngay, data,this->balance,"");
		this->history.push_back(x);
		return true;
	}
	else {
		int x = this->balance + data;
		if (x >= 0) {
			this->balance = x;
			int choice_purpose; 
			print_purpose(); 
			cout << "\nChon muc dich chi tieu: "; 
			cin >> choice_purpose; 
			while (choice_purpose < 1 || choice_purpose>10) {
				cout << "Loi! Vui long nhap lai lua chon\n";
				cin >> choice_purpose;
			}
			string dest; // lưu mục đích vào giao dịch
			dest = destArr[choice_purpose - 1];
			this->purpose[choice_purpose - 1] -= data;
			Transaction giaodich;
			std::tm ngay = getCurrentDate();
			/*string note; 
			cout << "Ghi chu: ";
			getline(cin, note);*/
			giaodich.setTransaction(nameB,ngay, data,this->balance,dest);
			this->history.push_back(giaodich);
			cout << endl;
			return true; 
		}
		else {
			cout << "\nSo du khong du de thuc hien giao dich!\n\n";
			return false; 
		}
	}
}

bool AccountBank::updateBalance(const double& data, Transaction &giaodich,int &indexPurpose) {
	if (data == 0) return false;
	if (data > 0) {
		this->balance += data;
		this->history.push_back(giaodich);
		return true;
	}
	else {
		int x = this->balance + data;
		if (x >= 0) {
			this->balance = x;
			int choice_purpose;
			print_purpose();
			cout << "\nChon muc dich chi tieu: ";
			cin >> choice_purpose;
			while (choice_purpose < 1 || choice_purpose>10) {
				cout << "Loi! Vui long nhap lai lua chon\n";
				cin >> choice_purpose;
			}
			string dest; // lưu mục đích vào giao dịch
			dest = destArr[choice_purpose - 1];
			this->purpose[choice_purpose - 1] -= data;
			indexPurpose = choice_purpose - 1;
			std::tm ngay = getCurrentDate();
			/*string note;
			cout << "Ghi chu: ";
			getline(cin, note);*/
			giaodich.setTransaction(ngay, data,this->balance, dest);
			this->history.push_back(giaodich);
			cout << endl;
			return true;
		}
		else {
			cout << "\nSo du khong du de thuc hien dao dich!\n\n";
			return false; 
		}
	}
}

double AccountBank::getBalance() {
	//cout << "So du: " << this->balance << endl;
	return this->balance;
}

