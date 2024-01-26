// list standard header

#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
    ListNode* next;  // successor node, or first element if head
    ListNode* prev;  // predecessor node, or last element if head
    ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
    using node = ListNode< Ty >;
    using nodePtr = node*;

    using value_type = Ty;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    ListVal() // initialize data
        : myHead(),
        mySize(0)
    {
    }

    nodePtr myHead; // pointer to head node
    size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
    using node = ListNode< Ty >;
    using nodePtr = node*;
    using ScaryVal = ListVal< Ty >;

public:
    using value_type = Ty;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    using iterator = node*;
    using const_iterator = const node*;

    // empty container constructor (default constructor)
    // Constructs an empty container, with no elements.
    list()
        : myData()
    {
        myData.myHead = new node;
        myData.myHead->myVal = Ty();
        myData.myHead->prev = myData.myHead->next = myData.myHead;
    }

    // fill constructor
    // Constructs a container with "count" elements.
    // Each element is initialized as 0.
    list(size_type count) // construct list from count * Ty()
        : myData()
    {
        myData.myHead = new node;
        myData.myHead->myVal = Ty();
        myData.myHead->prev = myData.myHead->next = myData.myHead;

        if (count > 0)
            for (size_type i = 0; i < count; ++i)
                push_back(Ty());
    }

    // copy constructor
    // Constructs a container with a copy of each of the elements in "right",
    // in the same order.
    list(const list& right)
        : myData()
    {   
        myData.myHead = new node;
        myData.myHead->myVal = Ty();
        myData.mySize = right.myData.mySize;
        nodePtr temp = myData.myHead; nodePtr rtemp = right.myData.myHead->next; //set the node pointer
        for (size_t i = 0; i < right.myData.mySize; i++)
        {
            nodePtr nextN = new node;
            nextN->myVal = rtemp->myVal; nextN->prev = temp;
            temp->next = nextN; temp = nextN; rtemp = rtemp->next;
        }
        temp->next = myData.myHead;
        myData.myHead->prev = temp;
    }

    // List destructor
    // Destroys the container object.
    // Deallocates all the storage capacity allocated by the list container.
    ~list()
    {
        clear();
        delete myData.myHead;
    }

    // Assigns new contents to the container, replacing its current contents,
    // and modifying its size accordingly.
    // Copies all the elements from "right" into the container
    // (with "right" preserving its contents).
    list& operator=(const list& right)
    {   

        if (this != &right)
        {   
            
            resize(right.myData.mySize);
            nodePtr temp = myData.myHead->next; nodePtr rtemp = right.myData.myHead->next; //set the node pointer
            for (size_t i = 0; i <myData.mySize; i++)
            {
                temp->myVal = rtemp->myVal;
                temp = temp->next; rtemp = rtemp->next;
            }
        }
        return *this;
    }

    // Returns an iterator pointing to the first element in the list container.
    // If the container is empty, the returned iterator value shall not be dereferenced.
    iterator begin()
    {
        return iterator(myData.myHead->next);
    }

    // Returns an iterator pointing to the first element in the list container.
    // If the container is empty, the returned iterator value shall not be dereferenced.
    const_iterator begin() const
    {
        return const_iterator(myData.myHead->next);
    }

    // Returns an iterator referring to the past-the-end element in the list container.
    // The past-the-end element is the theoretical element
    // that would follow the last element in the list container.
    // It does not point to any element, and thus shall not be dereferenced.
    // If the container is empty, this function returns the same as list::begin.
    iterator end()
    {
        return iterator(myData.myHead);
    }

    // Returns an iterator referring to the past-the-end element in the list container.
    // The past-the-end element is the theoretical element
    // that would follow the last element in the list container.
    // It does not point to any element, and thus shall not be dereferenced.
    // If the container is empty, this function returns the same as list::begin.
    const_iterator end() const
    {
        return const_iterator(myData.myHead);
    }

    // Resizes the container so that it contains "newSize" elements.
    // If "newSize" is smaller than the current container size,
    // the content is reduced to its first "newSize" elements,
    // removing those beyond( and destroying them ).
    // If "newSize" is greater than the current container size,
    // the content is expanded by inserting at the end
    // as many elements as needed to reach a size of "newSize".
    // The new elements are initialized as 0.
    void resize(size_type newSize)
    {
        if (myData.mySize < newSize) // pad to make larger
        {
            size_type difference = newSize - myData.mySize;
            for (size_type i = 0; i < difference; i++) // create newSize - myData.mySize elements
                push_back(Ty());
        }
        else
        {
            while (newSize < myData.mySize)
                pop_back();
        }
    }

    // Returns the number of elements in the list container.
    size_type size() const
    {
        return myData.mySize;
    }

    // Returns whether the list container is empty (i.e. whether its size is 0).
    bool empty() const
    {
        return myData.mySize == 0;
    }

    // Returns a reference to the first element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    reference front()
    {
        return myData.myHead->next->myVal;
    }

    // Returns a reference to the first element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    const_reference front() const
    {
        return myData.myHead->next->myVal;
    }

    // Returns a reference to the last element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    reference back()
    {
        return myData.myHead->prev->myVal;
    }

    // Returns a reference to the last element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    const_reference back() const
    {
        return myData.myHead->prev->myVal;
    }

    // Inserts a new element at the beginning of the list,
    // right before its current first element.
    // The content of val is copied (or moved) to the inserted element.
    // This effectively increases the container size by one.
    void push_front(const Ty& val)
    {
        nodePtr front = new node; front->myVal = val; 
        front->prev = myData.myHead;
        front->next = myData.myHead->next;
        myData.myHead->next->prev = front; myData.myHead->next = front; myData.mySize += 1;

    }

    // Removes the first element in the list container,
    // effectively reducing its size by one.
    // This destroys the removed element.
    void pop_front()
    {
        if (myData.mySize > 0)
        {
            nodePtr front = myData.myHead->next;
            front->prev->next = front->next;
            front->next->prev = front->prev;
            delete front; myData.mySize -= 1;
        }
    }

    // Adds a new element at the end of the list container,
    // after its current last element.
    // The content of val is copied (or moved) to the new element.
    // This effectively increases the container size by one.
    void push_back(const Ty& val)
    {
        nodePtr back = new node; back->myVal = val;
        back->next = myData.myHead;
        back->prev = myData.myHead->prev;
        myData.myHead->prev->next = back; myData.myHead->prev = back; myData.mySize += 1;
    }

    // Removes the last element in the list container,
    // effectively reducing the container size by one.
    void pop_back()
    {
        if (myData.mySize > 0)
        {
            nodePtr temp;
            temp = myData.myHead->prev;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp; myData.mySize -= 1;
        }
    }

    // Removes all elements from the list container (which are destroyed),
    // and leaving the container with a size of 0.
    void clear() // erase all
    {
        if (myData.mySize != 0) // the list is not empty
        {
            nodePtr c = myData.myHead->next;
            while ( c != myData.myHead)
            {
                nodePtr temp = c;
                c = c->next;
                delete temp;
            }
            myData.mySize = 0;
        }
    }
private:
    ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==(const list< Ty >& left, const list< Ty >& right)
{   
    if (left.myData->mySize != right.myData->mySize)
        return false;
    list::nodePtr firstL = left.myData->myHead->next; list::nodePtr firstR = left.myData->myHead->next;
    
    for (; left.myData.myHead != firstL; firstL = firstL->next , firstR = firstR->next)
    {
        if ((firstL->myVal != firstR->myVal))
            return false;
    }
    return true;
    
}

template< typename Ty >
bool operator!=(const list< Ty >& left, const list< Ty >& right)
{
    return !(left == right);
}

#endif // LIST