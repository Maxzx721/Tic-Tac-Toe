#include <stdio.h>
#include <string.h>
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

void initGameBoard(int gameBoard[3][3]) {

    int i,j;                          //i for rows and j for columns in 3-D array.

    for(i=0;i<=2;i++) {              //loop row form 0 to 2.
        for(j=0;j<=2;j++) {         //loop column from 0 to 2.
            gameBoard[i][j]=EMPTY;
        }
    }
}

void printGameBoard(int gameBoard[3][3]) {

    int i,j,k=7,n;                              //i for rows, j for columns and k is the initial number of the 1st 3-D array.

    for(i=0;i<=4;i++) {                      //loop through the rows form top to bottom.
        if(i==0||i==4) {                    //if it is first row or last row then print "=========".
            printf("=========\n");
            continue;
        }
        for(j=0;j<=2;j++) {               //loop through the columns form left to right to print.
            if(j!=2) {                   //if it's the last column, we have to skip line (showed after line 58-66).
                if(gameBoard[i-1][j]==EMPTY) {
                    printf("|%d|",k);
                } else if(gameBoard[i-1][j]==CIRCLE) {
                    printf("|O|");
                } else {
                    printf("|X|");
                }
            } else {
                if(gameBoard[i-1][j]==EMPTY) {
                    printf("|%d|\n",k);
                } else if(gameBoard[i-1][j]==CIRCLE) {
                    printf("|O|\n");
                } else {
                    printf("|X|\n");
                }
            }
            k++;
        }
        k-=6;
    }
}

void removeSpaces(char remove[]) {          //to remove spaces before and after the input.

    int i,j;
    
    for(i=0;i<strlen(remove);i++) {         //count spaces before actual value.
        if(remove[i]!=' ') {
            break;
        }
    }
    for(j=strlen(remove)-1;j>i;j--) {       //count spaces after actual value.
        if(remove[j]!=' ') {
            break;
        }
    }

    strcpy(remove,remove+i);                //replace remove[] with frount spaces removed.
    remove[j-i+1]='\0';                    //put '\0' to end the string.

}

void placeMarkByHumanPlayer(int gameBoard[3][3], int mark, int currentPlayer) {

    int i,j,k,occ;
    char input[1000];

    while(1) {
        gets(input);
        removeSpaces(input);
        if(strlen(input)==1&&input[0]>='1'&&input[0]<='9') {         //to check the user input by comparing the string
            if(input[0]=='1'||input[0]=='2'||input[0]=='3') {       //which shorten to length of code to increase the readability of the code.
                i=2;
            } else if(input[0]=='4'||input[0]=='5'||input[0]=='6') {
                i=1;
            } else {
                i=0;
            }
            if(input[0]=='3'||input[0]=='6'||input[0]=='9') {
                j=2;
            } else if(input[0]=='2'||input[0]=='5'||input[0]=='8') {
                j=1;
            } else {
                j=0;
            }
            if(gameBoard[i][j]==EMPTY) {            //if the given location is empty, then place the mark into the array.
                gameBoard[i][j]=mark;
                for(k=1;k<=100;k++){
                    printf("\n");
                }
                printf("Placed by Player %d:\n",currentPlayer);
                printGameBoard(gameBoard);
                break;
            } else {                                //if the given location is NOT empty, then request the user to input again.
                for(k=1;k<=100;k++){
                    printf("\n");
                }
                occ=gameBoard[i][j]==CIRCLE ? 1 : 2 ;   //check the location for player 1/2.
                printGameBoard(gameBoard);
                printf("/\\%s is occupied by Player %d. Player %d please place your mark [1-9]:D/\\\nInput: ", input, occ , currentPlayer);        
            }
        } else {                                    //if the input is NOT valid, then request the user to input again.
            for(k=1;k<=100;k++){
                printf("\n");
            }
            printGameBoard(gameBoard);
            printf("/\\Invalid Input. Player %d please place your mark [1-9]:D/\\\nInput: ", currentPlayer);          //if the user input an invalid input, then request the user to input again.
        }
    }

}

int hasWinner(int gameBoard[3][3]) {

    if(gameBoard[0][0]!=0&&gameBoard[0][0]==gameBoard[1][0]&&gameBoard[1][0]==gameBoard[2][0]) {       //check 3 rows.
        return 1;
    }
    if(gameBoard[0][1]!=0&&gameBoard[0][1]==gameBoard[1][1]&&gameBoard[1][1]==gameBoard[2][1]) {
        return 1;
    }
    if(gameBoard[0][2]!=0&&gameBoard[0][2]==gameBoard[1][2]&&gameBoard[1][2]==gameBoard[2][2]) {
        return 1;
    }
    if(gameBoard[0][0]!=0&&gameBoard[0][0]==gameBoard[0][1]&&gameBoard[0][1]==gameBoard[0][2]) {       //check 3 columns.
        return 1;
    }
    if(gameBoard[1][0]!=0&&gameBoard[1][0]==gameBoard[1][1]&&gameBoard[1][1]==gameBoard[1][2]) {
        return 1;
    }
    if(gameBoard[2][0]!=0&&gameBoard[2][0]==gameBoard[2][1]&&gameBoard[2][1]==gameBoard[2][2]) {
        return 1;
    }
    if(gameBoard[0][0]!=0&&gameBoard[0][0]==gameBoard[1][1]&&gameBoard[1][1]==gameBoard[2][2]) {       // check 2 diagonals.
        return 1;
    }
    if(gameBoard[2][0]!=0&&gameBoard[2][0]==gameBoard[1][1]&&gameBoard[1][1]==gameBoard[0][2]) {
        return 1;
    }

    return 0;       //return 0 to continue the game.

}

int isFull(int gameBoard[3][3]) {              

    int i,j;

    for(i=0;i<=2;i++) {                           //loop row from top to bottom.
        for(j=0;j<=2;j++) {                      //loop column form left to right.
           if(gameBoard[i][j]==EMPTY) {         //if theres a blank in the array, then return 0.
                return 0;
            }
        }
    }

    return 1;           //return 1 to indicate the game board is full and the game has drawn.

}

int minimax(int gameBoard[3][3], int depth, int alpha, int beta, int isMaximizer) {

    int i,j,score,result=hasWinner(gameBoard);

    if(result || isFull(gameBoard)) {                  //if theres already a winner or the board is full.
        if(!result) {
            return 0;                                //return 0 for tie game
        } else if(isMaximizer) {
            return -(10-depth);                    //return -(10-depth) if 
        } else {
            return 10-depth;                     //return 10-depth if 
        }
    }

    if(isMaximizer) {                                 //Maximizer wants to win => find bestscore.
        int bestscore=-99999;                        //set bestscore to be -INF. 
        for(i=2;i>=0;i--) {                         //loop row from bottom to top.
            for(j=0;j<=2;j++) {                    //loop column form left to right.
                if(gameBoard[i][j]==EMPTY) {
                    gameBoard[i][j]=CROSS;
                    score=minimax(gameBoard, depth+1, alpha, beta, 0);      //apply recursion to get the score
                    gameBoard[i][j]=EMPTY;
                    if(score>bestscore) {              //find the Max value for bestscore.
                        bestscore=score;
                    }
                    if(score>alpha) {               //find the Max value for alpha.
                        alpha=score;
                    }
                    if(beta<=alpha) {            //if beta is less then or equal to alpha => leave the for loop to save run time.
                        break;
                    }
                }
            }
        }
        return bestscore;
    } else {                                          //Minimizer wants Maximizer to lose => find the least bestscore.
        int bestscore=99999;                         //set bestscore to be INF. 
        for(i=2;i>=0;i--) {                         //loop row from bottom to top.
            for(j=0;j<=2;j++) {                    //loop column form left to right.
                if(gameBoard[i][j]==EMPTY) {   
                    gameBoard[i][j]=CIRCLE;
                    score=minimax(gameBoard, depth+1, alpha, beta, 1);      //apply recursion to get the score
                    gameBoard[i][j]=EMPTY;
                    if(score<bestscore) {              //find the Min value for bestscore.
                        bestscore=score;
                    }
                    if(score<beta) {                //find the Min value for beta.
                        beta=score;
                    }
                    if(beta<=alpha) {            //if beta is less then or equal to alpha => leave the for loop to save run time.
                        break;
                    }
                }
            }
        }
        return bestscore;
    } 

}

void placeMarkByComputerPlayer(int gameBoard[3][3]) {

    int i,j,bestscore=-99999, bestX, bestY;

    for(i=2;i>=0;i--) {                           //loop row from bottom to top.
        for(j=0;j<=2;j++) {                      //loop column form left to right.
           if(gameBoard[i][j]==EMPTY) {         //if theres a blank in the array, use minimax algo. to find the optimal location to place a mark.
                gameBoard[i][j]=CROSS;
                int score=minimax(gameBoard, 0, -99999, 99999, 0);       //use minimax algo. to find the optimal move for the BOT.
                gameBoard[i][j]=EMPTY;
                if(score>bestscore) {                                  //by minimax algo.'s return score, we can store the current best move.
                    bestscore=score;
                    bestX=i;                                         //store the current i as best row.
                    bestY=j;                                        //store the current j as best column.
                }
            }
        }
    }
    gameBoard[bestX][bestY]=CROSS;
    printGameBoard(gameBoard);
}

/* The main function */
int main() {
    /* Local variables */
    int gameBoard[3][3];                  // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS).
    int currentPlayer;                   // 1: Player 1 (Human)   2: Player 2 (Human) or Computer Player.
    int gameEnds;                       // 0: The game continues   1: The game ends.
    char numOfHumanPlayers[1000];      // '1' or '2'.

    currentPlayer = 1;
    gameEnds = 0;
    
    printf("How many human players [1-2]?\n");
    gets(numOfHumanPlayers);
    removeSpaces(numOfHumanPlayers);
    while(strcmp(numOfHumanPlayers,"1")&&strcmp(numOfHumanPlayers,"2")) {         //Input validation by comparing the string which user input.                                                                  
        printf("\n/\\Invalid Input. How many human players [1-2]?/\\\nInput: ");                    
        gets(numOfHumanPlayers);
        removeSpaces(numOfHumanPlayers);
    }

    initGameBoard(gameBoard);
    printf("\nGAME START!!!\n");
    printGameBoard(gameBoard);
    if(strcmp(numOfHumanPlayers,"1")==0) {          //check if theres 1 player or 2 players.
        while(gameEnds!=1) {                       //while the game is not yet finished,continues the game.
            printf("Player %d [O], Please place your mark [1-9]:\n", currentPlayer);
            placeMarkByHumanPlayer(gameBoard, CIRCLE, currentPlayer);                            //call placeMarkByHumanPlayer() to place a mark.
            if(hasWinner(gameBoard)) {
                printf("Player %d wins! Congratulations!", currentPlayer);      //player 1 wins.
                gameEnds=1;
                continue;
            }

            if(isFull(gameBoard)) {                                             //call isFull(),if it return the value of "1". It implies the game has drawn.
                printf("Draw game!");
                gameEnds=1;
                continue;
            }

            printf("Computer places the mark:\n");
            placeMarkByComputerPlayer(gameBoard);                                 //call placeMarkByComputerPlayer() to place a mark.
            if(hasWinner(gameBoard)) {
                printf("Computer Player wins! Congratulations!");               //computer wins.
                gameEnds=1;
                continue;
            }
        }
    } else {                                       //for 2 players.                                              
        while(gameEnds!=1) {                      //while the game is not yet finished,continues the game.
            currentPlayer=1;
            printf("Player %d [O], Please place your mark [1-9]:\n", currentPlayer);
            placeMarkByHumanPlayer(gameBoard, CIRCLE, currentPlayer);                            //call placeMarkByHumanPlayer() to place a mark.
            if(hasWinner(gameBoard)) {
                printf("Player %d wins! Congratulations!", currentPlayer);      //player 1 wins.
                gameEnds=1;
                continue;
            }

            if(isFull(gameBoard)) {                                       //call isFull(),if it return the value of "1". It implies the game has drawn.
                printf("Draw game!");
                gameEnds=1;
                continue;
            }

            currentPlayer=2;
            printf("Player %d [X], Please place your mark [1-9]:[X]\n", currentPlayer);
            placeMarkByHumanPlayer(gameBoard, CROSS, currentPlayer);                             //call placeMarkByHumanPlayer() to place a mark.
            if(hasWinner(gameBoard)) {
                printf("Player %d wins! Congratulations!", currentPlayer);      //player 2 wins.
                gameEnds=1;
                continue;
            }
        }
    }

    return 0;

}
