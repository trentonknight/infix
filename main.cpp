#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

struct Stack{
  char data;
  int count;
  Stack *top;
  Stack *next;
};

Stack *createStack(Stack*);
Stack *pushStack(Stack* ,char);
char popStack(Stack*);
void postFIX(Stack*);



int main(){
  int a = 0;
  char flip;
  string fix = " (A+(B*C)) ";
  Stack *infix = new(nothrow) Stack;
  if(!infix){
    cout << "Allocation Error!" << endl;
  }
  Stack *reverse = new(nothrow) Stack;
  if(!reverse){
    cout << "Allocation Error!" << endl;
  }
  createStack(infix);

  while(fix[a] != '\0'){
    pushStack(infix,fix[a]);
    a++;
  }
  //pop and restack to get ordered list
  while(infix->top->next != 0){
   flip = popStack(infix);
   pushStack(reverse,flip);
  }
  ///now take ordered stack and change to
  ///postfix
  postFIX(reverse);

  return 0;
}
Stack *createStack(Stack* first){

  first->count = 0;
  first->top = 0;
  first->next = 0;
  first->data = '\0';

  return first;
}
Stack *pushStack(Stack* push,char data){
  Stack *newPtr = new(nothrow) Stack;
  if(!newPtr){
    cout << "Allocation Error!" << endl;
  }  
  else{
    //append new data to node and 
    //add to the stack
    newPtr->data = data;
    newPtr->next = push->top;
    push->top = newPtr;
    push->count = push->count + 1;
  }
  return push;
}
char popStack(Stack* pop){
  char outData;
  Stack *dltPtr;
   
  //pointer to address of node
  //to be deleted
  dltPtr = pop->top;
  //grab character data
  outData = pop->top->data;
  //traverse
  pop->top = pop->top->next;
  //decrement count
  pop->count = pop->count - 1;
  //delete un-needed node
  delete dltPtr;
  //return character data.
  return outData;
}
void postFIX(Stack *in){
  Stack *postList = new(nothrow) Stack;
  if(!postList){
    cout << "Allocation Error!" << endl;
  }
  int index;
  char post;
  char expression[20];
  
  while(in->top->next != 0){
   post =  popStack(in);
   if(post == '('){
     //open bracket
     pushStack(postList,post);
   }
   if(post == ')'){
     //closed bracket
     while(post == ')' && postList != 0){
       expression[index] = post;
       post =  popStack(in);
     }
   }
   if(post == '*' || post == '+' || post == '-'|| post == '/'){
     //operators
     while((post == '*' || post == '+' || post == '-'|| post == '/') && (postList != 0)){
      
     }
   }
   index++;
  }
  cin.get(); 
}
