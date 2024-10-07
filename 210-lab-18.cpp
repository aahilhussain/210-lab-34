#include <iostream>
#include <string>
using namespace std;

struct Review {
    float rating;
    string comments;
    Review* next;
};

Review* head = nullptr;


//function to add in front
void addNodeAtHead(float rating, string comments) {
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
    while (teamp-> next != nullptr) {
        
    }
}

