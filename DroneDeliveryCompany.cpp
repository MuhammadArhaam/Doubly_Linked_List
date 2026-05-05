#include<iostream>
#include<string>
using namespace std;
struct package
{
    int id, distance;
    string dest, priority, status;
    package* next;
    package* prev;
    package(int i, string d, int dist, string p, string s)
    {
        id = i;
        dest = d;
        distance = dist;
        priority = p;
        status = s;
        next = prev = NULL;
    }
};
class droneSystem
{
    package* head;
    package* tail;
    package* current;
    int priorityValue(string p)
    {
        if (p == "High")
        {
            return 3;;
        }
        if (p == "Medium")
        {
            return 2;
        }
        return 1;
    }
public:
    droneSystem()
    {
        head = tail = current = NULL;
    }
    void addPackage(int id, string dest, int dist, string pr, string st)
    {
        package* newp = new package(id, dest, dist, pr, st);
        if (head == NULL)
        {
            head = tail = current = newp;
            return;
        }
        package* temp = head;
        while (temp != NULL)
        {
            if (priorityValue(pr) > priorityValue(temp->priority) ||
                (priorityValue(pr) == priorityValue(temp->priority) && dist < temp->distance))
            {
                newp->next = temp;
                newp->prev = temp->prev;
                if (temp->prev != NULL)
                {
                    temp->prev->next = newp;
                }
                else
                {
                    head = newp;
                }
                temp->prev = newp;
                return;
            }
            temp = temp->next;
        }
        newp->prev = tail;
        tail->next = newp;
        tail = newp;
    }
    void view()
    {
        package* temp = head;
        while (temp != NULL)
        {
            cout << temp->id << "(" << temp->priority << "," << temp->distance << ") <=> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
    void currentPackage()
    {
        if (current != NULL)
        {
            cout << "Current Delivery: " << current->dest << endl;
        }
    }
    void nextDelivery()
    {
        if (current && current->next)
        {
            current = current->next;
            cout << "Now delivering: " << current->dest << endl;
        }
        else
        {
            cout << "No next delivery" << endl;
        }
    }
    void prevDelivery()
    {
        if (current && current->prev)
        {
            current = current->prev;
            cout << "Back to: " << current->dest << endl;
        }
        else
            cout << "No previous delivery" << endl;
    }
    void reinsert()
    {
        if (!current)
        {
            return;
        }
        package* temp = current;
        if (temp == head)
        {
            head = head->next;
            if (head)
            {
                head->prev = NULL;
            }
        }
        else if (temp == tail)
        {
            tail = tail->prev;
            tail->next = NULL;
        }
        else
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        current = head;
        addPackage(temp->id, temp->dest, temp->distance, temp->priority, temp->status);
    }
    void reverseLow()
    {
        package* temp = head;
        while (temp)
        {
            if (temp->priority == "Low")
            {
                package* start = temp;
                while (temp && temp->priority == "Low")
                {
                    temp = temp->next;
                }
                package* prev = temp;
                package* curr = start;
                while (curr != temp)
                {
                    package* next = curr->next;
                    curr->next = prev;
                    curr->prev = next;
                    prev = curr;
                    curr = next;
                }
            }
            else
            {
                temp = temp->next;
            }
        }
    }
};
int main()
{
    droneSystem d;
    d.addPackage(1, "Lahore", 10, "High", "Pending");
    d.addPackage(2, "Karachi", 30, "Low", "Pending");
    d.addPackage(3, "Islamabad", 20, "Medium", "Pending");
    d.view();
    d.currentPackage();
    d.nextDelivery();
    d.prevDelivery();
    cout << endl;
    cout << "After failure reinsertion: " << endl;
    d.reinsert();
    d.view();
    cout << endl;
    cout << "After reversing low priority: " << endl;
    d.reverseLow();
    d.view();
    return 0;
}