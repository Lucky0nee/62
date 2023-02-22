#include <iostream>
#include <vector>
#include <string>
using namespace std;

int g_id = 1;

class realEstate {
public:
	realEstate() {
		cost = (rand() % 10 + 1) * 10000;
		name = "Empty";
	}

	void setName(string name) {
		this->name = name;
	}

	void setCost(double cost) {
		this->cost = cost;
	}

	double GetCost() {
		return cost;
	}

	string GetName() {
		return name;
	}

protected:
	double cost;
	string name;
};

void PrintRealEstates(vector<realEstate*>realEstates) {
	if (realEstates.size() <= 0) {
		cout << "Nothing...";
		return;
	}

	for (int i = 0; i < static_cast<int>(realEstates.size()); i++) {
		cout << i + 1 << ". " << realEstates[i]->GetName() << " - " << realEstates[i]->GetCost() << "\n";
	}
}

class People {
public:
	People() {
		money = 100000; // 100.000
		id = g_id;
		g_id++;
	}

	void DeleteElement(vector<realEstate*>& Vector, int index) {
		if (Vector.size() <= 0 || Vector.size() == index)
			return;

		//cout << Vector.size() << " ";

		for (int i = 0; i < static_cast<int>(Vector.size()); i++) {
			if (i >= index) {
				Vector[i] = (std::exchange(Vector[i + 1], nullptr));
			}
		}

		Vector.pop_back();
		return;
	}

	void BuySomethingFromSomeOne(People &Seller, People& Buyer, int rE_id) {
		if (rE_id < 0 || rE_id > static_cast<int>(Seller.realEstates.size() - 1) || static_cast<int>(Seller.realEstates.size()) == rE_id) {
			cout << "error, try again \n";
			return;
		}

		if (Buyer.money < static_cast<double>(Seller.realEstates[rE_id]->GetCost())) {
			cout << "not enough money \n";
			return;
		}

		Buyer.money -= Seller.realEstates[rE_id]->GetCost();
		Seller.money += Seller.realEstates[rE_id]->GetCost();

		Buyer.realEstates.push_back(std::exchange(Seller.realEstates[rE_id], nullptr));
		DeleteElement(Seller.realEstates, rE_id);

		cout << "Operation successful \n";
	}

	std::vector<realEstate*> GetRealEstateOfPeople() {
		return this->realEstates;
	}

	void AddRealEstate(realEstate* SomeThing) {
		this->realEstates.push_back(SomeThing);
	}

	void PrintInfo() {
		cout << "\nId - " << id;
		cout << "\nmoney - " << money;

		cout << "\nReal Estates: \n";
		PrintRealEstates(realEstates);
	}

protected:
	int id;
	double money;
	std::vector<realEstate*> realEstates;
};

void PrintPeoples(vector<People> Peoples) {
	for (int i = 0; i < static_cast<int>(Peoples.size()); i++) {
		cout << i + 1 << ". ";
		Peoples[i].PrintInfo();
		cout << "\n\n";
	}
}

int main() {
	srand(static_cast<unsigned>(time(NULL)));

	vector<People> Peoples(5);
	realEstate* something1 = new realEstate; something1->setName("Car");      Peoples[rand() % 5].AddRealEstate(something1);
	realEstate* something2 = new realEstate; something2->setName("House");    Peoples[rand() % 5].AddRealEstate(something2);
	realEstate* something3 = new realEstate; something3->setName("Phone");    Peoples[rand() % 5].AddRealEstate(something3);
	realEstate* something4 = new realEstate; something4->setName("Laptop");   Peoples[rand() % 5].AddRealEstate(something4);
	realEstate* something5 = new realEstate; something5->setName("Pot");      Peoples[rand() % 5].AddRealEstate(something5);
	realEstate* something6 = new realEstate; something6->setName("Painting"); Peoples[rand() % 5].AddRealEstate(something6);
	
	while (true) {
		string temp; int p_id = 0; int s_id = 0; int rE_id = 0;
	x:
		cout << "\n";
		cout << "Write 1 to buy something from the user \n";
		cout << "Write 2 to see all people \n";
		cout << "-> "; cin >> temp;

		system("cls");

		if (temp == "1") {
			cout << "Write id (Buyer): "; cin >> p_id;
			cout << "Write id (Seller): "; cin >> s_id;
			
			cout << "Write id (realEstate): "; cin >> rE_id;
			if (rE_id - 1 < 0 || rE_id - 1 > static_cast<int>(Peoples[s_id - 1].GetRealEstateOfPeople().size() - 1)) {
				cout << "error, try again";
				goto x;
			}
			Peoples[p_id - 1].BuySomethingFromSomeOne(Peoples[s_id - 1], Peoples[p_id - 1], rE_id - 1);
			goto x;
		}
		else if (temp == "2") {
			PrintPeoples(Peoples);
			cout << "\n \n";
			goto x;
		}
	}

	return 0;
}
/*
Створити клас об’єктів власності. Кожен об’єкт характеризується вказівником на унікальну адресу об’єкта, назвою, а
також ціною.
Далі створити клас власників. Кожен власник має унікальний ідентифікатор (можна за прикладом податкового коду),
ім’я, прізвище, рахунок із залишком коштів, вектор(список або інший контейнер) з вказівниками на об’єкти власності.
Розробити методи передачі власності від одного власника до іншого. При цьому вказівник на об’єкт власності має
переходити від одного власника до іншого, а також відбуватися передача коштів.
В головній функції створіть перелік об’єктів власності з усіма атрибутами, зокрема ціною. Створіть первісний перелік
власників, які вже володіють певною власністю з вищезгаданого переліка. Застосуйте методи зміни власника таким
чином, щоб в одного з них появився новий об’єкт власності, а в другого збільшилася кількість коштів на рахунку.
*/
