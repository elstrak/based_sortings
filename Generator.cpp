#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

struct key {
public:
    string s;
    int num;
    string name;
    string surname;
    string secName;
    int day;
    int month;
    int year;
};

void generate_name(std::string& name, std::string& surname, std::string& patronymic) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100);

    std::string names[] = { "Danil", "Mihail", "Dmitriy", "Ivan", "Petr", "Maksim", "Oleg", "Denis", "Artem", "Nikita" };
    std::string surnames[] = { "Ivanov", "Balabanov", "Reshetnev", "Bobrovkiy", "Harlamov", "Nalimov", "Petrov", "Parkerov", "Popov", "Hagivagov" };
    std::string patronymics[] = { "Ivanovich", "Maksimovich", "Mihailovich", "Petrovich", "Artemovich", "Nikitych", "Borisovich", "Olegovich", "Dmitrievich", "Andreevich" };

    name = names[dist(rng) % 10];
    surname = surnames[dist(rng) % 10];
    patronymic = patronymics[dist(rng) % 10];
}

std::string random_string() {
    std::string str;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(65, 90);
    for (int i = 0; i < 2; i++) {
        str += (char)dist(gen);
    }
    return str;
}

std::vector<key> generate_keys(int n) {
    std::vector<key> keys;
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distnum(1000, 9999);
    std::uniform_int_distribution<int> distDay(1, 31);
    std::uniform_int_distribution<int> distMonth(1, 12);
    std::uniform_int_distribution<int> distYear(2021, 2025);
    for (int i = 0; i < n; i++) {
        key new_key;
        new_key.s = random_string();
        new_key.num = distnum(rng);
        generate_name(new_key.name, new_key.surname, new_key.secName);
        new_key.day = distDay(rng);
        new_key.month = distMonth(rng);
        new_key.year = distYear(rng);
        keys.push_back(new_key);
    }
    return keys;
}

void write_keys_to_file(const std::vector<key>& keys, const std::string& file_name) {
    std::ofstream file(file_name);
    if (file.is_open()) {
        for (const auto& k : keys) {
            file << k.s << " " << k.num << " " << k.name << " " << k.surname << " " << k.secName << " " << k.day << " " << k.month << " " << k.year << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Could not open file: " << file_name << std::endl;
    }
}

int main() {
    std::vector<key> keys = generate_keys(10);
    write_keys_to_file(keys, "in10.txt");
}
