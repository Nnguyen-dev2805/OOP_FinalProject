#pragma once
#include"Transaction.h"
#include<fstream>
using namespace std;

class TransactionManage {
private:
	vector<Transaction>TransManage;
public: 
	void insertTransaction(Transaction &giaodich);
	void printHistory();
	void printHistoryBank();
	void printHistoryReport( string &purpose);
	void filterTransaction(const std::tm timeStart, const std::tm timeEnd);
	void LoadFromFile();
	void WirteToFile();
	vector<Transaction> getTrans();
};

void TransactionManage::WirteToFile() {
	string fileName = "inputTrans.txt";
	ofstream file(fileName);
	file << this->TransManage.size() << endl;
	for (int i = 0; i < this->TransManage.size(); i++) {
		this->TransManage[i].WriteToFile(file);
	}
	file.close();
}

vector<Transaction> TransactionManage::getTrans() {
	return this->TransManage;
}

void TransactionManage::LoadFromFile() {
	string fileName = "inputTrans.txt";
	ifstream file(fileName);
	int size; 
	file >> size;
	file.ignore();
	for (int i = 0; i < size; i++) {
		Transaction x;
		x.loadFromFile(file);
		this->TransManage.push_back(x);
	}
	file.close();
}

void TransactionManage::filterTransaction(const std::tm timeStart, const std::tm timeEnd) {
	if (this->TransManage.empty()) {
		cout << "Chua co giao dich\n";
	}
	else {
		bool check = false;
		for (int i = 0; i < this->TransManage.size(); i++) {
			if (compareDate(this->TransManage[i].date, timeStart) >= 0 && compareDate(this->TransManage[i].date, timeEnd) <= 0) {
				this->TransManage[i].dispalyForManage();
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

void TransactionManage::printHistoryReport( string &purpose) {
	bool flag = false;
	for (int i = 0; i < this->TransManage.size(); i++) {
		if (standardize(this->TransManage[i].purpose) == purpose) {
			flag = true;
			this->TransManage[i].dispalyForManage();
		}
	}
	if (flag == false) {
		cout << "Khong co giao dich cho muc dich " << purpose<<endl;
	}
}

void TransactionManage::printHistoryBank() {
	if (this->TransManage.empty()) {
		cout << "Chua co giao dich\n";
	}
	else {
		cout << "Lich su giao dich: \n";
		for (int i = 0; i < this->TransManage.size(); i++) {
			this->TransManage[i].displayTransaction();
		}
	}
}

void TransactionManage::insertTransaction(Transaction& giaodich) {
	this->TransManage.push_back(giaodich);
}

void TransactionManage::printHistory() {
	if (this->TransManage.empty()) {
		cout << "Chua co giao dich\n";
	}
	else {
		cout << "Lich su giao dich: \n";
		for (int i = 0; i < this->TransManage.size(); i++) {
			this->TransManage[i].dispalyForManage();
		}
	}
}