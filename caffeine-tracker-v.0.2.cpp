#include <iostream>
#include <string>
using namespace std;

struct var {
	string name; int cup;
};
int caffeine(var v){return v.cup * 94.8;} // Average caffeine content per cup of coffee

int main(){
	var v;
    int choice;
    string name;
    cout << "-----CAFFEINE TRACKER------" << endl;
    cout << "Hi! Please enter your name." << endl;
    cout << "[Enter name]: ";
    getline(cin, v.name);
    cout << "Hi! " << v.name << "!" << endl << endl;
    while(choice!=2){
	    cout << "What would you want to do?" << endl;
	    cout << "1. Caffeine Tracker" << endl;
	    cout << "2. Exit" << endl;
	    cout << "[Insert choice]: ";
	    cin >> choice;
	    switch (choice) {
	        case 1: {
	            cout << "How many cups did you drink today?" << endl;
	            cout << "[Cups]: ";
	            cin >> v.cup;
	            if (caffeine(v) >= 0 && caffeine(v) <= 200) {
	                cout << "Your total caffeine is: " << caffeine(v) << " mg" << endl;
	                cout << "You haven't reached your daily limit." << endl;
	                cout << "The maximum caffeine per day is 400 mg.\n\n";
	            }
				else if (caffeine(v) > 200 && caffeine(v) <= 400) {
	                cout << "Your total caffeine is: " << caffeine(v) << " mg" << endl;
	                cout << "You almost reached your daily limit.\n\n";
	            }
				else {
	                cout << "Your total caffeine is: " << caffeine(v) << " mg" << endl;
	                cout << "You have exceeded your daily limit.\n\n";
	            }
	            break;
	        }
	        case 2: {
	            cout << "Thank you for using the caffeine tracker!" << endl;
	            break;
	        }
	        default: {
	            cout << "Wrong input.\n\n";
	            break;
	        }
	    }
	}
}
