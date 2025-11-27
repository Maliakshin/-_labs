#include <iostream>
#include <string>
#include <vector>

using namespace std;

int standart_price;
int lux_price;
int premium_price;

struct WrongInputException {
	int i;
	WrongInputException(int a) : i(a) {}
};

int Input(string x) {
	cout << x << endl;
	int i;
	std::cin >> i;
	if (cin.peek() != EOF && cin.peek() != '\n') {
		throw WrongInputException(i);
	}
	if (i <= 0 || i >= 2000000000) {
		throw WrongInputException(i);
	}
	std::cin.exceptions(std::istream::failbit);
	return i;
}
int input(string x) {
	trying:
	try {
		return Input(x);
	}
	catch (WrongInputException& ex) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Wrong input! " << endl;
		goto trying;
	}
	catch (...) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Some other exception" << endl;
		goto trying;
	}
}

class Roomtype {
	// тут у меня чисто виртуальные функции и парочка параметров по типу цены и пр
	// логичнее было бы сделать этот класс просто абстрактным добавив функции расчета скидки и конструктор 
public:
	float price;
	virtual void discount(int a) = 0;  
	virtual void get_name() = 0;
	virtual void showprice() = 0;
};
class standart : public Roomtype {
public:
	standart(int Price) {
		price = Price;
	}
	void discount(int a) override {
		price = price - ((price * a) / 100);
		cout << "current price: " << price << endl;
	}
	void get_name() override {
		cout << "This is standart room" << endl;
	}
	void showprice() override {
		cout << "price: "<< price << endl;
	}
};
class lux : public Roomtype {
public:
	lux(int Price) {
		price = Price;
	}
	void discount(int a) override {
		price = price - ((price * a) / 100);
		cout << "current price: " << price << endl;
	}
	void get_name() override {
		cout << "This is lux room" << endl;
	}
	void showprice() override {
		cout << "price: " << price << endl;
	}
};
class premium : public Roomtype {
public:
	premium(int Price) {
		price = Price;
	}
	void discount(int a) override {
		price = price - ((price * a) / 100);
		cout << "current price: " << price << endl;
	}
	void get_name() override {
		cout << "This is premium room" << endl;
	}
	void showprice() override {
		cout << "price: " << price << endl;
	}
};
class room {
private:
	int room_number;
	int roomtype;
	Roomtype* room_type;
public:
// тут в конструкторе я передаю тип комнаты и в привате храню указатель на объект класса конкретного типа комнаты
	void set_room_type(int price) {
		if (price == 0) {
			switch (roomtype)
			{
			case 1:
				room_type = new standart(standart_price);
				break;
			case 2:
				room_type = new lux(lux_price);
				break;
			case 3:
				room_type = new premium(premium_price);
				break;
			}
		}
		else
		{
			switch (roomtype)
			{
			case 1:
				room_type = new standart(price);
				break;
			case 2:
				room_type = new lux(price);
				break;
			case 3:
				room_type = new premium(price);
				break;
			}
		}
	}
	room(int roomnumber, int roomtype1) {
		room_number = roomnumber;
		roomtype = roomtype1;
		set_room_type(0);
	}
	room(const room& other) {
		room_number = other.room_number;
		roomtype = other.roomtype;
		set_room_type(other.room_type->price);
	}
	~room(){
		delete room_type;
	}
	void get_roomtype(){
		room_type->get_name();
	}
	void discount(int a) {
		room_type->discount(a);
	}
	float get_price() {
		return room_type->price;
	}
	void set_price(int Price) {
		room_type->price = Price;
		cout << "new price set" << endl;
	}
	int get_room_number() {
		return room_number;
	}
	void show_price() {
		room_type->showprice();
	}
};

class hotel {
private:
	vector <room> rooms;
	int find_room(int room_number) {
		for (int i = 0; i < rooms.size(); i++) {
			if (room_number == rooms[i].get_room_number()) {
				return i;
			}
		}
		return -1;
	}
public:
	hotel() {
		standart_price = input("standart price");
		lux_price = input("lux price");
		premium_price = input("premium price");

	}
	void add_room(int room_number, int roomtype){
		rooms.emplace_back(room(room_number, roomtype));
	}
	void show_rooms()
	{
		if (rooms.size() == 0) {
			cout << "no rooms yet" << endl;
			return;
		}
		cout << "rooms:" << endl;
		for (int i = 0; i < rooms.size(); i++) {
			cout << rooms[i].get_room_number() << endl;
		}
	}
	void discount(int room_number, int disc)
	{
		int i = find_room(room_number);
		if (i != -1) {
			rooms[i].discount(disc);
		}
		else {
			cout << "no such room" << endl;
		}
	}
	void average_cost() {
		float summ = 0;
		for (int i = 0; i < rooms.size(); i++) {
			summ = summ + rooms[i].get_price();
		}
		cout << summ / rooms.size() << endl;
	}
	void change_price(int room_number, int price){
		int i = find_room(room_number);
		if (i != -1) {
			rooms[i].set_price(price);
		}
		else {
			cout << "no such room" << endl;
		}
	}
	void get_roomtype(int room_number) {
		int i = find_room(room_number);
		if (i != -1) {
			rooms[i].get_roomtype();
		}
		else {
			cout << "no such room" << endl;
		}
	}
	void get_room_price(int room_number) {
		int i = find_room(room_number);
		if (i != -1) {
			rooms[i].show_price();
		}
		else {
			cout << "no such room" << endl;
		}
	}
};

void menu(hotel*& hotel1) {
	int variant;
	cout << "Menu:" << endl;
	cout << "1. add room" << endl;
	cout << "2. show rooms" << endl;
	cout << "3. make a discount" << endl;
	cout << "4. average cost" << endl;
	cout << "5. change price" << endl;
	cout << "6. get room type" << endl;
	cout << "7. show room price" << endl;
	cout << "8. exit" << endl;
	variant = input("choose variant: ");

	if (!(1 <= variant && variant <= 8)) {
		cout << "incorrect!" << endl;
		return;
	}

	switch (variant) {
	case 1: {
		int roomtype = input("roomtype(1-standart, 2-lux, 3-premium):");
		if (!(1 <= roomtype && roomtype <= 3)) {
			cout << "incorrect!" << endl;
			return;
		}
		hotel1->add_room(input("room number: "), roomtype);
		break;
	}
	case 2:
		hotel1->show_rooms();
		break;
	case 3: {
		int discount = input("discount: ");
		if (!(1 <= discount && discount <= 100)) {
			cout << "incorrect!" << endl;
			return;
		}
		hotel1->discount(input("room number: "), discount);
		break;
	}
	case 4:
		hotel1->average_cost();
		break;
	case 5:
		hotel1->change_price(input("room number: "), input("new price: "));
		break;
	case 6:
		hotel1->get_roomtype(input("room: "));
		break;
	case 7:
		hotel1->get_room_price(input("room: "));
		break;
	case 8:
		exit(0);
		break;
	}
}

int main() {
	hotel* hotel1 = new hotel();
	while (1) {
		menu(hotel1);
	}
}