#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <variant>

class UserTable;

class User {
    friend class UserTable;
private:
public:
    std::vector<int> record;
    std::string Name;
    int id;
    int Score = 0;
    std::size_t Hash;

    User();

    User(std::string name, std::string password);

    bool operator==(const User& rhs) { return (Name == rhs.Name && Hash == rhs.Hash); }

    bool sameName(const User& other) { return Name == other.Name; }
    friend std::istream &operator>>(std::istream &in, User &user);
    friend std::ostream &operator<<(std::ostream &out, User &user);
    void addNewRecord(int score);
    std::vector<float> GetRecord(int size);
};

class UserTable {
    // friend class FinalScoreBoardScene;
private:
    int total_user;
    User *table;
    User not_a_user{"not_a_user", "not_a_user"};
    int capacity = 100;
    void resizeTable(void);
    int prevMode = 1;
public:
    enum GAMEMODE { SIXTYSECOND = 1, SURVIVAL = 2 };
    UserTable(void);
    void Update(int mode = -1);
    std::string GetMode();
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
