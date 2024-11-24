#include<iostream>
#include<math.h>
#include<string>
//#include"Manage.h"
#include"ManageUser.h"

using namespace std;

void menu() {
	cout << "[1]. update tien\n";
	cout << "[2]. xem lich su\n";
	cout << "[3]. Bao cao\n";
	cout << "[4]. Xem so du.\n";
	cout << "[5]. Kiem tra giao lich su giao dich voi muc chi tieu\n";
	cout << "[6]. Kiem tra lich su giao dich cua tung tai khoan\n";
	cout << "[7]. Kiem tra so du cac tai khoan\n";
	cout << "[8]. Kiem tra lich su giao dich trong khoang thoi gian\n";
	cout << "[9]. Them tai khoan\n";
	cout << "[10]. Xoa tai khoan\n";
	cout << "[11]. Bao cao tai khoan\n";
}

int main() {
	ManageUser Hoangha;
	string filename = "inputUser.txt";
	Hoangha.loadFromFile(filename);
	while (true) {
		/*if (!Hoangha.checkBalance()) {
			cout << "Tai khoan cua ban sap het\n\n";
		}*/
		menu();
		std::cout << "Chon chuc nang: ";
		int program;
		cin >> program;
		cout << endl;
		switch (program) {
		case 1: {
			Hoangha.updateBalance();
			break;
		}
		case 2: {
			Hoangha.printHistory();
			break;
		}
		case 3: {
			Hoangha.printReport();
			break;
		}
		case 4: {
			cout << "So du: " << Hoangha.getBalance();
			break;
		}
		case 5: {
			cout << "Nhap muc chi tieu ban muon kiem tra: ";
			string purpose;
			cin.ignore();
			getline(cin, purpose);
			purpose = standardize(purpose);
			cout << purpose << endl;
			Hoangha.filterTransaction(purpose);
			break;
		}
		case 6: {
			Hoangha.printHistoryBank();
			break;
		}
		case 7: {
			Hoangha.getBalanceBank();
			break;
		}
		case 8:
		{
			cout << "Nhap nhay bat dau (DD/MM/YYYY): ";
			string timeStart;
			cin.ignore();
			getline(cin, timeStart);
			cout << "Nhap ngay ket thuc (DD/MM/YYYY): ";
			string timeEnd;
			getline(cin, timeEnd);
			std::tm dateStart = stringChangeDate(timeStart);
			std::tm dateEnd = stringChangeDate(timeEnd);
			Hoangha.filterTransaction(dateStart, dateEnd);
			break;
		}
		case 9: {
			AccountBank newBank;
			cin.ignore();
			newBank.EditBank();
			Hoangha.addAccountBank(newBank);
			break;
		}
		case 10: {
			Hoangha.deleteAccountBank();
			break;
		}
		case 11: {
			Hoangha.printReportBank();
			break;
		}
		default: {

			break;
		}
		}
		cout << endl << endl;
		cout << "CONTINUE (Y/N)?  ";
		char x;
		cin >> x;
		if (x != 'Y' && x != 'y') {
			break;
		}
	}
	Hoangha.WriteToFile();
}
