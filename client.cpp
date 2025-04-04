#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>

using namespace std;

// ---------- Utility Hash Function ----------
class Hasher {
public:
    static string simpleHash(const string& password) {
        unsigned long hash = 5381;
        for (char c : password) {
            hash = ((hash << 5) + hash) + c;
        }
        stringstream ss;
        ss << hex << hash;
        return ss.str();
    }
};

// ---------- User Class ----------
class User {
private:
    string username;
    string passwordHash;
public:
    User(string uname, string pass) : username(uname), passwordHash(Hasher::simpleHash(pass)) {}

    string getUsername() const { return username; }
    string getPasswordHash() const { return passwordHash; }

    bool verifyPassword(const string& pass) {
        return Hasher::simpleHash(pass) == passwordHash;
    }
};

// ---------- UserManager Class ----------
class UserManager {
private:
    vector<User> users;
    const string userDataFile = "users.txt";
public:
    void loadUsers() {
        ifstream file(userDataFile);
        string uname, pHash;
        while (file >> uname >> pHash) {
            users.emplace_back(uname, pHash); // Use protected constructor or update logic if needed
        }
    }

    void saveUsers() {
        ofstream file(userDataFile);
        for (const auto& user : users) {
            file << user.getUsername() << " " << user.getPasswordHash() << "\n";
        }
    }

    bool userExists(const string& username) {
        return findUser(username) != nullptr;
    }

    User* findUser(const string& username) {
        for (auto& user : users) {
            if (user.getUsername() == username) return &user;
        }
        return nullptr;
    }

    void registerUser() {
        string uname, pass;
        cout << "Enter new username: ";
        cin >> uname;
        if (userExists(uname)) {
            cout << "User already exists!\n";
            return;
        }
        cout << "Enter password: ";
        cin >> pass;
        users.emplace_back(uname, pass);
        saveUsers();
        cout << "Registration successful!\n";
    }

    bool loginUser() {
        string uname, pass;
        cout << "Enter username: ";
        cin >> uname;
        User* user = findUser(uname);
        if (!user) {
            cout << "User not found!\n";
            return false;
        }
        cout << "Enter password: ";
        cin >> pass;
        if (user->verifyPassword(pass)) {
            cout << "Login successful!\n";
            return true;
        } else {
            cout << "Incorrect password!\n";
            return false;
        }
    }

    void displayUsers() {
        cout << "\nRegistered Users (Encrypted Passwords):\n";
        for (const auto& user : users) {
            cout << "Username: " << user.getUsername() << " | Encrypted Password: " << user.getPasswordHash() << "\n";
        }
    }
};

// ---------- Abstract Device Class ----------
class SerialDevice {
protected:
    HANDLE serialHandle;
public:
    virtual bool connect(const string& portName) = 0;
    virtual string readData() = 0;
    virtual ~SerialDevice() = default;
};

// ---------- ESP32Device Class ----------
class ESP32Device : public SerialDevice {
public:
    bool connect(const string& portName) override {
        serialHandle = CreateFile(portName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (serialHandle == INVALID_HANDLE_VALUE) {
            cout << "Failed to connect to ESP32 on " << portName << endl;
            return false;
        }
        cout << "Connected to ESP32 on " << portName << endl;
        return true;
    }

    string readData() override {
        char buffer[64];
        DWORD bytesRead;
        if (ReadFile(serialHandle, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0';
            return string(buffer);
        }
        return "";
    }
};

// ---------- SensorDataManager ----------
class SensorDataManager {
private:
    vector<string> history;
public:
    void addData(const string& data) {
        history.push_back(data);
    }

    void showHistory() {
        if (history.empty()) {
            cout << "No sensor data available.\n";
            return;
        }
        cout << "\nSensor Data History:\n";
        for (const auto& entry : history) {
            cout << entry << "\n";
        }
    }

    void showCurrentData(SerialDevice* device) {
        string data = device->readData();
        if (!data.empty()) {
            cout << "Received Sensor Data: " << data << endl;
            addData(data);
        } else {
            cout << "No data received from ESP32." << endl;
        }
    }
};

// ---------- PumpController ----------
class PumpController {
private:
    bool status = false;
public:
    void setPump(bool on) {
        status = on;
        cout << "Pump is now " << (on ? "ON" : "OFF") << ".\n";
    }

    bool getPumpStatus() const { return status; }

    void remoteControl() {
        int choice;
        cout << "\nRemote Mode:\n1. Turn Pump ON\n2. Turn Pump OFF\nEnter choice: ";
        cin >> choice;
        if (choice == 1) setPump(true);
        else if (choice == 2) setPump(false);
        else cout << "Invalid choice.\n";
    }
};

// ---------- MenuSystem ----------
class MenuSystem {
private:
    UserManager& userManager;
    SerialDevice* device;
    SensorDataManager sensorManager;
    PumpController pump;

public:
    MenuSystem(UserManager& um, SerialDevice* dev) : userManager(um), device(dev) {}

    void mainMenu() {
        while (true) {
            cout << "\nSelect Mode:\n1. Auto Mode\n2. Remote Mode\n3. Show History\n4. Show Current Sensor Data\n5. Show Registered Users\n6. Logout\nEnter choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Auto Mode Activated.\n";
                    break;
                case 2:
                    pump.remoteControl();
                    break;
                case 3:
                    sensorManager.showHistory();
                    break;
                case 4:
                    sensorManager.showCurrentData(device);
                    break;
                case 5:
                    userManager.displayUsers();
                    break;
                case 6:
                    return;
                default:
                    cout << "Invalid choice.\n";
            }
        }
    }
};

// ---------- Main ----------
int main() {
    UserManager userManager;
    userManager.loadUsers();

    ESP32Device esp32;
    string portName = "COM3"; // Update if needed
    if (!esp32.connect(portName)) return 1;

    MenuSystem system(userManager, &esp32);

    while (true) {
        cout << "\n1. Register\n2. Login\nEnter choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) userManager.registerUser();
        else if (choice == 2 && userManager.loginUser()) {
            system.mainMenu();
        } else {
            cout << "Invalid choice or login failed.\n";
        }
    }

    return 0;
}
