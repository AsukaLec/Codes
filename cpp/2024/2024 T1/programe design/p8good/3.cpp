#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    Person() {}
    Person(int ID, string name) : mId(ID), mName(name) {}
    void showMessage() {
        cout << this->mId << " " << this->mName << endl;
    }
    int getId() {
        return mId;
    }

private:
    int mId;              // 编号
    string mName;        // 姓名
};

class Node {
public:
    friend class LinkList;
    Node() : next(nullptr) {}
    Node(Person val) : data(val), next(nullptr) {}
    void showMessage() {
        data.showMessage();
    }

protected:
    Person data;         // 存储Person对象
    Node *next;          // 指针指向下一个节点
};

class LinkList {
public:
    LinkList() : head(nullptr) {}
    void addNodeAtTail(Person val);
    void print();
    void deleteNode(int id);
    int getHead(Person &val); // 从表头取出
    void addNodeAtHead(const Person &val);

protected:
    Node *head;          // 指针指向头节点
};

void LinkList::addNodeAtTail(Person val) {
    Node *newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkList::print() {
    Node *temp = head;
    while (temp != nullptr) {
        temp->showMessage();
        temp = temp->next;
    }
}

void LinkList::deleteNode(int id) {
    Node *temp = head, *prev = nullptr;
    while (temp != nullptr && temp->data.getId() != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) return; // 没有找到
    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;
}

int LinkList::getHead(Person &val) {
    if (head == nullptr) {
        cout << "error" << endl;
        return 0;
    } else {
        val = head->data;
        Node *temp = head;
        head = head->next;
        delete temp;
        return 1;
    }
}

void LinkList::addNodeAtHead(const Person &val) {
    Node *newNode = new Node(val);
    newNode->next = head;
    head = newNode;
}

class Queue : public LinkList {
public:
    void enterQueue(const Person &val) {
        addNodeAtTail(val);
    }
    int outQueue(Person &val) {
        return getHead(val);
    }
    void printQueue() {
        cout<<"queue member:"<<endl;         
        print();
    }
};

class Stack : public LinkList {
public:
    void push(const Person &val) {
        addNodeAtHead(val);
    }
    int pop(Person &val) {
        return getHead(val);
    }
    void printStack() {
        cout << "stack member:" << endl;
        print();
    }
};

int main() {
    string name;
    Queue *q1 = new Queue;
    Stack *s1 = new Stack;
    cout << "请输入学生姓名：" << endl;
    Person val;
    for (int i = 2018003; i >= 2018001; i--) { // 依次输入名字
        cin >> name;
        val = Person(i, name);
        s1->push(val);
    }
    for (int i = 2018004; i <= 2018006; i++) { // 依次输入名字
        cin >> name;
        val = Person(i, name);
        q1->enterQueue(val);
    }
    cout << "学生信息为：" << endl;
    q1->printQueue();
    s1->printStack();
    cout << "outQueue:" << endl;
    for (int i = 0; i < 2; i++) {
        if (q1->outQueue(val)) {
            val.showMessage();
        }
    }
    cout << "pop:" << endl;
    for (int i = 0; i < 2; i++) {
        if (s1->pop(val)) {
            val.showMessage();
        }
    }
    cout << "after deletes:" << endl;
    q1->printQueue();
    s1->printStack();
    delete q1;
    delete s1;
    return 0;
}




