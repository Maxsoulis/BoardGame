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
int moveBack(node* &currentNode,node* firstNode  ){
    cout << currentNode->value << '\n';
    int value = currentNode->value;
    for(int i = 0; i >  value; value++){
        cout << "Moving back 1" << '\n';
        if(currentNode->prev == NULL){
            currentNode = firstNode;
            cout << "You hit a    ";
            printSquare (currentNode ->type, currentNode->value) ;
            cout << '\n';
            return currentNode->value;
            
        }
            currentNode = currentNode->prev;
    }
   
    return currentNode->value;
}
int moveForward(node* &headNode, node* firstNode, int spaces ){
     
    int addscore = 0;
    for(int i = 0; i < spaces; i++)
    {
        
        if(headNode->next == NULL){
            cout << "You hit a +" << headNode->value << '\n';
             addscore = headNode->value;
            headNode = NULL;
            return addscore;
        }
        headNode = headNode->next;
    }
    // checking if the next square type is a move tile
    while(true){
        if(headNode->type == 'M'){
            cout << "You hit a ";
            printSquare(headNode->type, headNode->value);
            cout << '\n';
            if(headNode ->value > 0){
                int value = headNode ->value;
                for(int i = 0; i < value; i++){
                cout << "Moving 1" << '\n';
                if(headNode->next == NULL)
               {    
                   cout << "You hit a + "  << headNode->value << '\n';
                   addscore = headNode->value;
                   headNode = NULL;
                   
                   return addscore;
                   
               }
               
                   headNode = headNode -> next;
               
            }
                break;
            }
            else{
               
                moveBack(headNode, firstNode);
                break;
            }
        }
             else{
                break;
            }
        
            
    }
        
        cout << "You hit a ";
        printSquare(headNode->type, headNode->value) ;
        cout << '\n';
        addscore = headNode->value;
        return addscore;
    
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
    int totalSpacesOnTop = size - 2 ;
    int difference =  totalSpacesOnTop - 6;
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
double specialSquare(char type){
    if(type == '!'){
        cout << "Do you want to double your score and risk it all?" << '\n';
        char doubleOrNothingInput;
        cout << "(y/n) "; 
        while(true)
        {
            cin >> doubleOrNothingInput;
            if(doubleOrNothingInput == 'y'){
                double multiplyTwo = 2;
                double dividedTwo = 0.5;
                int chance = rand() % 10;
                if(chance >=7){
                    return dividedTwo;
                }
            else{
                return multiplyTwo;
            }
             
        }
        else if(doubleOrNothingInput == 'n'){
            return 1;
        }
        else {
            cout << "Enter (y/n) ";
        }
            
        }
    }
    else {
        return 1;
    }
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
    int squares = 44;
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
            last->next = NULL;
            }
    }
     
    copyOfLast = last;
    char rollDice;
    double playerScore = 0;
    int previousValue = head->value;
    
     //main game loop
    while(head != NULL){
        
         printBoard(head , firstNode, last,copyOfLast , squares);
         cout << "Score: " << playerScore << '\n';
          double multiply = specialSquare(head->type);
         
         while(true){
            cout << "Enter r to roll the dice" << '\n';
            cin >> rollDice;
            head->value = previousValue;
             if(rollDice == 'r'){
                 int moves = rand() % 6 + 1;
                 cout << "You rolled a " <<  moves << '\n';
                 
                 int addToScore = moveForward(head,firstNode, moves);
                  
                 playerScore *= multiply;
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
