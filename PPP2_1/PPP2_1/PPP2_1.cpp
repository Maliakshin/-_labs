#include <iostream>
#include <string>
#include <vector>
using namespace std;
int input(string x);
class guest;
enum class roomtype { standart = 1, lux, president };
int getroomprice(roomtype type);

int standart_price;
int lux_price;
int president_price;

class room {
private:
	int price;
	int room_number;
	guest* client;
public:
	room(int x, roomtype type)
	{
		price = getroomprice(type);
		room_number = x;
	}
	~room() {
		cout << "room destroyed" << endl;
	}
};
class hotel {
private:
	vector <room> rooms;
	string name;
public:
	int price_st = 100;
	hotel() {
		cout << "hotel name:" << endl;
		cin >> name;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		int rooms_amount = input("amount of standart rooms:");
		standart_price = input("price of standart rooms:");
		int luxrooms_amount = input("amount of lux rooms:");
		lux_price = input("price of lux rooms:");
		int prrooms_amount = input("amount of president rooms:");
		president_price = input("price of president rooms:");
		for (int i = 1; i <= rooms_amount; i++) {
			rooms.push_back(room(i, roomtype::standart));
		}
		for (int i = 1; i <= luxrooms_amount; i++) {
			rooms.push_back(room(i, roomtype::lux));
		}
		for (int i = 1; i <= prrooms_amount; i++) {
			rooms.push_back(room(i, roomtype::president));
		}
	}
	~hotel() {
		cout << "hotel destroyed" << endl;
	}
};
class guest {
private:
	string name;
	string surname;
	int passport;
	int days;
};
void menu() {
	int variant;
	cout << "Menu:" << endl;
	cout << "1. add money" << endl;
	cout << "2. delivery" << endl;
	cout << "3. use boxes" << endl;
	cout << "4. new order" << endl;
	cout << "5. meal done" << endl;
	cout << "6. cooking list" << endl;
	cout << "7. info" << endl;
	cout << "8. exit" << endl;
	cin >> variant;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (!(1 <= variant && variant <= 8)) {
		cout << "incorrect!" << endl;
		return;
	}
	switch (variant) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		exit(0);
		break;
	}
}
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
int getroomprice(roomtype type) {
	switch (static_cast<int>(type)) {
		case 1:
			return standart_price;
			break;
		case 2:
			return lux_price;
			break;
		case 3:
			return president_price;
			break;
	}
}
int main() {
	hotel* hotel1 = new hotel();
	delete hotel1;
	while (1) {
		menu();
	}
}