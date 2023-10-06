#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Structure to represent employee data
struct Employee {
    string positionID;
    string employeeName;
    string time;
    string timeOut;
};

// Function to read employee data from a CSV file
vector<Employee> readEmployeeDataFromCSV(const string& filename) {
    vector<Employee> employees;

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening CSV file: " << filename << endl;
        return employees;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        Employee emp;
        istringstream iss(line);
        getline(iss, emp.positionID, ',');
        getline(iss, emp.employeeName, ',');
        getline(iss, emp.time, ',');
        getline(iss, emp.timeOut, ',');

        if (!emp.positionID.empty() && !emp.employeeName.empty()) {
            employees.push_back(emp);
        }
    }

    file.close();
    return employees;
}



// Function to parse date and time strings
std::tm parseDateTime(const std::string& dateTimeStr) {
    std::tm dateTime = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&dateTime, "%m/%d/%Y %I:%M %p");
    return dateTime;
}

// ...

// Function to check if an employee has less than 10 hours between shifts but greater than 1 hour
void checkShiftHours(const std::vector<Employee>& employees) {
    std::cout << "Checking for employees who have less than 10 hours between shifts but greater than 1 hour..." << std::endl;

    // Initialize variables to track shift hours
    std::string currentEmployeeName = "";
    std::tm previousTime = {};

    // Iterate through the employees
    for (const Employee& emp : employees) {
        if (emp.employeeName != currentEmployeeName) {
            // Reset shift hours and previous time when encountering a new employee
            currentEmployeeName = emp.employeeName;
            previousTime = {};
        }

        // Parse the time strings into tm structures for comparison
        std::tm currentTime = parseDateTime(emp.time);

        if (previousTime.tm_hour != 0) {
            // Calculate the time difference between shifts
            std::time_t timeDifference = std::mktime(&currentTime) - std::mktime(&previousTime);

            if (timeDifference > 3600 && timeDifference < 36000) { // 1 hour and 10 hours in seconds
                std::cout << "Employee: " << emp.employeeName << ", Position ID: " << emp.positionID << " has less than 10 hours between shifts but greater than 1 hour." << std::endl;
            }
        }

        // Update previous time for the next iteration
        previousTime = currentTime;
    }
}

// Function to check if an employee has worked for more than 14 hours in a single shift
void checkSingleShiftHours(const std::vector<Employee>& employees) {
    std::cout << "Checking for employees who have worked for more than 14 hours in a single shift..." << std::endl;

    // Initialize variables to track shift hours
    std::string currentEmployeeName = "";
    std::tm shiftStartTime = {};

    // Iterate through the employees
    for (const Employee& emp : employees) {
        if (emp.employeeName != currentEmployeeName) {
            // Reset shift start time when encountering a new employee
            currentEmployeeName = emp.employeeName;
            shiftStartTime = {};
        }

        // Parse the time strings into tm structures for comparison
        std::tm currentTime = parseDateTime(emp.time);

        if (shiftStartTime.tm_hour == 0) {
            // If shift start time is not set, set it to the current time
            shiftStartTime = currentTime;
        } else {
            // Calculate the shift duration
            std::time_t shiftDuration = std::mktime(&currentTime) - std::mktime(&shiftStartTime);

            if (shiftDuration > 50400) { // 14 hours in seconds
                std::cout << "Employee: " << emp.employeeName << ", Position ID: " << emp.positionID << " has worked for more than 14 hours in a single shift." << std::endl;
            }
        }
    }
}



// Function to check if an employee has worked for 7 consecutive days
void checkConsecutiveDays(const vector<Employee>& employees) {
    cout << "Checking for employees who have worked for 7 consecutive days..." << endl;

    // Initialize variables to track consecutive days
    int consecutiveDays = 0;
    string currentDate = "";
    string currentEmployeeName = "";

    // Iterate through the employees
    for (const Employee& emp : employees) {
        if (emp.employeeName != currentEmployeeName) {
            // Reset consecutive days and current date when encountering a new employee
            currentEmployeeName = emp.employeeName;
            consecutiveDays = 0;
            currentDate = "";
        }

        // Extract the date portion from the time data
        size_t spacePos = emp.time.find(' ');
        if (spacePos != string::npos) {
            string datePart = emp.time.substr(0, spacePos);

            if (datePart != currentDate) {
                // If the date is different from the current date, reset consecutive days
                currentDate = datePart;
                consecutiveDays = 1;
            } else {
                consecutiveDays++;
            }
        }

        if (consecutiveDays == 7) {
            cout << "Employee: " << emp.employeeName << ", Position ID: " << emp.positionID << " has worked for 7 consecutive days." << endl;
        }
    }
}

// Function to check if an employee has less than 10 hours between shifts but greater than 1 hour
void checkShiftHours(const vector<Employee>& employees) {
    cout << "Checking for employees who have less than 10 hours between shifts but greater than 1 hour..." << endl;

    // Initialize variables to track shift hours
    string currentEmployeeName = "";
    struct tm previousTime = {0}; // Initialize the previous time structure

    // Iterate through the employees
    for (const Employee& emp : employees) {
        if (emp.employeeName != currentEmployeeName) {
            // Reset shift hours and previous time when encountering a new employee
            currentEmployeeName = emp.employeeName;
            previousTime = {0};
        }

        // Parse the time strings into tm structures for comparison
        struct tm currentTime = {0};
        strptime(emp.time.c_str(), "%m/%d/%Y %I:%M %p", &currentTime);

        if (previousTime.tm_hour != 0) {
            // Calculate the time difference between shifts
            int timeDifference = difftime(mktime(&currentTime), mktime(&previousTime));

            if (timeDifference > 3600 && timeDifference < 36000) { // 1 hour and 10 hours in seconds
                cout << "Employee: " << emp.employeeName << ", Position ID: " << emp.positionID << " has less than 10 hours between shifts but greater than 1 hour." << endl;
            }
        }

        // Update previous time for the next iteration
        previousTime = currentTime;
    }
}

// Function to check if an employee has worked for more than 14 hours in a single shift
void checkSingleShiftHours(const vector<Employee>& employees) {
    cout << "Checking for employees who have worked for more than 14 hours in a single shift..." << endl;

    // Initialize variables to track shift hours
    string currentEmployeeName = "";
    struct tm shiftStartTime = {0};

    // Iterate through the employees
    for (const Employee& emp : employees) {
        if (emp.employeeName != currentEmployeeName) {
            // Reset shift start time when encountering a new employee
            currentEmployeeName = emp.employeeName;
            shiftStartTime = {0};
        }

        // Parse the time strings into tm structures for comparison
        struct tm currentTime = {0};
        strptime(emp.time.c_str(), "%m/%d/%Y %I:%M %p", &currentTime);

        if (shiftStartTime.tm_hour == 0) {
            // If shift start time is not set, set it to the current time
            shiftStartTime = currentTime;
        } else {
            // Calculate the shift duration
            int shiftDuration = difftime(mktime(&currentTime), mktime(&shiftStartTime));

            if (shiftDuration > 50400) { // 14 hours in seconds
                cout << "Employee: " << emp.employeeName << ", Position ID: " << emp.positionID << " has worked for more than 14 hours in a single shift." << endl;
            }
        }
    }
}

int main() {
    string filename = "Assignment_Timecard.csv"; // Replace with the path to your CSV file

    vector<Employee> employees = readEmployeeDataFromCSV(filename);

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Check for employees who have worked for 7 consecutive days" << endl;
        cout << "2. Check for employees who have less than 10 hours between shifts but greater than 1 hour" << endl;
        cout << "3. Check for employees who have worked for more than 14 hours in a single shift" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                checkConsecutiveDays(employees);
                break;
            case 2:
                checkShiftHours(employees);
                break;
            case 3:
                checkSingleShiftHours(employees);
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
