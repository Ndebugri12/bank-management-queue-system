
#include <iostream>
#include <string>
#include <new>
#include <limits>
#include <cctype>

using namespace std;

// =====================================
// CUSTOMER STRUCTURE
// =====================================
struct Customer {
    string name;
    Customer* next;
};

// =====================================
// QUEUE STRUCTURE
// =====================================
struct Queue {
    Customer* front;
    Customer* rear;

    Queue() {
        front = nullptr;
        rear = nullptr;
    }
};

// =====================================
// CHECK IF QUEUE IS EMPTY
// =====================================
bool isEmpty(Queue &q) {
    return q.front == nullptr;
}

// =====================================
// 1. JOIN QUEUE (ENQUEUE)
// =====================================
void joinQueue(Queue &q) {

    string name;

    cout << "Enter customer name: ";
    getline(cin >> ws, name);

    if (name.empty()) {
        cout << "Customer name cannot be empty.\n";
        return;
    }

    Customer* newCustomer = new(nothrow) Customer;

    if (newCustomer == nullptr) {
        cout << "Memory allocation failed!\n";
        return;
    }

    newCustomer->name = name;
    newCustomer->next = nullptr;

    if (isEmpty(q)) {
        q.front = newCustomer;
        q.rear = newCustomer;
    }
    else {
        q.rear->next = newCustomer;
        q.rear = newCustomer;
    }

    cout << name << " joined the queue successfully!\n";
}

// =====================================
// 2. SERVE CUSTOMER (DEQUEUE)
// =====================================
void serveCustomer(Queue &q) {

    if (isEmpty(q)) {
        cout << "Queue is empty! No customer to serve.\n";
        return;
    }

    Customer* temp = q.front;

    cout << temp->name << " has been served.\n";

    q.front = q.front->next;

    if (q.front == nullptr) {
        q.rear = nullptr;
    }

    delete temp;
}

// =====================================
// 3. DISPLAY QUEUE
// =====================================
void displayQueue(Queue &q) {

    if (isEmpty(q)) {
        cout << "No customers are waiting.\n";
        return;
    }

    Customer* temp = q.front;

    cout << "\n--- CUSTOMERS IN QUEUE ---\n";

    while (temp != nullptr) {
        cout << temp->name << endl;
        temp = temp->next;
    }
}

// =====================================
// 4. COUNT CUSTOMERS
// =====================================
void countCustomers(Queue &q) {

    int count = 0;
    Customer* temp = q.front;

    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    cout << "Total customers waiting: "
         << count << endl;
}

// =====================================
// 5. SHOW NEXT CUSTOMER
// =====================================
void showNextCustomer(Queue &q) {

    if (isEmpty(q)) {
        cout << "No customer is waiting.\n";
        return;
    }

    cout << "Next customer to be served: "
         << q.front->name << endl;
}

// =====================================
// RELEASE REMAINING MEMORY
// =====================================
void clearQueue(Queue &q) {

    while (!isEmpty(q)) {
        Customer* temp = q.front;
        q.front = q.front->next;
        delete temp;
    }

    q.rear = nullptr;
}

// =====================================
// MAIN FUNCTION
// =====================================
int main() {

    Queue bankQueue;
    int choice;

    do {

        cout << "\n========================================\n";
        cout << " BANK CUSTOMER QUEUE MANAGEMENT SYSTEM\n";
        cout << "========================================\n";

        cout << "1. Join Queue\n";
        cout << "2. Serve Customer\n";
        cout << "3. Display Queue\n";
        cout << "4. Show Number of Customers\n";
        cout << "5. Show Next Customer\n";
        cout << "6. Exit\n";

        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {

            case 1:
                joinQueue(bankQueue);
                break;

            case 2:
                serveCustomer(bankQueue);
                break;

            case 3:
                displayQueue(bankQueue);
                break;

            case 4:
                countCustomers(bankQueue);
                break;

            case 5:
                showNextCustomer(bankQueue);
                break;

            case 6:
                cout << "Exiting system...\n";
                break;

            default:
                cout << "Invalid choice! Select 1 to 6.\n";
        }

    } while (choice != 6);

    clearQueue(bankQueue);

    cout << "Thank you for using the Bank Queue System!\n";

    return 0;
}
