#include <string>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include "File/User.hpp"


std::istream &operator>>(std::istream &in, User &user) {
    in >> user.Name >> user.Hash >> user.id;
    return in;
}
std::ostream &operator<<(std::ostream &out, User &user) {
    out << user.Name << ' ' << user.Hash << ' ' << user.id << '\n';
    return out;
}
User::User() {
    Score = 0;
}
User::User(std::string name, std::string password) {
    Score = 0;
    Name = name;
    std::size_t hname = std::hash<std::string>{}(name);
    std::size_t hpwd = std::hash<std::string>{}(password);
    Hash = hname ^ (hpwd << 1);
}
void User::addNewRecord(int score) {
    Score = std::max(Score, score);
    record.emplace_back(score);
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
    std::map<int, int> id_to_i;
    clearTable();

    std::ifstream in;

    in.open("Resource/user.txt");

    int now_user;
    User Useri;
    char ignore;
    in >> now_user;
    for (int i = 0; i < now_user; i++) {
        in >> Useri;
        id_to_i.insert({Useri.id, i});
        AddNewUser(Useri);
    }

    in.close();

    in.open("Resource/score.txt");

    int n;
    in >> n;
    int score;
    int id;
    for (int i = 0; i < n; i++) {
        in >> id >> score;
        table[id_to_i[id]].addNewRecord(score);
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
    int n_record = 0;
    out.open("Resource/user.txt");

    out << total_user << '\n';

    for (int i = 0; i < total_user; i++) {
        out << table[i];
        n_record += table[i].record.size();
    }

    out.close();

    out.open("Resource/score.txt");

    out << n_record << '\n';

    for (int i = 0; i < total_user; i++) {
        for (int r : table[i].record) {
            out << table[i].id << " " << r << '\n';
        }
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
        return u1.Score > u2.Score;
    });
}
User& UserTable::operator[](int rank) {
    if (rank >= 0 && rank < total_user) {
        return table[rank];
    }
    return not_a_user;
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
User& UserTable::at(int id) {
    for (int i = 0; i < total_user; i++) {
        if (table[i].id == id) {
            return table[i];
        }
    }
    return table[-1];
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
