#pragma once
#include"AccountBank.h"

using namespace std;

class BankManage {
private:
	vector<AccountBank>bankManage;
	double balance;
public:
	BankManage() {
		this->balance = 0;
	}
	int updateBalance();
	int updateBalance(double& money);
	void addAccountBank();
	void addAccountBank(AccountBank newBank);
	void deleteAccountBank();
	double getBalance();
	double getBalanceBank();
	void printReport();
	void loadFromFile();
	vector<AccountBank> getBank();
	void printAccountBank();
	void printHistoryBank();
	void addTransaction(const Transaction& x,int index);
	void WriteToFile();
};

int BankManage::updateBalance(double& money) {
	if (this->bankManage.empty()) {
		cout << "Vui long them tai khoan\n";
		return -1;
	}
	else {
		for (int i = 0; i < this->bankManage.size(); i++) {
			cout << "[" << i + 1 << "]. ";
			this->bankManage[i].printAccountBank();
		}
		cout << endl;
		int choiceAccount;
		cout << "Nhap [0] de quay lai\n";
		cout << "Nhap tai khoan ban muon cap nhat theo STT: ";
		cin >> choiceAccount;
		while (choiceAccount < 0 || choiceAccount > this->bankManage.size()) {
			cout << "Vui long nhap dung STT tai khoan ban muon cap nhat: ";
			cin >> choiceAccount;
		}
		if (choiceAccount == 0) return -1;
		if (!this->bankManage[choiceAccount - 1].updateBalance(money)) {
			return -1;
		}
		this->balance += money;
		return choiceAccount - 1;
	}
}

int BankManage::updateBalance() {
	if (this->bankManage.empty()) {
		cout << "Vui long them tai khoan\n";
		return -1;
	}
	else {
		cout << "[0] Quay lai Menu\n";
		cout << "Nhap so tien ban muon cap nhat: ";
		double money;
		cin >> money;
		for (int i = 0; i < this->bankManage.size(); i++) {
			cout << "[" << i + 1 << "]. ";
			this->bankManage[i].printAccountBank();
		}
		cout << endl;
		int choiceAccount;
		cout << "Nhap tai khoan ban muon cap nhat theo STT: ";
		cin >> choiceAccount;
		while (choiceAccount < 0 || choiceAccount > this->bankManage.size()) {
			cout << "Vui long nhap dung STT tai khoan ban muon cap nhat: ";
			cin >> choiceAccount;
		}
		if (choiceAccount == 0) return -1;
		bool checkUpdate = this->bankManage[choiceAccount - 1].updateBalance(money);
		if (!checkUpdate) {
			return -1;
		}
		this->balance += money;
		//cout << "\n Hoang Ha :" << this->balance << endl;
		return choiceAccount - 1;
	}
}

void BankManage::WriteToFile() {
	string fileName = "inputBank.txt";
	ofstream file(fileName);
	file << this->balance << endl;
	file << this->bankManage.size()<<endl;
	for (int i = 0; i < this->bankManage.size(); i++) {
		this->bankManage[i].WriteToFile(file);
	}
	file.close();
}

void BankManage::addTransaction(const Transaction& x,int index) {
	this->bankManage[index].history.push_back(x);
}

void BankManage::printHistoryBank() {
	if (this->bankManage.empty()) {
		cout << "Vui long them tai khoan\n";
	}
	else {
		this->printAccountBank();
		cout << "[0] Xem lich su giao dich cua tat ca cac tai khoan\n";
		cout << "Nhap tai khoan ban muon kiem tra theo STT: "; 
		int choice;
		cin >> choice;
		while (choice<0 || choice>this->bankManage.size()) {
			cout << "Vui long nhap dung dinh dang: "; 
			cin >> choice;
		}
		if (choice == 0) {
			for (int i = 0; i < this->bankManage.size(); i++) {
				this->bankManage[i].printAccountBank();
				this->bankManage[i].printHistory();
				cout << endl;
			}
		}
		else {
			this->bankManage[choice - 1].printAccountBank();
			this->bankManage[choice - 1].printHistory();
		}
	}
}


void BankManage::printAccountBank() {
	if (this->bankManage.empty()) {
		cout << "Vui long them tai khoan\n";
	}
	else {
		for (int i = 0; i < this->bankManage.size(); i++) {
			cout << "[" << i + 1 << "]. ";
			this->bankManage[i].printAccountBank();
		}
	}
}

vector<AccountBank> BankManage::getBank() {
	return this->bankManage;
}

void BankManage::loadFromFile() {
	string fileName = "inputBank.txt";
	ifstream file(fileName);
	int size; 
	file >> this->balance;
	file >> size;
	for (int i = 0; i < size; i++) {
		file.ignore();
		AccountBank ans;
		ans.loadFromFile(file);
		this->bankManage.push_back(ans);
	}
	file.close();
}

void BankManage::printReport() {
	if (this->bankManage.empty()) {
		cout << "Vui long them tai khoan\n";
	}
	else {
		for (int i = 0; i < this->bankManage.size(); i++) {
			cout << "[" << i + 1 << "]" << ". ";
			this->bankManage[i].printAccountBank();
			//cout << "SD: " << this->bankManage[i].getBalance() << " VND" << endl;
		}
		cout << "[0]. Bao cao tat ca tai khoan.\n";
		cout << "Chon tai khoan theo STT ban muon xem bao cao: ";
		int choiceBank;
		cin >> choiceBank;
		while (choiceBank<0 || choiceBank>this->bankManage.size()) {
			cout << "Vui long nhap dung dinh dang: ";
			cin >> choiceBank;
		}
		if (choiceBank == 0) {
			for (int i = 0; i < this->bankManage.size(); i++) {
				this->bankManage[i].printAccountBank();
				this->bankManage[i].printReport();
				cout << endl;
			}
		}
		else this->bankManage[choiceBank - 1].printReport();
		cout << endl;
	}
}

double BankManage::getBalanceBank() {
	if (this->bankManage.empty()) {
		cout << "Chua co tai khoan\n";
		return 0;
	}
	else {
		double sum = 0;
		for (int i = 0; i < this->bankManage.size(); i++) {
			cout << endl;
			this->bankManage[i].printAccountBank();
			//cout << "SD: " << this->bankManage[i].getBalance() << "VND";
			sum += this->bankManage[i].getBalance();
		}
		return sum;
	}
}

double BankManage::getBalance() {
	return this->balance;
}

void BankManage::deleteAccountBank() {
	if (this->bankManage.empty()) {
		cout << "Chua co tai khoan\n";
	}
	else {
		//double sum = 0;
		for (int i = 0; i < this->bankManage.size(); i++) {
			cout << i + 1 << ". ";
			this->bankManage[i].printAccountBank();
			//sum += this->bankManage[i].getBalance();
		}
		int deleteBank;
		cout << "[0] : Quay lai Menu\n";
		cout << "Nhap tai khoan ban muon xoa theo STT: ";
		cin >> deleteBank;
		if (deleteBank == 0) return;
		while (deleteBank<0 || deleteBank>this->bankManage.size()) {
			cout << "[0] : Quay lai Menu\n";
			cout << "Vui long nhap dung STT tai khoan ban muon xoa.";
			cin >> deleteBank;
			if (deleteBank == 0) return;
		}
		this->balance = this->balance - this->bankManage[deleteBank - 1].getBalance();
		cout << "Da xoa tai khoan ";
		this->bankManage[deleteBank - 1].printAccountBank();
		cout << endl;
		this->bankManage.erase(this->bankManage.begin() + (deleteBank - 1));
	}
}

void BankManage::addAccountBank(AccountBank newBank) {
	this->bankManage.push_back(newBank);
	cout << "Da them tai tai khoan ";
	newBank.printAccountBank();
}

void BankManage::addAccountBank() {
	AccountBank newBank;
	newBank.EditBank();
	this->bankManage.push_back(newBank);
	cout << "Da them tai tai khoan ";
	newBank.printAccountBank();
}