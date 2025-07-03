#include <iostream>

using namespace std;

class Node
{

public:
    int data;
    Node *prev;
    Node *next;

    Node(int d)
    {

        data = d;
        prev = nullptr;
        next = nullptr;
    }
    ~Node(){
        cout<<"Deleting node with value: "<<this->data<<endl;
        delete prev;
        delete next;
        prev = nullptr;
        next = nullptr;
    }
};

void InsertAtHead(Node *&head , Node *&tail, int d)
{
    if (head == nullptr)
    {
        Node *n = new Node(d);
        head = n;
        tail = n;
    }
    else
    {
        Node *temp = head;
        Node *n = new Node(d);
        head = n;
        n->next = temp;
        temp->prev = n;
    }
}

void InsertAtTail(Node*&head , Node *&tail, int d)
{

    if (tail == nullptr)
    {
        Node *n = new Node(d);
        tail = n;
        head = n;
    }
    else
    {
        Node *temp = tail;
        Node *n = new Node(d);
        tail = n;
        temp->next = n;
        n->prev = temp;
    }
}

void InsertAtPosition(int pos, Node *&head, Node *&tail, int d)
{
    if (pos == 1)
    {
        InsertAtHead(head , tail , d);
        return;
    }

    Node *n = new Node(d);
    Node *temp = head;
    int count = 1;

    while (count < pos - 1)
    {

        temp = temp->next;
        count++;
    }

    if (temp->next == nullptr)
    {
        InsertAtTail(head, tail, d);
        return;
    }

    Node *t = temp->next;
    n->next = t;
    n->prev = temp;
    temp->next = n;
    t->prev = n;
}

void Print(Node *head)
{

    while (head != nullptr)
    {

        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int getLength(Node *head)
{

    int count = 0;
    while (head != nullptr)
    {
        head = head->next;
        count++;
    }
    return count;
}

void deleteNode(int pos, Node * &head , Node * &tail){
     
     if(pos==1){

        Node * temp = head;
        head = head -> next;
        head->prev = nullptr;
        temp->next = nullptr;
        temp->prev = nullptr;
        delete temp;
     }
     else{

        int count = 1;
        Node * curr = head;
        Node * prev = nullptr;

        while(count<pos){
            prev = curr;
            curr = curr->next;
            count++;
        }
        prev->next = curr->next;
        if(curr->next!=nullptr){
            curr->next->prev = prev;
        }
        if(prev->next==nullptr){
            tail = prev;
        }
        curr->next = nullptr;
        curr->prev = nullptr;
        delete curr;
     }
}

int main()
{

    Node *n = new Node(20);
    Node *head = n;
    Node *tail = n;

    Print(head);
    InsertAtHead(head , tail , 10);
    Print(head);

    InsertAtTail(head,tail, 40);
    Print(head);

    InsertAtPosition(3, head, tail, 30);
    Print(head);

    InsertAtPosition(4, head, tail, 50);
    Print(head);

    deleteNode(5,head,tail);
     Print(head);
    cout << "Head: " << head->data << endl;
    cout << "Tail: " << tail->data << endl;
    cout << "Length of the doubly linked list: " << getLength(head) << endl;

    return 0;
}