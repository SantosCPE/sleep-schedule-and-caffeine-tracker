#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

float recommendation_weekbasis(int total_sleep, int days_logged) {
    if (days_logged == 0) return 0; // no data

    float average_sleep = static_cast<float>(total_sleep) / days_logged;

    if (average_sleep < 7) {          // less than 7 hours per day
        return 1; // Not enough sleep
    } else if (average_sleep >= 7 && average_sleep <= 9) {
        return 2; // Optimal sleep
    } else {
        return 3; // Too much sleep
    }
}

struct User {
    string name;
};

struct CaffeineLog {
    int cups;
};

int caffeine_mg(CaffeineLog v) {
    return static_cast<int>(v.cups * 94.8); // average caffeine per cup in mg
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
                cout << "Please enter today's date (YYYY-MM-DD): ";
                string date;
                cin >> date;
                cout << "Please enter number of hours you slept last night: ";
                int hours;
                cin >> hours;
                ofstream file("sleep_log.txt", ios::app);
                if (file.is_open()) {
                    file << date << " " << hours << endl;
                    file.close();
                    cout << "Sleep log saved successfully." << endl;
                } else {
                    cout << "Error opening file." << endl;
                }
                break;
            }
            case 2: {
                cout << "Past Sleep Logs:" << endl;
                cout << left << setw(15) << "Date" << setw(10) << "Hours" << endl;
                cout << setfill('-') << setw(25) << "-" << setfill(' ') << endl;
                ifstream file("sleep_log.txt");
                if (file.is_open()) {
                    string date;
                    int log_hours;
                    bool found = false;
                    while (file >> date >> log_hours) {
                        cout << left << setw(15) << date << setw(10) << log_hours << endl;
                        found = true;
                    }
                    file.close();
                    if (!found) cout << "No logs found." << endl;
                } else {
                    cout << "No past sleep logs found." << endl;
                }
                break;
            }
            case 3: {
                ifstream file("sleep_log.txt");
                if (file.is_open()) {
                    string date;
                    int log_hours;
                    int total_sleep = 0;
                    int days_logged = 0;
                    while (file >> date >> log_hours) {
                        total_sleep += log_hours;
                        days_logged++;
                    }
                    file.close();

                    if (days_logged == 0) {
                        cout << "No sleep logs found to provide a recommendation." << endl;
                    } else {
                        int recommendation = recommendation_weekbasis(total_sleep, days_logged);
                        if (recommendation == 1) {
                            cout << "You are not getting enough sleep. Try to increase your sleep hours." << endl;
                        } else if (recommendation == 2) {
                            cout << "You are getting an optimal amount of sleep. Keep it up!" << endl;
                        } else {
                            cout << "You are getting too much sleep. Try to reduce your sleep hours." << endl;
                        }
                    }
                } else {
                    cout << "No sleep logs found to provide a recommendation." << endl;
                }
                break;
            }
            case 4: {
                ofstream file("sleep_log.txt", ios::trunc);
                file.close();
                cout << "All previous sleep logs deleted." << endl;
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
    while (choice != 2) {
        cout << "\nCaffeine Tracker Menu:" << endl;
        cout << "1. Log your caffeine intake" << endl;
        cout << "2. Return to main menu" << endl;
        cout << "[Insert choice]: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                CaffeineLog log;
                cout << "How many cups did you drink today? ";
                cin >> log.cups;
                int total_caffeine = caffeine_mg(log);
                cout << "Your total caffeine intake is: " << total_caffeine << " mg" << endl;
                if (total_caffeine <= 200) {
                    cout << "You haven't reached your daily limit. The maximum caffeine per day is 400 mg." << endl;
                } else if (total_caffeine <= 400) {
                    cout << "You almost reached your daily limit." << endl;
                } else {
                    cout << "You have exceeded your daily limit." << endl;
                }
                break;
            }
            case 2: {
                cout << "Returning to main menu." << endl;
                break;
            }
            default:
                cout << "Wrong input." << endl;
        }
    }
}

int main() {
    User user;
    cout << "Hello, welcome to your health tracker." << endl;
    cout << "Please enter your name: ";
    getline(cin, user.name);
    cout << "Hi " << user.name << "!" << endl;

    int main_choice = 0;
    while (main_choice != 3) {
        cout << "\nMain Menu:" << endl;
        cout << "1. Sleep Journal" << endl;
        cout << "2. Caffeine Tracker" << endl;
        cout << "3. Exit" << endl;
        cout << "[Enter choice]: ";
        cin >> main_choice;

        switch (main_choice) {
            case 1:
                sleepJournal(user);
                break;
            case 2:
                caffeineTracker(user);
                break;
            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Select a valid option." << endl;
        }
    }
    return 0;
}
