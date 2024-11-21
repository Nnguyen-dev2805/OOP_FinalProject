#include<iostream>
#include<math.h>
#include<string>
#include"Manage.h"
using namespace std; 

void menu() {
	cout << "[1]. update tien\n"; 
	cout << "[2]. xem lich su\n"; 
	cout << "[3]. Bao cao\n";
	cout << "[4]. Xem so du.\n"; 
	cout << "[5]. Kiem tra giao lich su giao dich voi muc chi tieu\n";
	cout << "[6]. Kiem tra lich su giao dich cua tung tai khoan\n";
	cout << "[7]. Kiem tra so du cac tai khoan\n";
}

int main() {
	/*AccountBank hoangha; 
	hoangha.loadFromFile("input.txt");
	while (true) {
		system("cls");
		menu(); 
		cout << "Nhap: "; 
		int choice; 
		cin >> choice;
		switch(choice)
		{
		case 1: {
			cout << "Nhap so tien: "; 
			double data;
			cin >> data;
			hoangha.updateBalance(data);
			break;
		}
		case 2: {
			hoangha.printHistory(); 
			break;
		}
		case 3: {
			hoangha.printReport();
			break;
		}
		case 4: {
			hoangha.getBalance();
			break;
		}
		case 5: {
			cout << "Nhap muc chi tieu ban muon kiem tra: ";
			string purpose; 
			cin.ignore(); 
			getline(cin, purpose);
			purpose = standardize(purpose);
			cout << purpose << endl;
			hoangha.filterTransaction(purpose);
			break;
		}
		case 6: {
			cout << "Nhap nhay bat dau (DD/MM/YYYY): "; 
			string timeStart; 
			cin.ignore();
			getline(cin, timeStart);
			cout << "Nhap ngay ket thuc (DD/MM/YYYY): "; 
			string timeEnd; 
			getline(cin, timeEnd); 
			std::tm dateStart = stringChangeDate(timeStart); 
			std::tm dateEnd = stringChangeDate(timeEnd);
			hoangha.filterTransaction(dateStart, dateEnd);
			break;
		}
		default:
			continue;
		}
		cout << "Nhap 1 de tiep tuc\n"; 
		cout << "Nhap 0 de dung lai\n";
		cout << "Nhap: "; 
		int stop; 
		cin >> stop;
		if (stop != 1) {
			system("cls"); 
			cout << "              goodbye!!!\n";
			break;
		}
	}
	hoangha.saveToFile("input.txt"); 
	return 0;*/
	Manage Hoangha;
	string filename = "input.txt";
	Hoangha.LoadFromFile(filename);
	while (true) {
		menu();
		cout << "Chon chuc nang: ";
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
			cout<<"So du: "<<Hoangha.getBalance();
			break;
		}
		case 5: {

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
		default: {

			break;
		}
		}
		cout << endl<<endl;
		cout << "CONTINUE (Y/N)?  ";
		char x;
		cin >> x;
		if (x != 'Y' && x != 'y') {
			break;
		}
	}
	Hoangha.WriteToFile(filename);
}
