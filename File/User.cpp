#include <string>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "File/User.hpp"


std::istream &operator>>(std::istream &in, User &user) {
    // Fri May 16 14:25:00 2025
    std::string day;
    std::string month;
    int date;
    std::string yymmss;
    int year;
    in >> user.Name >> user.Hash >> user.Score >> day >> month >> date >> yymmss >> year;
    std::stringstream ss;
    ss << day << ' ' << month << ' ' << date << ' ' << yymmss << ' ' << year;
    user.Time = ss.str();
    return in;
}
std::ostream &operator<<(std::ostream &out, User &user) {
    out << user.Name << ' ' << user.Hash << ' ' << user.Score << ' ' << user.Time << '\n';
    return out;
}
UserTable::UserTable(void) {
    table = new User[capacity];
    Update();
    Sort();
}
void UserTable::clearTable(void) {
    total_user = 0;
}
void UserTable::Update(void) {
    clearTable();

    std::ifstream in;

    in.open("Resource/finalscoreboard.txt");

    int now_user;
    User Useri;
    char ignore;
    in >> now_user;
    for (int i = 0; i < now_user; i++) {
        in >> Useri;
        AddNewUser(Useri);
    }

    in.close();
    /*
    FILE *fr = fopen("Resource/scoreboard.txt", "r");

    if (fr) {
        int now_user;
        fscanf(fr, "%d\n", &now_user);
        table = new User[capacity];
        for (int i = 0; i < now_user; i++) {
            char tempname[500];
            int tempscore;
            fscanf(fr, "%s %d\n", tempname, &tempscore);
            User tempUser;
            tempUser.name = tempname;
            tempUser.score = tempscore;
            AddNewUser(tempUser);
        }
    }
    fclose(fr);
    */

    Sort();
}
void UserTable::Save(bool dontchange) {

    std::ofstream out;
    out.open("Resource/scoreboard.txt");

    out << total_user << '\n';

    for (int i = 0; i < total_user; i++) {
        if (!dontchange) {
            if (table[i].Time == "--") {
                std::time_t cur_time = std::time(nullptr);
                table[i].Time = std::asctime(std::localtime(&cur_time));
            }
        }
        out << table[i];
    }

    out.close();

    /*
    for (int i = 0; i < total_user; i++) {
        if (table[i].name == "[]") {
            total_user = i;
        }
    }
    */
    /*
    FILE *fw = fopen("Resource/scoreboard.txt", "w");

    fprintf(fw, "%d\n", total_user);

    for (int i = 0; i < total_user; i++) {
        fprintf(fw, "%s %d\n",
            table[i].name.data(), table[i].score);
    }

    fclose(fw);
    */
}
void UserTable::Sort(void) {
    std::sort(table, table + total_user, [](User u1, User u2) {
        if (u1.Name == "[]" && u2.Name != "[]") {
            return false;
        } else if (u2.Name == "[]" && u1.Name != "[]") {
            return true;
        }
        return u1.Score > u2.Score;
    });
}
User& UserTable::operator[](int idx) {
    return table[idx];
}
int UserTable::size() {
    return total_user;
}
void UserTable::resizeTable(void) {
    capacity *= 2;
    User *temp = table;
    table = new User[capacity];
    memcpy((void*) table, temp, total_user * sizeof(User));
    delete[] temp;
}
void UserTable::AddNewUser(User newuser) {
    if (total_user == capacity) {
        resizeTable();
    }
    table[total_user++] = newuser;
}
void UserTable::GiveName(std::string name) {
    if (name != "") {
        for (int i = 0; i < total_user; i++) {
            if (table[i].Name == "[]") {
                table[i].Name = name;
            }
        }
    }
}
