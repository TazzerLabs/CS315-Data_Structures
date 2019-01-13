#include <iostream>
const int MSIZE = 1000;

using namespace std;

class Node {

  public:
   Node(int x) {
    key = x;
    next = 0;
  }

  public:
     int key;
     Node* next;
 };

class List {

public:
List() {
  head = 0;
}

List(int x) {
 head = new Node(x);
}

void increment() {
// increment the first member of the list
if (head == 0) return;
 else ++head->key;
 }

void insert(int k) {
 // insert k as the first item of the list
 Node* tmp = new Node(k);
 tmp->next = head;
 head = tmp;
 }

void print() {
 Node* temp = head;
 cout << "{";
 while (temp != 0) {
  cout << temp->key;
  if (temp->next!= 0) cout << ", ";
  temp = temp->next;
  }
  cout << "}";
  cout << endl;
 }

 public:
 Node* head;
};

class prj1{

public:
List* mems[MSIZE];
int current; // current number of lists filled
int size; // size of mems

public:
prj1(int n) {
  size = n;
  for (int j=0; j < n; ++j)
   mems[j] = 0;
  current = n;
}


void print() {
 int len = current;
 for (int j = 0; j < len; ++j)
   mems[j]->print();
 }

static int power(int x, int n) {
if (n == 0) return 1;
if (n == 1) return x;
if (n% 2 == 1) return x*power(x, n-1);
else
 { int temp = power(x, n/2);
   return temp * temp;
 }
}

static prj1 merge(prj1 L1, prj1 L2) {
 int s1 = L1.current;
 int s2 = L2.current; int s = s1 + s2;
 // prj1 tmp = new prj1(s);
 prj1 tmp(s);
 for (int i = 0; i < s1; ++i)
   tmp.mems[i] = L1.mems[i];
 for (int i = 0; i < s2; ++i)
   tmp.mems[s1+i] = L2.mems[i];
 return tmp;
 }

static prj1 build(int a[], int s) {
 // build all subsets of {1, 2, ... , s} as an array of lists.
 // assume that s <= a.length
 if (s == 0) {
	 prj1 x(1);
	 x.mems[0] = new List();
	 x.size = 1; return x;
   }
 else if (s == 1) {
   prj1 x(2);
   x.mems[0] = new List();
   x.mems[1] = new List(a[0]); x.current = 2; x.size = 2; return x;
  }
 else
  {
   prj1 L1 = build(a,s-1);
   prj1 L2 = build(a, s-1);  // copying will be more efficient
   int pow = L2.size;
   for (int k = 0; k < pow; ++k)
    L2.mems[k]->insert(a[s-1]);
   prj1 L = merge(L1, L2);
   return L;
  }
 }
};

int main() {
 int s;
 cout << "Enter the size of the set." << endl;
 cin >> s;
 int a[s];
 if (s!= 0)
   cout << "Enter the elements of the set." << endl;
 for (int j=0; j < s; ++j)
   cin >> a[j];
 prj1 temp = prj1::build(a, s);
 cout << "The subsets are: " << endl;
 temp.print();
 }
