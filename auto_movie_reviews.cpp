// COMSC-210 | Lab 18 | Jed Aficial |
// github link: https://github.com/jaficial/210-lab-18
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// CITED: Will be reusing my Lab 17 submission, except editting it to fit Lab 19
struct Node {
    float rating;
    string comments;
    Node *next;
};

void output(Node *);
void add_front_node(Node *, Node *, string, int);
void delete_linked_list(Node *, Node *);

/* funtion takes in the head and current node of the linked list,
   and deallocates the memory for each node.*/
void delete_linked_list(Node*current, Node *head){
    while(current){
        head = current->next;
        delete current;
        current = head;
    }
}

/* add_front_node takes in the new node, data for the new node, and the previous head node,
   and sets the new node to point at the head node */
void add_front_node(Node *new_value, Node *head, string temp_comment, float temp_rating){
	new_value->next = head;
	new_value->comments = temp_comment;
	new_value->rating = temp_rating;
}

/* output function traverses the linked list and outputs the nodes of the linked list, 
   as well as calulates the average of the movie ratings. */ 
void output(Node * list){
    if (!list){
        cout << "Empty list." << endl;
        return;
    }
    else{
        int count = 1;
        Node * current = list;
        cout << "Outputting all reviews:" << endl;
        float average;
        while(current){
            cout << setw(4) << "" << "> Review " << count++ << ": " << current->rating << ": " << current->comments;
            cout << endl;
            average += current->rating;
            current = current->next;
        }
        count--;
        average = average / count;
        cout << setw(4) << "" << "> Average: " << average << endl;
    }
}
class Movie {
private:
    string movie_title;
    Node *movie_ratings;
    Node *movie_comments;

public:
    Movie(string title, Node *ratings, Node *comments) {string }
};

/* NOTES: - REVIEW COMMENTS NEED TO BE READ FROM AN EXTERNAL FILE
          - MOVIE RATING IS A RANDOM (type double) NUMBER BETWEEN 1.0 and 5.0 (must only have 1 decimal place))
          - NEED A MOVIE CLASS 
            - OBJECTS: TITLE, 
                LINKED LIST FOR RATING NUMBER 
                LINKED LIST FOR REVIEW COMMENTS
          - main() needs to feature a container of the Movie objects*/
int main(){
    Node *head = nullptr; // node
    Node *current = head; // current points to head node

    bool more_reviews = 1; // if 0, while loop ends
    char temp_more_reviews;
    
    // adding node to the head of the linked list
    while(more_reviews){
        float temp_rating;
        string temp_comment;

        cout << "Enter review rating 0-5: ";
        Node *new_value = new Node; // Node *new_value is in loop as a new one has to get defined for each new node
        cin >> temp_rating;
        cout << "Enter review comments: ";
        cin.ignore();
        getline(cin, temp_comment);
    
        if (!head){ // if its the first node
            head = new_value;
            new_value->next = nullptr;
            new_value->rating = temp_rating;
            new_value->comments = temp_comment;
        }
        else{ // if its not the first node
            add_front_node(new_value, head, temp_comment, temp_rating);
            head = new_value; // head node is now the most recently added node
        }
        cout << "Enter another review? Y/N: ";
        cin >> temp_more_reviews;
        if ((temp_more_reviews == 'n') || (temp_more_reviews == 'N')){
            more_reviews = 0;
        }
    }

    // output is printing out correctly
    output(head);

    delete_linked_list(current, head);
    head = nullptr;
    // linked list is properly deallocated
    return 0;
}
