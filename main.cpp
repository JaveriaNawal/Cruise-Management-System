#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <thread> // Include the thread header
//#include <termios.h> // Include for non-Windows system

#ifdef _WIN32
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#else
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#endif

using namespace std;

namespace std {
    string getMaskedInput() {
        string password;
        char ch;
    #ifdef _WIN32
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }
    #else
        struct termios oldTerm, newTerm;
        tcgetattr(STDIN_FILENO, &oldTerm);
        newTerm = oldTerm;
        newTerm.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);
        while ((ch = getchar()) != '\n') {
            if (ch == '\b') {
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);
    #endif
        cout << endl;
        return password;
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void gotoRowCol(int rpos, int cpos) {
    int xpos = cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

const string MANAGER_ID = "admin";
const string MANAGER_PASSWORD = "admin";

class Person {
protected:
    string name;
    int age;
    string sex;
    string address;
    string phone;

public:
    Person(string nm = "Null", int ag = 0, string sx = "Null", string addr = "Null", string ph = "Null")
        : name(nm), age(ag), sex(sx), address(addr), phone(ph) {}

    virtual void enterDetails() {
        cout << BLUE << "Enter Name: " << RESET;
        cin.ignore();
        getline(cin, name);
        cout << CYAN << "Enter Age: " << RESET;
        cin >> age;
        cout << GREEN << "Enter Sex: " << RESET;
        cin.ignore();
        getline(cin, sex);
        cout << YELLOW << "Enter Address: " << RESET;
        getline(cin, address);
        cout << RED << "Enter Phone Number: " << RESET;
        getline(cin, phone);
    }

    virtual void displayDetails() const {
        cout << GREEN << "Name: " << RESET << name << endl;
        cout << BLUE << "Age: " << RESET << age << endl;
        cout << CYAN << "Sex: " << RESET << sex << endl;
        cout << RED << "Address: " << RESET << address << endl;
        cout << MAGENTA << "Phone: " << RESET << phone << endl;
    }

    virtual void saveToFile(ofstream &ofs) const {
        ofs << name << '\n' << age << '\n' << sex << '\n' << address << '\n' << phone << '\n';
    }

    virtual void loadFromFile(ifstream &ifs) {
        getline(ifs, name);
        ifs >> age;
        ifs.ignore();
        getline(ifs, sex);
        getline(ifs, address);
        getline(ifs, phone);
    }
};

class Journey {
protected:
    string source;
    string destination;
    string date;
    int duration;

public:
    Journey(string src = "Undefined", string dest = "Undefined", string dt = "Undefined", int dur = 0)
        : source(src), destination(dest), date(dt), duration(dur) {}

    virtual void enterDetails() {
        cout << BLUE << "Enter Source: " << RESET;
        cin.ignore();
        getline(cin, source);
        cout << YELLOW << "Enter Destination: " << RESET;
        getline(cin, destination);
        cout << GREEN << "Enter Date: " << RESET;
        getline(cin, date);
        cout << RED << "Enter Duration (in days): " << RESET;
        cin >> duration;
    }

    virtual void displayDetails() const {
        cout << GREEN << "Source: " << RESET << source << endl;
        cout << CYAN << "Destination: " << RESET << destination << endl;
        cout << RED << "Date: " << RESET << date << endl;
        cout << BLUE << "Duration: " << RESET << duration << " days" << endl;
    }

    int getTicketPrice() const {
        return 50 * duration;
    }

    virtual void saveToFile(ofstream &ofs) const {
        ofs << source << '\n' << destination << '\n' << date << '\n' << duration << '\n';
    }

    virtual void loadFromFile(ifstream &ifs) {
        getline(ifs, source);
        getline(ifs, destination);
        getline(ifs, date);
        ifs >> duration;
        ifs.ignore();
    }
};

class Food {
protected:
    int chinese;
    int indian;
    int other;
    string extraPreferences;

public:
    Food(int chi = 0, int ind = 0, int oth = 0, string extra = "None")
        : chinese(chi), indian(ind), other(oth), extraPreferences(extra) {}

    virtual void enterDetails() {
        cout << BLUE << "Do you want Chinese food (1/0): " << RESET;
        cin >> chinese;
        cout << MAGENTA << "Do you want Indian food (1/0): " << RESET;
        cin >> indian;
        cout << RED << "Do you want to add some extra food like snacks etc (1/0): " << RESET;
        cin >> other;
        cout << GREEN << "Enter extra food preferences: " << RESET;
        cin.ignore();
        getline(cin, extraPreferences);
    }

    virtual void displayDetails() const {
        cout << GREEN << "Chinese: " << RESET << chinese << endl;
        cout << RED << "Indian: " << RESET << indian << endl;
        cout << YELLOW << "Other: " << RESET << other << endl;
        cout << MAGENTA << "Extra Preferences: " << RESET << extraPreferences << endl;
    }

    int calculateFoodExpenses() const {
        return (chinese * 10) + (indian * 8) + (other * 12);
    }

    virtual void saveToFile(ofstream &ofs) const {
        ofs << chinese << '\n' << indian << '\n' << other << '\n' << extraPreferences << '\n';
    }

    virtual void loadFromFile(ifstream &ifs) {
        ifs >> chinese >> indian >> other;
        ifs.ignore();
        getline(ifs, extraPreferences);
    }
};

class Activities {
protected:
    int swimming;
    int theatre;
    int casino;
    int indoorSports;

public:
    Activities(int swim = 0, int theat = 0, int cas = 0, int indoor = 0)
        : swimming(swim), theatre(theat), casino(cas), indoorSports(indoor) {}

    virtual void enterDetails() {
        cout << BLUE << "Do you want swimming activities (1/0): " << RESET;
        cin >> swimming;
        cout << MAGENTA << "Do you want theatre activities (1/0): " << RESET;
        cin >> theatre;
        cout << RED << "Do you want casino activities (1/0): " << RESET;
        cin >> casino;
        cout << CYAN << "Do you want indoor sports activities (1/0): " << RESET;
        cin >> indoorSports;
    }

    virtual void displayDetails() const {
        cout << CYAN << "Swimming: " << swimming << endl;
        cout << GREEN << "Theatre: " << theatre << endl;
        cout << YELLOW << "Casino: " << casino << endl;
        cout << MAGENTA << "Indoor Sports: " << indoorSports << endl << RESET;
    }

    int calculateActivityExpenses() const {
        return (swimming * 5) + (theatre * 7) + (casino * 15) + (indoorSports * 10);
    }

    virtual void saveToFile(ofstream &ofs) const {
        ofs << swimming << '\n' << theatre << '\n' << casino << '\n' << indoorSports << '\n';
    }

    virtual void loadFromFile(ifstream &ifs) {
        ifs >> swimming >> theatre >> casino >> indoorSports;
        ifs.ignore();
    }
};

class Employee : public Person {
private:
    string ID;
    string password;
    int salary;

public:
    Employee(string id = "Undefined", string pass = "Undefined", int sal = 0, string nm = "Undefined", int ag = 0, string sx = "Undefined", string addr = "Undefined", string ph = "Undefined")
        : Person(nm, ag, sx, addr, ph), ID(id), password(pass), salary(sal) {}

    void enterDetails() override {
        Person::enterDetails();
        cout << BLUE << "Enter ID: " << RESET;
        cin.ignore();
        getline(cin, ID);
        cout << GREEN << "Enter Password: " << RESET;
        password = std::getMaskedInput();
        cout << CYAN << "Enter Salary: " << RESET;
        cin >> salary;
    }

    void displayDetails() const override {
        Person::displayDetails();
        cout << RED << "ID: " << RESET << ID << endl;
        cout << MAGENTA << "Salary: " << RESET << salary << endl;
    }

    void saveToFile(ofstream &ofs) const override {
        Person::saveToFile(ofs);
        ofs << ID << '\n' << password << '\n' << salary << '\n';
    }

    void loadFromFile(ifstream &ifs) override {
        Person::loadFromFile(ifs);
        getline(ifs, ID);
        getline(ifs, password);
        ifs >> salary;
        ifs.ignore();
    }

    string getID() const {
        return ID;
    }

    string getPassword() const {
        return password;
    }

    int getSalary() const {
        return salary;
    }
};

class Customer : public Person, public Journey, public Food, public Activities {
private:
    string customerID;

public:
    Customer(string custID = "Undefined", string nm = "Undefined", int ag = 0, string sx = "Undefined", string addr = "Undefined", string ph = "Undefined",
             string src = "Undefined", string dest = "Undefined", string dt = "Undefined", int dur = 0,
             int chi = 0, int ind = 0, int oth = 0, string extra = "None",
             int swim = 0, int theat = 0, int cas = 0, int indoor = 0)
        : Person(nm, ag, sx, addr, ph), Journey(src, dest, dt, dur), Food(chi, ind, oth, extra), Activities(swim, theat, cas, indoor), customerID(custID) {}

    void enterDetails() override {
        Person::enterDetails();
        Journey::enterDetails();
        Food::enterDetails();
        Activities::enterDetails();
    }

    void displayDetails() const override {
        Person::displayDetails();
        Journey::displayDetails();
        Food::displayDetails();
        Activities::displayDetails();
    }

    void saveToFile(ofstream &ofs) const override {
        Person::saveToFile(ofs);
        Journey::saveToFile(ofs);
        Food::saveToFile(ofs);
        Activities::saveToFile(ofs);
        ofs << customerID << '\n';
    }

    void loadFromFile(ifstream &ifs) override {
        Person::loadFromFile(ifs);
        Journey::loadFromFile(ifs);
        Food::loadFromFile(ifs);
        Activities::loadFromFile(ifs);
        getline(ifs, customerID);
    }

    string getCustomerID() const {
        return customerID;
    }

    void displayTotalExpenses() const {
        int totalExpenses = getTicketPrice() + calculateFoodExpenses() + calculateActivityExpenses();
        cout << GREEN << "Total Expenses: $" << RESET << totalExpenses << endl;
    }
};

void managerMenu();
void employeeMenu();
void customerMenu();

void mainMenu() {
    int choice;
    while (true) {
        clearScreen();
        cout << YELLOW << "********** Main Menu **********" << RESET << endl;
        cout << "1. Manager" << endl;
        cout << "2. Employee" << endl;
        cout << "3. Customer" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            managerMenu();
            break;
        case 2:
            employeeMenu();
            break;
        case 3:
            customerMenu();
            break;
        case 4:
            cout << RED << "Exiting..." << RESET << endl;
            return;
        default:
            cout << RED << "Invalid choice. Please try again." << RESET << endl;
        }
    }
}

void managerMenu() {
    clearScreen();
    cout << YELLOW << "********** Manager Login **********" << RESET << endl;
    cout << "Enter Manager ID: ";
    string id;
    cin >> id;
    cout << "Enter Password: ";
    string password = std::getMaskedInput();

    if (id == MANAGER_ID && password == MANAGER_PASSWORD) {
        int choice;
        while (true) {
            clearScreen();
            cout << YELLOW << "********** Manager Menu **********" << RESET << endl;
            cout << "1. Add Employee" << endl;
            cout << "2. View Employees" << endl;
            cout << "3. Add Customer" << endl;
            cout << "4. View Customers" << endl;
            cout << "5. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                Employee emp;
                emp.enterDetails();
                ofstream ofs("employees.txt", ios::app);
                emp.saveToFile(ofs);
                ofs.close();
                cout << GREEN << "Employee added successfully!" << RESET << endl;
                break;
            }
            case 2: {
                ifstream ifs("employees.txt");
                while (ifs.peek() != EOF) {
                    Employee emp;
                    emp.loadFromFile(ifs);
                    emp.displayDetails();
                    cout << endl;
                }
                ifs.close();
                break;
            }
            case 3: {
                Customer cust;
                cust.enterDetails();
                ofstream ofs("customers.txt", ios::app);
                cust.saveToFile(ofs);
                ofs.close();
                cout << GREEN << "Customer added successfully!" << RESET << endl;
                break;
            }
            case 4: {
                ifstream ifs("customers.txt");
                while (ifs.peek() != EOF) {
                    Customer cust;
                    cust.loadFromFile(ifs);
                    cust.displayDetails();
                    cust.displayTotalExpenses();
                    cout << endl;
                }
                ifs.close();
                break;
            }
            case 5:
                cout << RED << "Logging out..." << RESET << endl;
                return;
            default:
                cout << RED << "Invalid choice. Please try again." << RESET << endl;
            }
        }
    } else {
        cout << RED << "Invalid Manager ID or Password. Try again." << RESET << endl;
    }
}

void employeeMenu() {
    clearScreen();
    cout << YELLOW << "********** Employee Login **********" << RESET << endl;
    cout << "Enter Employee ID: ";
    string id;
    cin >> id;
    cout << "Enter Password: ";
    string password = std::getMaskedInput();

    ifstream ifs("employees.txt");
    Employee emp;
    bool loggedIn = false;
    while (ifs.peek() != EOF) {
        emp.loadFromFile(ifs);
        if (emp.getID() == id && emp.getPassword() == password) {
            loggedIn = true;
            break;
        }
    }
    ifs.close();

    if (loggedIn) {
        int choice;
        while (true) {
            clearScreen();
            cout << YELLOW << "********** Employee Menu **********" << RESET << endl;
            cout << "1. View My Details" << endl;
            cout << "2. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                emp.displayDetails();
                break;
            case 2:
                cout << RED << "Logging out..." << RESET << endl;
                return;
            default:
                cout << RED << "Invalid choice. Please try again." << RESET << endl;
            }
        }
    } else {
        cout << RED << "Invalid Employee ID or Password. Try again." << RESET << endl;
    }
}

void customerMenu() {
    clearScreen();
    cout << YELLOW << "********** Customer Menu **********" << RESET << endl;
    Customer cust;
    cust.enterDetails();
    ofstream ofs("customers.txt", ios::app);
    cust.saveToFile(ofs);
    ofs.close();
    cout << GREEN << "Customer added successfully!" << RESET << endl;
}

int main() {
        clearScreen();
    gotoRowCol(2, 10);
    drawShip();
    gotoRowCol(13, 12);
    cout << "Titanic";
   thread waveThread(animateWaterWaves, 20, 25);

    cin.get();

   waveThread.join();
    clearScreen();
    const int MAX_USERS = 100;
    User users[MAX_USERS];
    int userCount = 0;

    loadUsers(users, userCount, "users.dat", MAX_USERS);

    int choice;
    do {
        clearScreen();
        cout << "\n" << MAGENTA << "Cruise Management System:\n" << RESET;
        cout << CYAN << "1. Register New User\n";
        cout << MAGENTA << "2. User Login\n";
        cout << RED << "3. Manager Login\n";
        cout << GREEN << "4. Exit\n" << RESET;
        cout << BLUE << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerUser(users, userCount, MAX_USERS);
                break;
            case 2:
                if (loginUser(users, userCount)) {
                    saveUsers(users, userCount, "users.dat");
                }
                break;
            case 3:
                 {
                Manager manager(users, userCount);
                manager.login();
                saveUsers(users, userCount, "users.dat");
                break;
            }
            case 4:
                saveUsers(users, userCount, "users.dat");
                cout << "Exiting the program...\n";
                break;
            default:
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
                Sleep(1500);
        }
    } while (choice != 4);

    return 0;
}
