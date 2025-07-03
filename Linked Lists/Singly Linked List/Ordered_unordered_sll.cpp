#include <iostream>

using namespace std;

class Node
{

public:
    int data;
    Node *next;

    Node(int d)
    {
        data = d;
        next = nullptr;
    }

    ~Node()
    {
        delete next;
        next = nullptr;
    }
};

class LinkedListIterator
{

private:
    Node *current;

public:
    LinkedListIterator()
    {
        current = nullptr;
    }

    LinkedListIterator(Node *ptr)
    {
        current = ptr;
    }

    int operator*()
    {
        return current->data;
    }

    LinkedListIterator operator++()
    {
        current = current->next;
        return current;
    }

    bool operator==(LinkedListIterator *right)
    {

        return (current == right->current);
    }

    bool operator!=(LinkedListIterator *right)
    {

        return (this->current != right->current);
    }
};

class LinkedListType
{

protected:
    int count;
    Node *head;
    Node *tail;

public:
    LinkedListType()
    {
        count = 0;
        head = nullptr;
        tail = nullptr;
    }

    void copyList(LinkedListType &otherList)
    {

        if (otherList.head == nullptr)
        {
            cout << "Other list is empty" << endl;
            return;
        }

        if (head != nullptr)
        {
            destroyList();
        }
        head = nullptr;
        tail = nullptr;

        Node *temp = otherList.head;
        while (temp != nullptr)
        {

            Node *n = new Node(temp->data);
            if (head == nullptr)
            {

                head = n;
                tail = n;
            }
            else
            {
                tail->next = n;
                tail = n;
            }
            temp = temp->next;
        }
        count = otherList.count;
    }

    LinkedListType(LinkedListType &otherList)
    {
        copyList(otherList);
    }

    LinkedListType &operator=(LinkedListType &otherList)
    {
        copyList(otherList);
    }

    void InitializeList()
    {
        destroyList();
        count = 0;
        head = nullptr;
        tail = nullptr;
    }
    bool IsEmpty()
    {
        if (head == nullptr)
        {
            return true;
        }
        return false;
    }

    void Print()
    {

        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node *temp = head;
        cout << "Data in the list: " << endl;

        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
        temp = nullptr;
    }

    int length()
    {

        return count;
    }

    void destroyList()
    {

        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            temp->next = nullptr;
            delete temp;
            temp = nullptr;
        }
        tail = nullptr;
        count = 0;
        cout << "Linked List destroyed" << endl;
    }

    int front()
    {

        if (head == nullptr)
        {
            cout << "List is empty! returning -1" << endl;
            return -1;
        }
        return head->data;
    }

    int back()
    {

        if (tail == nullptr)
        {
            cout << "List is empty! returning -1" << endl;
            return -1;
        }
        return tail->data;
    }

    LinkedListIterator begin()
    {

        LinkedListIterator i(head);
        return i;
    }

    LinkedListIterator end()
    {
        LinkedListIterator i(tail);
        return i;
    }

    virtual bool Search(int) = 0;
    virtual void insertFirst(int) = 0;
    virtual void insertLast(int) = 0;
    virtual void deleteNode(int) = 0;

    ~LinkedListType()
    {
        destroyList();
        cout << "The list object is removed" << endl;
    }
};

class UnorderedLinkedList : public LinkedListType
{

public:
    bool Search(int searchItem)
    {

        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return false;
        }
        Node *temp = head;
        while (temp != nullptr)
        {

            if (temp->data == searchItem)
            {
                return true;
            }
            temp = temp->next;
        }
        temp = nullptr;
        return false;
    }

    void insertFirst(int d)
    {

        Node *n = new Node(d);
        if (head == nullptr)
        {
            head = n;
            tail = n;
        }
        else
        {
            n->next = head;
            head = n;
        }
        count++;
    }

    void insertLast(int d)
    {

        Node *n = new Node(d);

        if (head == nullptr)
        {
            head = n;
            tail = n;
        }
        else
        {

            tail->next = n;
            tail = n;
        }
        count++;
    }

    void deleteNode(int d)
    {

        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }

        Node *temp = head;
        Node *prev = nullptr;

        while (temp != nullptr)
        {

            if (temp->data == d)
            {
                if (temp == head)
                {
                    cout << "Node with data " << temp->data << " deleted successfully" << endl;
                    head = temp->next;
                    temp->next = nullptr;
                    delete temp;
                    count--;
                    return;
                }
                if (temp == tail)
                {
                    tail = prev;
                }
                prev->next = temp->next;
                cout << "Node with data " << temp->data << " deleted successfully" << endl;
                temp->next = nullptr;
                delete temp;
                count--;
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "The given value doesnt exist in the list" << endl;
    }
};

class OrderedLinkedList : public LinkedListType
{

public:
    bool Search(int d)
    {

        Node *temp = head;
        bool flag = false;

        while (temp != nullptr)
        {

            if (temp->data >= d)
            {
                flag = true;
            }
            else
            {
                temp = temp->next;
            }

            if (flag)
            {
                return (temp->data == d);
            }
        }

        return flag;
    }

    void Insert(int d)
    {

        Node *n = new Node(d);
        Node *current = head;
        Node *prev = nullptr;
        bool flag = false;

        if (head == nullptr)
        {
            head = n;
            tail = n;
            count++;
        }

        else
        {

            while (current != nullptr && !flag)
            {

                if (current->data >= d)
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
                n->next = head;
                head = n;
                count++;
            }
            else
            {

                prev->next = n;
                n->next = current;

                if (current == nullptr)
                {

                    tail = n;
                }
                count++;
            }
        }
    }

    void insertFirst(int d)
    {
        Insert(d);
    }
    void insertLast(int d)
    {
        Insert(d);
    }

    void deleteNode(int d)
    {

        Node *current = head;
        Node *prev = nullptr;
        bool flag = false;

        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }

        while (current != nullptr && flag)
        {

            if (current->data >= d)
            {
                flag = true;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }

        if (current == nullptr)
        {
            cout << "Item not in the list" << endl;
        }
        else if (current->data == d)
        {

            if (current == head)
            {
                head = head->next;
                current->next = nullptr;
                delete current;
                if (head == nullptr)
                {
                    tail = nullptr;
                }
            }
            else
            {
                prev->next = current->next;
                current->next = nullptr;
                if (current == tail)
                {
                    tail = prev;
                }
                delete current;
            }
            count--;
        }
        else
        {
            cout << "Item not in the list" << endl;
        }
    }
};

int main()
{
   
    //Unordered test
    LinkedListType *list = new UnorderedLinkedList;

    list->insertFirst(10);
    list->insertLast(20);
    list->insertLast(30);
    list->insertLast(40);

    list->Print();
    cout << "Length of the list: " << list->length() << endl;
    list->deleteNode(10);
    list->Print();
    list->deleteNode(40);
    list->Print();

    if (list->Search(50))
    {
        cout << "Found" << endl;
    }
    else
    {
        cout << "Not found" << endl;
    }

    list->insertLast(30);
    list->insertLast(40);

    LinkedListType *listt = new UnorderedLinkedList;
    listt->copyList(*list);
    listt->Print();
    listt->destroyList();
    list->destroyList();
    

    //Ordered Test
    OrderedLinkedList list1, list2; // Line 5
    int num;                        // Line 6
    cout << "Line 7: Enter numbers ending "
         << "with -999." << endl; // Line 7
    cin >> num;                   // Line 8
    while (num != -999)           // Line 9
    {                             // Line 10
        list1.Insert(num);        // Line 11
        cin >> num;               // Line 12
    } // Line 13
    cout << endl;               // Line 14
    cout << "Line 15: list1: "; // Line 15
    list1.Print();              // Line 16
    cout << endl;               // Line 17
    list2 = list1;              // test the assignment operator Line 18
    cout << "Line 19: list2: "; // Line 19
    list2.Print();              // Line 20
    cout << endl;               // Line 21
    cout << "Line 22: Enter the number to be "
         << "deleted: ";                                              // Line 22
    cin >> num;                                                       // Line 23
    cout << endl;                                                     // Line 24
    list2.deleteNode(num);                                            // Line 25
    cout << "Line 26: After deleting " << num << ", list2: " << endl; // Line 26
    list2.Print();                                                    // Line 27
    cout << endl;                                                     // Line 28
                                                                      // Line 29

    return 0;
}