#include <iostream>
#include <string>
#include <vector>
using namespace std;
int input(string x);
string input_name(string x);
class guest;
enum class roomtype {standart = 1, lux, president };
int getroomprice(roomtype type);


int standart_price;
int lux_price;
int president_price;

class guest {
private:
	string name;
	string surname;
	int passport;
	int days;
public:
	guest(int set_passport) {
		name = input_name("guest name: ");
		surname = input_name("guest surname: ");
		days = input("how many days: ");
		passport = set_passport;
	}
	void get_info() {
		cout << "name:" << endl;
		cout << name << endl;
		cout << "surname:" << endl;
		cout << surname << endl;
		cout << "days:" << endl;
		cout << days << endl;
		cout << "passport:" << endl;
		cout << passport << endl;
	}
	int get_days() {
		return days;
	}
	int get_passport() {
		return passport;
	}
};
class room {
private:
	int price;
	int room_number;
	guest* client = nullptr;
public:
	room(int x, roomtype type)
	{
		price = getroomprice(type);
		room_number = x;
	}
	bool free() {
		if (client == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	void new_guest(int passport) {
		if (client == nullptr) {
			client = new guest(passport);
		}
	}
	void get_profit() {
		cout << "profit:" << endl;
		cout << client->get_days()*price << endl;
	}
	int get_passport() {
		return client->get_passport();
	}
	void get_guest_info() {
		client->get_info();
	}
};
class hotel {
private:
	vector <room> rooms;
	vector <room> luxrooms;
	vector <room> presidentrooms;
	string name;
public:
	int price_st = 100;
	hotel() {
		name = input_name("hotel name:");
		int rooms_amount = input("amount of standart rooms:");
		standart_price = input("price of standart rooms:");
		int luxrooms_amount = input("amount of lux rooms:");
		lux_price = input("price of lux rooms:");
		int prrooms_amount = input("amount of president rooms:");
		president_price = input("price of president rooms:");
		for (int i = 1; i <= rooms_amount; i++) {
			rooms.emplace_back(room(i, roomtype::standart));
		}
		for (int i = 1; i <= luxrooms_amount; i++) {
			luxrooms.emplace_back(room(i, roomtype::lux));
		}
		for (int i = 1; i <= prrooms_amount; i++) {
			presidentrooms.emplace_back(room(i, roomtype::president));
		}
	}
	~hotel() {
		cout << "hotel destroyed" << endl;
	}
	void new_client(roomtype type) {
		int passport = input("passport number (together): ");
		bool flag = false;
		for (int i = 0; i < rooms.size(); i++) {
			if (!rooms[i].free()) {
				if (passport == rooms[i].get_passport()) {
					flag = true;
					break;
				}
			}
		}
		if (!flag)
		{
			for (int i = 0; i < luxrooms.size(); i++) {
				if (!luxrooms[i].free()) {
					if (passport == luxrooms[i].get_passport()) {
						flag = true;
						break;
					}
				}
			}
		}
		if (!flag)
		{
			for (int i = 0; i < presidentrooms.size(); i++) {
				if (!presidentrooms[i].free()) {
					if (passport == presidentrooms[i].get_passport()) {
						flag = true;
						break;
					}
				}
			}
		}
		if (flag)
		{
			cout << "this passport already used!" << endl;
			return;
		}
		flag = false;
		switch (static_cast<int>(type))

		{
		case(1) :
			for (int i = 0; i < rooms.size(); i++) {
				if (rooms[i].free()) {
					rooms[i].new_guest(passport);
					cout << "Guest added" << endl;
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				cout << "all rooms of this type are busy!" << endl;
			}
			break;
		case(2):
			for (int i = 0; i < luxrooms.size(); i++) {
				if (luxrooms[i].free()) {
					luxrooms[i].new_guest(passport);
					cout << "Guest added" << endl;
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				cout << "all rooms of this type are busy!" << endl;
			}
			break;
		case(3):
			for (int i = 0; i < presidentrooms.size(); i++) {
				if (presidentrooms[i].free()) {
					presidentrooms[i].new_guest(passport);
					cout << "Guest added" << endl;
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				cout << "all rooms of this type are busy!" << endl;
			}
			break;
		}

	}
	void free_rooms() {
		cout << "free standart rooms: " << endl;
		for (int i = 0; i < rooms.size(); i++) {
			if (rooms[i].free()) {
				cout << "standart " << i + 1 << endl;
			}
		}
		cout << "free lux rooms: " << endl;
		for (int i = 0; i < luxrooms.size(); i++) {
			if (luxrooms[i].free()) {
				cout << "lux " << i+1 << endl;

			}
		}
		cout << "free president rooms: " << endl;
		for (int i = 0; i < presidentrooms.size(); i++) {
			if (presidentrooms[i].free()) {
				cout << "president " << i+1 << endl;
			}
		}
	}
	void guests() {
		for (int i = 0; i < rooms.size(); i++) {
			if (!rooms[i].free()) {
				cout << "room standart:" << endl;
				cout << i + 1 << endl;
				rooms[i].get_guest_info();
			}
		}
		for (int i = 0; i < luxrooms.size(); i++) {
			if (!luxrooms[i].free()) {
				cout << "room lux:" << endl;
				cout << i + 1 << endl;
				luxrooms[i].get_guest_info();
			}
		}
		for (int i = 0; i < presidentrooms.size(); i++) {
			if (!presidentrooms[i].free()) {
				cout << "room president:" << endl;
				cout << i + 1 << endl;
				presidentrooms[i].get_guest_info();
			}
		}
	}
	void get_profit() {
		int passport = input("passport (together): ");
		bool fl = false;
		for (int i = 0; i < rooms.size(); i++) {
			if (!rooms[i].free()) {
				if (passport == rooms[i].get_passport()) {
					rooms[i].get_profit();
					fl = true;
					break;
				}
			}
		}
		if (!fl) {
			for (int i = 0; i < luxrooms.size(); i++) {
				if (!luxrooms[i].free()) {
					if (passport == luxrooms[i].get_passport()) {
						luxrooms[i].get_profit();
						fl = true;
						break;
					}
				}
			}
		}
		if (!fl) {
			for (int i = 0; i < presidentrooms.size(); i++) {
				if (passport == presidentrooms[i].get_passport()) {
					presidentrooms[i].get_profit();
					fl = true;
					break;
				}
			}
		}
		if (!fl) {
			cout << "no such guest" << endl;
		}
	}
	void get_info() {
		cout << "name: " << endl;
		cout << name << endl;
		cout << "amount of standart rooms:" << endl;
		cout << rooms.size() << endl;
		cout << "price of standart rooms:" << endl;
		cout << standart_price << endl;
		cout << "amount of lux rooms:" << endl;
		cout << luxrooms.size() << endl;
		cout << "price of lux rooms:" << endl;
		cout << lux_price << endl;
		cout << "amount of president rooms:" << endl;
		cout << presidentrooms.size() << endl;
		cout << "price of president rooms:" << endl;
		cout << president_price << endl;
	}
};

void menu(hotel*& hotel1) {
	int variant;
	cout << "Menu:" << endl;
	cout << "1. new guest" << endl;
	cout << "2. free rooms" << endl;
	cout << "3. guests" << endl;
	cout << "4. get profit" << endl;
	cout << "5. info" << endl;
	cout << "6. exit" << endl;
	cin >> variant;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (!(1 <= variant && variant <= 8)) {
		cout << "incorrect!" << endl;
		return;
	}
	switch (variant) {
	case 1: {
		cout << "choose room type: 1 - standart, 2 - lux, 3 - president" << endl;
		int type = input("room type: ");
		if (!(1 <= type && type <= 3)) {
			cout << "incorrect!" << endl;
			return;
		}
		hotel1->new_client(static_cast<roomtype>(type));
		break;
	}
	case 2:
		hotel1->free_rooms();
		break;
	case 3:
		hotel1->guests();
		break;
	case 4:
		hotel1->get_profit();
		break;
	case 5:
		hotel1->get_info();
		break;
	case 6:
		exit(0);
		break;
	}
}
int input(string x) {
	string y;
	int i = 0;
	do
	{
		i = 0;
		cout << x << endl;
		cin >> y;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		for (char c : y) {
			if (c >= '0' && c <= '9') {
				i = i * 10 + (c - '0');
			}
			else {
				cout << "Bad Input"<< endl;
				i = -1000;
				break;
			}
		}
	} while (i < 1 || i > 46000);
	return i;
}
string input_name(string x) {
	string y;
	cout << x << endl;
	cin >> y;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
	while (1) {
		menu(hotel1);
	}
}