#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }
    bool isEmpty() {
        return head == nullptr;
    }

    int size() {
        int count = 0;
        Node* temp = head;
        while(temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void insert_after(string value, int position) {
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
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    string delete_pos(int pos) {
        if (pos == 1) {
            return pop_front();
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return "";
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    string pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return " ";
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    string pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return " ";
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

void openTxt(vector<string>& names) {
    ifstream file("C:\\Users\\ahussain\\Downloads\\names.txt");
    string name;
    while (file >> name){
    names.push_back(name);
    }
}

int main() {
    srand(time(0));
    vector<string> names;
    openTxt(names);

    if(names.empty()) {
        cout << "nothing" << endl;
        return 1;
    }

    DoublyLinkedList line;

    cout << "opened" << endl;
    //trying to print first 5 names
    for (int i = 0; i<5; ++i) {
        //rand amount of customers
        string customer = names[rand() % names.size()];
        line.push_back(customer);
        cout << customer << " has joined the line" << endl;
    }

    line.print();

    for (int minute = 1; minute <= 20; ++minute) {
        cout << "Time step #" << minute << ":" << endl;
        
        int prob = rand() % 100 + 1;  // returns random number 1-100
        if(prob <= 40) {
            string servedCust = line.pop_front();
            cout << servedCust << " is Served" << endl;
        }

        prob = rand() % 100 + 1;
        if(prob <=60) {
            string newCust = names[rand() % names.size()];
            line.push_back(newCust);
            cout << newCust << " has joined the line" << endl;
        }

        prob = rand() % 100 + 1;
        if (prob <=20){
            string endCust = line.pop_back();
            cout << endCust << " (at the rear) has left the line" << endl;
        }
        line.print();

        prob = rand() % 100 + 1;
        if (prob <= 10){
            int pos = rand() % line.size();
            string leavingCust;
            //string leavingCust = line.delete_pos(pos);
            cout << leavingCust<< " has left the line" << endl;
        }

        prob = rand() % 100 + 1;
        if (prob <= 10) {
            string VIPCust = names[rand() % names.size()];
            line.push_front(VIPCust);
            cout << VIPCust << " (VIP) joins the front of the line" << endl;
        }


        line.print();
    }
    
    return 0;
}