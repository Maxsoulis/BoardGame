// Online C++ compiler to run C++ program online
#include <iostream>
#include <stdlib.h> 
#include <string>
using std::string;
using std::cin;
using std::cout;
struct node{
    char type; 
    int value, position;
    struct node* next;
    struct node* prev;
        node(){}
    node(int value, node * p): value(value), next(p) {}
    ~node(){}
};
void printSquare(char type, int value){
    string positive;
    if(value > 0){
        positive = "+";
    }
   if(value == 0 && type != '!'){
        cout << " P  ";
        return;
    }
    
   switch(type){
       case '!': {
           cout << " !  ";
           break;
       }
       case 'M': {
           cout << "M" << positive << value << " ";
           break;
       }
       case 'S': {
           cout << "S" << positive << value << " ";
           break;
       }
       
   }
}
int moveBack(node* &headNode,node* firstNode, int numSquares ){
     
    for(int i = 0; i < numSquares; i++){
        if(headNode->prev == NULL){
            headNode = firstNode;
            cout << "You hit a ";
            printSquare (headNode ->type, headNode->value) ;
            cout << '\n';
            return headNode->value;
            
        }
            headNode = headNode->prev;
    }
    cout << "You hit a ";
    printSquare (headNode->type, headNode->value);
    cout << '\n';
    return headNode->value;
}
int moveForward(node* &headNode,node* firstNode, int spaces ){
    for(int i = 0; i < spaces; i++)
    {
        if(headNode->next == NULL){
            cout << "You hit a +" << headNode->value << '\n';
            int addscore = headNode->value;
            headNode = NULL;
            return addscore;
        }
        headNode = headNode->next;
    }
    while(true)
        {if(headNode->type == 'M'){
            if(headNode ->value > 0)
            {for(int i = 0; i< headNode->value; i++){
                headNode = headNode->next;
            }}
            else{
                moveBack(headNode, firstNode, spaces);
                
            }
            }
             else{
                break;
            }
        
            
        }
        cout << "You hit a ";
        printSquare(headNode->type, headNode->value) ;
        cout << '\n';
        return headNode->value;
    
}
 
void generateTypes(char types[], int size){
  
    for(int i = 0; i < size; i++){
        int max = 100;
        int number = rand() % max;
        if(number >= 85){
            types[i] = '!';
        }
        else if(number <= 25){
            types[i] = 'M';
        }
        else{
            types[i] = 'S';
        }
   
    }
}
void generateValues(int vals[], char types[], int size){
    
    for(int i = 0; i < size; i++)
    {
        char type = types[i];
        if(type != '!')
        {
            int subtract = rand() % 10;
            int value = rand() % 10 - subtract;
            if(value == 0){
                value += 1;
            }
            vals[i] = value;
        }
        else 
        {
            vals[i] = 0;
        }
    }
}

void printBoard(node* headNode,node* resetHead, node* last, node* resetLast, int size){
   headNode = resetHead;
    int row = size/4;
    int totalSpacesOnTop = (size/2) + (size/4) - 1 ;
    int difference =  totalSpacesOnTop - 1;
    //prints top row
    for(int i = 0; i < row; i++){
 
        printSquare (headNode-> type, headNode->value);
   
        headNode = headNode ->next;
        size -=1;
    }
    cout << '\n';
    //prints sides
    for(int i = size; i > row; i-=2){
        printSquare (last->type,last-> value);
        for(int i = 0; i < difference; i++){
            cout << " ";
        }
        printSquare (headNode ->type, headNode-> value);
        last = last->prev;
        headNode = headNode->next;
        cout << '\n';
    }
    //prints bottom row
    for(int i = 0; i < row; i++){
        printSquare (last->type, last->value);
        last = last->prev;
    }
    cout << '\n';
}
int main() {
    srand((unsigned) time(NULL));
 
    node* temp;
    node* last = NULL ;
    node* head = NULL;
    node* firstNode;
    node* copyOfLast;
    node* result  ;
    // regulates board size
    int squares = 24;
    if((squares % 4 != 0) || squares >= 100 || squares < 16 ){
        cout << "Error, Invalid Size" << '\n';
        return 0;
    }
    // sets up the value and type generation
    int values[squares];
    char types[squares];
    generateTypes(types, squares);
    generateValues(values,types, squares);
    //sets up the doubly linked list
    for(int i = squares; i > 0; i-- ){
     
            
            if(i == squares){
                result = new node();
                result->value = values[i - 1];
                result->type = types[i -1];
                result->position = i;
                result ->prev = NULL;
                head = result;
                firstNode = result;
                temp = result;
            }
            else{
            result = new node();
            result->value = values[i -1];
            result->type = types[i-1];
            result->position = i;
            result->prev = temp;
            temp-> next = result;
            temp = result; 
            temp->next = result;
            last = temp;
            }
    }
    copyOfLast = last;
    char rollDice;
    int playerScore = 0;
    int previousValue = head->value;
     //main game loop
    while(head != NULL){
        
         printBoard(head , firstNode, last,copyOfLast , squares);
         cout << "Score: " << playerScore << '\n';
         while(true){
            cout << "Enter r to roll the dice" << '\n';
            cin >> rollDice;
            head->value = previousValue;
             if(rollDice == 'r'){
                 int moves = rand() % 6 + 1;
                 
                 cout << "You rolled a " <<  moves << '\n';
                 int addToScore = moveForward(head,firstNode, moves);
                 
                 playerScore+= addToScore;
                 if(head != NULL){
                 previousValue = head->value;
                 head->value = 0;}
                 else{ cout << "Final Score" << playerScore;
                 return 0;}
                 break;
             }
         }
    }
    return 0;
}
