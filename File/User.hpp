#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>


typedef struct _User {
    int score;
    std::string name;
    std::string time;
} User;

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
