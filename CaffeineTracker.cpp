#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
int recommendation_weekbasis(int total_caffeine){
	if (total_caffeine < 3080){
		return 1; // Too much caffeine
	} else if (total_caffeine >= 0 && total_caffeine <= 3080){
		return 2; // Optimal amount
	} else {
		return 3; // Not enough or not taking any caffeine
	}
}
int main(){ 
	string name;
	int choice = 0;
	cout << "-----CAFFEINE TRACKER------\n";
	cout << "Hi! Please enter your name.\n";
	cout << "[Enter name]: ";
	getline(cin, name);
	cout << "Hi, " << name << "!" << endl;
	
	while (choice!=4){
		cout << "--------------------------\n";
		cout << "What would you want to do?\n";
		cout << "1. Log in today's date\n";
		cout << "2. Caffeine tracker \n";
		cout << "3. Checking logs \n";
		cout << "4. Exit\n";
		 cout << "[Insert choice]: ";
		cin >> choice;
		switch (choice){
			case 1: {
				cout << "--------------------------\n";
				cout << "Please enter date: (Use space for day and year) \n";
				string month,day,year;
			    cin >> month >> day >> year;
				cout << "[Date]: " << month << "/" << day << "/" << year << "\n\n";
				
				ofstream file("caffeine_log.txt", ios::app);
					if (file.is_open()){
					file << month 
					<< "/" << day << "/" << year << endl;
					file.close();
					cout << "Caffeine Tracker has been saved." << endl;
				} else {
					cout << "Error input." << endl;
			}
			break;
			}
			case 2: {
				int cup;
				double caffeine;
				cout << "--------------------------\n";
				cout << "\nHow many cups did you drink today?" << endl;
				cout << "[Cups]: ";
				cin >> cup;
				caffeine = cup * 94.8;
				if (caffeine >= 0 && caffeine <= 200){ 
				cout << "Your total caffeine is: " << caffeine << " mg" << endl;
				cout << "You haven't reach your daily limit.\n";
				cout << "The maximum caffeine per day is 400 mg.\n" << endl;
				} 
				else if (caffeine >= 200 && caffeine <= 400){
				cout << "Your total caffeine is: " << caffeine << " mg" << endl;
				cout << "You almost reach your daily limit.\n\n";
				}
				else {
				cout << "Your total caffeine is: " << caffeine << " mg" << endl;
				cout << "You have exceeded your daily limit.\n\n";	
			}
			break;
			case 3: {
				cout << "--------------------------\n";
				ifstream file("caffeine_log.txt");
				string month, day, year;
				int total_cups;
				int total_caffeine = 0;
				int days_logged = 0;

				if (file.is_open()) {
				while (file >> month >> day >> year >> caffeine){
				total_cups += total_caffeine;
				days_logged++;
				}
				file.close();

            	if (days_logged == 0) {
                cout << "No caffeine logs found to provide a recommendation.\n\n" << endl;
				} else {
				int recommendation = recommendation_weekbasis(total_caffeine);
                	if (recommendation == 1) {
                    cout << "You may or may not getting enough caffeine. You may or may not increase your caffeine intake." << endl;
                	} else if (recommendation == 2) {
                    cout << "You are getting an optimal amount of caffeine. Good work!" << endl;
					} else {
                    cout << "You are getting too much caffeine. Too much caffeine is very dangerous for your health." << endl;
					}
					}
				} else {
					cout << "No caffeine logs found to provide a recommendation.\n\n" << endl;
				}
				break;
			}
			case 4: {
				cout << "--------------------------\n";
				cout << "Thank you for using the caffeine tracker!\n\n";
				break;
			}
			default: {
				cout << "--------------------------\n";
				cout << "Wrong input.\n\n";
				break;
			}
		}
	}
}
}


