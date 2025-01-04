#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

// Global variables
map<string, string> registeredUsers; // Stores username and password
map<string, pair<int, int>> shoppingCartItems; // Stores product name, price, and quantity
vector<string> orderDetails; // Stores details of the order
map<string, int> productCatalogItems = { {"Laptop", 50000}, {"Smartphone", 20000}, {"Headphones", 3000}, {"Camera", 25000} };
map<string, vector<string>> userPaymentDetails; // Stores payment details for each user
time_t orderPlacedDate;
time_t expectedDeliveryDate;
string currentUsername; // Tracks logged-in user

// Function declarations
void userRegistration();
void userLogin();
void productCatalog();
void shoppingCart();
void paymentProcessing(string username);
void orderManagement();
void reviewAndRatingSystem();
void adminDashboard();
void manageProducts();
void displayPaymentDetails();
void userMenu();

int main() {
    int userType;
    cout << "\n=== Online Shopping Portal ===\n";
    cout << "1. Admin\n";
    cout << "2. User\n";
    cout << "3. Exit\n";

    do {
        cout << "\nEnter your choice: ";
        cin >> userType;

        switch (userType) {
            case 1:
                adminDashboard();
                break;
            case 2:
                userMenu();
                break;
            case 3:
                cout << "Exiting the system. Thank you for visiting!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (userType != 3);

    return 0;
}

// Function implementations
void userMenu() {
    int choice;
    do {
        cout << "\n=== User Dashboard ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Product Catalog\n";
        cout << "4. Shopping Cart\n";
        cout << "5. Payment Processing\n";
        cout << "6. Order Management\n";
        cout << "7. Review and Rating System\n";
        cout << "8. Back to Main Menu\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                userRegistration();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                productCatalog();
                break;
            case 4:
                shoppingCart();
                break;
            case 5:
                paymentProcessing(currentUsername);
                break;
            case 6:
                orderManagement();
                break;
            case 7:
                reviewAndRatingSystem();
                break;
            case 8:
                cout << "Returning to the main menu...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);
}

void userRegistration() {
    cout << "\n=== User Registration ===\n";
    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    if (registeredUsers.find(username) != registeredUsers.end()) {
        cout << "Username already exists. Please try logging in.\n";
        return;
    }
    cout << "Enter a password: ";
    cin >> password;
    registeredUsers[username] = password;
    cout << "Registration successful! You can now log in.\n";
}

void userLogin() {
    cout << "\n=== User Login ===\n";
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    if (registeredUsers.find(username) != registeredUsers.end() && registeredUsers[username] == password) {
        cout << "Login successful! Redirecting to Product Catalog...\n";
        currentUsername = username;
        productCatalog();
    } else {
        cout << "Invalid credentials. Please register first.\n";
        userRegistration();
    }
}

void productCatalog() {
    cout << "\n=== Product Catalog ===\n";
    cout << "Available Products:\n";
    int index = 1;
    for (const auto& product : productCatalogItems) {
        cout << char('A' + index - 1) << ". " << product.first << " - Rs. " << product.second << "\n";
        index++;
    }
    char choice;
    cout << "\nEnter the letter of the product you want to add to your cart (Q to return to User Menu): ";
    cin >> choice;
    if (choice >= 'A' && choice < 'A' + productCatalogItems.size()) {
        auto it = productCatalogItems.begin();
        advance(it, choice - 'A');
        string productName = it->first;
        int productPrice = it->second;

        int quantity;
        cout << "Enter the quantity you want to add: ";
        cin >> quantity;

        shoppingCartItems[productName].first = productPrice;
        shoppingCartItems[productName].second += quantity;

        cout << quantity << " " << productName << "(s) have been added to your cart.\n";
    } else if (choice != 'Q' && (choice < 'A' || choice >= 'A' + productCatalogItems.size())) {
        cout << "Invalid choice!\n";
    }
}

void shoppingCart() {
    cout << "\n=== Shopping Cart ===\n";
    if (shoppingCartItems.empty()) {
        cout << "Your cart is currently empty.\n";
    } else {
        cout << "Items in your cart:\n";
        int total = 0;
        int index = 1;
        for (const auto& item : shoppingCartItems) {
            int itemTotal = item.second.first * item.second.second;
            cout << index++ << ". " << item.first << " - Rs. " << item.second.first << " x " << item.second.second << " = Rs. " << itemTotal << "\n";
            total += itemTotal;
        }
        cout << "Total amount: Rs. " << total << "\n";
        cout << "\nEnter 1 to proceed for payment or 0 to return to User Menu: ";
        int proceed;
        cin >> proceed;
        if (proceed == 1) {
            paymentProcessing(currentUsername);
        }
    }
}

void paymentProcessing(string username) {
    cout << "\n=== Payment Processing ===\n";
    if (shoppingCartItems.empty()) {
        cout << "Your cart is empty. Add items to your cart before proceeding to payment.\n";
    } else {
        int total = 0;
        for (const auto& item : shoppingCartItems) {
            int itemTotal = item.second.first * item.second.second;
            total += itemTotal;
        }
        cout << "Total amount to pay: Rs. " << total << "\n";
        cout << "Processing your payment...\n";
        srand(time(0));
        int paymentID = rand() % 100000 + 10000;
        cout << "Payment ID: " << paymentID << "\n";
        cout << "Payment successful!\n";

        string paymentDetails = "Payment ID: " + to_string(paymentID) + ", Total: Rs. " + to_string(total);
        userPaymentDetails[username].push_back(paymentDetails);

        shoppingCartItems.clear();
        cout << "Your order has been placed successfully.\n";
    }
}

void orderManagement() {
    cout << "\n=== Order Management ===\n";
    if (userPaymentDetails[currentUsername].empty()) {
        cout << "No orders available.\n";
    } else {
        cout << "Your Orders:\n";
        for (const string& detail : userPaymentDetails[currentUsername]) {
            cout << detail << "\n";
        }
    }
}

void reviewAndRatingSystem() {
    cout << "\n=== Review and Rating System ===\n";
    string review;
    int rating;
    cout << "Enter your review: ";
    cin.ignore();
    getline(cin, review);
    cout << "Rate the product (1-5): ";
    cin >> rating;
    cout << "Thank you for your feedback!\n";
}

void adminDashboard() {
    int adminChoice;
    cout << "\n=== Admin Dashboard ===\n";
    cout << "1. View Order Management\n";
    cout << "2. View Payment Details\n";
    cout << "3. View User Entry Details\n";
    cout << "4. Manage Product Catalog\n";
    cout << "5. Back to Main Menu\n";
    do {
        cout << "Enter your choice: ";
        cin >> adminChoice;
        switch (adminChoice) {
            case 1:
                orderManagement();
                break;
            case 2:
                displayPaymentDetails();
                break;
            case 3:
                cout << "\n=== User Entry Details ===\n";
                for (const auto& user : registeredUsers) {
                    cout << "Username: " << user.first << "\n";
                }
                break;
            case 4:
                manageProducts();
                break;
            case 5:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (adminChoice != 5);
}

void manageProducts() {
    int productChoice;
    cout << "\n=== Manage Product Catalog ===\n";
    cout << "1. Add New Product\n";
    cout << "2. Delete Existing Product\n";
    cout << "3. Back to Admin Dashboard\n";
    do {
        cout << "Enter your choice: ";
        cin >> productChoice;
        switch (productChoice) {
            case 1: {
                string productName;
                int productPrice;
                cout << "Enter product name: ";
                cin.ignore();
                getline(cin, productName);
                cout << "Enter product price: ";
                cin >> productPrice;
                productCatalogItems[productName] = productPrice;
                cout << "Product added successfully!\n";
                break;
            }
            case 2: {
                string productName;
                cout << "Enter product name to delete: ";
                cin.ignore();
                getline(cin, productName);
                if (productCatalogItems.erase(productName)) {
                    cout << "Product deleted successfully!\n";
                } else {
                    cout << "Product not found.\n";
                }
                break;
            }
            case 3:
                cout << "Returning to Admin Dashboard...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (productChoice != 3);
}

void displayPaymentDetails() {
    cout << "\n=== Payment Details ===\n";
    for (const auto& user : userPaymentDetails) {
        cout << "Username: " << user.first << "\n";
        for (const string& detail : user.second) {
            cout << "  " << detail << "\n";
        }
    }
}
