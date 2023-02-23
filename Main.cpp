#include <iostream>
#include <vector>
using namespace std;

class realEstate {
public:
	realEstate() {
		this->cost = (rand() % 10 + 1) * 10000;
		this->address = new string(AddressCountry[rand() % 4] + "/" + AddressCity[rand() % 4] + "/" + AddressHouse[rand() % 4]); // [rand() % 4]
		this->name = "Empty"; 
	}

	realEstate(string name) {
		this->cost = (rand() % 10 + 1) * 10000;
		this->address = new string(AddressCountry[rand() % 4] + "/" + AddressCity[rand() % 4] + "/" + AddressHouse[rand() % 4]); // [rand() % 4]
		this->name = name;
	}

	realEstate(string name, string address) {
		cost = (rand() % 100 + 1) * 1000;
		this->name = name;
		this->address = new string(address);
	}

	double GetCost() {
		return cost;
	}

	string GetName() {
		return name;
	}

	string* GetAddress() {
		return address;
	}

protected:
	string* address;
	string name;
	double cost;
	vector<string> AddressHouse{ "House #1", "House #2", "House #3", "House #4" };
	vector<string> AddressCity{ "City #1", "City #2", "City #3", "City #4" };
	vector<string> AddressCountry{ "Botswana", "Brazil", "Brunei", "Burkina Faso" };
};

void PrintRealEstates(vector<realEstate*>realEstates) {
	if (realEstates.size() <= 0) {
		cout << "Nothing...\n";
		return;
	}

	for (int i = 0; i < static_cast<int>(realEstates.size()); i++) {
		cout << i + 1 << ". " << realEstates[i]->GetName() << " - " << realEstates[i]->GetCost() << " - " << *(realEstates[i]->GetAddress()) << "\n";
	}

}

class People {
public:
	People() {
		money = 100000; // 100.000
		name = Names[rand() % 4];

		id = g_id; g_id++;
	}

	void DeleteElement(vector<realEstate*>& Vector, int index) {
		if (Vector.size() <= 0 || Vector.size() == index)
			return;

		for (int i = 0; i < static_cast<int>(Vector.size()); i++) {
			if (i >= index) {
				Vector[i] = Vector[i + 1];
			}
		}

		Vector.pop_back();
		return;
	}

	void BuySomethingFromSomeOne(People& Seller, People& Buyer, int rE_id) {
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

		Buyer.realEstates.push_back(Seller.realEstates[rE_id]);
		DeleteElement(Seller.realEstates, rE_id);

		cout << "Operation successful \n";
	}

	vector<realEstate*> GetRealEstateOfPeople() {
		return this->realEstates;
	}

	void AddRealEstate(realEstate* SomeThing) {
		this->realEstates.push_back(SomeThing);
	}

	void PrintInfo() {
		cout << "\nId - " << id;
		cout << "\nMoney - " << money;
		cout << "\nName - " << name;

		cout << "\nReal Estates: \n";
		PrintRealEstates(realEstates);
	}

protected:
	int id;
	static int g_id;
	double money;
	string name;
	vector<realEstate*> realEstates;
	vector<string> Names{ "Sasha", "Ivan", "Anya", "Danya"};
};

void PrintPeoples(vector<People> Peoples) {
	for (int i = 0; i < static_cast<int>(Peoples.size()); i++) {
		cout << i + 1 << ". ";
		Peoples[i].PrintInfo();
		cout << "\n";
	}
}

int People::g_id = 1;

int main() {
	srand(static_cast<unsigned>(time(NULL)));

	vector<People> Peoples(3);

	realEstate* something1 = new realEstate("Car");		Peoples[rand() % 3].AddRealEstate(something1);
	realEstate* something2 = new realEstate("House");	Peoples[rand() % 3].AddRealEstate(something2);
	realEstate* something3 = new realEstate("Phone");	Peoples[rand() % 3].AddRealEstate(something3);
	realEstate* something4 = new realEstate("Laptop");	Peoples[rand() % 3].AddRealEstate(something4);
	realEstate* something5 = new realEstate("Pot");     Peoples[rand() % 3].AddRealEstate(something5);
	realEstate* something6 = new realEstate("Painting");Peoples[rand() % 3].AddRealEstate(something6);

	char choice; int p_id = 0, s_id = 0, rE_id = 0;

	while (true) {
		cout << "Write 1 to buy something from the user \n";
		cout << "Write 2 to see all people \n";
		cout << "-> "; cin >> choice;

		system("cls");

		switch (choice) {
		case '1':
			cout << "Write id (Buyer): "; cin >> p_id;
			cout << "Write id (Seller): "; cin >> s_id;
			cout << "Write id (realEstate): "; cin >> rE_id;

			Peoples[p_id - 1].BuySomethingFromSomeOne(Peoples[s_id - 1], Peoples[p_id - 1], rE_id - 1);
			break;
		case '2':
			PrintPeoples(Peoples);
			cout << "\n";
			break;
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
