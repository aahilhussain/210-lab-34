#include <iostream> //allows the program to use cin and cout functions
using namespace std; //allows you to bypass the use of std:: where needed

//given constants for future function uses
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

//creates the class DoublyLinkedList with given definition using private and public variables
class DoublyLinkedList {
private: // keeps the variables within the class itself and cannot be directly accessed outside
    struct Node { //defines a struct called Node
        int data; //an integer stored in Node struct
        Node* prev; //pointer pointing to previous node
        Node* next; //pointer pointing to next node
        //default constructor that initializes the 3 private members created above
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p; // p is set to a null pointer
            next = n; // n is set to a null pointer
        }
    };

    Node* head; //pointer set to the head/front of the list
    Node* tail; //pointer set to the tail/end of the list

//public variables which can be accessed outside of the class
public:
    //constructor that initializes the list
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //this method puts a node after the given position
    void insert_after(int value, int position) {
        //if the position(given) is greater than 0 than it will output that it must be greater than 0. 
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        //creates a new node using the given variable value
        Node* newNode = new Node(value);
        //if the list is empty then the new node(value) will equal the head as well as the tail
        if (!head) {
            head = tail = newNode;
            return;
        }
        
        //creates a temp pointer that will traverse the list
        Node* temp = head;
        //as long as i is less than the last position, it will go to the next position
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        //continuation 
        //if the temp pointer goes past the end, it will output the string because it will have no value to point to
        //will delete the newNode afterwards
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        //sets the next pointer to the newnode
        newNode->next = temp->next;
        //sets prev pointer to the temp
        newNode->prev = temp;
        //if temp points to the next pointer where it exists
        if (temp->next)
        //this will set the prev pointer of the next node to point to newNode
        //essentially helps maintain the structure
            temp->next->prev = newNode;
        //or else it will update the tail if it reaches the end
        else
            tail = newNode;
        temp->next = newNode;
    }

    //function that will delete a node with a given value
    void delete_val(int value) {
        //if the list is empty, nothing will occur and traverse the list
        if (!head) return;
        Node* temp = head;
        
        //as long as temp and data that temp is pointing to do not contain a value
        while (temp && temp->data != value)
            //move to the next pointer
            temp = temp->next;
        //if no value, then do nothing
        if (!temp) return; 
        //if temp points to the previous node
        if (temp->prev)
            //adjust the next pointer of the prior node
            temp->prev->next = temp->next;
        else
        //or else update the head
            head = temp->next; 

        //if temp points to next node
        if (temp->next)
        //adjust the previous pointer to the next node
            temp->next->prev = temp->prev;
        else
        //or else update the tail
            tail = temp->prev; 

        //delete the node
        delete temp;
    }

    //deletes a node at a given position in the list
    void delete_pos(int pos) {
        //if the list is empty print out list is empty
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
    //if the position is 1 then delete the front node
        if (pos == 1) {
            pop_front();
            return;
        }
    
    //used to travers the list
        Node* temp = head;
    //is pos is less than 1, print out position doesn't exist
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            //else move to the next node
            else
                temp = temp->next;
        }
        //the temp node doesn't exist, print out position doesn't exist
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        // if it reaches the end then delete the last node
        if (!temp->next) {
            pop_back();
            return;
        }
    
        //point to prev node
        Node* tempPrev = temp->prev;
        //set next pointer to prev node
        tempPrev->next = temp->next;
        //set previous pointer to next node
        temp->next->prev = tempPrev;
        //delete it
        delete temp;
    }

    //put a node at the end of the list
    void push_back(int v) {
        //create a new node
        Node* newNode = new Node(v);
        //if the list is empty then the new node equals head and tail
        if (!tail)
            head = tail = newNode;
        else {
            //or else tail node is adjusted to the next pointer
            tail->next = newNode;
            //then prev pointer sets the new node
            newNode->prev = tail;
            //and tail is updated
            tail = newNode;
        }
    }
    
    //put a node at the front of the list
    void push_front(int v) {
        //create the new node
        Node* newNode = new Node(v);
        //if empty then head and tail equal the new node
        if (!head)
            head = tail = newNode;
        else {
            // else modify pointer of new node
            newNode->next = head;
            // modify prev pointer of head node
            head->prev = newNode;
            //update head node
            head = newNode;
        }
    }
    
    //removes the front node
    void pop_front() {

        //if the list is empty print list is empty
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        //temp pointer to head node
        Node * temp = head;

    //if head has a value, update the head and then set prev pointer to nullptr
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
        //else head and tail equal nullptr
            head = tail = nullptr;
        delete temp;
    }

    //removes the last node
    void pop_back() {
        //if the list is empty print list is empty
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
         //temp pointer to tail node
        Node * temp = tail;

    //if tail has a value, update the tail and then set next pointer of new tail to nullptr

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        //else head and tail equal nullptr
            head = tail = nullptr;
            //delete the previous tail node
        delete temp;
    }

//destructor that will delete nodes and free up the memory so no memory leak
    ~DoublyLinkedList() {
        //delete as you traverse
        while (head) {
            //point to the head node
            Node* temp = head;
            //move to following node
            head = head->next;
            //delete the previous head node
            delete temp;
        }
    }

    //print the list from start to end
    void print() {
        //traverse the list using temp pointer
        Node* current = head;
        if (!current) {
        //if the list is empty print list is empty
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            //print the data of the current node with a space then move to the next and print again 
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    //prints it in reverse from end to start
    void print_reverse() {
        //traverse the list using temp pointer starting at the tail
        Node* current = tail;
        if (!current) { 
            //if the list is empty print list is empty
            cout << "List is empty." << endl;
            return;
        }
        //print the data from current node with a space then move to previous node
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    //will print the list skipping one each time
    void every_other_element() {
        //traverse list
        Node* current = head;
        if(!current){
        //if list is empty print out list is empty
        cout << "List is empty." << endl;
        return;
        }
        

        //use the bool to skip over a node
        bool pass = false;
        while(current) {
            //if the node does not equal pass print out the data
            if(!pass)
                cout << current->data << " ";
            //once data is printed then set the bool to true
            //this will set the condition to false causing it to skip a node
            pass = !pass;
            current = current->next;
        }
        cout << endl;
    }
};


int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning
    
    //create a doublylinkedlist object
    DoublyLinkedList list;

    //insert elements into a list
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    //print a list
    cout << "Final List: ";
    list.print();

    cout << endl;
    //print every other element
    cout << "Every other element list: ";
    list.every_other_element();
    
    return 0;
}