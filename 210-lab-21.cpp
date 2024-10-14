#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class Goat {
private:
    int age;
    string name;
    string color;
    static const string names[15];
    static const string colors[15];
public: 
    Goat() {
        age = rand() % 20 + 1;
        name = names[rand() % 15];
        color = colors[rand() % 15];
    }

    Goat(int a, string n, string c) : age(a), name(n), color(c) {}

    string getDescription() const {
        return name + " (" + color + ", " + to_string(age) + ")";
    }
};

const string Goat::names[15] = {
    "Aahil", "Momma", "Poppa", "Baby", "Alex", "Daisy", "Jasmine",
    "Pumpkin", "Theodore", "Grover", "Buddy", "Bobby", "Barney",
    "Mondo", "Momo"
};

const string Goat::colors[15] = {
    "Red", "Orange", "Yellow", "Green", "Blue", "Indigo", "Violet", 
    "White", "Black", "Rose", "Brown", "Purple", "Pink", "Cream", "Grey"
};

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) : data(val), prev(p), next(n) {}
        };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void push_back(Goat value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(const Goat& value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data.getDescription() != value.getDescription())
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() const {
        if (!head) {
            cout << "List is Empty" << endl;
            return;
        }
        Node* current = head;
        while(current) {
            cout << "   " << current->data.getDescription() << endl;
            current = current->next;
        }
    }

    void print_reverse() {
        if (!tail) {
            cout << "List is Empty" << endl;
            return;
        }
        Node* current = tail;
        while(current) {
            cout << "   " << current->data.getDescription() << endl;
            current = current->next;
        }
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    for (int i = 0; i < size; ++i){
        list.push_back(Goat());
    }

    cout << "List forward: " << endl;
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: \n";
    list.print();

    return 0;
}
