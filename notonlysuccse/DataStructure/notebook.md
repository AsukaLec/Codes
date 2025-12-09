[TOC]
# <center> 数据结构
## Part 1 Vector
### 1. <> ? 何时来的？ 模板优化
常见的vector的定义中， 总有 vector<typename>。<>代表的，其实是模板化的概念。
``` cpp
template <typename T>
class MyVector {
    T* data;
    int n;
}

int main(){
    MyVector<int> vint;
    MyVector<Myvector<int>> v_MyV;
}
```
一次编写，多次复用。

### 2. 构造函数
期望是实现如下操作
``` cpp
vector <int> (10); // 十维空向量
vector <int> (10, 123); // 带初始化
```
实现即可
```cpp
MyVector() { // 默认构造函数
    data = nullptr;
    _size = 0;
}
MyVector(int n, T init = T()) { //一个缺省值  T()，用来给MyVector<int>(10, 123)用的 
    data = new T[n];
    for (int i = 0; i < n; i ++) {
        data[i] = init ;
    }
    _size = n;
}
MyVector(MyVector<T> &other) {//拷贝构造函数
    data = new T[other.size()];
    for (int i = 0; i < other.size(); i ++) {
        data[i] = other[i];
    }
    _size = other.size();
}
MyVector(initializer_list<T> &list) {//列表初始化
    data = new T[init.size()];//list不能下标访问，只能范围循环
    _size = 0;
    for (T x : init) {
        data[_size] = x;
    }
}
~MyVector() {delete[] data;} 
```

### 3. a[i] 怎么error了？运算符重载
很遗憾，对于一个全新的类，用[]来访问特定的值的行为还没有定义，运算符重载即可。
``` cpp
T operator[](int index) {
    return data[index];
}
```
注意，返回值的类型也要用占位符代替。

### 4. at访问 下标检测，更加安全
```cpp
T& at(size_t index){
    if(index >=_size) {
        stringstream ss;
        ss << "out of range, index: " << index << " , size = " << _size;
        throw out_of_range(ss.str());
    }
    return_data[index];
}
```

### 5. 动态管理内存
数组是一段**内存连续**的空间

如果要插入新的元素，而现有的容量不足以支撑这个操作，要如何呢？
朴素的想法是申请一个多一段元素的内存，然后复制。
但是这样复杂度会变得很高。

$O(1)$的方法：每次内存溢出，就把现有的容量乘以2。
为什么是$O(1)$？<mark>要进行复杂度分析</mark>

**分摊复杂度**：
分析对该结构进行n次操作，将所有操作时间累计起来在除以n， n足够大，这一平均时间就是用于扩容这一操作的分摊时间复杂度
假设一开始数组的容量为 $N$,同时，既然是讨论上界，不妨设目前元素的个数就是 $N$，且之后进行的每一步操作都是向数组中插入一个元素。
$size(n) = N + n$
$siza(n) \leqslant capacity(n) < 2 * size(n)$
$capacity(n) = \varTheta(n) $
$T(n) = 2n + 4n +8n + ... + capacity(n) < 2 * size(n) = \varTheta(n)$
$T(n) / n = O(1)$

同时，如果每次扩容操作不是乘2而是加上固定的一个常数，复杂度恒为$O(n)$


``` cpp
size_t capacity() {return _capacity;}

void reserve(size_t new_capacity) { //预存空间，同时保存原有的内容
    if (new_capacity > _capacity) {
        _capacity = new_capacity;
        T *new_data = new T[_capacity];
        for (size_t i = 0; i < _size; i ++) new_data[i] = _data[i];
        delete[] _data;
        _data = new_data;
    }
}

void push_back (T elem) { //复杂度也是O(1)哦
    if (_size == _capacity) {
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    }
    _data[_size++] = elem;
}

void resize(size_t _new_size, T init = T()) { //更改已有的data的大小，缺失值补齐
    if (new_size > _capacity) reserve(new_size);
    for (size_t i = _size; i < _new_size; i ++) {
        _data[i] = init;
    }
    _size = new_size;
}

void pop_back() {
    if (_size == 0) throw out_of_range("can not pop_back empty vector")
    _size --;
}

void clear() {
    _size = 0;
}
```

### 6. 常量const
1. 引用传参
    ``` cpp
    void fuc (MyVector <int> a) {

    }

    int main () {
        MyVector <int> a {1, 2, 3}
        fuc(a); 
    }
    ```
    在主函数调用时，对于传入的a， fuc实际上会创建一个新的对象，并用拷贝构造函数构建，这实际上开销会很大，所以说，实际上在写类的实现方法时运用引用会是一个更好的选择。
    ```cpp
    void fuc (MyVector <int> &a) {

    }
    ```

2. const 引用
    若要是想以以下方式传参呢？
    ``` cpp
    fuc({1, 2, 3}) // MyVector 的列表初始化
    ```
    就需要用到 const，以支持临时变量否则会被认为时不被接受的左值
    ```cpp
    void fuc (MyVector <int> &a) {

    }
    ```

3. **不同位置的 const**
    <mark>const 对象只能使用 const成员函数
    const 成员函数可以被任何对象调用</mark>

    **eg1.**
    ``` cpp
    cout << b.size() << endl;
    ```
    就需要
    ``` cpp
        size_t size() const {return _size;}
    ```
    这里 后置 const 代表 将成员函数声明为const成员函数

   **eg2.**
    然鹅，有些时候我们会需要对const的内容进行修改，这就需要一个函数两个实现
    ``` cpp
    const T& operator[](int index) const { //索引访问，返回引用以修改
        return _data[index];               // const 对象调用 且返回的对象不可以被修改
    }

    T& operator[](int index)  { //非 const 对象调用
        return _data[index];
    }
    ```

    **All in All**
    1. 加在函数的参数前的const 
        ``` cpp
        MyVector(const MyVector<T> &other) : _data(new T[other.size()], _size(other.size()), _capacity(other.size())){ //拷贝构造函数
            for (size_t i = 0; i < other.size(); i ++) {
                _data[i] = other[i];
            }
        }
        ```
        代表这个参数不能被修改

    2. 加在括号前面的 const
        代表该函数是类中的const成员函数

    3. 函数名之前的 const 
        表示该函数的返回值是一个常量，不能被修改。
        通常还会有一个同名的不带const的版本

### 7. 迭代器
万恶的 iter 如是说：
```cpp
for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter ++) {
    cout << *iter << endl; // 星号：解引用
}
```
但实际上map这类数据结构里的迭代器是很好用的
```cpp
for (map<int, int>::iterator iter = mp.begin(); iter != mp.end(); iter ++) {
    cout << iter->first << iter->second << endl;
}
```
或者是排序
```cpp
sort(vec.begin(), vec.end());
```

**但这东西究竟是什么？**
一个对容器数据的封装，一个特殊的类型
让整个stl十分的整洁
同时，使用迭代器和一些给定的函数 (sort(), max_element())  之类的需要对运算符进行重载，所以在类内进行实现。
```cpp
// ====== 迭代器类 ======
class iterator {
    private:
    T* ptr;

    public:
    iterator() {}
    iterator(T* ptr): ptr(ptr) {}
    
    using value_type = T; //stl会用到
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;
    // ====== 运算符重载 ======
    iterator &operator ++ ()  { // ++iter;
        ptr ++;
        return *this;//返回自身
    }

    iterator operator ++ (int) { // iter ++；
        iterator temp = *this;
        ptr ++;
        return temp;
    } // 复杂类型，++在前没有产生新数据，性能会好很多

    iterator &operator -- ()  { // ++iter;
        ptr --;
        return *this;//返回自身
    }

    iterator operator -- (int) { // iter ++；
        iterator temp = *this;
        ptr --;
        return temp;
    } // 复杂类型，++在前没有产生新数据，性能会好很多

    T &operator *() const {
        return *ptr;
    }

    T *operator ->() const {
        return ptr;
    }

    bool operator != (const iterator& other) const {
        return ptr != other.ptr;
    }
    bool operator < (const iterator &other) const {
        return ptr < other.ptr;
    }
    bool operator > (const iterator &other) const {
        return ptr > other.ptr;
    }
    bool operator == (const iterator &other) const {
        return ptr == other.ptr;
    }


    iterator operator+ (int n) const {
        return iterator(ptr + n);
    }
    iterator operator- (int n) const {
        return iterator(ptr - n);
    }

    int operator- (const iterator &other) const {
        return ptr - other.ptr;
    }

};

iterator begin() {
    return iterator(_data);
}
iterator end() {
    return iterator(_data + _size);
}

```

### 8. insert & erase
最基本要实现以下函数
```cpp
void insert(const iterator & pos, const T &x);
void erase(const iterator &pos);
void erase(const iterator &start, const iterator &end);
```

**insert 的 bug**
以下是insert的实现
```cpp
void insert(const iterator & pos, const T &x) {
    size_t index = pos - begin();
    if (_size == _capacity) reserve(_capacity == 0 ? 1 : _capacity * 2);
    for (size_t i = _size; i > index; i --) _data[i] = _data[i - 1];
    _data[index] = x;
    _size ++;
}
```
以下是一个特殊的样例，让我们看看会发生什么
``` cpp
MyVector<int> vec1 {1, 2, 3, 4};
for (int i = 0; i < 17; i++) {
    vec1.insert(vec1.begin(), vec1[vec1.size() - 1]);
}

for (auto & x : vec1) cout << x << " " ;
cout << endl;
```
```cpp
3 3 3 3 4 3 3 3 3 3 3 3 4 3 3 3 4 1 2 3 4 
```
可以看到，因为我们在insert函数中参数为传值是 const T &x, 所以说当我们用结构中已经存在的元素去进行插入， 在不发生扩容的情况下(这个例子可以看到每次发生扩容时是按照预期进行输出的)，函数实际引用的位置会有偏差
同样的
``` cpp
MyVector<int> vec1 {1, 2, 3, 4};
for (int i = 0; i < 17; i++) {
    vec1.insert(vec1.begin(), vec1[vec1.size() - 2]);
}

for (auto & x : vec1) cout << x << " " ;
cout << endl;
```
```cpp
2 2 2 2 3 2 2 2 2 2 2 2 3 2 2 2 3 1 2 3 4
```
让我们看看stl中的vector是怎么说的
``` cpp
const auto __pos = begin() + (__position - cbegin());
// __x could be an existing element of this vector, so make a
// copy of it before _M_insert_aux moves elements around.
_Temporary_value __x_copy(this, __x);
_M_insert_aux(__pos, std::move(__x_copy._M_val()));
```
stl中的解决方式是传入一个复制的值

!!! : 如何解决？
```cpp
void insert(const iterator & pos,  T x) {
    size_t index = pos - begin();
    if (_size == _capacity) reserve(_capacity == 0 ? 1 : _capacity * 2);
    for (size_t i = _size; i > index; i --) _data[i] = _data[i - 1];
    _data[index] = x;
    _size ++;
}
```
憋引用了，直接传复制吧
但是或许可以写个特判？当元素不是在vector中的时候就传引用？

### 9. 小修小补
**重载 " = " 运算符**
C++类有一个默认的 = 的实现，但如果是两个对象之间的调用可能会出现像python复制那样指针指向错误的问题。
eg.
```cpp
MyVector<int> a = {1, 2, 3};
MyVector<int> b = {1, 2, 3, 4};
a = b;
a[0] = 123;
b.show(); // 其实没写， 但是就是逐个输出，意思是这个意思
```
```cpp
123 2 3 4
```
实际上，a 此时和 b 已经是同一个东西了。

运算符重载实现：
```cpp
MyVector<T>& operator = (const MyVector<T> &other) {
    if (this != &other) {
        delete[] _data;
        _data = new T[other.size()];
        _size = other.size();
        _capacity = other.capacity();
        for (size_t i = 0; i < _size; i ++) _data = other[i];
    }
    return *this;
}
```

**和 push_back 很像的 emplace_back**
```cpp
template <typename ... Args>
void emplace_back(const Args&... args) { //emplace_back 支持多种数据类型的插入
    if (_size == _capacity) reserve(_capacity == 0 ? 1 : _capacity * 2);
    _data[_size++] = T(args...);
}
```
```cpp
MyVector<pair<int, double>> a;
a.emplace_back(1, 114.514);
cout << a.front().first << endl;
cout << a.front().second << endl;

MyVector<tuple<int, double, bool, char>> b;
b.emplace_back(1, 114.514, true, '*');
cout << get<0>(b.front()) << endl;
cout << get<1>(b.front()) << endl;
cout << get<2>(b.front()) << endl;
cout << get<3>(b.front()) << endl;
```
对于特别复杂的数据类型， 用这个东西特别方便，tuple就完事了，用push_back就要到make_tuple

### 10. 完事 请见hpp文件！

```cpp
#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
class MyVector {
    private: 
    T* _data;
    size_t _size; //size_t == unsigned longlong
    size_t _capacity;

    void check_range(size_t index) {
        if(index >=_size) {
            stringstream ss;
            ss << "out of range, index: " << index << " , size = " << _size;
            throw out_of_range(ss.str());
        }
    }

    public:
    // ====== 迭代器类 ======
    class iterator {
        private:
        T* ptr;

        public:
        iterator() {}
        iterator(T* ptr): ptr(ptr) {}
        
        using value_type = T; //stl会用到
        using iterator_category = std::random_access_iterator_tag; //reverse 会用到 可以随机访问的迭代器
        using difference_type   = std::ptrdiff_t; //计算两个迭代器的距离 
        using pointer           = T*; //什么值的一个pointer
        using reference         = T&; //什么值的类型引用
        // ====== 运算符重载 ======
        iterator &operator ++ ()  { // ++iter;
            ptr ++;
            return *this;//返回自身
        }

        iterator operator ++ (int) { // iter ++；
            iterator temp = *this;
            ptr ++;
            return temp;
        } // 复杂类型，++在前没有产生新数据，性能会好很多

        iterator &operator -- ()  { // ++iter;
            ptr --;
            return *this;//返回自身
        }

        iterator operator -- (int) { // iter ++；
            iterator temp = *this;
            ptr --;
            return temp;
        } // 复杂类型，++在前没有产生新数据，性能会好很多

        T &operator *() const { return *ptr; }
        T *operator ->() const { return ptr; }

        bool operator != (const iterator& other) const { return ptr != other.ptr; }
        bool operator < (const iterator &other) const { return ptr < other.ptr; }
        bool operator > (const iterator &other) const { return ptr > other.ptr; }
        bool operator == (const iterator &other) const { return ptr == other.ptr; }
        iterator operator+ (int n) const { return iterator(ptr + n); }
        iterator operator- (int n) const { return iterator(ptr - n); }

        int operator- (const iterator &other) const { return ptr - other.ptr; }

    };
    iterator begin() { return iterator(_data); }
    iterator end() { return iterator(_data + _size); }
    // ====== ======

    //====== 构造函数们 ======
    MyVector() { // 默认构造函数
        _data = nullptr;
        _size = 0;
        _capacity = 0;
    }

    // MyVector() :_data(nullptr), _size(0) {}

    MyVector(size_t n, T init = T()) { //一个缺省值  T()，用来给MyVector<int>(10, 123)用的 
        _data = new T[n];
        for (size_t i = 0; i < n; i ++) {
            _data[i] = init ;
        }
        _size = n;
        _capacity = n;
    }
    MyVector(const MyVector<T> &other) : _data(new T[other.size()], _size(other.size()), _capacity(other.size())){ //拷贝构造函数
        for (size_t i = 0; i < other.size(); i ++) {
            _data[i] = other[i];
        }
    }
    MyVector(const initializer_list<T> init) :_data(new T[init.size()]), _size(0), _capacity(init.size()){ //列表初始化
        for (T x : init) { //list不能下标访问，只能范围循环
            _data[_size++] = x;
        }
    }
    ~MyVector() { delete[] _data; } 
    // ====== ======

    // ====== 运算符重载 ======
    const T &operator[](int index) const {  return _data[index]; } //索引访问，返回引用以修改 const 对象调用 且返回的对象不可以被修改
    T &operator[](int index) { return _data[index];} //非 const 对象调用

    const T& at(size_t index) const { //at 访问，下标溢出检测
        check_range(index);
        return _data[index];
    }
    T &at(size_t index) { //at 访问，下标溢出检测
        check_range(index);
        return _data[index];
    }
    
    MyVector<T>& operator = (const MyVector<T> &other) {
        if (this != &other) {
            delete[] _data;
            _data = new T[other.size()];
            _size = other.size();
            _capacity = other.capacity();
            for (size_t i = 0; i < _size; i ++) _data[i] = other[i];
        }
        return *this;
    }


    // ====== ======

    // ====== 接口们 ======

    size_t size() const {return _size;}
    size_t capacity() const {return _capacity;}

    void reserve(size_t new_capacity) { //预存空间，同时保存原有的内容
        if (new_capacity > _capacity) {
            _capacity = new_capacity;
            T *new_data = new T[_capacity];
            for (size_t i = 0; i < _size; i ++) new_data[i] = _data[i];
            delete[] _data;
            _data = new_data;
        }
    }

    void push_back (T elem) { //复杂度也是O(1)哦
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        _data[_size++] = elem;
    }

    void resize(size_t _new_size, T init = T()) { //更改已有的data的大小，缺失值补齐
        if (_new_size > _capacity) reserve(_new_size);
        for (size_t i = _size; i < _new_size; i ++) {
            _data[i] = init;
        }
        _size = _new_size;
    }

    void pop_back() {
        if (_size == 0) throw out_of_range("can not pop_back empty vector");
        _size --;
    }

    void clear() { _size = 0; }

    void insert(const iterator & pos, T x) {
        size_t index = pos - begin();
        if (_size == _capacity) reserve(_capacity == 0 ? 1 : _capacity * 2);
        for (size_t i = _size; i > index; i --) _data[i] = _data[i - 1];
        _data[index] = x;
        _size ++;
    }
 
    void erase(const iterator &pos) {
        for (size_t i = pos - begin(); i < _size - 1; i ++) {
            _data[i] = _data[i + 1];
        }
        _size --;
    }

    void erase(const iterator &start, const iterator &end) { // [star, end)
        int diff = end - start; // 注意end > start 
        for (size_t i = start - begin(); i < _size - diff; i ++) {
            _data[i] = _data[i + diff];
        } 
        _size -= diff;
    }

    T &front() { return _data[0]; }
    const T &front() const { return _data[0]; }
    T &back () { return _data[_size - 1]; }
    const T &back() const { return _data[_size - 1]; }

    bool empty() const { return _size == 0; }

    template <typename ... Args>
    void emplace_back(const Args&... args) { //emplace_back 支持多种数据类型的插入
        if (_size == _capacity) reserve(_capacity == 0 ? 1 : _capacity * 2);
        _data[_size++] = T(args...);
    }
    // ====== ======
};
#endif 
```

---

## Part 2 List
### 1. 初见链表
最直观的，vector申请的是一段连续的内存空间，对其进行插入元素的操作的复杂度是O(n)
而链表最明显的特征就是其插入元素的复杂度为O(1)，血赚
当然，总有一些代价的

### 2. 链表的结构
链表作为一个数据结构，是由一个个结点组成的，里面存储的数据类型是待定义的
``` cpp
template<typename T>
struct Node {
    T val;
    Node* next; // 指向下一个结点
};
```
指针指向的即是当前结点的下一个结点
头结点和尾结点(`head & tail`) 有一些特殊的表示

**链表的基本操作**
1. 遍历整个链表
``` cpp
void traversal (Node *head) {
    
    for (Node *cur = head; cur != nullptr; cur = cur-> next) {
        // do sth.
    }

}
```
2. 获取链表长度
``` cpp
int size (Node *head) {
    int len = 0;
    for (Node *cur = head; cur != nullptr; cur = cur-> next) {
        len ++;
    }
    return len;
}
```

>但是在全局来说，因为我们目前会改变到链表长度的操作就只有增加和删除两个操作，所以可以在链表类中维护一个变量`len`用于记录长度，在进行增删操作的时候改变`len`即可，最后需要用到长度时返回`len`即可。

3. 在某个结点后加入结点
``` cpp
template<typename T>
void insert(Node *cur, T x) {
    Node *newNode = new Node (x, nullptr);
    newNode->next = cur->next;
    cur->next = newNode;
}
```
4. 在某个结点后删除一个结点
``` cpp
void erase_after(Node *cur) {
    if (cur->next == nullptr) return;
    cur->next = cur->next->next;
}
```

### 3. 双向链表
!!! : 想要直接插入或删除某个结点，但不知道上一个结点是啥
改一下结点类的定义就行
``` cpp
template<typename T>
struct Node {
    T val;
    Node* next; // 指向下一个结点
    Node* prev; // 指向上一个结点
};
```
这样子删除结点时只需要修改`prev`的`next`指针和`next`的`prev`指针，被删除元素的`prev`和`next`指针是不需要动的，因为被删除元素已经不在指针序列组成的环内了（不从被删除元素开始遍历的话）
但是增加结点还是要把所有的边都处理了

1. 删除节点
``` cpp
void erase(Node *node) {
    Node* prev = node->prev;
    Node* next = node->next;
    if(prev) prev->next = next; //保证非空
    if(next) next->prev = prev; //保证非空
    delete node;
}
```
2. 插入结点
``` cpp
void insert(Node *cur, int x) {
    Node* next = cur->next;
    Node* new_node = new Node{x, cur, next};
    cur->next = new_node;
    if(next) next->prev = new_node;
}
```

### 4. 操作头尾结点？ dummy结点(哨兵结点)
`dummy`结点是一个不具备实际意义的结点，因此不会对其进行操作
用  ```dummy_head->next``` 代替 ```head``` 
```dummy_tail->prev``` 代替 ```tail```
就算整个链表都被删了，```dummy```还在