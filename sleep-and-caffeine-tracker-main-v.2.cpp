#include <iostream>
#include <fstream> //For data storage
#include <iomanip>
#include <string>

using namespace std;

float recommendation_weekbasis(int total_sleep, int days_logged) {
    if (days_logged == 0) return 0; // no data

    float average_sleep = static_cast<float>(total_sleep) / days_logged;
    // Converts total_sleep to float ^

    if (average_sleep < 7) {          // less than 7 hours per day
        return 1; // Not enough sleep
    }
	else if (average_sleep >= 7 && average_sleep <= 9) {
        return 2; // Optimal sleep
    }
	else {
        return 3; // Too much sleep
    }
}

struct User {
    string name;
};

int caffeine_mg(int cups) {
    return static_cast<int>(cups * 94.8); // average mg per cup
}

bool login(User& user) {
	cout << "Login to your account" << endl;
    cout << "Username: ";
    string username;
    cin >> username;
    cout << "Password: ";
    string password;
    cin >> password;

    ifstream users_file("users.txt");
    if (!users_file.is_open()) {
		cout << "User database not found. Creating default user." << endl;
		ofstream create_file("users.txt");
        create_file << "admin admin123" << endl; // default user
        create_file.close();
        cout << "Default user 'admin' with password 'admin123' created. Please login again." << endl;
        return false;
    }

    string file_user, file_pass;
    while (users_file >> file_user >> file_pass) {
		if (file_user == username && file_pass == password) { // Compares username and password from current username
            user.name = username; // User gets authenticated when true
            return true;
            // file_user stores username and file_pass stores password
        }
    }
    cout << "Invalid username or password. Try again." << endl;
    return false;
}

bool registerUser() {
    cout << "Create a new account" << endl;
    cout << "Enter a new username: ";
    string username;
    cin >> username;
    cout << "Enter a new password: ";
    string password;
    cin >> password;

    ifstream users_file("users.txt");
    if (users_file.is_open()) {
		string file_user, file_pass;
        // Compares variables, if both are == then username exists already
        while (users_file >> file_user >> file_pass) {
        	if (file_user == username) {
                cout << "Username already exists. Please choose a different username." << endl;
                return false;
            }
        }
        users_file.close();
    }

    ofstream users_file_out("users.txt", ios::app);
    if (!users_file_out.is_open()) {
        cout << "Could not open users file for writing." << endl;
        return false;
    }
    users_file_out << username << " " << password << endl;
    users_file_out.close();

    cout << "Account created successfully! You can now log in." << endl;
    return true;
}

bool deleteAccount(const string& username) {
    // Remove user from users.txt
    ifstream infile("users.txt");
    ofstream temp("temp_users.txt"); // Stores all users not getting deleted
    if (!infile.is_open() || !temp.is_open()) { // Checks for errors
        cout << "Error accessing user database." << endl;
        return false;
    }
    
	// Copies all other users except the deleted one
    string file_user, file_pass;
    bool found = false;
    while (infile >> file_user >> file_pass) {
        if (file_user != username) {
            temp << file_user << " " << file_pass << endl;
        } else {
            found = true;
        }
    }
    infile.close();
    temp.close();
    
    // Handles case where user was not found
    if (!found) {
        cout << "User not found in database." << endl;
        remove("temp_users.txt");
        return false;
    }
    
    // Replace old user file
    remove("users.txt");
    rename("temp_users.txt", "users.txt");

    // Delete user's sleep logs
    ifstream sl_in("sleep_log.txt");
    ofstream sl_temp("temp_sleep_log.txt");
    if (sl_in.is_open() && sl_temp.is_open()) {
        string uname, date;
        int hours;
        while (sl_in >> uname >> date >> hours) {
            if (uname != username) {
                sl_temp << uname << " " << date << " " << hours << endl;
            }
        }
        sl_in.close();
        sl_temp.close();
        remove("sleep_log.txt");
        rename("temp_sleep_log.txt", "sleep_log.txt");
    }

    // Delete user's caffeine logs
    ifstream cf_in("caffeine_log.txt");
    ofstream cf_temp("temp_caffeine_log.txt");
    if (cf_in.is_open() && cf_temp.is_open()) {
        string uname, date;
        int cups;
        while (cf_in >> uname >> date >> cups) {
            if (uname != username) {
                cf_temp << uname << " " << date << " " << cups << endl;
            }
        }
        cf_in.close();
        cf_temp.close();
        remove("caffeine_log.txt");
        rename("temp_caffeine_log.txt", "caffeine_log.txt");
    }

    cout << "Account '" << username << "' and all associated data have been deleted." << endl;
    return true;
}

void sleepJournal(User& user) {
    int choice = 0;
    while (choice != 5) {
        cout << "\nSleep Journal Menu:" << endl;
        cout << "1. Log today's sleep" << endl;
        cout << "2. View past sleep logs" << endl;
        cout << "3. Get sleep recommendation" << endl;
        cout << "4. Delete previous logs" << endl;
        cout << "5. Return to main menu" << endl;
        cout << "[Enter choice]: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Please enter today's date: ";
                string date;
                cin >> date;
                cout << "Please enter number of hours you slept last night: ";
                int hours;
                cin >> hours;
                ofstream file("sleep_log.txt", ios::app);
                if (file.is_open()) {
                    file << user.name << " " << date << " " << hours << endl;
                    file.close();
                    cout << "Sleep log saved successfully." << endl;
                }
				else {
                    cout << "Error opening file." << endl;
                }
                break;
            }
            case 2: {
                cout << "Past Sleep Logs:" << endl;
                cout << left << setw(15) << "Username" << setw(15) << "Date" << setw(10) << "Hours" << endl;
                cout << setfill('-') << setw(40) << "-" << setfill(' ') << endl;
                ifstream file("sleep_log.txt");
                if (file.is_open()) {
                    string uname, date;
                    int log_hours;
                    bool found = false;
                    while (file >> uname >> date >> log_hours) {
                        cout << left << setw(15) << uname << setw(15) << date << setw(10) << log_hours << endl;
                        found = true;
                    }
                    file.close();
                    if (!found) cout << "No logs found." << endl;
                }
				else {
                    cout << "No past sleep logs found." << endl;
                }
                break;
            }
            case 3: {
                ifstream file("sleep_log.txt");
                if (file.is_open()) {
                    string uname, date;
                    int log_hours;
                    int total_sleep = 0;
                    int days_logged = 0;
                    while (file >> uname >> date >> log_hours) {
                        if (uname == user.name) {  // Only consider current user's logs
                            total_sleep += log_hours;
                            days_logged++;
                        }
                    }
                    file.close();

                    if (days_logged == 0) {
                        cout << "No sleep logs found to provide a recommendation." << endl;
                    }
					else {
                        int recommendation = recommendation_weekbasis(total_sleep, days_logged);
                        if (recommendation == 1) {
                            cout << "You are not getting enough sleep. Try to increase your sleep hours." << endl;
                        }
						else if (recommendation == 2) {
                            cout << "You are getting an optimal amount of sleep. Keep it up!" << endl;
                        }
						else {
                            cout << "You are getting too much sleep. Try to reduce your sleep hours." << endl;
                        }
                    }
                }
				else {
                    cout << "No sleep logs found to provide a recommendation." << endl;
                }
                break;
            }
            case 4: {
                // Delete only current user's logs by rewriting file excluding them
                ifstream infile("sleep_log.txt");
                ofstream temp("temp_sleep_log.txt");
                if (infile.is_open() && temp.is_open()) {
                    string uname, date;
                    int hours;
                    while (infile >> uname >> date >> hours) {
                        if (uname != user.name) {
                            temp << uname << " " << date << " " << hours << endl;
                        }
                    }
                    infile.close();
                    temp.close();
                    remove("sleep_log.txt");
                    rename("temp_sleep_log.txt", "sleep_log.txt");
                    cout << "Your previous sleep logs deleted." << endl;
                }
				else {
                    cout << "Error deleting logs." << endl;
                }
                break;
            }
            case 5: {
                cout << "Returning to main menu." << endl;
                break;
            }
            default:
                cout << "Select a valid option." << endl;
        }
    }
}

void caffeineTracker(User& user) {
    int choice = 0;
    while (choice != 5) {
        cout << "\nCaffeine Tracker Menu:" << endl;
        cout << "1. Log caffeine intake" << endl;
        cout << "2. View past caffeine logs" << endl;
        cout << "3. Get caffeine intake status" << endl;
        cout << "4. Delete previous caffeine logs" << endl;
        cout << "5. Return to main menu" << endl;
        cout << "[Enter choice]: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Please enter today's date: ";
                string date;
                cin >> date;
                cout << "How many cups of coffee did you drink today? ";
                int cups;
                cin >> cups;
                ofstream file("caffeine_log.txt", ios::app);
                if (file.is_open()) {
                    file << user.name << " " << date << " " << cups << endl;
                    file.close();
                    cout << "Caffeine intake logged successfully." << endl;
                }
				else {
                    cout << "Error opening file." << endl;
                }
                break;
            }
            case 2: {
                cout << "Past Caffeine Logs:" << endl;
                cout << left << setw(15) << "Username" << setw(15) << "Date" << setw(10) << "Cups" << setw(15) << "Caffeine(mg)" << endl;
                cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
                ifstream file("caffeine_log.txt");
                if (file.is_open()) {
                    string uname, date;
                    int cups;
                    bool found = false;
                    while (file >> uname >> date >> cups) {
                        cout << left << setw(15) << uname << setw(15) << date << setw(10) << cups << setw(15) << caffeine_mg(cups) << endl;
                        found = true;
                    }
                    file.close();
                    if (!found) cout << "No caffeine logs found." << endl;
                }
				else {
                    cout << "No caffeine logs found." << endl;
                }
                break;
            }
            case 3: {
                ifstream file("caffeine_log.txt");
                if (file.is_open()) {
                    string uname, date;
                    int cups;
                    int total_cups = 0;
                    bool found = false;
                    while (file >> uname >> date >> cups) {
                        if (uname == user.name) {  // Only current user's data
                            total_cups += cups;
                            found = true;
                        }
                    }
                    file.close();

                    if (!found) {
                        cout << "No caffeine logs found to evaluate." << endl;
                    }
					else {
                        int total_caffeine = caffeine_mg(total_cups);
                        cout << "Your total caffeine intake for logged days is: " << total_caffeine << " mg" << endl;
                        if (total_caffeine <= 200) {
                            cout << "You haven't reached your daily limit. The maximum caffeine per day is 400 mg." << endl;
                        }
						else if (total_caffeine <= 400) {
                            cout << "You almost reached your daily limit." << endl;
                        }
						else {
                            cout << "You have exceeded your daily limit. This might be affecting your sleeping habits." << endl;
                        }
                    }
                }
				else {
                    cout << "No caffeine logs found to evaluate." << endl;
                }
                break;
            }
            case 4: {
                // Delete only current user's caffeine logs
                ifstream infile("caffeine_log.txt");
                ofstream temp("temp_caffeine_log.txt");
                if (infile.is_open() && temp.is_open()) {
                    string uname, date;
                    int cups;
                    while (infile >> uname >> date >> cups) {
                        if (uname != user.name) {
                            temp << uname << " " << date << " " << cups << endl;
                        }
                    }
                    infile.close();
                    temp.close();
                    remove("caffeine_log.txt");
                    rename("temp_caffeine_log.txt", "caffeine_log.txt");
                    cout << "Your previous caffeine logs deleted." << endl;
                }
				else {
                    cout << "Error deleting logs." << endl;
                }
                break;
            }
            case 5: {
                cout << "Returning to main menu." << endl;
                break;
            }
            default:
                cout << "Select a valid option." << endl;
        }
    }
}

int main() {
    User user;
    cout << "Hello, welcome to your sleep tracker." << endl;

    bool loggedIn = false;
    while (!loggedIn) {
        cout << "Enter 1 to Login\nEnter 2 to Register a new account \n[Enter Option]: ";
        int option;
        cin >> option;

        switch(option) {
            case 1: {
                loggedIn = login(user);
                break;
            }
            case 2:{
                registerUser();
                break;
            }
            default:{
                cout << "Invalid option. Please enter 1 or 2." << endl;
                break;
            }
        }
    }

    cout << "Hi " << user.name << "!" << endl;

    int main_choice = 0;
    bool userLoggedIn = true;  // Track if user is logged in or deleted account
    while (main_choice != 4 && userLoggedIn) {
        cout << "\nMain Menu:" << endl;
        cout << "1. Sleep Journal" << endl;
        cout << "2. Caffeine Tracker" << endl;
        cout << "3. Delete Account" << endl;
        cout << "4. Exit" << endl;
        cout << "[Enter choice]: ";
        cin >> main_choice;

        switch (main_choice) {
            case 1:
                sleepJournal(user);
                break;
            case 2:
                caffeineTracker(user);
                break;
            case 3: {
                cout << "Are you sure you want to delete your account? This action cannot be undone. (y/n): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    if (deleteAccount(user.name)) {
                        cout << "Your account has been deleted. Exiting program..." << endl;
                        userLoggedIn = false;
                    }
                }
				else {
                    cout << "Account deletion canceled." << endl;
                }
                break;
            }
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Select a valid option." << endl;
        }
    }
    return 0;
}
