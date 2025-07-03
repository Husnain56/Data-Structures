#include <iostream>

using namespace std;

class Node
{

public:
    int data;
    Node *ptr;

    Node(int d)
    {
        data = d;
        ptr = nullptr;
    }

    ~Node()
    {

        delete ptr;
        ptr = nullptr;
        cout << "Node successfully deleted" << endl;
    }
};

void InsertatHead(Node *&head, Node *&tail, int d)
{
    if (head == nullptr)
    {
        Node *n = new Node(d);
        head = n;
        tail = n;
    }
    else
    {
        Node *n = new Node(d);
        n->ptr = head;
        head = n;
    }
}

void InsertatTail(Node *&head, Node *&tail, int d)
{
    if (tail == nullptr)
    {
        Node *n = new Node(d);
        head = n;
        tail = n;
    }
    else
    {
        Node *n = new Node(d);
        tail->ptr = n;
        tail = n;
    }
}

void InsertatPosition(Node *&head, Node *&tail, int position, int d)
{

    if (position == 1)
    {
        InsertatHead(head, tail, d);
        return;
    }
    Node *temp = head;
    int count = 1;

    while (count < position - 1)
    {
        temp = temp->ptr;
        count++;
    }

    if (temp->ptr == nullptr)
    {
        InsertatTail(head, tail, d);
        return;
    }

    Node *n = new Node(d);
    n->ptr = temp->ptr;
    temp->ptr = n;
}

void deleteNode(int pos, Node *&head, Node *&tail)
{

    if (pos == 1)
    {
        Node *temp = head;
        head = head->ptr;
        temp->ptr = nullptr;
        delete temp;
    }
    else
    {
        int count = 1;
        Node *curr = head;
        Node *prev = nullptr;

        while (count < pos)
        {
            prev = curr;
            curr = curr->ptr;
            count++;
        }
        prev->ptr = curr->ptr;
        if (prev->ptr == nullptr)
        {
            tail = prev;
        }
        curr->ptr = nullptr;
        delete curr;
    }
}

void Print(Node *head)
{

    while (head != nullptr)
    {
        cout << head->data << " ";
        head = head->ptr;
    }
    cout << endl;
}

int main()
{

    Node *n1 = new Node(30);
    Node *head = n1;
    Node *tail = n1;

    Print(head);
    InsertatHead(head, tail, 20);
    Print(head);
    InsertatHead(head, tail, 10);
    Print(head);
    cout << "tail: " << tail->data << endl;

    InsertatTail(head, tail, 50);
    InsertatTail(head, tail, 60);
    Print(head);

    InsertatPosition(head, tail, 6, 40);
    Print(head);
    cout << "head: " << head->data << endl;
    cout << "tail: " << tail->data << endl;

    deleteNode(6, head, tail);
    Print(head);
    cout << "head: " << head->data << endl;
    cout << "tail: " << tail->data << endl;

    return 0;
}