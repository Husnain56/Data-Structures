#include <iostream>

using namespace std;

class Node
{

public:
    int info;
    Node *next;

    Node(int info_)
    {
        info = info_;
        next = nullptr;
    }

    ~Node()
    {
        next = nullptr;
    }
};

class CircularLinkedList
{

public:
    Node *head;
    int count;

public:
    CircularLinkedList()
    {
        head = nullptr;
        count = 0;
    }

    bool IsEmpty()
    {

        if (head == nullptr)
        {
            return true;
        }
        return false;
    }

    void InsertItem(int info_)
    {

        Node *n = new Node(info_);

        if (head == nullptr)
        {
            head = n;
            n->next = n;
            count++;
        }

        else
        {
            Node *current = head->next;
            Node *prev = head;
            bool flag = false;

            while (current != head && !flag)
            {

                if (current->info >= info_)
                {
                    flag = true;
                }
                else
                {
                    prev = current;
                    current = current->next;
                }
            }

            if (current == head)
            {

                if (head->info <= info_)
                {
                    n->next = head->next;
                    head->next = n;
                    head = n;
                }
                else if (head->info > info_)
                {
                    prev->next = n;
                    n->next = head;
                }
                count++;
            }

            else
            {

                prev->next = n;
                n->next = current;
                count++;
            }
        }
    }

    void Print()
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            cout << "Count: " << count << endl;
            return;
        }
        Node *temp = head->next;

        while (temp != head)
        {

            cout << temp->info << " ";
            temp = temp->next;
        }

        cout << head->info << endl;
    }

    void DestroyList()
    {

        Node *current = head->next;

        while (current != head)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
            temp = nullptr;
        }
        delete head;
        head = nullptr;
        cout << "List Destroyed" << endl;
        count = 0;
    }

    int getLength()
    {
        return count;
    }

    bool SearchList(int item)
    {

        if (head == nullptr)
        {
            cout << "List is empty" << endl;
        }
        else
        {

            Node *current = head->next;
            bool flag = false;

            while (current != head && !flag)
            {

                if (current->info >= item)
                {
                    flag = true;
                }
                else
                {
                    current = current->next;
                }
            }

            if (current->info == item)
            {
                cout << "Number found" << endl;
                return true;
            }
            else
            {
                cout << "Number not found" << endl;
                return false;
            }
        }
        return false;
    }

    void DeleteItem(int item)
    {

        Node *current = head->next;
        Node *prev = head;
        bool flag = false;

        if (head == nullptr)
        {
            cout << "List is empty" << endl;
        }
        else
        {

            while (current != head && !flag)
            {

                if (current->info >= item)
                {
                    flag = true;
                }
                else
                {
                    prev = current;
                    current = current->next;
                }
            }
            if (current == head)
            {
                if (head->info == item)
                {

                    prev->next = head->next;
                    head = prev;
                    delete current;
                    current = nullptr;
                    count--;
                }
            }
            else if (current->info == item)
            {
                prev->next = current->next;
                delete current;
                current == nullptr;
                count--;
            }
            else
            {
                cout << "Number not found" << endl;
            }
        }
    }

    void InitializeList()
    {
        head = nullptr;
    }

    void CopyList(CircularLinkedList &List)
    {

        if (List.head == nullptr)
        {
            cout << "Given List is empty" << endl;
            return;
        }
        
        InsertItem(List.head->info);
        Node * current = List.head->next;

        while(current!=List.head){
              
            InsertItem(current->info);  
            current = current->next;
        }
        cout<<"List copied successfully"<<endl;
    }
};
main()
{

    CircularLinkedList *List = new CircularLinkedList;

    List->InsertItem(1);
    List->InsertItem(10);
    List->InsertItem(15);
    List->InsertItem(20);
    List->InsertItem(15);
    List->InsertItem(25);
    List->Print();
    List->DeleteItem(10);
    List->Print();
    List->SearchList(9);

    CircularLinkedList *List1 = new CircularLinkedList;
    List1->CopyList(*List);
    List1->Print();

    return 0;
}