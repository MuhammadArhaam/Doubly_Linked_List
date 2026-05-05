#include<iostream>
#include<string>
using namespace std;
struct event
{
    int id, threat, time;
    string ip;
    event* next;
    event* prev;
    event(int i, string ipaddr, int t, int tm)
    {
        id = i;
        ip = ipaddr;
        threat = t;
        time = tm;
        next = prev = NULL;
    }
};
class securitySystem
{
    event* head;
    event* tail;
    event* current;
public:
    securitySystem()
    {
        head = tail = current = NULL;
    }
    void addEvent(int id, string ip, int threat, int time)
    {
        event* e = new event(id, ip, threat, time);
        if (head == NULL)
        {
            head = tail = current = e;
            return;
        }
        event* temp = head;
        while (temp)
        {
            if (threat > temp->threat ||
                (threat == temp->threat && time > temp->time))
            {
                e->next = temp;
                e->prev = temp->prev;
                if (temp->prev)
                {
                    temp->prev->next = e;
                }
                else
                {
                    head = e;
                }
                temp->prev = e;
                return;
            }
            temp = temp->next;
        }
        e->prev = tail;
        tail->next = e;
        tail = e;
    }
    void view()
    {
        event* temp = head;
        while (temp)
        {
            cout << temp->ip << "(" << temp->threat << ") <=> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
    void detectAttack()
    {
        event* temp = head;
        int count = 1;
        while (temp && temp->next)
        {
            if (temp->ip == temp->next->ip)
            {
                count++;
                if (count == 3)
                {
                    cout << "Attack from IP: " << temp->ip << endl;
                }
            }
            else
            {
                count = 1;
            }
            temp = temp->next;
        }
    }
    void dangerousIP()
    {
        event* i = head;
        string ans = "";
        int maxSum = 0;
        while (i)
        {
            int sum = 0;
            event* j = head;
            while (j)
            {
                if (i->ip == j->ip)
                {
                    sum += j->threat;
                }
                j = j->next;
            }
            if (sum > maxSum)
            {
                maxSum = sum;
                ans = i->ip;
            }
            i = i->next;
        }
        cout << "Most Dangerous IP: " << ans << endl;
    }
};
int main()
{
    securitySystem s;
    s.addEvent(1, "192.168.1.1", 8, 100);
    s.addEvent(2, "192.168.1.1", 9, 101);
    s.addEvent(3, "192.168.1.1", 7, 102);
    s.addEvent(4, "10.0.0.1", 10, 103);
    s.view();
    s.detectAttack();
    s.dangerousIP();
    return 0;
}