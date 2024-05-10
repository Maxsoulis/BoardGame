// Online C++ compiler to run C++ program online
#include <iostream>
#include <stdlib.h> 
using std::cin;
using std::cout;
struct node{
    int value, position;
    struct node* next;
        node(){}
    node(int value, node * p): value(value), next(p) {}
    ~node(){}
};
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
        vals[i] = value;
    }
}
void printBoard(node* headNode, int size){
    int row = size/4;
    for(int i = 0; i < row; i++){
        if(headNode -> value >= 0){
        cout << "+" <<  headNode->value << " " ;
        }
        else{
            cout << headNode -> value << " ";
        }
        headNode = headNode ->next;
        size -=1;
    }
    cout << '\n';
    for(int i = size; i >row ; i -= 2){
        if(headNode -> value >= 0){
            cout << "+" << headNode ->value;
        }
        else
        {cout << headNode->value;}
        headNode = headNode ->next;
        for(int i = 0; i < (row*2) + (row/4); i++){
            cout << " ";
        }
        if(headNode->value >= 0)
        {cout << "+" <<  headNode->value << '\n';}
        else
        {cout << headNode->value << '\n';}
        headNode = headNode -> next;
    }
    for(int i = 0; i < row; i++){
        if(headNode->value >= 0){
            cout << "+" <<  headNode->value << " ";
        }
        else
       { cout << headNode -> value << " ";}
        headNode = headNode ->next;
    }
}
int main() {
    // Write C++ code here
    srand((unsigned) time(NULL));
    
    node* temp = nullptr;
    node* head;
    node* result;
    int squares = 32;
    if((squares % 4 != 0) || squares >= 100 || squares < 16 ){
        cout << "Error, Invalid Size" << '\n';
        return 0;
    }
    
    int values[squares];
    generateValues(values, squares);
    for(int i = squares; i > 0; i-- ){
        result = new node();
        result->value = values[i-1];
        result->position = i;
        result->next = temp;
        temp = result;
    }
    char rollDice;
    int playerScore = 0;
    head = temp;
    while(head != NULL){
        printBoard(head, squares);
         cout << "Score: " << playerScore << '\n';
         while(true){
             cout << "Enter r to roll the dice" << '\n';
             cin >> rollDice;
              
             if(rollDice == 'r'){
                 int moves = rand() % 6 + 1;
                 cout << "You rolled a " <<  moves << '\n';
                 int addToScore = moveForward(head, moves);
                 playerScore+= addToScore;
                 break;
             }
         }
      
         
    }
    std::cout << "Final Score " << playerScore;

    return 0;
}
