#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <variant>


struct User {
    int Score;
    std::string Name;
    std::size_t Hash;

    User() {}

    User(std::string name, std::string password) {
        Score = 0;
        Name = name;
        std::size_t hname = std::hash<std::string>{}(name);
        std::size_t hpwd = std::hash<std::string>{}(password);
        Hash = hname ^ (hpwd << 1);
    }

    bool operator==(const User& rhs) {
        return (Name == rhs.Name && Hash == rhs.Hash);
    }
    friend std::istream &operator>>(std::istream &in, User &user);
    friend std::ostream &operator<<(std::ostream &out, User &user);
};

class UserTable {
private:
    int total_user;
    User *table;
    int capacity = 100;
    void resizeTable(void);
public:
    UserTable(void);
    void Update(void);
    void clearTable();
    void Save(bool dontchange = false);
    void Sort(void);
    void AddNewUser(User newuser);
    User& operator[](int idx);
    int size (void);
    void GiveName(std::string name);
    friend std::istream &operator>>(std::istream &in, User &user);
    friend std::ostream &operator<<(std::ostream &out, User &user);
};
#endif
