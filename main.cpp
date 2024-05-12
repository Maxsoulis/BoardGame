// Online C++ compiler to run C++ program online
#include <iostream>
#include <stdlib.h> 
using std::cin;
using std::cout;
struct node{
    int value, position;
    struct node* next;
    struct node* prev;
        node(){}
    node(int value, node * p): value(value), next(p) {}
    ~node(){}
};
void printValue(int value){
    if(value > 0){
        cout << "+" << value << " " ;
    }
    else if(value == 0){
        cout << " P ";
    }
    else{
        cout << value << " " ;
    }
}
int moveForward(node* &headNode, int spaces ){
    for(int i = 0; i < spaces; i++)
    {
        if(headNode->next == NULL){
            cout << "You hit a + " << headNode->value << '\n';
            int addscore = headNode->value;
            headNode = NULL;
            return addscore;
        }
        headNode = headNode->next;
    }
        cout << "You hit a + " << headNode->value << '\n';
        return headNode->value;
    
}
void moveBack(node* &headNode, node* temp, int numSquares, int currentSquare){
    headNode = temp;
    int newSquare = currentSquare - numSquares;
    for(int i = newSquare; i > 0; i--){
        headNode = headNode->next;
    }
}
void generateValues(int(&vals)[], int size){
    
    for(int i = 0; i < size; i++)
    {
        int subtract = rand() % 10;
        int value = rand() % 10 - subtract;
        if(value == 0){
            value += 1;
        }
        vals[i] = value;
        
    }
        
    
}
void printBoard(node* headNode,node* resetHead, node* last, node* resetLast, int size){
   headNode = resetHead;
    int row = size/4;
    int totalSpacesOnTop = (size/2) + (size/4) - 1 ;
    //four  for the top beginning and end two characters and one for the extra space created in the print function
    int difference =  totalSpacesOnTop - 5;
    //prints top row
    for(int i = 0; i < row; i++){
        printValue(headNode->value);
        headNode = headNode ->next;
        size -=1;
    }
    cout << '\n';
    //prints sides
    for(int i = size; i > row; i-=2){
        printValue(last-> value);
        for(int i = 0; i < difference; i++){
            cout << " ";
        }
        printValue(headNode-> value);
        last = last->prev;
        headNode = headNode->next;
        cout << '\n';
        
    }
    //prints bottom row
    for(int i = 0; i < row; i++){
        printValue(last->value);
        last = last->prev;
        
    }
    
    cout << '\n';
}
int main() {
   
    
    // Write C++ code here
    srand((unsigned) time(NULL));
 
    node* temp = new node();
    node* last ;
    node* head = NULL;
    node* copyOfHead;
    node* copyOfLast;
    node* result  ;
    int squares = 24;
    if((squares % 4 != 0) || squares >= 100 || squares < 16 ){
        cout << "Error, Invalid Size" << '\n';
        return 0;
    }
 
    int values[squares];
    generateValues(values, squares);
 
    for(int i = squares; i > 0; i-- ){
     
            
            if(i == squares){
                result = new node();
                result->value = values[i - 1];
                result->position = i;
                result ->prev = NULL;
                head = result;
                copyOfHead = result;
                temp = result;
                
                
            }
            else{
            result = new node();
            result->value = values[i -1];
            result->position = i;
            result->prev = temp;
            temp-> next = result;
            temp = result; 
            }
            last = temp;
    }
    copyOfLast = last;
    char rollDice;
    int playerScore = 0;
    int previousValue = head->value;
    while(head != NULL){
         printBoard(head , copyOfHead, last,copyOfLast , squares);
         cout << "Score: " << playerScore << '\n';
         while(true){
            cout << "Enter r to roll the dice" << '\n';
            cin >> rollDice;
            head->value = previousValue;
            cout << "Setting value to " << previousValue << '\n';
             if(rollDice == 'r'){
                 int moves = rand() % 6 + 1;
                 
                 cout << "You rolled a " <<  moves << '\n';
                 int addToScore = moveForward(head, moves);
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
