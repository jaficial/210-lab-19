// COMSC-210 | Lab 18 | Jed Aficial |
// github link: https://github.com/jaficial/210-lab-18
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

void output(Node *);
void add_front_node(Node *, Node *, string, int);
void delete_linked_list(Node *, Node *);

/* add_front_node takes in the new node, data for the new node, and the previous head node,
   and sets the new node to point at the head node */
void add_front_node(Node *new_value, Node *head, string temp_comment){
	new_value->next = head;
	new_value->comments = temp_comment;
}

/* output function traverses the linked list and outputs the nodes of the linked list, 
   as well as calulates the average of the movie ratings. */ 
// void output(Node * list){

// }
class Movie {
private:
    string movie_title;
    double movie_rating;
    Node *movie_comments;

public:
    Movie(string title, double rating, Node *comments) {movie_title = title; movie_rating = rating; movie_comments = comments;}
    
    // string get_movie_title() {return movie_title;}
    // void set_title(string title) {movie_title = title;}

    // double get_movie_rating() {return movie_rating;}
    // void set_rating(double rating) {movie_rating = rating;}

    // Node *get_movie_comments() {return movie_comments;}
    // void set_comments(Node *comments) {movie_comments = comments;}
    // might have to move output function to here

    void print() {
        cout << "This is the title of the movie: " << movie_title << endl;
        cout << "These were the reviews:\n";

        Node *current = movie_comments;
        while (current){
            cout << movie_comments->comments << endl;
            current = current->next;
        }
        cout << endl;
    }
};

struct movieNode {
    Movie movie_obj;
    movieNode *next;
};

void output(movieNode *hd){
    if(!hd){
        cout << "Empty list.\n";
        return;
    }
    int count = 1;
    movieNode * current = hd;
    while (current){
        current->movie_obj.print();
    }



}
/* funtion takes in the head and current node of the linked list,
   and deallocates the memory for each node.*/
void delete_linked_list(movieNode*current, movieNode *head){
    while(current){
        head = current->next;
        delete current;
        current = head;
    }
}

/* NOTES: - REVIEW COMMENTS NEED TO BE READ FROM AN EXTERNAL FILE
          - MOVIE RATING IS A RANDOM (type double) NUMBER BETWEEN 1.0 and 5.0 (must only have 1 decimal place))
          - NEED A MOVIE CLASS 
            - OBJECTS: TITLE, 
                DOUBLE FOR RATING
                LINKED LIST FOR REVIEW COMMENTS
          - main() needs to feature a container of the Movie objects*/

          // GOING TO USE A LINKED LIST FOR THE CONTAINER
int main(){
    ifstream fin ("reviews_for_movies.txt");
    // Node *head = nullptr; // node 
    // Node *current = head; // current points to head node
    movieNode *container_head = nullptr; // for container
    movieNode *container_current = container_head;
    //
    // Node *head = nullptr; // for 
    // Node *current = head;

    // adding node to the head of the linked list

    /*
    double temp_rating;
    string temp_comment;

    cout << "Enter review rating 0-5: ";
    Node *new_value = new Node; // Node *new_value is in loop as a new one has to get defined for each new node
    cin >> temp_rating;
    cout << "Enter review comments: ";
    cin.ignore();
    getline(cin, temp_comment);
    */

    // NEED 2 SETS OF NODES: 
    //  - nodes for movies container
    //  - nodes for and comments 
    //  - ONLY NEED ONE RATING PER MOVIE, TWO COMMENTS PER MOVIE
    double temp_rating;
    for (int i = 0; i < MAX_MOVIES; i++){ // Outer for loop is for movie container (linked list)
        movieNode *new_movie = new movieNode;
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
        if (!container_head) { // for first node
            container_head = new_movie;
            new_movie->next = nullptr;
            new_movie->movie_obj =  Movie(temp_title, temp_rating, head);
        }
        else { // every other node
            new_movie->next = container_head;
            new_movie->movie_obj = Movie(temp_title, temp_rating, head);
            container_head = new_movie;
        }

    }
    // output is printing out correctly
    // output(head);
    output(container_head);
    fin.close();
    delete_linked_list(container_current, container_head);
    container_head = nullptr;
    // linked list is properly deallocated
    return 0;
}
