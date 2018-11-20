//by Miguel Dominguez helped by Ricardo
#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "../AVLPROJ/ArgumentManager.h"

//node cstruct for all the follwowing
template <class Type>
struct nodeType{
    Type info;
    nodeType<Type> *next;
};
///////////////////////////////////////////////////////////////////////////////
//book  database  for inherentence ////////////////////////////////////////////////////////////////////////////////
template <class Type>
class BookList{
private:
    nodeType<Type> * head;
public:
    bool emptyList() const ;
    Type size() const;
    void insert(string newElement, int pos, nodeType<Type> *&head);
    Type remove(const Type &pos, bool &success, nodeType<Type> *&head );
    Type retrive(const Type &pos, bool &success, nodeType<Type> *&head );

};



// checks to see if the list is empty
template < class Type>
bool BookList<Type>::emptyList() const {
    return(head == NULL);
}

// checks the size of the list
template <class Type>
Type BookList<Type>::size() const {
    nodeType<Type> *link =head;
    int counter = 0;
    while(link !=NULL){
        counter++;
        link = link->next;
    }
    return counter;
}

//inserts at position
template < class Type>
void  BookList<Type>::insert(string newElement, int pos, nodeType<Type> *&head) {
    nodeType<Type> *curr = 0;
    nodeType<Type> *temp = 0;
    nodeType<Type> *follower = 0;
    int counter = 0;
    temp->info = newElement;
    temp->next = 0;

    if (pos == 0) {
        temp->next = head;
        head = temp;
    } else {
        curr = head;
        while (curr->next != NULL && counter != pos - 1) {
            if(head ==0){
                cout << "no list to go through";
                break;
            }
            counter++;
            curr = curr->next;
        }
        follower = curr->next;
        curr->next = temp;
        temp->next = follower;
    }
}
// retrives book back from the list
template <class Type>
Type BookList<Type>::retrive(const Type &pos, bool &success, nodeType<Type> *&head) {
    int counter =0;
    string book;
    nodeType<Type> *current;
    if(!empty(head)) {

        int counter = 1;
        nodeType<Type> *temp = head;
        if(pos==0)
        {
            book = head->bookName;
            return book;
        }
        while(temp->next != NULL && counter >= pos)
        {
            temp = temp->next;
            counter++;
        }
        if(counter==pos)
        {
            book = temp->bookName;
            return book;
        }
    }
    return "NULL";
}

/// removes book from the list
template <class Type>
Type BookList<Type>::remove(const Type &pos, bool &success, nodeType<Type> *&head) {
    int counter =0;
    string book;
    nodeType<Type> *current=0;
    nodeType<Type> *temp=0;
    if(!empty(head)) {


        if (pos == 0) {
            success == true;
            current = head;
            book = head->info;
            head = head->next;
            delete (current);
            return book;
        } else {
            for (counter = 0; counter < pos - 1; counter++) {
                current = current->next;

            }
            success == true;
            book = current->info;
            temp = current->next;
            current->next = temp->next;
            delete (temp);
            return book;
        }
    }
    return "NULL";
}

///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
template <class Type>
class queueADT{
public:
    virtual bool isEmptyQueue() const = 0;
    virtual bool isFullQueue() const = 0;
    virtual void initializeQueue() = 0;
    virtual Type front() const = 0;
    virtual Type back() const = 0;
    virtual void addQueue(const Type &queueElement) = 0;
    virtual void delFromQ() = 0;


};



template <class Type>
class linkedQueueType:public BookList<Type>, public queueADT<Type> {
public:
    const linkedQueueType<Type>& operator=(const linkedQueueType<Type> &);
    bool isEmptyQueue() const ;
    bool isFullQueue() const ;
    void initializeQueue() ;
    bool inQueue(const Type &element);
    Type front() const ;
    Type back() const ;
    void addQueue(const Type &queueElement);
    void delFromQ();
    void build(const string &infilename);
    int QueueSale(const Type &element);
    void printToFile();
    void reverse(int spot, int count);// helped by Logan Fortune.
    linkedQueueType();
    linkedQueueType(const linkedQueueType<Type> & otherQueue);
    ~linkedQueueType();

private:
    nodeType<Type> *qFront;// pointer to the front
    nodeType<Type> *qRear; // ponter to the rear

};
//Checks to see if the stack is empty
template < class Type>
bool linkedQueueType<Type>::isEmptyQueue() const {
    return(qFront == NULL);

}
//Checks to see if the stack is full
template < class Type>
bool linkedQueueType<Type>::isFullQueue() const {
    return false;
}
template <class Type>
bool  linkedQueueType<Type>::inQueue(const Type &element)
{
    nodeType<Type> *temp = qFront;
    while (temp != NULL)
    {
        if (temp->info == element)
        {
            return true;
        }

        else
        {
            temp = temp->next;
        }
    }
    return false;
}
//prints Queue
template < class Type>
void linkedQueueType<Type>::printToFile()
{
    nodeType<Type> *temp;
    temp = qFront;
    while (temp != NULL)
    {
        cout << temp->info << " ";
        temp = temp->next;
    }
    cout << endl;
}


//initializes the stack
template < class Type>
void  linkedQueueType<Type>::initializeQueue() {
    nodeType<Type> *temp;
    while (qFront != NULL){
        temp = qFront;
        qFront= qFront->next;
        delete temp;

    }
    qRear= NULL;
}

//adds to the Queue
template < class Type>
void  linkedQueueType<Type>::addQueue(const Type &newElement) {
    nodeType<Type> * addNode;
    addNode =  new nodeType<Type>;
    addNode->info = newElement;
    addNode->next = NULL;
    if (qFront == NULL){
        qFront = addNode;
        qRear = addNode;

    }
    else{
        qRear->next = addNode;
        qRear = qRear->next;

    }
}
//displays the front of the queue
template <class Type>
Type linkedQueueType<Type>::front() const {
    assert(qFront != NULL);
    return qFront->info;
    //returns the info of the front of the queue

}

//its a circur queue this returns the end of the queue
template <class Type>
Type linkedQueueType<Type>::back() const {
    assert(qRear !=NULL);
    return qRear->info;
    //returns the info of the back of the queue
}
template <class Type> // helped by logan fortune in the reverser
void linkedQueueType<Type>::reverse(int pos, int counter)
{
    while(counter < pos)
    {
        if(qFront==NULL)
        {
            return;
        }
        string tempName = qFront->bookName;
        qFront(tempName);
        counter++;
        insert(tempName, size(qFront), qFront);
    }
}


//deletes from the front of theQ
template <class Type>
void linkedQueueType<Type>::delFromQ() {
    nodeType<Type> *temp;
    if(!isEmptyQueue()){
        if(qFront ==NULL){
            qRear = NULL; }
        temp = qFront;
        string bookQueue;
        bookQueue += temp->info;
        qFront = qFront->next;
        delete temp;
        cout << " " << bookQueue << endl;
    }
    else
        cout << "Cannot remove from an empty queue" <<endl;

}
template <class Type>
int linkedQueueType<Type>::QueueSale(const Type &element)
{
    if (inQueue(element)) {
        nodeType<Type> *temp;
        if (qFront->info == element) {
            int cost = 1;
            cout << "Finding " << element << " finding cost at stack: , at queue: " << cost << endl;
            printToFile();
            delFromQ();
            return cost;
        } else {
            temp = qFront;
            int cost = 1;

            while (temp != NULL && temp->info != element) {
                temp = temp->next;
                cost++;
            }

            cout << "Finding " << element << " finding cost at stack: , at queue: " << cost << endl;
            printToFile();

            for (int i = 0; i < cost; i++) {
                addQueue(front());
                delFromQ();
                printToFile();
            }
            delFromQ();
            return cost;
        }

    }
    else
    {
        return 0;
    }

}



template <class Type>
linkedQueueType<Type>::linkedQueueType() {
    qFront = NULL; // set fron to nullq
    qRear = NULL;

}
//deconstructs the queue
template <class Type>
linkedQueueType<Type>::~linkedQueueType()  {
    initializeQueue();
};

////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//Stack it inheretes from BookList//////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
class StackADT{
public:
    virtual bool isEmptyStack() const =0;
    virtual bool isFullStack() const= 0;
    virtual void initializeStack()=0;
    virtual  void push(const Type &newItem)=0;
    virtual void pop()=0;
    virtual Type top() const=0;
};

template <class Type>
class linkedStackType:public StackADT <Type>,public linkedQueueType<Type> {
public:
    const linkedStackType<Type> &operator=(const linkedStackType<Type>&);
    bool isEmptyStack() const;
    bool isFullStack() const;
    bool inStack(const Type &element);
    void initializeStack();
    void  reverseStack();
    void printS();
    void reverser(int pos, int counter);
    int remove(string p);
    void push(const Type &newItem);
    void pop();
    int stackSale(const Type &element);
    Type top() const;
    Type last() const;
    linkedStackType();
    linkedStackType(const linkedStackType<Type> &otherStack);
    ~linkedStackType();

private:
    nodeType<Type> *stackTop;
    void copyStack(const linkedStackType<Type> &otherStack);
    void ReversecopyStack(const linkedStackType<Type> &otherStack);

};
// sets stack top to null
template<class Type>
linkedStackType<Type>::linkedStackType() {
    stackTop= NULL;

};

// checks to see if stack is empty
template<class Type>
bool linkedStackType<Type>::isEmptyStack() const {
    return (stackTop==NULL);

};

//checks to see if stack is full(HINT : ITS NEVER FULL WITH LINKED LIST
template <class Type>
bool linkedStackType<Type>::isFullStack() const {
    return false;

};
// initializes the stack top
template<class Type>
void linkedStackType<Type>::initializeStack(){
    nodeType<Type> *temp;
    while(stackTop != NULL){
        temp= stackTop;
        stackTop = stackTop->next;

        delete temp;

    }

};

//pushs the element back to the end of the stack
template <class Type>
void linkedStackType<Type>::push(const Type &newElement) {
    nodeType<Type> *newNode;// pointer to create the new node
    newNode = new nodeType<Type>; //create node
    newNode->info = newElement;
    newNode->next = stackTop;
    stackTop = newNode;

};
template <class Type>
void linkedStackType<Type>::reverser(int pos, int counter)
{
    if(stackTop==NULL || counter>=pos)
    {
        return;
    }
    else
    {
        string tempStr = stackTop->info;
        remove(tempStr);
        counter++;
        reverser(pos, counter);
        insert(tempStr, pos, stackTop);
    }
}

//Type top
template <class Type>
Type linkedStackType<Type>::top() const {
    assert(stackTop!= NULL);
    return  stackTop->info;

};

template <class Type>
Type linkedStackType<Type>::last() const
{
    nodeType<Type> *temp;
    temp = stackTop;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    return temp->info;
}

//deletes the top of the stack// ALSO HAS THE FUNCTION TO SAVE EVERYTHING ITS DELETING INTO A STRING
template <class Type>
void linkedStackType<Type>::pop() {
    if (stackTop != NULL) {
        nodeType<Type> *temp;
        temp = stackTop;
        string bookStack;
        bookStack +=  temp->info;
        stackTop = stackTop->next;
        cout  <<" " << bookStack << endl;
        delete temp;
    } else
        std::cout << "Cannot remove from an empty stack" << std::endl;
};
template <class Type>
void linkedStackType<Type>::copyStack(const linkedStackType<Type> &otherStack) {
    nodeType<Type> *newNode, *current, *last;
    if (stackTop !=NULL){ // if stack is not empty make it empty
        initializeStack();
    }
    if(otherStack.stackTop == NULL)
        stackTop = NULL;
    else {
        current = otherStack.stackTop; //set current to point to the stack to be copied

        //Now copy the stackTop element of the stack
        stackTop = new nodeType<Type>;// create a node
        stackTop->info = current->info; //copy the info
        stackTop->next = NULL; // set next field to NULL
        last = stackTop;
        current = current->next; // set current to point to next

        //copy rest of stack
        while (current != NULL) {
            newNode = new nodeType<Type>;
            newNode->info = current->info;
            newNode->next = NULL;
            last->next = newNode;
            last = newNode;
            current = current->next;
        }
    }
};
//copy constructors
template<class Type>
linkedStackType<Type>::linkedStackType(const linkedStackType<Type> &otherStack) {
    stackTop= NULL;
//    copyStack(otherStack);
    ReversecopyStack(otherStack);

};


template <class Type>
const linkedStackType<Type>& linkedStackType<Type>::operator=(
        const linkedStackType<Type> &otherStack) {
    if (this != &otherStack)  // avoid self copy
        copyStack(otherStack);

    return *this;

}
template <class Type>
void linkedStackType<Type>::printS()
{
    nodeType<Type> *temp;
    temp = stackTop;

    while (temp != NULL)
    {
        cout << temp->info << endl;
        temp = temp->next;
    }
}

template <class Type>
int linkedStackType<Type>::stackSale(const Type &element)
{
    linkedStackType<Type> utilStack;
    if (inStack(element))
    {
        if (top() == element)
        {
            int stackCost = 1;
            pop();
            return stackCost;
        }

        else if (last() == element)
        {
            int stackCost = 1;
            while (stackTop->info != element)
            {
                string notIt = top();
                utilStack.push(notIt);
                pop();
                stackCost++;
            }
            pop();

            copyStack(utilStack);
            return stackCost;
        }

        else
        {
            linkedQueueType<Type> qForStack;
            qForStack.initializeQueue();
            int stackCost = 0;
            while (!isEmptyStack())
            {
                qForStack.addQueue(top());
                pop();
            }
            qForStack.QueueSale(element);

            while (!qForStack.isEmptyQueue())
            {
                string backToStack = qForStack.front();
                push(backToStack);
                qForStack.delFromQ();
                stackCost++;
            }
            return stackCost;
        }
    }

    else
    {
        int stackCost = 0;
        return stackCost;
    }

}
template <class Type>
void linkedStackType<Type>:: reverseStack()
{
    linkedStackType<Type> utilStack;
    while (!isEmptyStack())
    {
        string notIt = top();
        utilStack.push(notIt);
        pop();
    }
    copyStack(utilStack);
}

template <class Type>
bool linkedStackType<Type>::inStack(const Type &element)
{
    nodeType<Type> *temp = stackTop;
    while (temp != NULL)
    {
        if (temp->info == element)
        {
            return true;
        }

        else
        {
            temp = temp->next;
        }
    }
    return false;
}

//DESTRUCTS THE STACK
template <class Type>
linkedStackType<Type>::~linkedStackType() {
    initializeStack();
};


using namespace std;
int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);
    string input_file = am.get("input");
    string output_file = am.get("output");

    linkedStackType<string> myStack;
    linkedQueueType<string> myQ;

    string line;
    ifstream inFile(input_file);
    ofstream outfile;
    outfile.open(output_file);

    if (inFile.is_open())
    {
        cout <<"at least it went here " << endl;
        while (getline(inFile, line))
        {
            istringstream ss(line);
            string command;
            string book;
            ss >> command;
            if (line.empty())
            {
                continue;
            }

            if (command == "buy")
            {
                book = line.substr(line.find(" ") + 1);
                myQ.addQueue(book);
                myStack.push(book);
            }

            else if (line.find("sale") != string::npos)
            {

                book = line.substr(line.find(" ") + 1);
                if (!myStack.inStack(book) && !myQ.inQueue(book))
                {
                    outfile << book << " not found" << endl;
                    myStack.reverseStack();
                    myStack.printS();
                }

                else
                {
                    cout <<"at least it went here 5 " << endl;
                    int sPOS = myStack.stackSale(book);
                    int qPOS = myQ.QueueSale(book);
                    outfile << book << " finding cost at stack: " << sPOS<< ", at queue: " << qPOS << endl;
                }

            }
        }
    }

    if (!outfile.is_open())
    {
        cout << "Cannot open output file" << endl;
        return 0;
    }


    return 0;
}






