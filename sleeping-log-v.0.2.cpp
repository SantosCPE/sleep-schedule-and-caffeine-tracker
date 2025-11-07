#include <iostream>
#include <fstream>
#include <iomanip>

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

int main() {
    int choice = 0;
    int day_counter = 0;  // initialize day counter
    string name;
	cout << "Hello, welcome to your sleep journal log " << endl;
	cout << "Please enter your name: ";
	getline(cin,name);
	cout << "Hi " << name;
	
	while (choice != 5) { 
		cout << "\nPlease enter today's date: ";
		string date;
		cin >> date;
		cout << "What would you like to do today?" << endl;
		cout << "1.  Log today's sleep. " << endl;
		cout << "2.  View past sleep logs. " << endl;
		cout << "3.  Get sleep recommendation. " << endl;
		cout << "4.  Delete previous logs. " << endl;
		cout << "5.  Exit." << endl;
		cout << "[Enter choice]: ";
		cin >> choice;
		switch (choice) {
			case 1: {
			    cout << "Please enter the number of hours you slept last night: ";
			    int hours;
			    cin >> hours;
			    day_counter++;
			    ofstream file("sleep_log.txt", ios::app);
			    if (file.is_open()) {
			        file << date << " " << hours << endl;  // just date and hours
			        file.close();
			        cout << "Sleep log saved successfully." << endl;
			    } else {
			        cout << "Error opening file." << endl;
			    }
			    break;
			}
			
			case 2: {
			    cout << "Past Sleep Logs: " << endl;
			    cout << left << setw(15) << "Date" << setw(10) << "Hours" << endl;
			    cout << setfill('-') << setw(25) << "-" << setfill(' ') << endl;
			    string date;
			    int log_hours;
			    ifstream file("sleep_log.txt");
			    if (file.is_open()) {
			        while (file >> date >> log_hours) {
			            cout << left << setw(15) << date << setw(10) << log_hours << endl;
			        }
			        file.close();
			    } else {
			        cout << "No past sleep logs found." << endl;
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

		    case 4:{
		    	ofstream file("sleep_log.txt", ios::trunc);
   				file.close();
				break;
			}
		    case 5:{
		        cout << "Exiting the program. Goodbye!" << endl;
		        return 0;
		    }
		    default: {
		        cout << "Select a valid option." << endl;
		        break;
		    }
		}
	}
		    return 0;
}
