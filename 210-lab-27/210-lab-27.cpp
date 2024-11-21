#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <string>
using namespace std;

void displayVillagers(const map<string, tuple<int, string, string>>& villagerData) {
    cout << "Villager details:" << endl;
    for (const auto& pair : villagerData) {
        const auto& [friendship, species, catchphrase] = pair.second;
        cout << pair.first << " [" << friendship << ", " << species << ", " << catchphrase << "]" << endl;
    }
}

int main() {
    // declarations
    map<string, tuple<int, string, string>> villagerData;
    int choice;

    do {
        cout << "1. Add Villager\n"
                "2. Delete Villager\n"
                "3. Increase Friendship\n"
                "4. Decrease Friendship\n"
                "5. Search for Villager\n"
                "6. Exit\n"
                "Enter choices: ";
        cin >> choice;

        if(choice == 1) {
            string name, species, catchphrase;
            int friendship;
            cout << "Villager name: ";
            cin.ignore();
            getline(cin,name);
            cout << "Friendship level: ";
            cin >> friendship;
            cout << "Species: ";
            cin.ignore();
            getline(cin, species);
            cout << "Catchphrase: ";
            getline(cin, catchphrase);
            villagerData[name] = make_tuple(friendship, species, catchphrase);
            cout << name << " added." << endl;
        } else if (choice == 2) {
            string name;
            cout << "Villager name to delete: ";
            cin.ignore();
            getline(cin, name);
            auto it = villagerData.find(name);
            if (it != villagerData.end()) {
                villagerData.erase(it);
                    cout << name << " deleted." << endl;
            } else {
                cout << name << " not found." << endl;            
            }
        } else if (choice == 3) {
            string name;
            cout << "Villager name to increase friendship: ";
            cin.ignore();
            getline(cin, name);
            auto it = villagerData.find(name);
            if (it != villagerData.end()) {
                int& friendship = get<0>(it->second);
                if (friendship < 10) {
                    ++friendship;
                    cout << name << "'s friendship increased to " << friendship << "." << endl;
                } else {
                    cout << name << "'s friendship is already at maximum level." << endl;
                } 
                } else {
                    cout << name << " not found" << endl;
                }
            } else if (choice == 4) {
                string name;
                cout << "Villager name to decrease friendship: ";
                cin.ignore();
                getline(cin, name);
                auto it = villagerData.find(name);
                if (it != villagerData.end()) {
                    int& friendship = get<0>(it->second);
                    if (friendship > 0) {
                        --friendship;
                        cout << name << "'s friendship decreased to " << friendship << "." << endl;
                    } else {
                        cout << name << "'s friendship is already at minimum level" << endl;
                    }
                } else if (choice == 5) {
                    string name;
                    cout << "Villager name to search: ";
                    cin.ignore();
                    getline(cin, name);
                    auto it = villagerData.find(name);
                    if (it != villagerData.end()) {
                        const auto& [friendship, species, catchphrase] = it->second;
                        cout << name << " found: [" << friendship << ", " << species << ", " << catchphrase << "]" << endl;
                    } else {
                        cout << name << " not found." << endl;
                    }
                }
            }else if (choice == 6) {
                    cout << "Exiting..." << endl;
            } else {
                cout << "Invalid choice. Please try again." << endl;
        }

        displayVillagers(villagerData);
    } while (choice != 6);

    return 0;
 