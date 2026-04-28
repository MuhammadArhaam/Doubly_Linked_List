#include <iostream>
#include<string>
using namespace std;
class Node 
{
public:
    int songID;
    string songName;
    float duration;
    Node* next;
    Node* prev;
    Node(int id, string name, float dur)
    {
        songID = id;
        songName = name;
        duration = dur;
        next = prev = NULL;
    }
};
class Playlist 
{
private:
    Node* head;
    Node* tail;
    Node* current;
public:
    Playlist() 
    {
        head = tail = current = NULL;
    }
    void addSong(int id, string name, float duration) 
    {
        Node* newNode = new Node(id, name, duration);
        if (!head) 
        {
            head = tail = current = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    void deleteSong(string name) 
    {
        if (!head) {
            cout << "Playlist is empty" << endl;
            return;
        }
        Node* temp = head;
        while (temp) 
        {
            if (temp->songName == name) 
            {
                if (temp == head)
                    head = head->next;
                if (temp == tail)
                    tail = tail->prev;
                if (temp->prev)
                    temp->prev->next = temp->next;
                if (temp->next)
                    temp->next->prev = temp->prev;
                if (temp == current)
                    current = temp->next ? temp->next : temp->prev;
                delete temp;
                cout << "Song deleted" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found" << endl;
    }
    void playNext()
    {
        if (!current) 
        {
            cout << "No songs available" << endl;
            return;
        }
        if (current->next)
        {
            current = current->next;
            cout << "Now Playing: " << current->songName << endl;
        }
        else 
        {
            cout << "Already at last song" << endl;
        }
    }
    void playPrevious() 
    {
        if (!current)
        {
            cout << "No songs available" << endl;
            return;
        }
        if (current->prev) 
        {
            current = current->prev;
            cout << "Now Playing: " << current->songName << endl;
        }
        else
        {
            cout << "Already at first song" << endl;
        }
    }
    void reversePlaylist()
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
        cout << "Playlist reversed" << endl;
    }
    void display() 
    {
        if (!head) 
        {
            cout << "Playlist is empty" << endl;
            return;
        }
        Node* temp = head;
        while (temp)
        {
            cout << "ID: " << temp->songID
                << ", Name: " << temp->songName
                << ", Duration: " << temp->duration << " mins" << endl;
            temp = temp->next;
        }
    }
};
int main() 
{
    Playlist p;
    int choice, id;
    string name;
    float duration;
    do 
    {
        cout << "------Playlist Manager------" << endl;
        cout << "1. Add Song" << endl;
        cout << "2. Delete Song" << endl;
        cout << "3. Play Next" << endl;
        cout << "4. Play Previous" << endl;
        cout << "5. Reverse Playlist (Shuffle)" << endl;
        cout << "6. Display Playlist" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) 
        {
        case 1:
            cout << "Enter Song ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Song Name: ";
            getline(cin, name);
            cout << "Enter Duration: ";
            cin >> duration;
            p.addSong(id, name, duration);
            break;
        case 2:
            cin.ignore();
            cout << "Enter Song Name to delete: ";
            getline(cin, name);
            p.deleteSong(name);
            break;
        case 3:
            p.playNext();
            break;
        case 4:
            p.playPrevious();
            break;
        case 5:
            p.reversePlaylist();
            break;
        case 6:
            p.display();
            break;
        case 0:
            cout << "Exiting" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);
    return 0;
}