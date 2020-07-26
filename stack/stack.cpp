#include <iostream>
#include <memory>

using namespace std;

#define ASSERTME(x) { if (!(x)) { cout << "Test case " << #x << " failed" << endl; exit(-1);}}

template <typename T>
class Stack
{
public:
    virtual bool push(T&) = 0;
    virtual bool pop(T**) = 0;
    virtual bool peek(T**) = 0;
    virtual size_t size() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual void display() = 0;

    virtual ~Stack() = default;
};

template <class T>
class StackLL : public Stack<T>
{
public:
    bool push(T&) override;
    bool pop(T**) override;
    bool peek(T**) override;
    void display() override;
    size_t size() { return mSize; }
    bool isEmpty() { return (top == NULL); }
    bool isFull() { return (mSize == Size); }

    StackLL(size_t size): Size(size), top(NULL),
                          mSize(0)
    {
        cout << "Linked List Array initialized" << endl;
    }
private:
    const int Size;
    T* top;
    int mSize;
};

template <typename T>
class StackLinks
{
private:
    T* llprev;
    T* llnext;
    friend class StackLL<T>;
};

class Node : public StackLinks<Node>
{
public:
    Node(int num) : data(num) {}
    friend ostream& operator <<(ostream& os, const Node& node)
    {
        os << node.data;
        return os;
    }
    int operator*()
    {
        return data;
    }
private:
    int data;
};

template <typename T>
void StackLL<T>::display()
{
    if (isEmpty())
    {
        cout << "Nothing to display" << endl;
        return;
    }

    T* temp = top;
    while (temp)
    {
        cout << *temp << endl;
        temp = temp->llprev;
    }
}

template <typename T>
bool StackLL<T>::push(T& elem)
{
    if (isFull())
    {
        cout << "Stack is full" << endl;
        return false;
    }

    if (isEmpty())
    {
        top = &elem;
        top->llprev = NULL;
    }
    else
    {
        top->llnext = &elem;
        elem.llprev = top;
        top = &elem;
    }
    top->llnext = NULL;
    mSize++;
    return true;
}

template <typename T>
bool StackLL<T>::pop(T** elem)
{
    if (isEmpty())
    {
        cout << "Stack is empty" << endl;
        return false;
    }

    mSize--;
    *elem = top;

    if (top->llprev == NULL)
    {
        top = NULL;
    }
    else
    {
        T* temp = top;
        top = top->llprev;
        temp->llprev = NULL;
    }

    return true;
}

template <typename T>
bool StackLL<T>::peek(T** elem)
{
    if (isEmpty())
    {
        cout << "Stack is empty" << endl;
        return false;
    }
    *elem = top;

    return true;
}

template <typename T>
class StackArray : public Stack<T>
{
public:
    bool push(T&) override;
    bool pop(T**) override;
    bool peek(T**) override;
    void display() override;
    size_t size() { return top + 1; }
    bool isEmpty() { return (top == -1); }
    bool isFull() { return ((top + 1) == Size); }

    StackArray(size_t size): Size(size), top(-1)
    {
        cout << "Stack Array initialized" << endl;
    }
private:
    const int Size;
    int top;
    T arr[5];
};

template <typename T>
void StackArray<T>::display()
{
    if (isEmpty())
    {
        cout << "Nothing to display" << endl;
        return;
    }

    for (int i = top; i >= 0; i--)
    {
        cout << arr[i] << endl;
    }
}

template <typename T>
bool StackArray<T>::push(T& elem)
{
    if (isFull())
    {
        cout << "Stack is full" << endl;
        return false;
    }

    arr[++top] = elem;

    return true;
}

template <typename T>
bool StackArray<T>::pop(T** elem)
{
    if (isEmpty())
    {
        cout << "Stack is empty" << endl;
        return false;
    }

    *elem = &arr[top--];
    return true;
}

template <typename T>
bool StackArray<T>::peek(T** elem)
{
    if (isEmpty())
    {
        cout << "Stack is empty" << endl;
        return false;
    }
    *elem = &arr[top];

    return true;
}

template <typename T>
void runTestCases(Stack<T>& stack, int size)
{
    // Empty stack test cases
    ASSERTME(stack.size() == 0);
    ASSERTME(stack.isEmpty());
    ASSERTME(!stack.isFull());

    // Push test cases
    int baseNum(46);
    for (int i = 0; i < size; i++)
    {
        ASSERTME(!stack.isFull());
        T* node = new T(baseNum + (11* i));
        ASSERTME(stack.push(*node));
        ASSERTME(stack.size() == (i+1));
        ASSERTME(!stack.isEmpty());
        T* var = NULL;
        ASSERTME(stack.peek(&var));
        // if (is_same<T, Node>::value)
        // {
        //     ASSERTME(**var == (baseNum + (11* i)));
        // }
    }

    stack.display();

    // Full test cases
    {
        T* number = new T(baseNum);
        ASSERTME(!stack.push(*number));
        ASSERTME(stack.isFull());
        // delete number;
    }

    // Pop test cases
    for (int i = 0; i < size; i++)
    {
        ASSERTME(!stack.isEmpty());
        ASSERTME(stack.size() == (size - i));
        T *number = NULL;
        ASSERTME(stack.pop(&number));
        // delete number;
        ASSERTME(!stack.isFull());
    }

    {
        T *number = NULL;
        ASSERTME(!stack.pop(&number));
        ASSERTME(!stack.peek(&number));
    }
    ASSERTME(stack.size() == 0);
    ASSERTME(stack.isEmpty());
    ASSERTME(!stack.isFull());

    cout << "All test cases passed." << endl;
}

int main ()
{
    int size = 5;
    {
        std::unique_ptr<Stack<int>> stack(new StackArray<int>(size));
        runTestCases<int>(*stack, 5);
    }
    {
        std::unique_ptr<Stack<char>> stack(new StackArray<char>(size));
        runTestCases<char>(*stack, 5);
    }
    {
        std::unique_ptr<Stack<double>> stack(new StackArray<double>(size));
        runTestCases<double>(*stack, 5);
    }
    {
        std::unique_ptr<Stack<Node>> stack(new StackLL<Node>(size));
        runTestCases<Node>(*stack, 5);
    }
    return 0;
}

