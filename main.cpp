// Online C++ compiler to run C++ program online
#include <iostream>
using std::cout;
struct node{
    int value, position;
    struct node* next;
        node(){}
    node(int value, node * p): value(value), next(p) {}
    ~node(){}
};
void moveForward(node* &headNode, int spaces ){
    for(int i = 0; i < spaces; i++)
    {
        headNode = headNode->next;
    }
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
void printBoard(node* headNode){
    

}
int main() {
    // Write C++ code here
    srand((unsigned) time(NULL));
    
    node* temp = nullptr;
    node* head;
    node* result;
    int squares = 17;
    if(squares % 10 != 0){
        cout << "Error, Invalid Size" << '\n';
        return 0;
    }
    
    int values[squares];
    generateValues(values, squares);
    for(int i = 16; i > 0; i-- ){
        result = new node();
        result->value = values[i-1];
        result->position = i;
        result->next = temp;
        temp = result;
    }
    char rollDice;
    cout << "Enter r to roll the dice" << '\n';
    while(head != NULL){
          
         while(true){
             cin >> rollDice;
             if(rollDice == 'r'){
                 int moves = rand() % 6 + 1;
                 moveForward(head, moves);
                 break;
             }
             else cout <<
         }
    }
    std::cout << "Try programiz.pro";

    return 0;
}
