#include <stdio.h>
#include <iostream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

class myString
{
public:
  myString():len(0),data(NULL)
  {};
  myString(char *p);
  myString(myString &s);
  myString& operator=(myString &s);
  myString& operator+(myString &s); 
public:
  ~myString()
  {
	if(data)
	  delete data;
	len = 0;
  }  
public:
  int length(){return len;}  
  const char *c_str(){return data;} 
  
private:  
int len;
char * data;
friend ostream& operator<<(ostream& os,myString &s);
};

inline myString::myString(char* p)
{
  if(!p){
	data=NULL;
	len=0;
  } else {
    len=strlen(p);
	data = new char[len + 1];
	if(!data)
	  throw 1;
    strcpy(data,p);
  }	
}

inline myString::myString(myString &s)
{
	if(0 == s.length()) {
	  len = 0;
	  data = NULL;
	} else {
	  len = s.length();
	  data = new char[len + 1];
	  if(!data)
	    throw 1;
	  strcpy(data,s.c_str());
	}  
}

myString& myString::operator=(myString &s)
{
  if(this == &s)
    return *this;
  delete data;	
  if(0 == s.length()) {
	data =NULL;
    len = 0;
  } else {
    len = s.length();
    data = new char[len + 1];
	if(!data)
	  throw 1;
	strcpy(data,s.c_str());
  }
  return *this;
}

myString& myString::operator+(myString &s)
{
  if(0 == s.length())
    return *this;
  if(!data) {
	  len = s.length();
      data = new char[len + 1];
	  if(!data)
	    throw 1;
	  strcpy(data,s.c_str());
  } else {
    len +=s.length();
    char *p = new char[len+1];
	strcpy(p,data);
	strcat(p,s.c_str());
	delete data;
	data = p;
	p =NULL;
  }
  return *this;
    
  return *this;
}

ostream& operator<<(ostream& os,myString &s)
{
 os<<s.data;
 return os;
}


template <typename T>
struct Node{
  T value;
  struct Node<T> * next;
};


template <typename T>
class list_iterator
{
  typedef T* point_type;
  typedef T& ref_type;
  typedef T  value_type;
  typedef struct Node<T>* node_type;
public:
  list_iterator():node(NULL){}
  list_iterator(node_type x):node(x){}
  ~list_iterator(){node = NULL;}
public:
  node_type operator++();
  node_type operator++(int);
  ref_type  operator*();
  point_type operator->();
  bool operator!=(list_iterator<T> s);  
private:
  node_type  node;
};

template <typename T>
typename list_iterator<T>::node_type list_iterator<T>::operator++(){
  if(!node)
    return node;
  node_type p = node;
  node = node->next;
  return p;
}

template <typename T>
typename list_iterator<T>::node_type list_iterator<T>::operator++(int i){
  if(!node)
    return node;
  node = node->next;
  return node;
}

template <typename T>
typename list_iterator<T>::point_type list_iterator<T>::operator->(){
  return &(node->value);
}

template <typename T>
typename list_iterator<T>::ref_type list_iterator<T>::operator*(){
  return node->value;
}

template <typename T>
bool list_iterator<T>::operator!=(list_iterator<T> s){
  return (node!=s.node);
}

template <typename T>
class mylist
{
public:
typedef Node<T> N;
typedef list_iterator<T> iterator;
public:
  mylist():node(NULL){}
  mylist(mylist &l);
  ~mylist();
public:
  mylist& operator=(mylist &l);  
public:
  void clear();
  //void erese(T &e);
  void insert(T &i);
  iterator begin();
  iterator end();
    
private:
  N* node;
};

template <typename T>
mylist<T>::mylist(mylist &l){
  node = l.begin();
}
template <typename T>
mylist<T>::~mylist(){
  clear();
}

template <typename T>
void mylist<T>::clear() {
  while(node){
    N* p=node;
	node=node->next;
	delete p;
  }
}

template <typename T>
void mylist<T>::insert(T &i) {
  if(!node){
    node = new N;
	(*node).value=i;
  } else{
    N* p = new N;
	(*p).value=i;
	p->next=node;
	node=p;
  }
}

template <typename T>
typename  mylist<T>::iterator mylist<T>::begin() {
  return node;
}


template <typename T>
typename mylist<T>::iterator mylist<T>::end() {
  return NULL;
}

class StringTest : public testing::Test {
public:  
  virtual void SetUp() {
    a_.append("hello");
    b_.append("world");
  }
  virtual void TearDown() {
    printf("run my test\n");
  }

public:
string a_;
string b_;
};

TEST_F(StringTest, DefaultConstructor) {
  // You can access data in the test fixture here.
  EXPECT_EQ(0, strcmp(a_.c_str(), "hello"));
  EXPECT_EQ(0, strcmp(b_.c_str(), "hello"));
}

// Tests the c'tor that accepts a C string.
TEST(string, test) {
  string a("world");
  string b("hello");
  EXPECT_EQ(0, strcmp(a.c_str(), "world"));
  EXPECT_EQ(0, strcmp(b.c_str(), "hello"));
}

TEST(mylist, test) {
  string a("world");
  string b("hello");
  EXPECT_EQ(0, strcmp(a.c_str(), "world"));
  EXPECT_EQ(0, strcmp(b.c_str(), "hello"));
}


/*
int main(){
  string a("world");
  string b("hello");
  cout<<a<<"_"<<b<<"_"<<endl;
  mylist<string> list;
  list.insert(a);
  list.insert(b);
  mylist<string>::iterator iter;
  for(iter=list.begin();iter!=list.end();iter++)
   cout<<*iter;
  return 1;
}
*/
struct quene_s
{
struct quene_s* pre; 
struct quene_s* next;
};
typedef struct quene_s quene_t;

typedef struct testNode
{
char* str;
quene_t q;
int num;
}testNode_;

void quene_init(quene_t* h){
  h->pre=h->next=NULL;
}

bool quene_empty(quene_t* h){
  if(h->pre == NULL && h->next == NULL)
    return true;
  return false;
}

void quene_insert_head(quene_t* h,quene_t* x){
  quene_t* tmp=h->next;
  if(!quene_empty(h)) {
  h->next=x;
  x->pre=h;
  x->next=tmp;
  tmp->pre=x;
  } else {
  h->next=x;
  x->pre=h;
  x->next=NULL;
  }
}

void quene_insert_tail(quene_t* h,quene_t* x){
  quene_t* tmp=h;
  while(tmp->next){
    tmp=tmp->next;
  }
  tmp->next=x;
  x->pre=tmp;
  x->next=NULL;
}

void quene_remove(quene_t* x) {
  if(x->pre == NULL)
    return;
  if(x->next == NULL) {
    x->pre->next = x->next;
	return;
  }
  x->pre->next = x->next;
  x->next->pre=x->pre;
}


void quene_print(quene_t* h) {
  quene_t* tmp=h;
  while(tmp->next){
    testNode_* Node = (testNode_*)((unsigned char*)tmp->next -offsetof(testNode_,q));  
	printf("%s,%d\n",Node->str,Node->num);
	tmp=tmp->next;
  }
}



int main(int argc, char **argv) {
  quene_t head;
  quene_init(&head);
  testNode_ Node1,Node2;
  Node1.str="hello";
  Node1.num=1;
  Node2.str="world";
  Node2.num=2;
  
  quene_insert_head(&head,&Node1.q);
  quene_insert_tail(&head,&Node2.q);
  quene_remove(&Node2.q);
   quene_remove(&Node1.q);

  quene_print(&head);
  //::testing::InitGoogleTest(&argc, argv);
  //return RUN_ALL_TESTS();
}














