#include <iostream>;
#include <stdio.h>;
#include <vector>;
#include <string>;

using namespace std;
class hotel {
public:
    string name;
    int busy_rooms;
    int rooms;
    float price;
    void profit_per_day() {
        cout << "profit per day : " << fixed <<price * busy_rooms << endl;
    }
};

void menu(vector <hotel>* hotels) {
    int variant = 0;
    cout << "Menu:" << endl;
    cout << "1. add hotel" << endl;
    cout << "2. show hotels" << endl;
    cout << "3. count profit" << endl;
    cout << "4. exit" << endl;
    cin >> variant;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!(1 <= variant && variant <= 4)) {
        cout << "incorrect!" << endl;
        return;
    }
    if (variant == 1) {
        string nameinput;
        hotel new_hotel;
        int busy_roomsinput;
        int roomsinput;
        float priceinput;
        cout << "name:" << endl;
        cin >> nameinput;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (auto it = hotels->begin(); it != hotels->end(); ++it) {
            if (it->name == nameinput) {
                cout << "this hotel already added!" << endl;
                return;
            }
        }
        new_hotel.name = nameinput;
        cout << "busy_rooms: " << endl;
        cin >> busy_roomsinput;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (busy_roomsinput < 1 || busy_roomsinput > 2000000000) {
            cout << "incorrect!" << endl;
            return;
        }
        cout << "rooms: " << endl;
        cin >> roomsinput;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (roomsinput < 1 || roomsinput > 2000000000) {
            cout << "incorrect!" << endl;
            return;
        }
        if (busy_roomsinput > roomsinput) {
            cout << "incorrect! busy rooms > rooms. Try again" << endl;
            return;
        }
        cout << "price: " << endl;
        cin >> priceinput;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (priceinput < 0 || priceinput > 2000000000) {
            cout << "incorrect!" << endl;
            return;
        }
        new_hotel.busy_rooms = busy_roomsinput;
        new_hotel.rooms = roomsinput;
        new_hotel.price = priceinput;
        hotels->push_back(new_hotel);
        cout << "hotel added!" << endl;
    }
    if (variant == 2) {
        if (hotels->size() == 0){
            cout << "no hotels yet!" << endl;
            return;
        }
        cout << "hotels:" << endl;
        for (auto it = hotels->begin(); it != hotels->end(); ++it) {
            cout << it->name << endl;
        }
    }
    if (variant == 3) {
        if (hotels->size() == 0) {
            cout << "no hotels yet!" << endl;
            return;
        }
        string hotel_to_count;
        cout << "hotels:" << endl;
        for (auto it = hotels->begin(); it != hotels->end(); ++it) {
            cout << it->name << endl;
        }
        cout << "hotel to count:" << endl;
        cin >> hotel_to_count;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (auto it = hotels->begin(); it != hotels->end(); ++it) {
            if (it->name == hotel_to_count) {
                it->profit_per_day();
                return;

            }
        }
        cout << "no hotels with this name!" << endl;
    }
    if (variant == 4) {
        cout << "bye!" << endl;
        exit(0);
    }
}
int main()
{
    vector < hotel > hotels;
    while (1) {
        menu(&hotels);
    }
}