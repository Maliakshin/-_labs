#include <iostream>
#include <string>
#include <vector>
using namespace std;
int input(string x);
class Kitchen {
private:
	int budget;
	int place;
	int Boxes;
	vector<string> bills;
public:
	void moneyadd() {
		int money = input("how much money do you want to add: ");
		budget = budget + money;
		cout << "money added to the budget" << endl;
	}
	void delivery() {
		int boxes = input("how many boxes delivered: ");
		int money = input("how much do you need to pay: ");
		if (money <= budget) {
			budget = budget - money;
			if (Boxes + boxes <= place) {
				Boxes = Boxes + boxes;
				cout << "boxes added to the storage" << endl;
			}
			else {
				cout << "not enough place" << endl;
			}
		}
		else {
			cout << "not enough money" << endl;
		}
	}
	void boxes_used() {
		int boxes = input("how many boxes used: ");
		if (Boxes >= boxes) {
			Boxes -= boxes;
			cout << "boxes used" << endl;
		}
		else
		{
			cout << "boxes not used" << endl;
		}
	}
	void new_bill(){
		string meal;
		cout << "ordered dish: " << endl;
		cin >> meal;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		bills.push_back(meal);
		cout << "dish added to the bill list" << endl;
	}
	void meal_done() {
		string meal;
		cout << "made dish: " << endl;
		cin >> meal;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		auto element = find(bills.begin(), bills.end(), meal);
		if (element != bills.end()) {
			bills.erase(element);
		}

	}
	void cooking_list() {
		for (auto i : bills) {
			cout << i << endl;
		}

	}
	void setter(int x, int y, int z) {
		budget = x;
		place = y;
		Boxes = z;
	}
};
class Restaurant {
private:
	static Restaurant* objectR;
	Restaurant() {
		objectK = new Kitchen();
	}
	Kitchen* objectK;
public:
	Restaurant(const Restaurant&) = delete;
	~Restaurant() {
		delete objectK;
		objectR = nullptr;
	}
	static Restaurant* get_object() {
		if (objectR == nullptr) {
			objectR = new Restaurant;
		}
		return objectR;
	}
	Kitchen* get_Kitchen() {
		return objectK;
	}
};
Restaurant* Restaurant::objectR = nullptr;
int input(string x) {
	int y;
	do  
	{
		cout << x << endl;
		cin >> y;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (y < 1 || y > 2000000000);
	return y;
}
void menu(Kitchen*& kitchen1) {
	int variant;
	cout << "Menu:" << endl;
	cout << "1. add money" << endl;
	cout << "2. delivery" << endl;
	cout << "3. use boxes" << endl;
	cout << "4. new order" << endl;
	cout << "5. meal done" << endl;
	cout << "6. cooking list" << endl;
	cout << "7. exit" << endl;
	cin >> variant;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (!(1 <= variant && variant <= 6)) {
		cout << "incorrect!" << endl;
		return;
	}
	switch (variant) {
	case 1:
		kitchen1->moneyadd();
		break;
	case 2:
		kitchen1->delivery();
		break;
	case 3:
		kitchen1->boxes_used();
		break;
	case 4:
		kitchen1->new_bill();
		break;
	case 5:
		kitchen1->meal_done();
		break;
	case 6:
		kitchen1->cooking_list();
		break;
	case 7:
		exit(0);
		break;
	}
}
int main() {
	Restaurant* rest1 = Restaurant::get_object();
	Kitchen* kitchen1 = rest1->get_Kitchen(); 
	int x = input("kitchen budget: ");
	int y = input("Total place in the storage: ");
	int z = input("boxes in the storage: ");
	kitchen1->setter(x, y, z);
	while (1) {
		menu(kitchen1);
	}
	
}