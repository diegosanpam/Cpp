#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Supplier Class
class Supplier {
public:
    int supplierID;
    string name;
    string email;
    string phone;
    string address;

    Supplier(int id, string n, string e, string p, string a) {
        supplierID = id;
        name = n;
        email = e;
        phone = p;
        address = a;
    }

    // Marked as const to indicate it doesn't modify the object
    string toString() const {
        return to_string(supplierID) + "," + name + "," + email + "," + phone + "," + address;
    }
};

// Inventory Item Class
class InventoryItem {
public:
    int itemID;
    int supplierID;
    string itemName;
    int quantity;
    float unitPrice;

    InventoryItem(int iid, int sid, string name, int qty, float price) {
        itemID = iid;
        supplierID = sid;
        itemName = name;
        quantity = qty;
        unitPrice = price;
    }

    // Marked as const to indicate it doesn't modify the object
    string toString() const {
        return to_string(itemID) + "," + to_string(supplierID) + "," + itemName + "," + to_string(quantity) + "," + to_string(unitPrice);
    }
};

// Save data to file
void saveToFile(const string& filename, const string& data) {
    ofstream file;
    file.open(filename, ios::app);
    if (file.is_open()) {
        file << data << endl;
        file.close();
    }
    else {
        cerr << "Error opening file: " << filename << endl;
    }
}

// Load suppliers from file
vector<Supplier> loadSuppliers() {
    vector<Supplier> suppliers;
    ifstream file("suppliers.txt");
    string line;
    while (getline(file, line)) {
        int id;
        string name, email, phone, address;
        size_t pos = 0;
        id = stoi(line.substr(0, pos = line.find(',')));
        line.erase(0, pos + 1);
        name = line.substr(0, pos = line.find(','));
        line.erase(0, pos + 1);
        email = line.substr(0, pos = line.find(','));
        line.erase(0, pos + 1);
        phone = line.substr(0, pos = line.find(','));
        line.erase(0, pos + 1);
        address = line;
        suppliers.emplace_back(id, name, email, phone, address);
    }
    file.close();
    return suppliers;
}

// Load inventory items from file
vector<InventoryItem> loadInventory() {
    vector<InventoryItem> items;
    ifstream file("inventory.txt");
    string line;
    while (getline(file, line)) {
        int itemID, supplierID, quantity;
        float unitPrice;
        string itemName;
        size_t pos = 0;
        itemID = stoi(line.substr(0, pos = line.find(',')));
        line.erase(0, pos + 1);
        supplierID = stoi(line.substr(0, pos = line.find(',')));
        line.erase(0, pos + 1);
        itemName = line.substr(0, pos = line.find(','));
        line.erase(0, pos + 1);
        quantity = stoi(line.substr(0, pos = line.find(',')));
        line.erase(0, pos + 1);
        unitPrice = stof(line);
        items.emplace_back(itemID, supplierID, itemName, quantity, unitPrice);
    }
    file.close();
    return items;
}

int main() {
    vector<Supplier> suppliers = loadSuppliers();
    vector<InventoryItem> inventory = loadInventory();

    int choice;
    do {
        cout << "\n=== Inventory and Supplier Management System ===" << endl;
        cout << "1. Add Supplier" << endl;
        cout << "2. Add Inventory Item" << endl;
        cout << "3. Display Suppliers" << endl;
        cout << "4. Display Inventory" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            string name, email, phone, address;
            cout << "Enter Supplier ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Email: ";
            getline(cin, email);
            cout << "Enter Phone: ";
            getline(cin, phone);
            cout << "Enter Address: ";
            getline(cin, address);
            Supplier s(id, name, email, phone, address);
            suppliers.push_back(s);
            saveToFile("suppliers.txt", s.toString());
            break;
        }
        case 2: {
            int itemID, supplierID, quantity;
            float price;
            string itemName;
            cout << "Enter Item ID: ";
            cin >> itemID;
            cout << "Enter Supplier ID: ";
            cin >> supplierID;
            cin.ignore();
            cout << "Enter Item Name: ";
            getline(cin, itemName);
            cout << "Enter Quantity: ";
            cin >> quantity;
            cout << "Enter Unit Price: ";
            cin >> price;

            bool supplierExists = false;
            for (const auto& s : suppliers) {
                if (s.supplierID == supplierID) {
                    supplierExists = true;
                    break;
                }
            }
            if (!supplierExists) {
                cout << "Supplier ID not found. Please add the supplier first." << endl;
            }
            else {
                InventoryItem item(itemID, supplierID, itemName, quantity, price);
                inventory.push_back(item);
                saveToFile("inventory.txt", item.toString());
            }
            break;
        }
        case 3:
            cout << "\nSuppliers:\n";
            for (const auto& s : suppliers) {
                cout << s.toString() << endl; // Use toString to print the supplier details
            }
            break;
        case 4:
            cout << "\nInventory Items:\n";
            for (const auto& item : inventory) {
                cout << item.toString() << endl; // Use toString to print the inventory details
            }
            break;
        case 5:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
