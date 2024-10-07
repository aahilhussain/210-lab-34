#include <iostream>
#include <string>
using namespace std;

struct Review {
    float rating;
    string comments;
    Review* next;
};

//Review* head = nullptr;
class Movie {
    private:
        string title;
        Review* head;

    public:
        Movie(string movieTitle) : title(movieTitle), head(nullptr) {}

    //clean up memory
    ~Movie() {
        cleanup();
    }

    //function to add in front
    void addAReview(float rating, string comments) {
        Review* newReview = new Review{rating, comments, head};
        head = newReview;
    }

    //function to add to the back
    void addNodeAtTail(float rating, string comments) {
        if (head == nullptr) {
            head = new Review{rating, comments, nullptr};
            return;
        }
        Review* temp = head;
        while (temp-> next != nullptr) {
            temp = temp-> next;
        }
        temp -> next = new Review{rating, comments, nullptr};
    }

    void outputReviewsAndAverage() const {
        Review* temp = head;
        float sum = 0;
        int count = 0;
        while (temp != nullptr) {
            cout << "Rating: " << temp -> rating << ", Comments: " << temp->comments << endl;
            sum += temp-> rating;
            temp = temp->next;
            count++;
        }
        if (count > 0)
        {
            cout << "Average: " << sum / (count - 1) << endl;
        }
    }

    void cleanup() {
        while (head != nullptr) {
            Review* temp = head;
            head = head-> next;
            delete temp;
        }
    }
    
    string getTitle() const {
        return title;
    }
};

int main() {
    int choice;
    cout << "Which linked list method should we use?\n";
    cout << "   [1] New nodes are added at the head of the linked list\n";
    cout << "   [2] New nodes are added at the tail of the linked list\n";
    cout << "   Choise: ";
    cin >> choice;

    if(choice != 1 && choice != 2) {
        cout << "Invalid choice. Exiting...\n";
        return 1; 
    }

    char anotherReview ='y';
    while (anotherReview == 'y') {
        float rating;
        string comments;
        cout << "Enter review rating 0-5: ";
        cin >> rating;
        cout << "Enter review comments: ";
        cin.ignore();
        getline(cin, comments);

        if (choice == 1) {
            addNodeAtHead(rating, comments);
        } else if (choice == 2) {
            addNodeAtTail(rating, comments);
        }

        cout << "Enter another review? Y/N: ";
        cin >> anotherReview;
    }

    outputReviewsAndAverage();
    cleanup();
    return 0;


}
