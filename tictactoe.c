#include <stdio.h> 
#include <string.h>  // Include the header for string functions
#include <stdlib.h>
#include <time.h>

#define SPACE 32

enum Divider {
    VERTICAL = '|',
    HORIZONTAL = '-'
};


// prints a welcome to the user
void welcome(int nameLen, char name[]){
    char welcome[] = "Welcome #, let's play tic tac toe!";
    char formattedWelcome[100];

    int i = 0;
    int w = 0;

    // formats user welcome
    while(i < strlen(welcome)){

        if(welcome[i] == '#'){
              
            for(int j = 0; j < nameLen; w++, j++){
                formattedWelcome[w] = name[j];
            }
        }
        else {
            formattedWelcome[w] = welcome[i];
            w++;
        }

        i++;
    }

    formattedWelcome[w] = '\0';

    printf("%s\n", formattedWelcome);
}


// evaluates if there is a winner
int get_winner(char moves[]){

    // diagonal check
    int diagonal_match =
        ((moves[0] == moves[4]) && (moves[4] == moves[8])) || 
        ((moves[2] == moves[4]) && (moves[4] == moves[6]));

    

    if(diagonal_match && (moves[4] == 'X' || moves[4] == 'O')){
        return moves[4];
    }

    // column check
    // scan across the middle row, checking cells above and below each
    for(int c = 3; c < 6; c++){
        if((moves[c-3] == moves[c]) && (moves[c] == moves[c+3]) && (moves[c] == 'X' || moves[c] == 'O')){
            return moves[c];
        }
    }
    
    // row check
    for(int w = 0; w <= 6; w += 3){
        if((moves[w] == moves[w+1]) && (moves[w] == moves[w+2]) && (moves[w] == 'X' || moves[w] == 'O')){
            return moves[w];
        }
    }

    return 0;
}


// simulates a move by the computer
int sim_move(char moves[]){
    printf("My turn...\n");

    int random_moves = rand() % 9;
    int position = 0;

    // move r times, or into first open position
    while(position < random_moves || moves[position % 9] == 'X' || moves[position % 9] == 'O' ){
        position++;
    }

    return position % 9;
}


// board drawing helpers
void print_space(){
    printf(" ");
}


void print_move(char move, int cell){
    if(move == 'X' || move == 'O'){
        printf("%c", move);
    } else {
        printf("%d", cell);
    }
}


void print_divider(char divider){
    printf("%c", divider);
}


// draws the active tic tac toe board
void draw_board(char moves[]){
    printf("\n");

    // loop through the array of moves to draw the tic tac toe board
    int i = 0;
    int v = 1;

    // for each row
    for(int r = 0; r < 3; r++){

        // print the row
        while(i < ((r*3) + 3)){
            print_space();
            print_move(moves[i], i+1);
            print_space();
            if(v % 3){
                print_divider(VERTICAL);
            }
            v++;
            i++;
        }
        // add horizontal dividers above next row
        if(r < 2){
            printf("\n");
            for(int k = 0; k < 11; k++){
                print_divider(HORIZONTAL);
            }
            printf("\n");
        }
    }

    printf("\n\n");
}


// gets the users next move
int next_move(char moves[]){
    printf("Enter cell # of your next move: ");

    char c;
    int isValid = 0;
    int cell = 0;

    while((c = getchar()) || 1){
        if(c >= '1' && c <= '9'){
            cell = c - '0' - 1;
            if(moves[cell] == 'X' || moves[cell] == 'O')
                printf("\nThat cell is taken! Try again: ");
            else break;
        } 
        else if(c != EOF && c != '\n' && c != '\0') {
            printf("\nInvalid cell number. Try again: ");
        }
    }
    
    return cell;
}


// main
int main(){
    srand(time(NULL));

    // Introduction
    printf("What is your name?\n");

    char c;
    char name[100];
    int nameLen = 0;

    // TODO WHY DOES E0F NOT GET PICKED UP HERE
    while((c = getchar()) != EOF && c != '\n' && c != '\0')
        name[nameLen++] = c;

    name[nameLen] = '\0'; 

    welcome(nameLen, name);

    // Game logic

    // fill a board of empty moves
    char moves[10];
    int i;

    for (i = 0; i < 9; i++) {
        moves[i] = ' ';
    }
    moves[9] = '\0';

    int turn = 1;
    int winner = 0;

    draw_board(moves);

    while( ~winner ){
        if(turn == 1){
            moves[next_move(moves)] = 'X';
            if((winner = get_winner(moves)))
                break;
        }
        else {
            moves[sim_move(moves)] = 'O';
            if((winner = get_winner(moves)))
                break;
        }
        turn = ~turn;
        draw_board(moves);
    }

    draw_board(moves);

    if(winner == 'X'){
        printf("You win!\n\n");
    }
    else {
        printf("You lose! Maybe next time...\n\n");
    }


    return 0;

}