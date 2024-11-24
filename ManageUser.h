#pragma once

#include"AccountBank.h"
#include"TransactionManage.h"
#include"BankManage.h"

using namespace std; 


class ManageUser {
private: 
	string nameUser; 
	vector<double>purpose;
	BankManage bankManage; 
	TransactionManage transManage;
public:
	ManageUser() {
		this->nameUser = "";
	}
	void loadFromFile(const string& fileName);
	void WriteToFile();

	// lien quan den BankManage
	void printHistoryBank();
	void addAccountBank(); 
	void addAccountBank(AccountBank& Bank);
	void deleteAccountBank();
	double getBalance();
	double getBalanceBank();
	void updateBalance();
	void updateBalance(double& money);
	void printReportBank(); // bao cao chi tieu theo tung tai khoan
	
	// lien quan den TransactionManage
	void printHistory();
	void filterTransaction( string& purpose); // tra cuu lich su giao dich voi muc dich
	void filterTransaction(const std::tm timeStart, const std::tm timeEnd); // tra cứu lịch sử giao dịch với khoảng thời gian


	void editNameUser();
	void displayManage();
	void printReport();
};

void ManageUser::updateBalance(double& money) {
	int index = this->bankManage.updateBalance(money);
	if (index != -1) {
		Transaction ans = this->bankManage.getBank()[index].history[this->bankManage.getBank()[index].history.size() - 1];
		this->transManage.insertTransaction(ans);
		string purpose = ans.purpose;
		purpose = standardize(purpose);
		for (int i = 0; i < 10; i++) {
			if (standardize(destArr[i]) == purpose) {
				this->purpose[i] -= money;
			}
		}
	}
}

void ManageUser::updateBalance() {
	cout << "Nhap so tien ban muon cap nhat: ";
	double money;
	cin >> money;
	int index = this->bankManage.updateBalance(money);
	if (index != -1) {
		Transaction ans = this->bankManage.getBank()[index].history[this->bankManage.getBank()[index].history.size() - 1];
		this->transManage.insertTransaction(ans);
		string purpose = ans.purpose;
		purpose = standardize(purpose);
		for (int i = 0; i < 10; i++) {
			if (standardize(destArr[i]) == purpose) {
				this->purpose[i] -= money;
			}
		}
	}

}

void ManageUser::filterTransaction(const std::tm timeStart, const std::tm timeEnd) {
	this->transManage.filterTransaction(timeStart, timeEnd);
}

void ManageUser::filterTransaction(string& purpose) {
	this->transManage.printHistoryReport(purpose);
}

void ManageUser::printReport() {
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

void ManageUser::printReportBank()
{
	this->bankManage.printReport();
}
void ManageUser::displayManage() {
	cout << "Ten tai khoan: " << this->nameUser << endl;
	cout << "So du: " << this->getBalance() << endl;
}

double ManageUser::getBalanceBank() {
	return this->bankManage.getBalanceBank();
}

double ManageUser::getBalance() {
	return this->bankManage.getBalance();
}

void ManageUser::deleteAccountBank() {
	this->bankManage.deleteAccountBank();
}

void ManageUser::addAccountBank() {
	this->bankManage.addAccountBank();
}

void ManageUser::addAccountBank(AccountBank& Bank) {
	this->bankManage.addAccountBank(Bank);
}

void  ManageUser::editNameUser() {
	cout << "Nhap ten: ";
	getline(cin, this->nameUser);
}

void ManageUser::WriteToFile() {
	string fileName = "inputUser.txt";
	ofstream file(fileName);
	file << this->nameUser << endl;
	for (int i = 0; i < 10; i++) {
		file << this->purpose[i] << " ";
	}
	this->bankManage.WriteToFile();
	this->transManage.WirteToFile();
	file.close();
}

void ManageUser::printHistoryBank() {
	this->bankManage.printHistoryBank();
}

void ManageUser::printHistory() {
	this->transManage.printHistory();
}

void ManageUser::loadFromFile(const string& fileName) {
	ifstream file(fileName);
	if (!file) {
		cout << "Loi mo file\n";
		return;
	}
	getline(file, this->nameUser);
	this->purpose.resize(10);
	for (int i = 0; i < 10; i++) {
		file >> this->purpose[i];
	}
	this->bankManage.loadFromFile();
	this->transManage.LoadFromFile();
	vector<Transaction>Trans = this->transManage.getTrans();
	vector<AccountBank>Bank = this->bankManage.getBank();
	// kiem tra tat ca giao dich de them giao dich vao cac tai khoan]
	for (int i = 0; i < Trans.size(); i++) {
		string ans = Trans[i].nameBank;
		ans = standardize(ans);
		for (int j = 0; j < Bank.size(); j++) {
			string nameBank = Bank[j].accountNumber + Bank[j].nameBank;
			nameBank = standardize(nameBank);
			if (ans == nameBank) {
				this->bankManage.addTransaction(Trans[i], j);
				break;
			}
		}
	}
}


