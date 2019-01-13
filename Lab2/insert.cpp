#include <iostream>
using namespace std;

struct Node {
   int key;
   Node* next;
};

void insert(Node* & lst, int k, int posn) {
 // assume: 1 <= posn <= length of lst + 1
if (lst == NULL) {
     //in this case, posn must be 1
       lst = new Node();
       lst->key = k;
       lst->next = NULL;
     }
    else if (posn == 1) {
       Node* lst1 = new Node();
       lst->key = k;
       lst1->next = lst;
       lst1 = lst;
     }
   else
      insert(lst->next, k, posn-1);
  }

void delete1 (Node* & lst, int posn) {
// delete the item in position posn of the list
// assume 1 <= posn <= length of the list
if (posn == 1) 
   lst = lst->next;
else
  delete1(lst->next,posn-1);
}

void print(Node* lst) {
   if (lst!= NULL) {
      if (lst->next == NULL) 
          cout << lst->key;
      else {
       cout << lst->key << "," ;
       print(lst->next);
    }
   }
  cout << endl;
}

int main() {
   Node* mylst = new Node();
   for (int j = 1; j < 11; j++) 
     insert(mylst, j, j);
   print(mylst);
   delete1(mylst, 3);
   print(mylst);
}
