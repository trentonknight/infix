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
char topStack(Stack*);
void postFIX(Stack*);
bool valueMonster(char,char);


int main(int argc,char *argv[]){
  int a = 0;
  char flip;
  string fix = argv[1];

  Stack *infix = new(nothrow) Stack;
  if(!infix){
    cout << "Allocation Error!" << endl;
  }
  Stack *reverse = new(nothrow) Stack;
  if(!reverse){
    cout << "Allocation Error!" << endl;
  }
  createStack(infix);

  while(fix[a] != '\000'){
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
char topStack(Stack* pop){
  char outData;

  outData = pop->top->data;

  return outData;
}
void postFIX(Stack *in){
  Stack *postList = new(nothrow) Stack;
  if(!postList){
    cout << "Allocation Error!" << endl;
  }
  int index = 0, read = 0;
  char post, stackTop, clearStack;
  char expression[20];
  bool great = true;
  
  while(in->top != 0){
    post = popStack(in);
    if(post == '('){
    pushStack(postList,post);
    }
    if(post == ')'){
      post = popStack(in);
      if(postList->top != 0){
      	  clearStack = popStack(postList);
      	  expression[index] = clearStack;
      	  index++;
      }
    }
    if(post == '*'||post == '+'||post == '-'||post == '/'||post == '('){
      if(postList->top == 0){
	pushStack(postList,post);
      }
      else{
	stackTop = topStack(postList);
        great = valueMonster(post,stackTop);
        if(great){
          pushStack(postList,post);
	}
        else{
            clearStack = popStack(postList);
            expression[index] = clearStack;
            index++;
            pushStack(postList,post);
	}
      }   
    }
    else{
      expression[index] = post;
      index++;
    }
  }
  if(postList->top != 0){
    while(postList->top != 0){
      clearStack = popStack(postList);
      expression[index] = clearStack;
      index++;
    }
  }
  
  while(expression[read] != '\000'){
    cout << expression[read];
    read++;
  }
  cout << endl;

  cin.get(); 
}
bool valueMonster(char topChar,char currChar){
  bool greater = false;
  
  if((topChar == '*' || topChar == '/') && (currChar == '+' || currChar == '-')){
    greater = true;
  }
  if(topChar == '('){
    greater = true;
  }
  return greater;
}
