#include<iostream>
#include<string>
using namespace std;
class Node
{
public:
    int movieID;
    string movieName;
    float rating;
    Node* next;
    Node* prev;
    Node(int id, string name, float rate) 
    {
        movieID = id;
        movieName = name;
        rating = rate;
        next = prev = NULL;
    }
};
class Watchlist
{
private:
    Node* head;
    Node* tail;
    Node* current;
public:
    Watchlist() 
    {
        head = tail = current = NULL;
    }
    void addMovie(int id, string name, float rating);
    void removeMovie(string name);
    void playNext();
    void playPrevious();
    void reverseList();
    void display();
    void highestRated();
};
void Watchlist::addMovie(int id, string name, float rating) 
{
    Node* newNode = new Node(id, name, rating);
    if (!head) 
    {
        head = tail = current = newNode;
        return;
    }
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
}
void Watchlist::removeMovie(string name)
{
    Node* temp = head;
    while (temp) 
    {
        if (temp->movieName == name)
        {
            if (temp == head)
            {
                head = head->next;
            }
            if (temp == tail)
            {
                tail = tail->prev;
            }
            if (temp->prev)
            {
                temp->prev->next = temp->next;
            }
            if (temp->next)
            {
                temp->next->prev = temp->prev;
            }
            delete temp;
            return;
        }
        temp = temp->next;
    }
}
void Watchlist::playNext()
{
    if (current && current->next)
    {
        current = current->next;
    }
}
void Watchlist::playPrevious() 
{
    if (current && current->prev)
    {
        current = current->prev;
    }
}
void Watchlist::reverseList() 
{
    Node* temp = NULL;
    Node* curr = head;
    while (curr) 
    {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if (temp)
    {
        head = temp->prev;
    }
}
void Watchlist::highestRated() 
{
    if (!head)
    {
        return;
    }
    Node* temp = head;
    Node* best = head;
    while (temp)
    {
        if (temp->rating > best->rating)
        {
            best = temp;
        }
        temp = temp->next;
    }
    cout << "Highest Rated: " << best->movieName << endl;
}
void Watchlist::display() {
    Node* temp = head;

    if (!temp) {
        cout << "Watchlist is empty." << endl;
        return;
    }

    while (temp) {
        cout << temp->movieName << endl;
        temp = temp->next;
    }
}
int main() 
{
    Watchlist w;
    int choice, id;
    string name;
    float rating;
    do 
    {
        cout << "------Watchlist Manager------" << endl;
        cout << "1. Add Movie" << endl;
        cout << "2. Remove Movie" << endl;
        cout << "3. Play Next" << endl;
        cout << "4. Play Previous" << endl;
        cout << "5. Reverse Watchlist" << endl;
        cout << "6. Display Watchlist" << endl;
        cout << "7. Highest Rated Movie" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Rating: ";
            cin >> rating;
            w.addMovie(id, name, rating);
            break;
        case 2:
            cin.ignore();
            cout << "Enter Movie Name to delete: ";
            getline(cin, name);
            w.removeMovie(name);
            break;
        case 3:
            w.playNext();
            break;
        case 4:
            w.playPrevious();
            break;
        case 5:
            w.reverseList();
            break;
        case 6:
            w.display();
            break;
        case 7:
            w.highestRated();
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}