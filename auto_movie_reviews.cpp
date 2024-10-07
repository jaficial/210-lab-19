// COMSC-210 | Lab 19 | Jed Aficial |
// github link: https://github.com/jaficial/210-lab-19
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <array>

int MAX_MOVIES = 2;

using namespace std;

// CITED: Will be reusing my Lab 17 submission, except editting it to fit Lab 19
struct Node {
    string comments;
    Node *next;
};

void add_front_node(Node *, Node *, string, int);

/* add_front_node takes in the new node, data for the new node, and the previous head node,
   and sets the new node to point at the head node */
void add_front_node(Node *new_value, Node *head, string temp_comment){
	new_value->next = head;
	new_value->comments = temp_comment;
}

// Movie class for movie objects
class Movie {
private:
    string movie_title;
    double movie_rating;
    Node *movie_comments;

public:
    // set of setters and getters for the movie title, movie rating, and movie comments linked list
    string get_movie_title() {return movie_title;}
    void set_title(string title) {movie_title = title;}

    double get_movie_rating() {return movie_rating;}
    void set_rating(double rating) {movie_rating = rating;}
    
    Node *get_movie_comments() {return movie_comments;}
    void set_comments(Node *comments) {movie_comments = comments;} 
    void print() {
        cout << "This is the title of the movie: " << movie_title << endl;
        cout << "The movie rating was: " << movie_rating << endl;
        cout << "These were the reviews:\n";

        Node *current = movie_comments;
        while (current){
            cout << setw(4) << "" << movie_comments->comments << endl;
            current = current->next;
        }
    }
};

/* NOTES: - REVIEW COMMENTS NEED TO BE READ FROM AN EXTERNAL FILE
          - MOVIE RATING IS A RANDOM (type double) NUMBER BETWEEN 1.0 and 5.0 (must only have 1 decimal place))
          - NEED A MOVIE CLASS 
            - OBJECTS: TITLE, 
                DOUBLE FOR RATING
                LINKED LIST FOR REVIEW COMMENTS
          - main() needs to feature a container of the Movie objects*/

          // Ended up using an array container for the movie objects
          // NOTE: 2 comments, 1 rating per movie
int main(){
    ifstream fin ("reviews_for_movies.txt");
    array<Movie, 2> movies;
  
    double temp_rating;
    for (int i = 0; i < MAX_MOVIES; i++){ // Outer for loop is for movie container (array container)
        
        Node *head = nullptr; // if I have the head initialization here, i'll have a head for each set of movie data
        Node *current = head;
        string temp_title;
        temp_title = "Movie #" + to_string(i); // CITED from: https://www.geeksforgeeks.org/stdto_string-in-cpp/

        for (int j = 0; j < MAX_MOVIES; j++){ // inner for loop is for movie data per movie, two loops since there are two reveiws per movie
            string temp_comment;
            Node *new_value = new Node;
            getline(fin, temp_comment);
            if (!head){ // for first node of ratings and comments
                head = new_value; // head gets assigned to new node value
                new_value->next = nullptr; // newval points to null
                new_value->comments = temp_comment; // newval-comments gets assigned the temp comment
            }
            else{ //  for second node of comments
                add_front_node(new_value, head, temp_comment);
                head = new_value;
            }
        }
        temp_rating = rand() % 5 + 1;
        Movie temp_object;
        temp_object.set_rating(temp_rating);
        temp_object.set_title(temp_title);
        temp_object.set_comments(head);
        movies[i] = temp_object;
    }
   
    fin.close();
    for (auto movie_num : movies){
        movie_num.print();
        cout << endl;
    }
    return 0;
}
