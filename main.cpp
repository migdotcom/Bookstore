#include <iostream>
#include<fstream>
#include<assert.h>

using namespace std;

template <class Type>
struct nodeType{
    Type info;
    nodeType<Type> *next;
};

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
class linkedStackType:public StackADT <Type>{
public:
    const linkedStackType<Type> &operator=(const linkedStackType<Type>&);
    bool isEmptyStack() const;
    bool isFullStack() const;
    void initializeStack();
    void push(const Type &newItem);
    void pop();
    Type top() const;
    linkedStackType();
    linkedStackType(const linkedStackType<Type> &otherStack);
    ~linkedStackType();

private:
    nodeType<Type> *stackTop;
    void copyStack(const linkedStackType<Type> &otherStack);

};
template<class Type>
linkedStackType<Type>::linkedStackType() {
    stackTop= NULL;

};
template<class Type>
bool linkedStackType<Type>::isEmptyStack() const {
    return (stackTop==NULL);

};
template <class Type>
bool linkedStackType<Type>::isFullStack() const {
    return false;

};

template<class Type>
void linkedStackType<Type>::initializeStack(){
    nodeType<Type> *temp;
    while(stackTop != NULL){
        temp= stackTop;
        stackTop = stackTop->next;

        delete temp;

    }

};
template <class Type>
void linkedStackType<Type>::push(const Type &newElement) {
    nodeType<Type> *newNode;// pointer to create the new node
    newNode = new nodeType<Type>; //create node
    newNode->info = newElement;
    newNode->next = stackTop;
    stackTop = newNode;

};
template <class Type>
Type linkedStackType<Type>::top() const {
    assert(stackTop!= NULL);
    return  stackTop->info;

};
template <class Type>
void linkedStackType<Type>::pop() {
    if (stackTop != NULL) {
        nodeType<Type> *temp;
        temp = stackTop;
        stackTop = stackTop->next;
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
    copyStack(otherStack);

};

template <class Type>
linkedStackType<Type>::~linkedStackType() {
    initializeStack();
};

template <class Type>
const linkedStackType<Type>& linkedStackType<Type>::operator=(
        const linkedStackType<Type> &otherStack) {
    if (this != &otherStack)  // avoid self copy
        copyStack(otherStack);

    return *this;

}

void testCopy(linkedStackType<int> OStack);

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
    virtual void deleteQueue() = 0;


};



template <class Type>
class linkedQueueType: public queueADT<Type> {
public:
     const linkedQueueType<Type>& operator=(const linkedQueueType<Type> &);
     bool isEmptyQueue() const ;
     bool isFullQueue() const ;
     void initializeQueue() ;
     Type front() const ;
     Type back() const ;
     void addQueue(const Type &queueElement);
     void deleteQueue();
    linkedQueueType();
    linkedQueueType(const linkedQueueType<Type> & otherQueue);
//     ~linkedQueueType();

private:
    nodeType<Type> *qFront;// pointer to the front
    nodeType<Type> *qRear; // ponter to the rear

};

template < class Type>
bool linkedQueueType<Type>::isEmptyQueue() const {
    return(qFront == NULL);

}

template < class Type>
bool linkedQueueType<Type>::isFullQueue() const {
    return false;
}

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
template <class Type>
Type linkedQueueType<Type>::front() const {
    assert(qFront !=NULL);
    return qFront->info;
    //returns the info of the front of the queue
}

template <class Type>
Type linkedQueueType<Type>::back() const {
    assert(qRear !=NULL);
    return qRear->info;
    //returns the info of the back of the queue
}

template <class Type>
void linkedQueueType<Type>::deleteQueue() {
    nodeType<Type> *temp;
    if(!isEmptyQueue()){
        temp = qFront;
        qFront = qFront->next;
        delete temp;
         if(qFront ==NULL)
             qRear = NULL;
    }
    else
        cout << "Cannot remove from an empty queue" <<endl;

}
template <class Type>
linkedQueueType<Type>::linkedQueueType() {
    qFront = NULL; // set fron to nullq
    qRear = NULL;

}


using namespace std;

int main(){

    linkedStackType<int> stack;
    linkedStackType<int> otherStack;
    linkedStackType<int> newStack;

    //adding elements
    stack.push(34);
    stack.push(43);
    stack.push(27);
    // using assigment operator to copy
    newStack = stack;

    cout << "After the assigment operator newStack:"
         <<endl;
    while (!newStack.isEmptyStack()){
        cout <<newStack.top() <<endl;
        newStack.pop();
    }
    //using assigment operator again to copy elements
    otherStack =stack;

    cout << "Testing copy constructor." <<endl;
    testCopy(otherStack);

    cout<< "stack:" <<endl;
    while (!stack.isEmptyStack()){
        cout <<stack.top()<<endl;
        stack.pop();

    }



    /////////////////////////////////////////////////////////////////////////

    linkedQueueType<int> Myqueue;
    int x,y;
    Myqueue.initializeQueue();
    x=4;
    y=5;
    Myqueue.addQueue(x);
    Myqueue.addQueue(y);
    x = Myqueue.front();
    Myqueue.deleteQueue();
    Myqueue.addQueue(x+5);
    Myqueue.addQueue(16);
    Myqueue.addQueue(x);
    Myqueue.addQueue(y-3);
    cout << "queue elements:";
    while(!Myqueue.isEmptyQueue()){
        cout << Myqueue.front() <<" ";
        Myqueue.deleteQueue();

    }

    return 0;
}
void testCopy(linkedStackType<int> OStack){
    cout << "Stack in the function testCopy:" <<endl;

    while(!OStack.isEmptyStack()){
        cout <<OStack.top() << endl;
        OStack.pop();
    }
}