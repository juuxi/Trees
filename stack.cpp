template<typename S>
struct Node_solo
{
    S value;
    Node_solo* next;
    Node_solo<S>(Node_solo<S>* _next, S _value) {next = _next; value = _value;}
};

template<typename S>
class Stack
{
    Node_solo<S>* head;
public:
    Stack() {head = nullptr;}
    void push_front(S);
    void pop_front();
    S get_value() {return head->value;}
    bool is_empty() {if (head == nullptr) return true; return false;}
    S top() {return head->value;}
    ~Stack();
private:
    Node_solo<S>* front() {return head;}
};

template<typename S>
void Stack<S>::push_front(S _val)
{
    Node_solo<S>* curr = new Node_solo<S>(head, _val);
    head = curr;
}

template<typename S>
void Stack<S>::pop_front()
{
    Node_solo<S>* curr = head;
    head = head->next;
    delete curr;
}

template<typename S>
Stack<S>::~Stack()
{
    while (!is_empty())
        pop_front();
}