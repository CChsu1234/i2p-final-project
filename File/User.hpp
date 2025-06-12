#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <variant>


class User {
public:
    int id;
    int Score = 0;
    std::string Name;
    std::size_t Hash;
    std::vector<int> record;

    User();

    User(std::string name, std::string password);

    bool operator==(const User& rhs) { return (Name == rhs.Name && Hash == rhs.Hash); }

    bool sameName(const User& other) { return Name == other.Name; }
    friend std::istream &operator>>(std::istream &in, User &user);
    friend std::ostream &operator<<(std::ostream &out, User &user);
    void addNewRecord(int score);
};

class UserTable {
private:
    int total_user;
    User *table;
    User not_a_user{"not_a_user", "not_a_user"};
    int capacity = 100;
    void resizeTable(void);
public:
    UserTable(void);
    void Update(void);
    void clearTable();
    void Save(bool dontchange = false);
    void Sort(void);
    void AddNewUser(User newuser);
    User& operator[](int rank);
    User& at(int id);
    int size (void);
    void GiveName(std::string name);
    friend std::istream &operator>>(std::istream &in, User &user);
    friend std::ostream &operator<<(std::ostream &out, User &user);
};

#endif
