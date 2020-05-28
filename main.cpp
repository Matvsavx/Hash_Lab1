#include <iostream>
#include <string>

#define isEngaged true
#define isFree false
#define Found true
#define NotFound false

using namespace std;

struct BankCard {
        string name; //фамилия и имя long long
        unsigned long long number;
};

class HashTab {

private:
    unsigned short max_size; //Размер таблицы
    unsigned short curr_size; //Текущее количество записей в таблице
    BankCard *card_vector; //Вектор записей таблицы
    bool *filling_out; //Статус заполненности таблицы (1 – isEngaged (true), 0 – isFree(false))

    unsigned int first_hash(const unsigned long long int &key); //TODO:: Решить с типов данных хеш функций, тк значение будет большое
    unsigned int second_hash(unsigned int &cell);

public:
    HashTab(unsigned short max_size);
    ~HashTab();
    bool add(const BankCard &record);
    bool find(const BankCard &record);
    void print();
};

HashTab::HashTab(unsigned short max_size) {

    this->curr_size = 0;

    if (max_size >= 10)
        this->max_size = max_size;
    else
        this->max_size = 10;

    this->card_vector = new BankCard[max_size];

    this->filling_out = new bool[max_size];

    for (unsigned short i = 0; i < max_size; i++)
        filling_out[i] = isFree;
}

HashTab::~HashTab() {
    delete[] card_vector;
    delete[] filling_out;
}

unsigned int HashTab::first_hash(const unsigned long long int &key) {
    return key % max_size;
}

unsigned int HashTab::second_hash(unsigned int &cell ) {
    return (cell + 1) % max_size;
}

bool HashTab::add(const BankCard &record) {

    if (curr_size < max_size){
        unsigned int cell = first_hash(record.number);

        if (filling_out[cell]){
            if (record.number == card_vector[cell].number)
                return isFree;
            else{
                cell = second_hash(cell);
                while ((cell < max_size) && (filling_out[cell])) {
                    if (record.number != card_vector[cell].number)
                        cell = second_hash(cell);
                    }
            }
        }
        card_vector[cell].number = record.number;
        card_vector[cell].name = record.name;
        filling_out[cell] = isEngaged;
        curr_size++;
    }
    else{
        cout << "ВНИМАНИЕ!!! " << record.name<< " с номером карты " << record.number
        << " не добавлен в таблицу, по причине того, что таблица записей переполнена" << endl;
    }

}

bool HashTab::find(const BankCard &record) {

    unsigned short iterator = 0;
    unsigned int cell = first_hash(record.number);
    if (card_vector[cell].number == record.number) {
        cout << "\nКарта клиента " << record.name << " номер карты " << record.number << " НАЙДЕНА. "<<
        "Номер ячейки в таблице: " << cell << endl;
        return Found;
    }
    else {
        while ((filling_out[cell]) && (cell <= max_size) && (iterator != max_size)) {
            cell = second_hash(cell);
            if (card_vector[cell].number == record.number) {
                cout << "\nКарта клиента " << record.name << " номер карты " << record.number << " НАЙДЕНА. "<<
                     "Номер ячейки в таблице: " << cell << endl;
                return Found;
            }
            iterator++;
        }
    }
    cout << "\nКарта клиента " << record.name << " номер карты " << record.number << " НЕ НАЙДЕНА. " << endl;
    return NotFound;
}

void HashTab::print() {
    cout << "\nномер ячейки в таблице | имя и фамилия | номер карты | \n" << endl;
    for (unsigned int i = 0; i < max_size; i++) {
        if (filling_out[i]) {
            cout << i << " | " << card_vector[i].name << "  |  " << card_vector[i].number << " | " << endl;
        }
        else {
            cout << i << " | " << "Ячейка пуста | " << "Ячейка пуста |" << endl;
        }
    }
}

int main(){
    HashTab CardList = HashTab(10);

    CardList.add({"Савченко Матвей", 4276030012802142});
    CardList.add({"Петров Петр", 4276030012802162});
    CardList.add({"Иванов Иван", 4276030012825903});
    CardList.add({"Иванов Иван", 4276030012825904});
    CardList.add({"Иванов Иван", 4276030012825905});
    CardList.add({"Иванов Иван", 4276030012825906});
    CardList.add({"Иванов Иван", 4276030012825907});
    CardList.add({"Иванов Иван", 4276030012825908});
    CardList.add({"Иванов Иван", 4276030012825909});
    CardList.add({"Иванов Иван", 4276030012825900});
    CardList.add({"Иванов Иван", 4276030012825901});

    cout << "\nТаблица записей владельцов банковских карт\n" << endl;
    CardList.print();
    CardList.find({"Савченко Матве", 1234567812345678});
    CardList.find({"Савченко Матвей", 4276030012802142});
}













