#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> 
#include <cctype>  
using namespace std;



class menuItem {
    public:
    string name;
    int price;
    int rating;
    string type;

    menuItem() {
        name = "";
        price = 0;
        rating = 0.0f;
        type = "";
    }
    
    menuItem(string n, int p, float r, string t) {
        name = n;
        price = p;
        rating = r;
        type = t;
    }
};

class cafe {
    private:
    menuItem tempMenu;  
    
    public:
   
    menuItem menu[500]; 
    string cafeName;
    
    cafe(string fileName, string cName) {
        cafeName = cName;
        int i = 0;
        string nameStr, priceStr, ratingStr, typeStr, blank;
        ifstream file(fileName);
        
        if(!file.is_open()) {
            cout << "Error: Could not open file " << fileName << endl;
            return;
        }
        

        while (getline(file, nameStr)) {
           
            if(nameStr.empty()) continue;
            
            getline(file, priceStr);
            getline(file, ratingStr);
            getline(file, typeStr);
            
           
            if(!nameStr.empty() && nameStr.back() == '\r') nameStr.pop_back();
            if(!priceStr.empty() && priceStr.back() == '\r') priceStr.pop_back();
            if(!ratingStr.empty() && ratingStr.back() == '\r') ratingStr.pop_back();
            if(!typeStr.empty() && typeStr.back() == '\r') typeStr.pop_back();
            
            menu[i].name = nameStr;
            
            
            try {
              
                if(!priceStr.empty()) menu[i].price = stoi(priceStr);
                else menu[i].price = 0;
                
                if(!ratingStr.empty()) menu[i].rating = stof(ratingStr);
                else menu[i].rating = 0.0;
            } catch (...) {
                menu[i].price = 0;
                menu[i].rating = 0.0;
            }
            
            menu[i].type = typeStr;
            i++;
            
            
            if(file.peek() != EOF) {
                getline(file, blank);
            }
        }
        
        file.close();
    }

    string toLower(string str) {
        string result = "";
        for(int i = 0; i < str.length(); i++) {
            result += tolower(str[i]);
        }
        return result;
    }
    
   
    bool startsWith(string word, string searchTerm) {
        if(searchTerm.length() > word.length()) {
            return false;
        }
        for(int i = 0; i < searchTerm.length(); i++) {
            if(word[i] != searchTerm[i]) {
                return false;
            }
        }
        return true;
    }
    
    
    bool containsWordStartingWith(string str, string searchTerm) {
        str = toLower(str);
        searchTerm = toLower(searchTerm);
        string currentWord = "";
        
        for(int i = 0; i <= str.length(); i++) {
            if(i == str.length() || str[i] == ' ') {
                if(currentWord != "" && startsWith(currentWord, searchTerm)) {
                    return true;
                }
                currentWord = "";
            } else {
                currentWord += str[i];
            }
        }
        return false;
    }
    
    int itemCount() {
        menuItem* p = menu;
        int count = 0;
        for (int i = 0; i < 500; i++) {
            if ((p+i)->name != "")
                count++;
        }
        return count;
    }
    
   

    void sortAscendPrice() {
        int realCount = itemCount();
        for(int j = 0; j < realCount; j++) {
            for(int i = 0; i < realCount - j - 1; i++) {
                if(menu[i].price > menu[i+1].price) {
                    tempMenu = menu[i];
                    menu[i] = menu[i+1];
                    menu[i+1] = tempMenu;
                }
            }
        }
    }
    
    void sortDescendPrice() {
        int realCount = itemCount();
        for(int j = 0; j < realCount; j++) {
            for(int i = 0; i < realCount - j - 1; i++) {
                if(menu[i].price < menu[i+1].price) {
                    tempMenu = menu[i];
                    menu[i] = menu[i+1];
                    menu[i+1] = tempMenu;
                }
            }
        }
    }
    
    void sortName() {
        int realCount = itemCount();
        for(int j = 0; j < realCount; j++) {
            for(int i = 0; i < realCount - j - 1; i++) {
                if(menu[i].name > menu[i+1].name) {
                    tempMenu = menu[i];
                    menu[i] = menu[i+1];
                    menu[i+1] = tempMenu;
                }
            }
        }
    }

   

    void searchMenu(string searchTerm) {
        int realCount = itemCount();
        bool found = false;
        
        cout << "\nSearch Results for: \"" << searchTerm << "\"\n";
        
        for(int i = 0; i < realCount; i++) {
            if(containsWordStartingWith(menu[i].name, searchTerm)) {
                cout << left << setw(40) << menu[i].name 
                     << setw(10) << (to_string(menu[i].price) + " PKR")
                     << setw(15) << menu[i].type
                     << (to_string(menu[i].rating) + " stars")   
                     << endl;
                found = true;
            }
        }
        
        if(!found) {
            cout << "No items found matching \"" << searchTerm << "\"\n";
        }
    }

    void displayMenu() {
        int realCount = itemCount();
        sortAscendPrice();     
        cout << "Original Menu (" << realCount << " items):\n";
        cout << left << setw(40) << "ITEM" << setw(10) << "PRICE" << setw(15) << "TYPE" << setw(8) << "REVIEWS" <<endl;
        cout << "------------------------------------------------------------\n";
        for (int i = 0; i < realCount; i++) {
            cout << left << setw(40) << menu[i].name 
                 << setw(10) << (to_string(menu[i].price) + " PKR")
                 << setw(15) << menu[i].type 
                 << setw(8) << (to_string(menu[i].rating) + " stars")
                 << endl;
        }
    }
};



void globalSearch(cafe cafes[], int cafeCount, string searchTerm) {
    cout << "\n=== Global Search Results for: \"" << searchTerm << "\" ===\n\n";
    
    bool anyFound = false;
    
    for(int c = 0; c < cafeCount; c++) {
        int realCount = cafes[c].itemCount();
        bool foundInThisCafe = false;
        bool headerPrinted = false;
        
        for(int i = 0; i < realCount; i++) {
            if(cafes[c].containsWordStartingWith(cafes[c].menu[i].name, searchTerm)) {
                if(!headerPrinted) {
                    cout << "--- " << cafes[c].cafeName << " ---\n";
                    headerPrinted = true;
                }
                cout << left << setw(40) << cafes[c].menu[i].name 
                     << setw(10) << (to_string(cafes[c].menu[i].price) + " PKR")
                     << setw(15) << cafes[c].menu[i].type 
                     << setw(8) << (to_string(cafes[c].menu[i].rating) + " stars")
                     << endl;
                foundInThisCafe = true;
                anyFound = true;
            }
        }
        
        if(foundInThisCafe) {
            cout << endl;
        }
    }
    
    if(!anyFound) {
        cout << "No items found matching \"" << searchTerm << "\" in any cafe.\n";
    }
}

int main() {
   
    cafe Inno("Inno.txt", "Inno Cafe");
    cafe C1("C1.txt", "C1 Cafe");
    cafe C2("C2 Menu.txt", "C2 Cafe");
    cafe C3("C3 Menu.txt", "C3 Cafe");
    cafe C4("C4 menu.txt", "C4 Cafe");
    cafe CoffeeLounge("Coffee Lounge Menu.txt", "Coffee Lounge");
    cafe Nice("Nice Menu.txt", "Nice Cafe");
    cafe Retro("Retro Menu.txt", "Retro Cafe");
    cafe S3H("S3H Cafe.txt", "S3H Cafe");

    // 2. Setup Array
    cafe cafes[9] = {Inno, C1, C2, C3, C4, CoffeeLounge, Nice, Retro, S3H};
    int cafeCount = 9;

    int choice = -1;

    while (choice != 0) {
        cout << "\n================================\n";
        cout << "      NUST CAFE SYSTEM         \n";
        cout << "================================\n";
        cout << "1. Search by Category (View List)\n"; 
        cout << "2. Display Specific Cafe Menu\n"; 
        cout << "3. Search Food Item (Global Search)\n"; 
        cout << "0. Quit\n";
        cout << "Enter selection: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        
        if (choice == 1) {
            int knownCount = 31;
            string* knownCategories = new string[knownCount] {
                "BBQ", "Bread", "Burger", "Chinese", "Coffee", "Dessert", 
                "Drinks", "Extra", "Fries", "HotDrink", "IceCream", "Juices", 
                "Paratha", "Pasta", "Pizza", "Rice", "Roll", "RollParatha", 
                "Rolls", "Salad", "Salan", "Sandwich", "Shakes", "Shawarma", 
                "Sides", "Slush", "Snacks", "Soda", "Soup", "Tea", "Wings"
            };

            cout << "\nAvailable Categories:\n";
            for(int i = 0; i < knownCount; i++) {
                cout << left << setw(15) << knownCategories[i];
                if((i + 1) % 4 == 0) cout << endl;
            }
            cout << endl << endl;

            string catInput;
            cout << "Enter Category from above: ";
            cin.ignore();
            getline(cin, catInput);
            
            cout << "\n=== Category Results for: \"" << catInput << "\" ===\n\n";
            bool anyCatFound = false;

            for(int c = 0; c < cafeCount; c++) {
                bool headerPrinted = false; 
                int rCount = cafes[c].itemCount();
                
                for(int i = 0; i < rCount; i++) {
                    
                    if(cafes[c].containsWordStartingWith(cafes[c].menu[i].type, catInput)) {
                        if(!headerPrinted) {
                            cout << "--- " << cafes[c].cafeName << " ---\n";
                            headerPrinted = true;
                        }
                        cout << left << setw(40) << cafes[c].menu[i].name 
                             << setw(10) << (to_string(cafes[c].menu[i].price) + " PKR") 
                             << setw(15) << cafes[c].menu[i].type
                             << setw(8) << (to_string(cafes[c].menu[i].rating) + " stars")
                             << endl;
                        anyCatFound = true;
                    }
                }
                if(headerPrinted) cout << endl;
            }
            
            if(!anyCatFound) {
                cout << "No items found for category \"" << catInput << "\".\n";
            }
            delete[] knownCategories;
        }
        
        
        else if (choice == 2) {
            string inputName;
            cout << "Available Cafes: Inno, C1, C2, C3, C4, Coffee Lounge, Nice, Retro, S3H\n";
            cout << "Enter Cafe Name: ";
            cin.ignore(); 
            getline(cin, inputName); 

            int foundIndex = -1;
            
            for(int i = 0; i < cafeCount; i++) {
                
                if(cafes[i].containsWordStartingWith(cafes[i].cafeName, inputName)) {
                    foundIndex = i;
                    break;
                }
            }

            if(foundIndex != -1) {
                char sortChoice = ' ';
                cafes[foundIndex].sortAscendPrice(); // Sort by price by default
                
                while (sortChoice != 'Z') {
                    int rCount = cafes[foundIndex].itemCount();
                    
                    cout << "\n--- " << cafes[foundIndex].cafeName << " Menu (" << rCount << " items) ---\n";
                    cout << left << setw(40) << "ITEM" << setw(10) << "PRICE" << setw(15) << "TYPE" << endl;
                    cout << "------------------------------------------------------------\n";
                    
                    for(int k=0; k<rCount; k++) {
                         cout << left << setw(40) << cafes[foundIndex].menu[k].name 
                             << setw(10) << (to_string(cafes[foundIndex].menu[k].price) + " PKR") 
                             << setw(15) << cafes[foundIndex].menu[k].type << endl;
                    }

                    cout << "\n[Sort Options]\n";
                    cout << "A: Ascending Price\n";
                    cout << "B: Descending Price\n";
                    cout << "C: Sort by Name\n";
                    cout << "Z: Back to Main Menu\n";
                    cout << "Enter choice: ";
                    cin >> sortChoice;
                    sortChoice = toupper(sortChoice);

                    if (sortChoice == 'A') {
                        cafes[foundIndex].sortAscendPrice();
                    }
                    else if (sortChoice == 'B') {
                        cafes[foundIndex].sortDescendPrice();
                    }
                    else if (sortChoice == 'C') {
                        cafes[foundIndex].sortName();
                    }
                }
            } else {
                cout << "Cafe not found! Check spelling.\n";
            }
        }
        
       
        else if (choice == 3) {
            string term;
            cout << "Enter food name to search (e.g. Burger, Chai): ";
            cin >> term;
            globalSearch(cafes, cafeCount, term);
        }
        
        else if (choice == 0) {
            cout << "Exiting...\n";
        }
    }

    return 0;
}