// #include <iostream>
// #include <fstream>
// #include <string>
// #include <vector>
// #include <sstream>
// #include <iomanip>

// using namespace std;

// struct User {
//     string username;
//     string passwordHash; // Store hashed password
// };

// vector<string> sensorDataHistory;
// vector<User> users;
// bool pumpStatus = false; // False = OFF, True = ON
// const string userDataFile = "users.txt";

// // Simple hashing function (alternative to OpenSSL)
// string simpleHash(const string& password) {
//     unsigned long hash = 5381;
//     for (char c : password) {
//         hash = ((hash << 5) + hash) + c;
//     }
//     stringstream ss;
//     ss << hex << hash;
//     return ss.str();
// }

// // Load users from file
// void loadUsers() {
//     ifstream file(userDataFile);
//     if (!file) return;
//     string username, passwordHash;
//     while (file >> username >> passwordHash) {
//         users.push_back({username, passwordHash});
//     }
//     file.close();
// }

// // Save users to file
// void saveUsers() {
//     ofstream file(userDataFile);
//     for (const auto& user : users) {
//         file << user.username << " " << user.passwordHash << "\n";
//     }
//     file.close();
// }

// // Function to check if user exists
// User* findUser(const string& username) {
//     for (auto& user : users) {
//         if (user.username == username) {
//             return &user;
//         }
//     }
//     return nullptr;
// }

// // Register a new user
// void registerUser() {
//     string username, password;
//     cout << "Enter new username: ";
//     cin >> username;
//     if (findUser(username)) {
//         cout << "User already exists! Try logging in.\n";
//         return;
//     }
//     cout << "Enter password: ";
//     cin >> password;
//     users.push_back({username, simpleHash(password)});
//     saveUsers();
//     cout << "Registration successful!\n";
// }

// // Login function
// bool loginUser() {
//     string username, password;
//     cout << "Enter username: ";
//     cin >> username;
//     User* user = findUser(username);
//     if (!user) {
//         cout << "User not found! Try again.\n";
//         return false;
//     }
//     cout << "Enter password: ";
//     cin >> password;
//     if (user->passwordHash == simpleHash(password)) {
//         cout << "Login successful!\n";
//         return true;
//     }
//     cout << "Incorrect password! Try again.\n";
//     return false;
// }

// // Simulate sensor data collection
// void collectSensorData() {
//     float temp = 25.5; // Simulated data
//     float humidity = 60.2;
//     int soilMoisture = 400;
//     string data = "Temp: " + to_string(temp) + "C, Humidity: " + to_string(humidity) + "%, Soil Moisture: " + to_string(soilMoisture);
//     sensorDataHistory.push_back(data);
//     cout << "Current Sensor Data:\n" << data << "\n";
// }

// // Display history
// void showHistory() {
//     cout << "\nSensor Data History:\n";
//     for (const string& data : sensorDataHistory) {
//         cout << data << "\n";
//     }
// }

// // Remote Mode Function
// void remoteMode() {
//     int choice;
//     cout << "\nRemote Mode:\n1. Turn Pump ON\n2. Turn Pump OFF\nEnter choice: ";
//     cin >> choice;
//     if (choice == 1) {
//         pumpStatus = true;
//         cout << "Pump is now ON.\n";
//     } else if (choice == 2) {
//         pumpStatus = false;
//         cout << "Pump is now OFF.\n";
//     } else {
//         cout << "Invalid choice. Try again.\n";
//     }
// }

// // Main system menu
// void mainMenu() {
//     while (true) {
//         cout << "\nSelect Mode:\n1. Auto Mode\n2. Remote Mode\n3. Show History\n4. Show Current Sensor Data\n5. Logout\nEnter choice: ";
//         int choice;
//         cin >> choice;
//         switch (choice) {
//             case 1:
//                 cout << "Auto Mode Activated.\n";
//                 break;
//             case 2:
//                 remoteMode();
//                 break;
//             case 3:
//                 showHistory();
//                 break;
//             case 4:
//                 collectSensorData();
//                 break;
//             case 5:
//                 return;
//             default:
//                 cout << "Invalid choice. Try again.\n";
//         }
//     }
// }

// int main() {
//     loadUsers();
//     while (true) {
//         cout << "\n1. Register\n2. Login\nEnter choice: ";
//         int choice;
//         cin >> choice;
//         if (choice == 1) {
//             registerUser();
//         } else if (choice == 2) {
//             if (loginUser()) {
//                 mainMenu();
//             }
//         } else {
//             cout << "Invalid choice! Try again.\n";
//         }
//     }
//     return 0;
// }
/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

struct User {
    string username;
    string passwordHash; // Store hashed password
};

vector<string> sensorDataHistory;
vector<User> users;
bool pumpStatus = false; // False = OFF, True = ON
const string userDataFile = "users.txt";

// Simple hashing function (alternative to OpenSSL)
string simpleHash(const string& password) {
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c;
    }
    stringstream ss;
    ss << hex << hash;
    return ss.str();
}

// Load users from file
void loadUsers() {
    ifstream file(userDataFile);
    if (!file) return;
    string username, passwordHash;
    while (file >> username >> passwordHash) {
        users.push_back({username, passwordHash});
    }
    file.close();
}

// Save users to file
void saveUsers() {
    ofstream file(userDataFile);
    for (const auto& user : users) {
        file << user.username << " " << user.passwordHash << "\n";
    }
    file.close();
}

// Display registered users with encrypted passwords
void displayRegisteredUsers() {
    cout << "\nRegistered Users (Encrypted Passwords):\n";
    for (const auto& user : users) {
        cout << "Username: " << user.username << " | Encrypted Password: " << user.passwordHash << "\n";
    }
}

// Function to check if user exists
User* findUser(const string& username) {
    for (auto& user : users) {
        if (user.username == username) {
            return &user;
        }
    }
    return nullptr;
}

// Register a new user
void registerUser() {
    string username, password;
    cout << "Enter new username: ";
    cin >> username;
    if (findUser(username)) {
        cout << "User already exists! Try logging in.\n";
        return;
    }
    cout << "Enter password: ";
    cin >> password;
    users.push_back({username, simpleHash(password)});
    saveUsers();
    cout << "Registration successful!\n";
}

// Login function
bool loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    User* user = findUser(username);
    if (!user) {
        cout << "User not found! Try again.\n";
        return false;
    }
    cout << "Enter password: ";
    cin >> password;
    if (user->passwordHash == simpleHash(password)) {
        cout << "Login successful!\n";
        return true;
    }
    cout << "Incorrect password! Try again.\n";
    return false;
}

// Simulate sensor data collection
void collectSensorData() {
    float temp = 25.5; // Simulated data
    float humidity = 60.2;
    int soilMoisture = 400;
    string data = "Temp: " + to_string(temp) + "C, Humidity: " + to_string(humidity) + "%, Soil Moisture: " + to_string(soilMoisture);
    sensorDataHistory.push_back(data);
    cout << "Current Sensor Data:\n" << data << "\n";
}

// Display history
void showHistory() {
    cout << "\nSensor Data History:\n";
    for (const string& data : sensorDataHistory) {
        cout << data << "\n";
    }
}

// Remote Mode Function
void remoteMode() {
    int choice;
    cout << "\nRemote Mode:\n1. Turn Pump ON\n2. Turn Pump OFF\nEnter choice: ";
    cin >> choice;
    if (choice == 1) {
        pumpStatus = true;
        cout << "Pump is now ON.\n";
    } else if (choice == 2) {
        pumpStatus = false;
        cout << "Pump is now OFF.\n";
    } else {
        cout << "Invalid choice. Try again.\n";
    }
}

// Main system menu
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
                remoteMode();
                break;
            case 3:
                showHistory();
                break;
            case 4:
                collectSensorData();
                break;
            case 5:
                displayRegisteredUsers();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    loadUsers();
    while (true) {
        cout << "\n1. Register\n2. Login\nEnter choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            if (loginUser()) {
                mainMenu();
            }
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <windows.h> // For Serial Communication on Windows


using namespace std;


// OTP verification function

struct User {
    string username;
    string passwordHash; // Store hashed password
};

vector<string> sensorDataHistory;
vector<User> users;
bool pumpStatus = false; // False = OFF, True = ON
const string userDataFile = "users.txt";
HANDLE serialHandle;  // Serial Port Handle

// Simple hashing function (alternative to OpenSSL)
string simpleHash(const string& password) {
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c;
    }
    stringstream ss;
    ss << hex << hash;
    return ss.str();
}

// Display sensor data history
void showHistory() {
    cout << "\nSensor Data History:\n";
    if (sensorDataHistory.empty()) {
        cout << "No sensor data available.\n";
        return;
    }
    for (const string& data : sensorDataHistory) {
        cout << data << "\n";
    }
}


// Load users from file
void loadUsers() {
    ifstream file(userDataFile);
    if (!file) return;
    string username, passwordHash;
    while (file >> username >> passwordHash) {
        users.push_back({username, passwordHash});
    }
    file.close();
}

// Save users to file
void saveUsers() {
    ofstream file(userDataFile);
    for (const auto& user : users) {
        file << user.username << " " << user.passwordHash << "\n";
    }
    file.close();
}

// Display registered users with encrypted passwords
void displayRegisteredUsers() {
    cout << "\nRegistered Users (Encrypted Passwords):\n";
    for (const auto& user : users) {
        cout << "Username: " << user.username << " | Encrypted Password: " << user.passwordHash << "\n";
    }
}

// Function to check if user exists
User* findUser(const string& username) {
    for (auto& user : users) {
        if (user.username == username) {
            return &user;
        }
    }
    return nullptr;
}

// Register a new user
void registerUser() {
    string username, password;
    cout << "Enter new username: ";
    cin >> username;
    if (findUser(username)) {
        cout << "User already exists! Try logging in.\n";
        return;
    }
    cout << "Enter password: ";
    cin >> password;
    users.push_back({username, simpleHash(password)});
    saveUsers();
    cout << "Registration successful!\n";
}

// Login function
bool loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    User* user = findUser(username);
    if (!user) {
        cout << "User not found! Try again.\n";
        return false;
    }
    cout << "Enter password: ";
    cin >> password;
    if (user->passwordHash == simpleHash(password)) {
        cout << "Login successful!\n";
        return true;
    }
    cout << "Incorrect password! Try again.\n";
    return false;
}

// Function to connect to ESP32 via Serial
bool connectToESP32(const string& portName) {
    serialHandle = CreateFile(portName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (serialHandle == INVALID_HANDLE_VALUE) {
        cout << "Failed to connect to ESP32 on " << portName << endl;
        return false;
    }
    cout << "Connected to ESP32 on " << portName << endl;
    return true;
}

// Function to read data from Serial (ESP32)
string readFromESP32() {
    char buffer[64];
    DWORD bytesRead;
    if (ReadFile(serialHandle, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        return string(buffer);
    }
    return "";
}

// Collect sensor data from ESP32
void collectSensorData() {
    string sensorData = readFromESP32();
    if (!sensorData.empty()) {
        cout << "Received Sensor Data: " << sensorData << endl;
    } else {
        cout << "No data received from ESP32." << endl;
    }
}

// Remote Mode Function
void remoteMode() {
    int choice;
    cout << "\nRemote Mode:\n1. Turn Pump ON\n2. Turn Pump OFF\nEnter choice: ";
    cin >> choice;
    if (choice == 1) {
        pumpStatus = true;
        cout << "Pump is now ON.\n";
    } else if (choice == 2) {
        pumpStatus = false;
        cout << "Pump is now OFF.\n";
    } else {
        cout << "Invalid choice. Try again.\n";
    }
}

// Main system menu
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
                remoteMode();
                break;
            case 3:
            if (!sensorDataHistory.empty()) {
                showHistory();
            } else {
                cout << "No sensor data available.\n";
            }            
                break;
            case 4:
                collectSensorData();
                break;
            case 5:
                displayRegisteredUsers();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    loadUsers();
    string portName = "COM3"; // Change this to match your ESP32 COM port
    if (!connectToESP32(portName)) {
        return 1;
    }
    
    while (true) {
        cout << "\n1. Register\n2. Login\nEnter choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            if (loginUser()) {
                mainMenu();
            }
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
