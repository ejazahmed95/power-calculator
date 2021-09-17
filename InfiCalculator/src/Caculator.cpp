DSA_lab3.cpp
Who has access
Not shared
System properties
Type
C++
Size
22 KB
Storage used
22 KB
Location
Projects
Owner
me
Modified
4:04 PM by me
Opened
8 : 03 PM by me
Created
4 : 04 PM with Google Drive
Add a description
Viewers can download
#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

class DNode
{
private:
    int elm;
    DNode* prev;
    DNode* next;
    friend class DLL;
};
/*__________________________________________________________________________________*/
class DLL
{
public:
    DLL();
    ~DLL();
    void addFront(int e);		// add to front of list
    void addBack(const int e);		// add to back of list
    int front();				// get first element
    int back();				    // get last element
    void removeFront();					// remove from front
    void removeBack();					// remove from back
    bool isempty();
    void printlist();
    int Element(int position)const;      //to iterate front
    //int prevElement(int p); // fo the previous elemnt
    int size;
    friend class MyInteger;
private:								// local type definitions
    DNode* head;						// list sentinels
    DNode* tail;
protected:								// local utilities
    void add(DNode* v, int e);		// insert new node before v
    void remove(DNode* v);					// remove node v
};
/*_______________________________________________________*/
DLL::DLL()						// constructor
{
    size = 0;
    head = new DNode;			// create sentinels
    tail = new DNode;
    head->next = tail;			// have them point to each other
    tail->prev = head;
}

DLL::~DLL()						 // destructor
{
    while (!isempty()) removeFront();	// remove all but sentinels
    delete head;						// remove the sentinels
    delete tail;
}

bool DLL::isempty()						 // is list empty?
{
    return (head->next == tail);
}

int DLL::front()				// get front element
{
    return head->next->elm;
}

int DLL::back()					// get back element
{
    return tail->prev->elm;
}


void DLL::add(DNode* v, int e)				// insert new node before v
{
    DNode* u = new DNode;					// create a new node for e
    u->elm = e;
    u->next = v;							// link u in between v
    u->prev = v->prev;						// . . .and v->prev
    v->prev->next = u;
    v->prev = u;
    size++;
}

void DLL::addFront(int e)				// add to front of list
{
    add(head->next, e);
}

void DLL::addBack(int e)				// add to back of list
{
    add(tail, e);
}

void DLL::remove(DNode* v)		        // remove node v
{
    //DNode* u = v->prev;			 predecessor
    //DNode* w = v->next;			 successor
    v->prev->next = v->next;				// unlink v from list
    v->next->prev = v->prev;
    delete v;
    size--;
}

void DLL::removeFront() // remove from font
{
    remove(head->next);
}

void DLL::removeBack() // remove from back
{
    remove(tail->prev);
}

void DLL::printlist()
{
    DNode* tmp = head->next;
    while (tmp != tail)
    {
        cout << tmp->elm;
        tmp = tmp->next;
    }
    cout << endl;
    //cout<<"\t This is printlist function"<<endl;
}

int DLL::Element(int position) const
{
    int elem;
    DNode* tmp = head->next;
    for (int i = 1; tmp != tail; tmp = tmp->next)
    {
        elem = tmp->elm;
        if (i == position)    return elem;
        i++;
    }
}
/*_______________________________________________________________________________*/
class MyRational;       //to use myrational in myinteger.

class MyInteger
{
    friend class MyRational;
public:
    MyInteger();
    MyInteger(string s);
    MyInteger(const MyInteger& a);
    ~MyInteger();
    static MyInteger& parse(string s)
    {
        MyInteger* newobj = new MyInteger(s);
        return *newobj;
    }
    MyInteger& pow(MyInteger n);
    MyInteger& abs();
    MyInteger& operator+(MyInteger& a);
    MyInteger& operator-(MyInteger& a);
    MyInteger& operator*(MyInteger& a);
    MyInteger& operator/(MyInteger& a);
    MyInteger& operator%(MyInteger& b);
    MyInteger& operator++();
    MyInteger& operator--();
    MyInteger& operator++(int);
    MyInteger& operator--(int);
    MyRational& operator+(MyRational& b);
    MyRational& operator-(MyRational& b);
    MyRational& operator*(MyRational& b);
    MyRational& operator/(MyRational& b);
    bool operator<(MyInteger& b);
    bool operator>(MyInteger b);
    bool operator==(MyInteger& b);
    bool operator!=(MyInteger& b);
    bool operator<=(MyInteger& b);
    bool operator>=(MyInteger& b);
    MyInteger& operator>>(MyInteger& b);
    MyInteger& operator<<(MyInteger& b);
    friend ostream& operator<<(ostream& out, MyInteger& b);
private:
    int i;
    DLL lo;
};
/*_________________________________________________*/
MyInteger::MyInteger()
{
    lo.addBack(0);
}

MyInteger::MyInteger(string s) //_______OK_______
{
    for (i = 0; i < s.length(); i++)
    {
        lo.addBack(s[i] - 48);
    }
}

MyInteger::MyInteger(const MyInteger& b)
{
    while (!lo.isempty())    lo.removeFront();
    for (int i = 1; i <= b.lo.size; i++)
    {
        lo.addBack(b.lo.Element(i));
    }
}

MyInteger::~MyInteger()
{
    while (!lo.isempty()) lo.removeFront();
    //delete lo.head;
    delete lo.tail;
}

MyInteger& MyInteger::pow(MyInteger n)
{
    MyInteger* newobj = new MyInteger("");
    MyInteger tmp;
    newobj->lo.addFront(1);
    if (n.lo.front() == -3)
    {
        n.lo.removeFront();
        while (tmp < n)
        {
            *newobj = *newobj / (*this);
            tmp++;
        }
    }
    else
    {
        while (tmp < n)
        {
            *newobj = *newobj * (*this);
            tmp++;
        }
    }
    return *newobj;
}

MyInteger& MyInteger::abs()
{
    MyInteger* p = new MyInteger(*this);
    if (lo.front() == -3) p->lo.removeFront();
    return *p;
}
/*____________________________________________OPERATOR OVERLOADING*/

MyInteger& MyInteger::operator+(MyInteger& a)
{
    int carry = 0, num, flag = 0;
    MyInteger* add = new MyInteger("");
    MyInteger co(*this);
    MyInteger b(a);
    if (co.lo.front() == -3 && b.lo.front() != -3)
    {
        co.lo.removeFront();      *add = b - co;
    }
    else if (lo.front() != -3 && b.lo.front() == -3)
    {
        b.lo.removeFront();    *add = co - b;
    }
    else
    {
        if (co.lo.front() == -3)
        {
            co.lo.removeFront();
            b.lo.removeFront();
            flag = 1;
        }
        while (1)
        {
            if (co.lo.size != 0 && b.lo.size != 0)
            {
                num = co.lo.back() + b.lo.back() + carry;
                co.lo.removeBack();
                b.lo.removeBack();
            }
            else if (co.lo.size == 0)
            {
                num = b.lo.back() + carry;
                b.lo.removeBack();
            }
            else if (b.lo.size == 0)
            {
                num = co.lo.back() + carry;
                co.lo.removeBack();
            }
            carry = 0;
            if (num >= 10) carry++;
            add->lo.addFront(num % 10);
            if (co.lo.size == 0 && b.lo.size == 0)  break;
        }
        if (carry == 1)    add->lo.addFront(1);
        if (flag == 1)     add->lo.addFront(-3);
    }
    return *add;
}
/*_________________________________________OPERATOR " - "__________*/
MyInteger& MyInteger::operator-(MyInteger& a)
{
    MyInteger* newobj = new MyInteger("");
    MyInteger co(*this);
    MyInteger b(a);
    if (co == b)
    {
        newobj->lo.addFront(0); return *newobj;
    }
    int borrow = 0, num, flag = 0;
    if (co.lo.front() == -3 && b.lo.front() != -3)
    {
        b.lo.addFront(-3);      *newobj = b + (*this);
    }
    else if (co.lo.front() != -3 && b.lo.front() == -3)
    {
        b.lo.removeFront();    *newobj = (*this) + b;
    }
    else
    {
        if (co.lo.front() == -3)
        {
            co.lo.removeFront();
            b.lo.removeFront();
            if (co > b)    flag = 1;
        }
        else if (b > co)   flag = 1;
        if (co > b)
            while (co.lo.size != 0)
            {
                if (b.lo.size == 0)
                {
                    num = co.lo.back() - borrow;
                    co.lo.removeBack();
                }
                else if (b.lo.size != 0)
                {
                    num = co.lo.back() - b.lo.back() - borrow;
                    co.lo.removeBack();
                    b.lo.removeBack();
                }
                borrow = 0;
                if (num < 0)
                {
                    borrow++;  num = 10 + num;
                }
                newobj->lo.addFront(num);
            }
        else if (b > co)
            while (b.lo.size != 0)
            {
                if (co.lo.size == 0)
                {
                    num = b.lo.back() - borrow;
                    b.lo.removeBack();
                }
                else if (co.lo.size != 0)
                {
                    num = b.lo.back() - co.lo.back() - borrow;
                    co.lo.removeBack();
                    b.lo.removeBack();
                }
                borrow = 0;
                if (num < 0)
                {
                    borrow = 1;  num = 10 + num;
                }
                newobj->lo.addFront(num);
            }
        while (newobj->lo.front() == 0) newobj->lo.removeFront();
        if (flag == 1)     newobj->lo.addFront(-3);
    }
    return *newobj;
}
/*________________________________OPERATOR " * "______*/

MyInteger& MyInteger::operator*(MyInteger& a)
{
    MyInteger* newobj = new MyInteger;
    MyInteger copy("");
    MyInteger co(*this);
    MyInteger tmp1("");
    MyInteger b(a);
    int flag = 0, carry, num, l;
    if (co.lo.front() == -3)
    {
        co.lo.removeFront();  flag++;
    }
    if (b.lo.front() == -3)
    {
        b.lo.removeFront();    flag++;
    }
    l = b.lo.size;
    while (b.lo.size != 0)
    {
        carry = 0;
        for (i = 1; i <= co.lo.size; i++)
            copy.lo.addBack(co.lo.Element(i));
        while (copy.lo.size != 0)
        {
            num = copy.lo.back() * b.lo.back() + carry;
            carry = num / 10;
            tmp1.lo.addFront(num % 10);
            copy.lo.removeBack();
        }
        if (carry != 0)    tmp1.lo.addFront(carry);
        for (int j = 0; j < l - b.lo.size; j++) tmp1.lo.addBack(0);
        *newobj = *newobj + tmp1;
        while (!tmp1.lo.isempty())  tmp1.lo.removeFront();
        b.lo.removeBack();
    }
    if (flag == 1) newobj->lo.addFront(-3);
    return *newobj;
}
/*____________________________________________OPERATOR " / "______*/

MyInteger& MyInteger::operator/(MyInteger& a)
{
    MyInteger* newobj = new MyInteger;
    MyInteger tmp("");
    MyInteger co(*this);
    MyInteger b(a);
    if (b == *newobj)
    {
        cout << "division by zero" << endl;    return *newobj;
    }    //division by zero...
    int flag = 0, num, i;
    if (co.lo.front() == -3)
    {
        co.lo.removeFront();  flag++;
    }
    if (b.lo.front() == -3)
    {
        b.lo.removeFront();    flag++;
    }
    if (co < b)   return *newobj;
    while (!co.lo.isempty())
    {
        tmp.lo.addBack(co.lo.front());
        co.lo.removeFront();
        while (tmp.lo.size > 0 && tmp.lo.front() == 0)tmp.lo.removeFront();
        for (i = 0; tmp >= b; i++)
            tmp = tmp - b;
        newobj->lo.addBack(i);
    }
    while (newobj->lo.front() == 0) newobj->lo.removeFront();
    if (flag == 1) newobj->lo.addFront(-3);
    return *newobj;
}
/*_____________________________________________OPERATOR " % "_____*/

MyInteger& MyInteger::operator%(MyInteger& a)
{
    MyInteger* rem = new MyInteger("");
    MyInteger tmp(*this);
    MyInteger b(a);
    MyInteger zero;
    if (a == zero) { rem->lo.addFront(0); return *rem; }
    if (tmp.lo.front() == -3)
    {
        tmp.lo.removeFront();  cout << "First number is taken as positive" << endl;
    }
    if (b.lo.front() == -3)
    {
        b.lo.removeFront();    cout << "Second number is taken as positive" << endl;
    }
    while (!tmp.lo.isempty())
    {
        while (rem->lo.size > 0 && rem->lo.front() == 0)rem->lo.removeFront();
        rem->lo.addBack(tmp.lo.front());
        tmp.lo.removeFront();
        for (i = 0; *rem >= b; i++)
            *rem = *rem - b;
    }
    return *rem;
}



/*_______________________________________Increment & Decrement______*/

MyInteger& MyInteger::operator++()
{
    MyInteger one("1");
    *this = *this + one;
    return *this;
}

MyInteger& MyInteger::operator++(int)
{
    MyInteger one("1");
    *this = *this + one;
    return *this;
}
MyInteger& MyInteger::operator--()
{
    MyInteger one("1");
    *this = *this - one;
    return *this;
}
MyInteger& MyInteger::operator--(int)
{
    MyInteger one("1");
    *this = *this - one;
    return *this;
}

/*_________________________________INSTANCES___OF___MY_RATIONAL_______*/

/*____________________________________COMPARATOR OPERATORS___________*/
bool MyInteger::operator<(MyInteger& b)
{
    int flag = 0;
    if (lo.front() == -3 && b.lo.front() != -3)    return 1;
    if (lo.front() != -3 && b.lo.front() == -3)    return 0;
    if (lo.front() == -3) flag = 1;
    if (lo.size == b.lo.size)
    {
        for (i = 1; i <= lo.size; i++)
        {
            if (lo.Element(i) < b.lo.Element(i))       return (1 - flag);
            else if (lo.Element(i) > b.lo.Element(i))  return flag;
        }
    }
    else if (flag == 1)	return(lo.size > b.lo.size);
    else return(lo.size < b.lo.size);
}

bool MyInteger::operator>(MyInteger b)
{
    int flag = 0;
    if (lo.front() == -3 && b.lo.front() != -3)    return 0;
    if (lo.front() != -3 && b.lo.front() == -3)    return 1;
    if (lo.front() == -3) flag = 1;
    if (lo.size == b.lo.size)
    {
        for (i = 1; i <= lo.size; i++)
        {
            if (lo.Element(i) > b.lo.Element(i))       return (1 - flag);
            else if (lo.Element(i) < b.lo.Element(i))  return flag;
        }
    }
    else if (flag == 1)	return(lo.size < b.lo.size);
    else return(lo.size > b.lo.size);
}

bool MyInteger::operator==(MyInteger& b)
{
    return(!((*this<b || *this>b)));
}

bool MyInteger::operator!=(MyInteger& b)
{
    return (!((*this) == b));
}

bool MyInteger::operator<=(MyInteger& b)
{
    return (!((*this) > b));
}

bool MyInteger::operator>=(MyInteger& b)
{
    return (!((*this) < b));
}

MyInteger& MyInteger::operator>>(MyInteger& b)
{
    MyInteger* newobj = new MyInteger(*this);
    MyInteger tmp("2");
    tmp = tmp.pow(b);
    *newobj = (*newobj) / tmp;
    return *newobj;
}

MyInteger& MyInteger::operator<<(MyInteger& b)
{
    MyInteger* newobj = new MyInteger(*this);
    MyInteger tmp("2");
    tmp = tmp.pow(b);
    *newobj = (*newobj) * tmp;
    return *newobj;
}

ostream& operator<<(ostream& out, MyInteger& b)
{
    int i = 1;
    if (b.lo.front() == -3)
    {
        out << '-'; i = 2;
    }
    for (; i <= b.lo.size; i++)
        out << b.lo.Element(i);
    return out;
}

MyInteger& gcd(MyInteger& a, MyInteger& b)
{
    if (a.abs() >= b.abs()) {
        MyInteger x = a.abs() % b.abs();
        MyInteger y;
        if (x == y)
        {
            MyInteger* hcf = new MyInteger(b.abs());
            return *hcf;
        }
        else    return gcd(b, x);
    }
    if (a.abs() < b.abs()) {
        MyInteger x = b.abs() % a.abs();
        MyInteger y;
        if (x == y)
        {
            MyInteger* hcf = new MyInteger(a.abs());
            return *hcf;
        }
        else    return gcd(a, x);
    }
}
/*___________________________________________________RATIONAL_____________________________________*/


/*______________RATIONAL______________________RATIONAL____________________RATIONAL_________________*/

class MyRational
{
public:
    MyRational();
    MyRational(string s);
    MyRational(const MyRational& a);
    static MyRational parse(MyRational& a);
    MyRational& pow(MyInteger& n);
    MyRational& abs();
    MyInteger& intVal();
    MyInteger& floatVal();
    char* toString(int t);
    static MyRational& parse(string s)
    {
        MyRational* newob = new MyRational(s);
        return *newob;
    }
    MyRational& operator+(MyRational& a);
    MyRational& operator-(MyRational& a);
    MyRational& operator*(MyRational& a);
    MyRational& operator/(MyRational& a);
    MyRational& operator++();
    MyRational& operator--();
    MyRational& operator++(int);
    MyRational& operator--(int);
    bool operator<(MyRational& a);
    bool operator>(MyRational& a);
    bool operator==(MyRational& a);
    bool operator!=(MyRational& a);
    bool operator<=(MyRational& a);
    bool operator>=(MyRational& a);
    friend ostream& operator<<(ostream& out, MyRational& b);
    //private:
    MyInteger p;
    MyInteger q;
    friend class MyInteger;
};

MyRational::MyRational()
{
    q.lo.removeFront();
    q.lo.addBack(1);
}

MyRational::MyRational(string s)
{
    int i, flag = 0;
    p.lo.removeFront();
    q.lo.removeFront();
    for (i = 0; i < s.length(); i++)
    {
        if (flag == 1) q.lo.addBack(0);
        if (s[i] == '.') { flag = 1; q.lo.addBack(1); }
        else p.lo.addBack(s[i] - 48);
    }
    if (flag == 0)q.lo.addBack(1);
    MyInteger hc;
    if (gcd(p, q) != hc) {
        hc = gcd(p, q);
        p = p / hc;
        q = q / hc;
    }
}

MyRational::MyRational(const MyRational& a)
{
    p = a.p;
    q = a.q;
}

MyRational& MyRational::pow(MyInteger& n)
{
    MyRational* newob = new MyRational(*this);
    newob->p = newob->p.pow(n);
    newob->q = newob->q.pow(n);
    return *newob;
}

MyRational& MyRational::abs()
{
    MyRational* newob = new MyRational(*this);
    newob->p = p.abs();
    return *newob;
}

MyInteger& MyRational::intVal()
{
    MyInteger* n = new MyInteger(p / q);
    return *n;
}

MyInteger& MyRational::floatVal()
{
    int j;
    MyInteger* f = new MyInteger("");
    MyInteger tmp = p.abs() % q.abs();
    while (tmp.lo.size != 0 && (*f).lo.size < 20)
    {
        tmp.lo.addBack(0);
        while (tmp.lo.size > 0 && tmp.lo.front() == 0)tmp.lo.removeFront();
        //if(tmp.lo.size==0)break;
        for (j = 0; tmp >= q; j++)
            tmp = tmp - q;
        (*f).lo.addBack(j);
    }
    return *f;
}

char* MyRational::toString(int t)
{
    int i, j;
    MyInteger tmp = p.abs() / q;
    if (p.lo.front() == -3)tmp.lo.addFront(-3);
    MyInteger tmp1 = p.abs() % q;
    char* s = new char[tmp.lo.size + t + 1];
    for (i = 0; i <= tmp.lo.size; i++)
    {
        if (i < tmp.lo.size)
            s[i] = tmp.lo.Element(i + 1) + 48;
        else if (i == tmp.lo.size)
            s[i] = '.';
    }
    for (; i <= tmp.lo.size + t; i++)
    {
        tmp1.lo.addBack(0);
        while (tmp1.lo.size > 0 && tmp1.lo.front() == 0)tmp1.lo.removeFront();
        for (j = 0; tmp1 >= q; j++)
            tmp1 = tmp1 - q;
        s[i] = j + 48;
    }
    return s;
}

/*___________OVERLOADING____WITH___MYRATIONAL___AS RIGHT-SIDE___ARGUMENT___OF__MYINTEGER__________*/


MyRational& MyInteger::operator+(MyRational& b)
{
    MyRational q;
    q.p = (*this);
    MyRational* newobj = new MyRational(q + b);
    return *newobj;
}
MyRational& MyInteger::operator-(MyRational& b)
{
    MyRational q;
    q.p = (*this);
    MyRational* newobj = new MyRational();
    *newobj = q - b;
    return *newobj;
}
MyRational& MyInteger::operator*(MyRational& b)
{
    MyRational q;
    q.p = (*this);
    MyRational* newobj = new MyRational(q * b);
    return *newobj;
}
MyRational& MyInteger::operator/(MyRational& b)
{
    MyRational q;
    q.p = (*this);
    MyRational* newobj = new MyRational(q / b);
    return *newobj;
}

/*____________________________RATIONAL____OPERATOR_____OVERLOADING____________________*/

MyRational& MyRational::operator+(MyRational& a)
{
    int flag = 0;
    MyRational* newob = new MyRational();
    newob->p = p * a.q + a.p * q;
    newob->q = q * a.q;

    MyInteger hc;
    if (gcd(p, q) != hc) {
        hc = gcd(p, q);
        p = p / hc;
        q = q / hc;
    }
    return *newob;
}

MyRational& MyRational::operator-(MyRational& a)
{
    int flag = 0;
    MyRational* newob = new MyRational();
    newob->p = p * a.q - a.p * q;
    newob->q = q * a.q;
    MyInteger hc;
    if (gcd(newob->p, newob->q) != hc) {
        hc = gcd(newob->p, newob->q);
        newob->p = newob->p / hc;
        newob->q = newob->q / hc;
    }
    return *newob;
}

MyRational& MyRational::operator*(MyRational& a)
{
    MyRational* newob = new MyRational();
    newob->p = p * a.p;
    newob->q = q * a.q;
    MyInteger hc;
    if (gcd(newob->p, newob->q) != hc) {
        hc = gcd(newob->p, newob->q);
        newob->p = newob->p / hc;
        newob->q = newob->q / hc;
    }
    return *newob;
}

MyRational& MyRational::operator/(MyRational& a)
{
    MyRational* newob = new MyRational();
    newob->p = p * a.q;
    newob->q = q * a.p;
    if (newob->p.lo.front() == -3 && newob->q.lo.front() == -3)
    {
        newob->p.lo.removeFront();
        newob->q.lo.removeFront();
    }
    else if (newob->q.lo.front() == -3)
    {
        newob->q.lo.removeFront();
        newob->p.lo.addFront(-3);
    }
    MyInteger hc;
    if (gcd(newob->p, newob->q) != hc) {
        hc = gcd(newob->p, newob->q);
        newob->p = newob->p / hc;
        newob->q = newob->q / hc;
    }
    return *newob;
}

MyRational& MyRational::operator++()
{
    p = p + q;
    return *this;
}
MyRational& MyRational::operator++(int)
{
    p = p + q;
    return *this;
}
MyRational& MyRational::operator--()
{
    p = p - q;
    return *this;
}
MyRational& MyRational::operator--(int)
{
    p = p - q;
    return *this;
}

bool MyRational::operator<(MyRational& a)
{
    return(p * a.q < q* a.p);
}

bool MyRational::operator>(MyRational& a)
{
    return(p * a.q > q * a.p);
}

bool MyRational::operator==(MyRational& b)
{
    return(!((*this<b || *this>b)));
}

bool MyRational::operator!=(MyRational& b)
{
    return (!((*this) == b));
}

bool MyRational::operator<=(MyRational& b)
{
    return (!((*this) > b));
}

bool MyRational::operator>=(MyRational& b)
{
    return (!((*this) < b));
}

ostream& operator<<(ostream& out, MyRational& b)
{
    char* st;
    st = b.toString(15);
    out << st;
    return out;
}
/*_______________________________________________________________________________________________*/
int main()
{
    MyRational x, y;
    string num, op;
    string s1, s2;
    int opt;
    cout << "Enter '1' To check the boolean operations" << endl;
    cout << "Enter '2' to input an Expression" << endl;
    cin >> opt;
    switch (opt)
    {
    case 1:
        cout << "Enter 1st Rational number" << endl;
        cin >> s1;
        x = x.parse(s1);
        cout << "Enter 2nd Rational number" << endl;
        cin >> s2;
        y = y.parse(s2);
        if (x < y)cout << "x<y" << endl;
        if (x > y)cout << "x>y" << endl;
        if (x == y)cout << "x=y" << endl;
        if (x != y)cout << "x!=y" << endl;
        if (x <= y)cout << "x<=y" << endl;
        if (x >= y)cout << "x>=y" << endl;
        break;
    case 2:
        cout << "Enter the terms in a valid order: " << endl;
        cin >> num;
        MyRational answer(num);
        while (1)
        {
            cin >> op;
            if (op[0] == '$')
            {
                cout << "The final answer is: " << answer << endl;
                break;
            }
            cin >> num;
            MyRational n(num);
            if (op[0] == '+')
            {
                answer = answer + n;
            }
            else if (op[0] == '-')
            {
                answer = answer - n;
            }
            else if (op[0] == '*')
            {
                answer = answer * n;
            }
            else if (op[0] == '/')
            {
                answer = answer / n;
            }
            else if (op[0] == 'p')
            {
                MyInteger k(num);
                answer = answer.pow(k);
            }
        }
        break;
    }
    return 0;
}