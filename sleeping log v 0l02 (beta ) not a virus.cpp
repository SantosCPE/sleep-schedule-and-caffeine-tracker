#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int recommendation_weekbasis(int total_sleep) {
    if (total_sleep < 63) {
        return 1; // Not enough sleep
    } else if (total_sleep >= 49 && total_sleep <= 63) {
        return 2; // Optimal sleep
    } else {
        return 3; // Too much sleep
    }
}


int main() {
    int choice = 0;
cout << " Hello, welcome to your sleep journal log " << endl;
cout << " Please enter your name: " << endl;
string name;
cin >> name;
cout << " Hi " << name << ",";
while (choice != -1) {
    
cout << "Please enter today's date: " << endl;
string date;
cin >> date;
cout << " what would you like to do today? (enter -1 to end program)" << endl;
cout << " 1.  log todays sleep. " << endl;
cout << " 2.  view past sleep logs. " << endl;
cout << " 3.  get sleep recommendation. " << endl;
cin >> choice;
switch (choice) {
    case -1:
        cout << " Exiting the program. Goodbye!" << endl;
        return 0;
    case 1: {
        cout << " Please enter the number of hours you slept last night: " << endl;
       int hours;
        cin >> hours;
        ofstream file("sleep_log.txt", ios::app);
        if (file.is_open()) {
            file << date << ": " << hours << " hours" << endl;
            file.close();
            cout << " Sleep log saved successfully." << endl;
        } else {
            cout << " Error opening file." << endl;
        }

        break;
    }



    case 2: {
        cout << " Past Sleep Logs: " << endl;
        cout << left << setw(15) << "Date" << setw(10) << "Hours" << endl;
        cout << setfill('-') << setw(25) << "-" << setfill(' ') << endl;
        cout << setfill(' ');

        ifstream file("sleep_log.txt");
        string date;
        int log_hours;

        if (file.is_open()) { while (file >> date >> log_hours) {
                cout << left << setw(15) << date.substr(0, date.length() - 1) << setw(10) << log_hours << endl;
            }
            file.close();
        } else {
            cout << "no past sleep logs found." << endl;
        
            break;
}
      break;
    }
    case 3: {
        ifstream file("sleep_log.txt");
        string date;
        int log_hours;
       int total_sleep = 0;
        int days_logged = 0;

        if (file.is_open()) {
            while (file >> date >> log_hours) {
                total_sleep += log_hours;
                days_logged++;
            }
            file.close();

            if (days_logged == 0) {
                cout << " No sleep logs found to provide a recommendation." << endl;
            } else {
                int recommendation = recommendation_weekbasis(total_sleep);
                if (recommendation == 1) {
                    cout << " You are not getting enough sleep. Try to increase your sleep hours." << endl;
                } else if (recommendation == 2) {
                    cout << " You are getting an optimal amount of sleep. Keep it up!" << endl;
                } else {
                    cout << " You are getting too much sleep. Try to reduce your sleep hours." << endl;
                }
            }
        } else {
            cout << " No sleep logs found to provide a recommendation." << endl;
        }

        break; 
    }
    default: {
        cout << "  select a valid option." << endl;
        break;
    }






    }
}
    return 0;
}
