#include <iostream>
#include <string>
using namespace std;
class Player 
{
public:
    int playerID;
    int score;
    Player* next;
    Player(int id, int s) 
    {
        playerID = id;
        score = s;
        next = NULL;
    }
};
class Game 
{
private:
    Player* tail;
    Player* current;
public:
    Game() {
        tail = current = NULL;
    }
    void addPlayer(int id, int score) 
    {
        Player* newPlayer = new Player(id, score);
        if (!tail) 
        {
            tail = newPlayer;
            tail->next = tail;
            current = tail;
            return;
        }
        newPlayer->next = tail->next;
        tail->next = newPlayer;
        tail = newPlayer;
    }
    void removePlayer(int id)
    {
        if (!tail) 
        {
            cout << "No players in game" << endl;
            return;
        }
        Player* curr = tail->next;
        Player* prev = tail;
        do {
            if (curr->playerID == id)
            {
                if (curr == tail && curr->next == tail)
                {
                    delete curr;
                    tail = current = NULL;
                    cout << "Last player removed. Game over" << endl;
                    return;
                }
                prev->next = curr->next;
                if (curr == tail)
                {
                    tail = prev;
                }
                if (curr == current)
                {
                    current = curr->next;
                }
                delete curr;
                cout << "Player removed" << endl;
                return;
            }
            prev = curr;
            curr = curr->next;

        } while (curr != tail->next);

        cout << "Player not found" << endl;
    }
    void nextTurn()
    {
        if (!current)
        {
            cout << "No players available" << endl;
            return;
        }
        current = current->next;
        cout << "Current Player: " << current->playerID << endl;
    }
    void skipTurn() 
    {
        if (!current || !current->next)
        {
            return;
        }
        current = current->next->next;
        cout << "Skipped! Now Player: " << current->playerID << endl;
    }
    void display() 
    {
        if (!tail) 
        {
            cout << "No players in game" << endl;
            return;
        }
        Player* temp = tail->next;
        do 
        {
            cout << "Player ID: " << temp->playerID
                << ", Score: " << temp->score << endl;
            temp = temp->next;
        } while (temp != tail->next);
    }
    void checkWinner() 
    {
        if (tail && tail->next == tail)
        {
            cout << "Winner is Player " << tail->playerID << endl;
        }
    }
};
int main()
{
    Game g;
    int choice, id, score;
    do 
    {
        cout << "------Multiplayer Game------" << endl;
        cout << "1. Add Player" << endl;
        cout << "2. Remove Player" << endl;
        cout << "3. Next Turn" << endl;
        cout << "4. Skip Turn" << endl;
        cout << "5. Display Players" << endl;
        cout << "6. Check Winner" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter Player ID: ";
            cin >> id;
            cout << "Enter Score: ";
            cin >> score;
            g.addPlayer(id, score);
            break;
        case 2:
            cout << "Enter Player ID to remove: ";
            cin >> id;
            g.removePlayer(id);
            break;
        case 3:
            g.nextTurn();
            break;
        case 4:
            g.skipTurn();
            break;
        case 5:
            g.display();
            break;
        case 6:
            g.checkWinner();
            break;
        case 0:
            cout << "Exiting game" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);
    return 0;
}