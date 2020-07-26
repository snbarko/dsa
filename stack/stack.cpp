#include <iostream>

using namespace std;

#define ASSERTME(x) { if (!(x)) { cout << "Test case " << #x << " failed" << endl; exit(-1);}}

template <typename T>
class Stack
{
public:
    virtual bool push(T) = 0;
    virtual bool pop(T&) = 0;
    virtual bool peek(T&) = 0;
    virtual size_t size() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual void display() = 0;

    virtual ~Stack() = default;
};

template <typename T>
class StackArray : public Stack<T>
{
public:
    bool push(T) override;
    bool pop(T&) override;
    bool peek(T&) override;
    void display() override;
    size_t size() { return top + 1; }
    bool isEmpty() { return (top == -1); }
    bool isFull() { return ((top + 1) == Size); }

    StackArray(size_t size): Size(size), top(-1)
    {
        cout << "Stack initialized" << endl;
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
bool StackArray<T>::push(T elem)
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
bool StackArray<T>::pop(T& elem)
{
    if (isEmpty())
    {
        cout << "Stack is empty" << endl;
        return false;
    }

    elem = arr[top--];
    return true;
}

template <typename T>
bool StackArray<T>::peek(T& elem)
{
    if (isEmpty())
    {
        cout << "Stack is empty" << endl;
        return false;
    }
    elem = arr[top];

    return true;
}

template <typename T>
void genericOptions(T elem, Stack<T>& stack)
{
    while (1)
    {
        cout << "Welcome to stack. Enter options as below\n1. Push\n2. Pop\n"
            "3. Peek\n4. Size\n5. IsEmpty\n6. IsFull\n7. Display\n8. Exit\n" << endl;
        int ch = -1;
        cin >> ch;
        bool status = false;
        switch(ch)
        {
        case 1:
            if (stack.isFull())
            {
                cout << "Stack is full" << endl;
                break;
            }
            cout << "Enter element to push: ";
            cin >> elem;
            status = stack.push(elem);
            cout << "Push status: " << status << endl;
            break;
        case 2:
            status = stack.pop(elem);
            cout << "Pop status: " << status ? "success" : "failed";
            if (status)
                cout << " Element: " << endl;
            else
                cout << endl;
            break;
        case 3:
            status = stack.peek(elem);
            cout << "Peek status: " << status ? "success" : "failed";
            if (status)
                cout << " Element: " << endl;
            else
                cout << endl;
                                                   
            break;
        case 4:
            cout << "Size of stack: " << stack.size() << endl;
            break;
        case 5:
            cout << "IsEmpty: " << stack.isEmpty() << endl;
            break;
        case 6:
            cout << "IsFull: " << stack.isFull() << endl;
            break;
        case 7:
            cout << "Stack: " <<endl;
            stack.display();
            break;
        case 8:
            cout << "Exiting." << endl;
            exit(0);
        default:
            cout << "Invalid Option Provided. Exiting." << endl;
            exit(-1);
            break;
        }
    }
}

template <typename T>
void runTestCases(Stack<T>& stack, size_t size)
{
    // Empty stack test cases
    ASSERTME(stack.size() == 0);
    ASSERTME(stack.isEmpty());
    ASSERTME(!stack.isFull());

    // Push test cases
    int baseNum(46);
    T number(baseNum);
    for (int i = 0; i < size; i++)
    {
        ASSERTME(!stack.isFull());
        T node(baseNum + (11* i));
        ASSERTME(stack.push(node));
        ASSERTME(stack.size() == (i+1));
        ASSERTME(!stack.isEmpty());
        T var = -1;
        ASSERTME(stack.peek(var));
        ASSERTME(var == (baseNum + (11* i)));
    }

    stack.display();

    // Full test cases
    ASSERTME(!stack.push(baseNum));
    ASSERTME(stack.isFull());

    // Pop test cases
    for (int i = 0; i < size; i++)
    {
        ASSERTME(!stack.isEmpty());
        ASSERTME(stack.size() == (size - i));
        ASSERTME(stack.pop(number));
        ASSERTME(!stack.isFull());
    }

    ASSERTME(!stack.pop(number));
    ASSERTME(!stack.peek(number));
    ASSERTME(stack.size() == 0);
    ASSERTME(stack.isEmpty());
    ASSERTME(!stack.isFull());

    cout << "All test cases passed." << endl;
}

int main ()
{
    {
        Stack<int>* stack = new StackArray<int>(5);
        // int elem = -1;
        // genericOptions(elem, *stack);

        runTestCases<int>(*stack, 5);
        delete stack;
    }
    {
        Stack<char>* stack = new StackArray<char>(5);
        runTestCases<char>(*stack, 5);
        delete stack;
    }
    {
        Stack<double>* stack = new StackArray<double>(5);
        runTestCases<double>(*stack, 5);
        delete stack;
    }

    return 0;
}
