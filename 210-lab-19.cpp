#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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

double randRating() {
    return static_cast<float> (rand() % 41 + 10) / 10.0;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<Movie> movies;
    movies.push_back(Movie("Movie A"));
    movies.push_back(Movie("Movie B"));

    ifstream inputFile("reviews.txt");
    if(!inputFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string comment;
    while(getline(inputFile, comment)) {
        double rating = randRating();
        movies[0].addAReview(rating, comment);

        rating = randRating();
        movies[1].addAReview(rating, comment);
    }

    inputFile.close();

    for (const auto& movie : movies) {
        cout << "Reviews for " << movie.getTitle() << ":" << endl;
        movie.outputReviewsAndAverage();
        cout << endl;
    }
    return 0;


}
