#pragma once

#include<iostream>
#include<string>
#include"AccountBank.h"


using namespace std; 

class Manage {
private:
	// tong thu va chi se duoc bao cao hang thang 
	// 
	string nameUser; 
	double balance; 
	//vector<LendLoan>lendLoan;
	//vector<BorrowLoan>borrowLoan; 
	vector<AccountBank>Account;
	vector<Transaction>history;
	vector<double>purpose;

public: 
	Manage() : purpose (10,0){
		this->nameUser = ""; 
		this->balance = 0;
	}
	Manage(const string& nameUser) : purpose(10,0){
		this->nameUser = nameUser;
		this->balance = 0;
	}
	void editNameUser(); // chinh sua thong tin nguoi dung 
	void editBalance(); // chinh sua so tien trong ghi chu
	void editManage(); // chinh sua ca hai
	void addAccountBank(); // them tai khoan giao dich moi
	void addAccountBank( AccountBank &Bank);  // them tai khoan moi
	void deleteAccountBank();  // xoa tai khoan ra khoi danh muc quan ly 
	//void Transfer();
	double getBalanceBank(); // báo cáo số dư cả tất cả tài khảon thuộc quyền quản lý
	double getBalance();  // trả về số dư tổng thể
	void updateBalance();  // thêm giao dịch
	void addTransaction(const Transaction &trans); // them giao dich
	void printHistory(); // lich sử giao dịch
	void WriteToFile(const string& fileName); // ghi file
	void displayManage(); // thong tin nguoi dung
	void printHistoryBank(); // in lich su theo tai khoan
	void LoadFromFile(const string& filename); // dọc file 
	void printReport(); // báo cáo chi tiêu theo danh mục
	void filterTransaction(string& purpose); // tra cuu lich su giao dich voi muc dich
	void filterTransaction(const std::tm timeStart, const std::tm timeEnd); // tra cứu lịch sử giao dịch với khoảng thời gian
	bool checkBalance(); // kiem tra neu tai khoan lon 20000 return true
	void printReportBank(); // bao cao chi tieu theo tung tai khoan
};

void Manage::printReportBank() {
	if (this->Account.empty()) {
		cout << "Vui long them tai khoan\n";
	}
	else {
		for (int i = 0; i < this->Account.size(); i++) {
			cout << "[" << i + 1 << "]" << ". ";
			this->Account[i].printAccountBank();
			cout << "SD: " << this->Account[i].getBalance() << " VND" << endl;
		}
		cout << "Chon tai khoan theo STT ban muon xem bao cao: ";
		int choiceBank;
		cin >> choiceBank;
		while (choiceBank<1 || choiceBank>this->Account.size()) {
			cout << "Vui long nhap dung dinh dang: ";
			cin >> choiceBank;
		}
		this->Account[choiceBank - 1].printReport();
		cout << endl;
	}
}

bool Manage::checkBalance() {
	return this->balance > 20000;
}

void Manage::filterTransaction(const std::tm timeStart, const std::tm timeEnd) {
	if (this->history.empty()) {
		cout << "Chua co giao dich\n";
	}
	else {
		bool check = false;
		for (int i = 0; i < this->history.size(); i++) {
			if (compareDate(this->history[i].date, timeStart) >= 0 && compareDate(this->history[i].date, timeEnd) <= 0) {
				this->history[i].dispalyForManage();
				check = true;
			}
		}
		if (check == false) {
			cout << "Khong co giao dich trong khoang thoi gian ";
			printDate(timeStart);
			cout << " - ";
			printDate(timeEnd);
			cout << endl;
		}
	}
}

void Manage::filterTransaction(string& purpose) {
	if (this->history.empty()) {
		cout << "Chua co giao dich\n";
	}
	else {
		bool check=false; 
		for (int i = 0; i < this->history.size(); i++) {
			if (this->history[i].purpose == purpose) {
				this->history[i].dispalyForManage();
				check = true;
			}
		}
		if (check == false) {
			cout << "Chua co giao dich cho muc dich " << purpose << endl;
		}
	}
}

void Manage::printReport() {
	cout << endl;
	cout << "Muc Chi tieu\n";
	cout << "1. Giao duc  : " << this->purpose[0] << " VND" << '\n';
	cout << "2. Suc khoe  : " << this->purpose[1] << " VND" << '\n';
	cout << "3. Gia dinh  : " << this->purpose[2] << " VND" << '\n';
	cout << "4. Mua sam   : " << this->purpose[3] << " VND" << '\n';
	cout << "5. An uong   : " << this->purpose[4] << " VND" << '\n';
	cout << "6. Dau tu    : " << this->purpose[5] << " VND" << '\n';
	cout << "7. Khan cap  : " << this->purpose[6] << " VND" << '\n';
	cout << "8. Du lich   : " << this->purpose[7] << " VND" << '\n';
	cout << "9. Di chuyen : " << this->purpose[8] << " VND" << '\n';
	cout << "Khac         : " << this->purpose[9] << " VND" << '\n';
}

void Manage::WriteToFile(const string& fileName) {
	ofstream file(fileName);
	if (!file) {
		cout << "Loi mo file\n";
		return;
	}
	else {
		// ghi ten nguoi dung
		file << this->nameUser << endl;
		// ghi so du tong the
		file << this->balance << endl;
		// ghi lai so tien cho tieu cho cac muc dich
		for (int i = 0; i < 10; i++) {
			file << this->purpose[i] << " "; 
		}
		file << endl;
		// ghi so luong cac tai khoan =
		file << this->Account.size() << endl;
		for (const auto& account : this->Account) {
			file << account.nameBank << endl; // gh ten ngan hang 
			file << account.accountNumber << endl; // so tai khoan
			file << account.nameUserbank << endl; // ten chu so huu
			file << account.balance <<  endl; // so du tai khoan
			for (const auto& pur : account.purpose) {
				file << pur << " ";
			}
			//file << endl;
		}
		// ghi so luong giao dich
		file << this->history.size() << endl;
		for (const auto& trans : this->history) {
			file << trans.nameBank << endl;
			file << trans.amount << " "<<trans.balance<<" ";
			file << std::put_time(&trans.date, "%d/%m/%Y");
			file<< " " << trans.purpose << " "<<endl;
		}
	}
	file.close();
}

void Manage::LoadFromFile(const string& fileName) {
	ifstream file(fileName); 
	if (!file) {
		cerr << "Khong mo duoc file\n";
		return;
	}
	else {
		getline(file, this->nameUser); // ghi ten
		file >> this->balance; // cap nhat so tien
		this->purpose.resize(10);
		for (int i = 0; i < 10; i++) {
			file >> this->purpose[i];
		}
		int AccountSize; 
		file >> AccountSize; // cap nhat so tai khoan dang duoc su dung
		for (int i = 0; i < AccountSize; i++) {
			file.ignore();
			AccountBank ans;
			ans.loadFromFile(file);
			this->Account.push_back(ans);
		}
		int HistorySize; 
		file >> HistorySize; // so giao dich trong lich su
		file.ignore();
		for (int i = 0; i < HistorySize; i++) {
			Transaction x;
			x.loadFromFile(file);
			this->history.push_back(x);
			for (int j = 0; j < this->Account.size(); j++) {
				string ans = this->Account[j].accountNumber  + this->Account[j].nameBank;
				ans = standardize(ans);
				string nameBank = standardize(x.nameBank);
				if (ans == nameBank) {
					this->Account[j].history.push_back(x);
					break;
				}
			}
		}
	}
	file.close();
}

void Manage::printHistoryBank() {
	if (this->Account.empty()) {
		cout << "Vui long them tai khoan\n";
	}
	else {
		for (int i = 0; i < this->Account.size(); i++) {
			cout << "[" << i + 1 << "]" << ". ";
			this->Account[i].printAccountBank();
			cout << "SD: " << this->Account[i].getBalance() <<" VND" << endl;
		}
		cout << "Chon 0 de xem tat ca\n";
		cout << "Chon tai khoan theo STT ban muon xem lich su: ";
		int choiceBank;
		cin >> choiceBank;
		while(choiceBank<0 || choiceBank>this->Account.size()) {
			cout << "Vui long hap dung dinh dang: ";
			cin >> choiceBank;
		}
		if (choiceBank == 0) {
			for (int i = 0; i < this->Account.size(); i++) {
				this->Account[i].printAccountBank();
				this->Account[i].printHistory();
				cout << endl;
			}
		}
		else {
			this->Account[choiceBank - 1].printAccountBank();
			this->Account[choiceBank - 1].printHistory();
			cout << endl;
		}
	}
}

void Manage::displayManage() {
	cout << "Ten tai khoan: " << this->nameUser << endl;
	cout << "So du: " << this->balance << endl;
}



void Manage::addAccountBank() {
	AccountBank newBank; 
	newBank.EditBank();
	this->Account.push_back(newBank); 
}

void Manage::updateBalance() {
	if (this->Account.empty()) {
		cout << "Vui long tao tai khoan!\n";
	}
	cout << "[0] Quay lai Menu\n"; 
	cout << "Nhap so tien ban muon cap nhat: ";
	double money;
	cin >> money; 
	if (money == 0) return; 
	else {
		for (int i = 0; i < this->Account.size(); i++) {
			cout << "["<<i + 1<<"]" << ". ";
			this->Account[i].printAccountBank();
			cout << "SD: " << this->Account[i].getBalance()<<" VND" << endl;
		}
		cout << endl;
		int choiceAccount; 
		cout << "Nhap tai khoan ban muon cap nhat theo STT: ";
		cin >> choiceAccount;
		while (choiceAccount < 1||choiceAccount > this->Account.size()) {
			cout << "Vui long nhap dung STT tai khoan ban muon cap nhat: "; 
			cin >> choiceAccount;
		}
		Transaction giaodich; 
		string nameBank="";
		nameBank = nameBank + this->Account[choiceAccount - 1].getAccountNumber() + this->Account[choiceAccount - 1].getnameBank();
		std::tm ngay = getCurrentDate();
		giaodich.setTransaction(nameBank,ngay, money,this->Account[choiceAccount-1].balance+money, "");
		// neu giao dich thanh conng
		int indexPurpose = -1;
		if (this->Account[choiceAccount - 1].updateBalance(money, giaodich,indexPurpose)) {
			this->history.push_back(giaodich);
			this->balance += money;
			if (indexPurpose != -1) {
				this->purpose[indexPurpose] -= money;
			}
		}
	}
}

void Manage::deleteAccountBank() {
	if (this->Account.empty()) {
		cout << "Chua co tai khoan\n";
	}
	else {
		//double sum = 0;
		for (int i = 0; i < this->Account.size(); i++) {
			cout << i+1 << ". ";
			this->Account[i].printAccountBank();
			cout << "So du: " << this->Account[i].getBalance()<<"VND "<<endl;
			//sum += this->Account[i].getBalance();
		}
		int deleteBank;
		cout << "[0] : Quay lai Menu\n";
		cout << "Nhap tai khoan ban muon xoa theo STT: "; 
		cin >> deleteBank; 
		if (deleteBank == 0) return; 
		while (deleteBank<0 || deleteBank>this->Account.size()) {
			cout << "[0] : Quay lai Menu\n";
			cout << "Vui long nhap dung STT tai khoan ban muon xoa.";
			cin >> deleteBank;
			if (deleteBank == 0) return;
		}
		this->balance = this->balance - this->Account[deleteBank - 1].getBalance();
		cout << "Da xoa tai khoan "; 
		this->Account[deleteBank - 1].printAccountBank(); 
		cout << endl;
		this->Account.erase(this->Account.begin()+(deleteBank-1));
	}
}

void Manage::printHistory() {
	if (this->history.empty()) {
		cout << "Chua co giao dich\n"; 
	}
	else {
		cout << "lich su giao dich: \n"; 
		for (int i = 0; i < this->history.size(); i++) {
			this->history[i].dispalyForManage();
		}
	}
}

void Manage::addTransaction(const Transaction &trans) {
	this->history.push_back(trans);
}


double Manage::getBalanceBank() {
	if (this->Account.empty()) {
		cout << "Chua co tai khoan\n";
		return 0;
	}
	else {
		double sum = 0;
		for (int i = 0; i < this->Account.size(); i++) {
			cout << endl;
			this->Account[i].printAccountBank(); 
			cout << "SD: " << this->Account[i].getBalance()<<"VND";
			sum += this->Account[i].getBalance();
		}
		return sum;
	}
}

double Manage::getBalance() {
	return this->balance;
}

void Manage::addAccountBank( AccountBank &Bank) {
	this->Account.push_back(Bank);
	cout << "Da them tai tai khoan "; 
	Bank.printAccountBank();
}

void Manage::editNameUser() {
	cout << "Nhap ten: "; 
	getline(cin, this->nameUser);
}

void Manage::editBalance() {
	cout << "Nhap so tien ban muon cap nhat: "; 
	cin >> this->balance;
}

void Manage::editManage() {
	this->editNameUser(); 
	this->editBalance();
}


