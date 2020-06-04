#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

/*
    function that returns a random number between 0 and 1
*/
double getRandomNumber(){
    srand(time(NULL));
    return (double) rand() / (double) RAND_MAX;
}

/*
    function that shows a welcome message
*/
void showWelcomeMessage(){
    printf("------------------------------\n\n");
    printf("Welcome to Tic Tac Toe!\n\n");
    printf("------------------------------\n\n");
}

/*
    function that shows the menu
*/
void showMenu(){
    printf("Please select your choice from the Menu below!\n");
    printf("1. New Game: 1 Player\n");
    printf("2. New Game: 2 Players\n");
    printf("3. Show Player Stats\n");
    printf("4. Exit Program\n");
}

/*
    function that shows an exit message
*/
void showExitMessage(){
    printf("\nThank you for playing! See you soon!\n");
}

/*
    function that shows the state of the board with another board that shows the indexes of the board
*/
void showCurrentState(char myCurrentState[],char myExampleState[]){
    printf("Current State\t     Indexes Of Input\n");
    printf("%c | %c | %c",myCurrentState[0],myCurrentState[1],myCurrentState[2]);
    printf("\t\t%c | %c | %c\n",myExampleState[0],myExampleState[1],myExampleState[2]);
    printf("----------");
    printf("\t\t----------\n");
    printf("%c | %c | %c",myCurrentState[3],myCurrentState[4],myCurrentState[5]);
    printf("\t\t%c | %c | %c\n",myExampleState[3],myExampleState[4],myExampleState[5]);
    printf("----------");
    printf("\t\t----------\n");
    printf("%c | %c | %c",myCurrentState[6],myCurrentState[7],myCurrentState[8]);
    printf("\t\t%c | %c | %c\n\n",myExampleState[6],myExampleState[7],myExampleState[8]);
}

/*
    function that shows the state of the board without the example board
*/
void showEndingState(char myCurrentState[]){
    printf("%c | %c | %c\n",myCurrentState[0],myCurrentState[1],myCurrentState[2]);
    printf("----------\n");
    printf("%c | %c | %c\n",myCurrentState[3],myCurrentState[4],myCurrentState[5]);
    printf("----------\n");
    printf("%c | %c | %c\n\n",myCurrentState[6],myCurrentState[7],myCurrentState[8]);
}

/*
    finds if there is a winner
*/
int thereIsAWinner(char currentState[],int whoPlaysFirst){//0 for player1, 1 for player2 or PC, same when returning value of winner,-1 for no winner
    int i,returnValue;
    char foundWinner=0;
    for (i=0;i<9;i+=3){
        if ((currentState[i]=='X') && (currentState[(i+1)]=='X') && (currentState[(i+2)]=='X')){
            if (whoPlaysFirst==0){
                returnValue=0;
            }
            else{
                returnValue=1;
            }
            foundWinner=1;
            break;
        }
        else if ((currentState[i]=='O') && (currentState[(i+1)]=='O') && (currentState[(i+2)]=='O')){
            if (whoPlaysFirst==0){
                returnValue=1;
            }
            else{
                returnValue=0;
            }
            foundWinner=1;
            break;
        }
        else{
            returnValue=-1;
        }
    }
    if (!foundWinner){
        for (i=0;i<3;i++){
            if ((currentState[i]=='X') && (currentState[(i+3)]=='X') && (currentState[(i+6)]=='X')){
                if (whoPlaysFirst==0){
                    returnValue=0;
                }
                else{
                    returnValue=1;
                }
                foundWinner=1;
                break;
            }
            else if ((currentState[i]=='O') && (currentState[(i+3)]=='O') && (currentState[(i+6)]=='O')){
                if (whoPlaysFirst==0){
                    returnValue=1;
                }
                else{
                    returnValue=0;
                }
                foundWinner=1;
                break;
            }
            else{
                returnValue=-1;
            }
        }
    }
    if (!foundWinner){
        if ((currentState[0]=='X') && (currentState[4]=='X') && (currentState[8]=='X')){
            if (whoPlaysFirst==0){
                returnValue=0;
            }
            else{
                returnValue=1;
            }
            foundWinner=1;
        }
        else if ((currentState[0]=='O') && (currentState[4]=='O') && (currentState[8]=='O')){
            if (whoPlaysFirst==0){
                returnValue=1;
            }
            else{
                returnValue=0;
            }
            foundWinner=1;
        }
        else{
            returnValue=-1;
        }
    }
    if (!foundWinner){
        if ((currentState[2]=='X') && (currentState[4]=='X') && (currentState[6]=='X')){
            if (whoPlaysFirst==0){
                returnValue=0;
            }
            else{
                returnValue=1;
            }
            foundWinner=1;
        }
        else if ((currentState[2]=='O') && (currentState[4]=='O') && (currentState[6]=='O')){
            if (whoPlaysFirst==0){
                returnValue=1;
            }
            else{
                returnValue=0;
            }
            foundWinner=1;
        }
        else{
            returnValue=-1;
        }
    }
    return returnValue;
}

/*
    returns 1 if board is empty, otherwise returns 0
*/
int boardIsEmpty(char indexIsTaken[]){
    int i;
    char returnValue=1;
    for (i=0;i<9;i++){
        if (indexIsTaken[i]==1){
            returnValue=0;
            break;
        }
    }
    return returnValue;
}

void playerPlays(char* playerUsername,int whoPlaysFirst,char letterToPlace,char indexIsTaken[],char currentState[],int* whoIsWinner){ //0 for player1, 1 for player2
    int tempIndex,foundWinner;
    do{
        printf("\nIndex of position to place: ");
        scanf("%d",&tempIndex);
        if ((indexIsTaken[tempIndex-1])==1){
            printf("Position already taken!");
        }
        if (tempIndex<1 || tempIndex>9){
            printf("Wrong Input!");
        }

    }
    while((indexIsTaken[tempIndex-1]==1) || (tempIndex<1 || tempIndex>9));
    currentState[tempIndex-1]=letterToPlace;
    indexIsTaken[tempIndex-1]=1;
    foundWinner=thereIsAWinner(currentState,whoPlaysFirst);
    if (foundWinner==0){
        *whoIsWinner=1;
        return;
    }
    else if (foundWinner==1){
        *whoIsWinner=2;
        return;
    }
    else{
        //do nothing
    }
}

/*
    finds the index which can win the game
*/
int mustPlaceInIndexWin(char indexIsTaken[],char currentState[],char letterToPlace){
    int tempIndex=-1;

    //horizontally
    if (currentState[0]==letterToPlace && currentState[1]==letterToPlace && indexIsTaken[2]==0){
        return 2;
    }
    if (currentState[1]==letterToPlace && currentState[2]==letterToPlace && indexIsTaken[0]==0){
        return 0;
    }
    if (currentState[0]==letterToPlace && currentState[2]==letterToPlace && indexIsTaken[1]==0){
        return 1;
    }
    if (currentState[3]==letterToPlace && currentState[4]==letterToPlace && indexIsTaken[5]==0){
        return 5;
    }
    if (currentState[4]==letterToPlace && currentState[5]==letterToPlace && indexIsTaken[3]==0){
        return 3;
    }
    if (currentState[3]==letterToPlace && currentState[5]==letterToPlace && indexIsTaken[4]==0){
        return 4;
    }
    if (currentState[6]==letterToPlace && currentState[7]==letterToPlace && indexIsTaken[8]==0){
        return 8;
    }
    if (currentState[7]==letterToPlace && currentState[8]==letterToPlace && indexIsTaken[6]==0){
        return 6;
    }
    if (currentState[6]==letterToPlace && currentState[8]==letterToPlace && indexIsTaken[7]==0){
        return 7;
    }

    //vertically
    if (currentState[0]==letterToPlace && currentState[3]==letterToPlace && indexIsTaken[6]==0){
        return 6;
    }
    if (currentState[3]==letterToPlace && currentState[6]==letterToPlace && indexIsTaken[0]==0){
        return 0;
    }
    if (currentState[0]==letterToPlace && currentState[6]==letterToPlace && indexIsTaken[3]==0){
        return 3;
    }
    if (currentState[1]==letterToPlace && currentState[4]==letterToPlace && indexIsTaken[7]==0){
        return 7;
    }
    if (currentState[4]==letterToPlace && currentState[7]==letterToPlace && indexIsTaken[1]==0){
        return 1;
    }
    if (currentState[1]==letterToPlace && currentState[7]==letterToPlace && indexIsTaken[4]==0){
        return 4;
    }
    if (currentState[2]==letterToPlace && currentState[5]==letterToPlace && indexIsTaken[8]==0){
        return 8;
    }
    if (currentState[5]==letterToPlace && currentState[8]==letterToPlace && indexIsTaken[2]==0){
        return 2;
    }
    if (currentState[2]==letterToPlace && currentState[8]==letterToPlace && indexIsTaken[5]==0){
        return 5;
    }

    //diagonally
    if (currentState[0]==letterToPlace && currentState[4]==letterToPlace && indexIsTaken[8]==0){
        return 8;
    }
    if (currentState[8]==letterToPlace && currentState[4]==letterToPlace && indexIsTaken[0]==0){
        return 0;
    }
    if (currentState[0]==letterToPlace && currentState[8]==letterToPlace && indexIsTaken[4]==0){
        return 4;
    }
    if (currentState[2]==letterToPlace && currentState[4]==letterToPlace && indexIsTaken[6]==0){
        return 6;
    }
    if (currentState[6]==letterToPlace && currentState[4]==letterToPlace && indexIsTaken[2]==0){
        return 2;
    }
    if (currentState[2]==letterToPlace && currentState[6]==letterToPlace && indexIsTaken[4]==0){
        return 4;
    }

    return tempIndex;
}

/*
    finds the index which can save pc from losing
*/
int mustPlaceInIndexNotLose(char indexIsTaken[],char currentState[],char letterToPlace){
    int tempIndex=-1;
    char opponentLetter;

    if (letterToPlace=='X'){
        opponentLetter='O';
    }
    else{
        opponentLetter='X';
    }

    //horizontally
    if (currentState[0]==opponentLetter && currentState[1]==opponentLetter && indexIsTaken[2]==0){
        return 2;
    }
    if (currentState[1]==opponentLetter && currentState[2]==opponentLetter && indexIsTaken[0]==0){
        return 0;
    }
    if (currentState[0]==opponentLetter && currentState[2]==opponentLetter && indexIsTaken[1]==0){
        return 1;
    }
    if (currentState[3]==opponentLetter && currentState[4]==opponentLetter && indexIsTaken[5]==0){
        return 5;
    }
    if (currentState[4]==opponentLetter && currentState[5]==opponentLetter && indexIsTaken[3]==0){
        return 3;
    }
    if (currentState[3]==opponentLetter && currentState[5]==opponentLetter && indexIsTaken[4]==0){
        return 4;
    }
    if (currentState[6]==opponentLetter && currentState[7]==opponentLetter && indexIsTaken[8]==0){
        return 8;
    }
    if (currentState[7]==opponentLetter && currentState[8]==opponentLetter && indexIsTaken[6]==0){
        return 6;
    }
    if (currentState[6]==opponentLetter && currentState[8]==opponentLetter && indexIsTaken[7]==0){
        return 7;
    }

    //vertically
    if (currentState[0]==opponentLetter && currentState[3]==opponentLetter && indexIsTaken[6]==0){
        return 6;
    }
    if (currentState[3]==opponentLetter && currentState[6]==opponentLetter && indexIsTaken[0]==0){
        return 0;
    }
    if (currentState[0]==opponentLetter && currentState[6]==opponentLetter && indexIsTaken[3]==0){
        return 3;
    }
    if (currentState[1]==opponentLetter && currentState[4]==opponentLetter && indexIsTaken[7]==0){
        return 7;
    }
    if (currentState[4]==opponentLetter && currentState[7]==opponentLetter && indexIsTaken[1]==0){
        return 1;
    }
    if (currentState[1]==opponentLetter && currentState[7]==opponentLetter && indexIsTaken[4]==0){
        return 4;
    }
    if (currentState[2]==opponentLetter && currentState[5]==opponentLetter && indexIsTaken[8]==0){
        return 8;
    }
    if (currentState[5]==opponentLetter && currentState[8]==opponentLetter && indexIsTaken[2]==0){
        return 2;
    }
    if (currentState[2]==opponentLetter && currentState[8]==opponentLetter && indexIsTaken[5]==0){
        return 5;
    }

    //diagonally
    if (currentState[0]==opponentLetter && currentState[4]==opponentLetter && indexIsTaken[8]==0){
        return 8;
    }
    if (currentState[8]==opponentLetter && currentState[4]==opponentLetter && indexIsTaken[0]==0){
        return 0;
    }
    if (currentState[0]==opponentLetter && currentState[8]==opponentLetter && indexIsTaken[4]==0){
        return 4;
    }
    if (currentState[2]==opponentLetter && currentState[4]==opponentLetter && indexIsTaken[6]==0){
        return 6;
    }
    if (currentState[6]==opponentLetter && currentState[4]==opponentLetter && indexIsTaken[2]==0){
        return 2;
    }
    if (currentState[2]==opponentLetter && currentState[6]==opponentLetter && indexIsTaken[4]==0){
        return 4;
    }

    return tempIndex;
}

void pcPlays(int whoPlaysFirst,char letterToPlace,char indexIsTaken[],char currentState[],int* whoIsWinner){
    int mustPlaceIndex,foundWinner;
    time_t t;
    srand((unsigned) time(&t));

    printf("PC is thinking..\n");
    Sleep(1500);

    if (boardIsEmpty(indexIsTaken)==1){
        do{
            mustPlaceIndex=rand()%9;
            if (indexIsTaken[mustPlaceIndex]!=1){
                currentState[mustPlaceIndex]=letterToPlace;
                indexIsTaken[mustPlaceIndex]=1;
                break;
            }
        }
        while (indexIsTaken[mustPlaceIndex]==1);
    }
    else{
        mustPlaceIndex=mustPlaceInIndexWin(indexIsTaken, currentState, letterToPlace);
        if (mustPlaceIndex==-1){ //NOT WINNING
            mustPlaceIndex=mustPlaceInIndexNotLose(indexIsTaken, currentState, letterToPlace);
            if (mustPlaceIndex==-1){ //NOT LOSING
                do{
                    mustPlaceIndex=rand()%9;
                    if (indexIsTaken[mustPlaceIndex]!=1){
                        currentState[mustPlaceIndex]=letterToPlace;
                        indexIsTaken[mustPlaceIndex]=1;
                        break;
                    }
                }
                while (indexIsTaken[mustPlaceIndex]==1);
            }
            else{
                //PLACE IN INDEX FOR NOT LOSE
                currentState[mustPlaceIndex]=letterToPlace;
                indexIsTaken[mustPlaceIndex]=1;
            }
        }
        else{
            //PLACE IN INDEX TO WIN
            currentState[mustPlaceIndex]=letterToPlace;
            indexIsTaken[mustPlaceIndex]=1;
        }
    }
    foundWinner=thereIsAWinner(currentState,whoPlaysFirst);
    if (foundWinner==0){
        *whoIsWinner=1;
        return;
    }
    else if (foundWinner==1){
        *whoIsWinner=2;
        return;
    }
    else{
        //do nothing
    }
}

/*
    searches for a user and returns 1 if found, otherwise 0
*/
int userFound(char** usernames, char usernameToFind[],int totalUsers){
    int i;
    for (i=0;i<totalUsers;i++){
        if (strcmp(usernames[i],usernameToFind)==0){
            return 1;
        }
    }
    return 0;
}

/*
    searches for a user and returns his index, if not found returns -1
*/
int userFoundInIndex(char** usernames, char usernameToFind[],int totalUsers){
    int i;
    for (i=0;i<totalUsers;i++){
        if (strcmp(usernames[i],usernameToFind)==0){
            return i;
        }
    }
    return -1;
}

/*
    shows stats of a player
*/
void showPlayerStatsInIndex(char** usernames, int* userWins, int* userDraws, int* userDefeats,int indexOfUser){
    printf("Username: %s.\tWins: %d.\tDraws: %d.\tDefeats: %d.\n",usernames[indexOfUser],userWins[indexOfUser],userDraws[indexOfUser],userDefeats[indexOfUser]);
    printf("\n\n");
}

void startNewGame1Player(char username1[],int* winner,char* saveResultsOfGame,char** usernames, int totalUsers,char* thereIsANewUser1,char* textFileIsEmpty){
    int i,whoIsWinner;
    char validUsername;
    char answer[3],tempUsername[256];
    char* playerUsername;
    char indexIsTaken[9]={0,0,0,0,0,0,0,0,0};
    char currentState[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char exampleInput[9]={'1','2','3','4','5','6','7','8','9'};
    whoIsWinner=0;
    *thereIsANewUser1=0;

    do{
        printf("Do you wish to save results of this game? (Yes/No): ");
        fflush(stdin);
        gets(answer);
    }
    while (strcmp(answer,"Yes")!=0 && strcmp(answer,"No")!=0);
    if (strcmp(answer,"Yes")==0){
        *saveResultsOfGame=1;
    }
    else{
        *saveResultsOfGame=0;
    }

    if (*saveResultsOfGame==1){
        do{
            printf("Please type your username below!\n");
            printf("Username: ");
            fflush(stdin);
            gets(tempUsername);
            printf("\n");
            if (strlen(tempUsername)>15){
                printf("\nPlease type a username no longer than 15 characters!\n\n");
                validUsername=0;
            }
                else{
                    if (!*textFileIsEmpty){
                        if (userFound(usernames,tempUsername,totalUsers)==0){
                            validUsername=1;
                            playerUsername=(char*) malloc(sizeof(char) * strlen(tempUsername+1));
                            strcpy(playerUsername,tempUsername);
                            printf("Welcome %s! From now on you can save and see your stats!\n\n",playerUsername);
                            *thereIsANewUser1=1;
                        }
                        else{
                            validUsername=1;
                            playerUsername=(char*) malloc(sizeof(char) * strlen(tempUsername+1));
                            strcpy(playerUsername,tempUsername);
                            printf("Welcome back %s!\n\n",playerUsername);
                        }
                    }
                    else{
                        validUsername=1;
                        playerUsername=(char*) malloc(sizeof(char) * strlen(tempUsername+1));
                        strcpy(playerUsername,tempUsername);
                        printf("Welcome %s! From now on you can save and see your stats!\n\n",playerUsername);
                        *thereIsANewUser1=1;
                        *textFileIsEmpty=0;
                    }
                }
            }
            while(!validUsername);
        }

    else{
        playerUsername="Player1";
    }


    printf("------------------------------\n\n");
    printf("New Game! %s vs PC! Good Luck!\n\n",playerUsername);
    printf("------------------------------\n\n");
    if (getRandomNumber()>0.5){
        printf("You play first!\n");
        for (i=1;i<=9;i++){
            if ((i%2)!=0){
                printf("\nIt's your turn! Place your X!\n");
                showCurrentState(currentState,exampleInput);
                playerPlays(playerUsername,0,'X',indexIsTaken,currentState,&whoIsWinner);
            }
            else{
                printf("\nPCs turn! PC places O!\n");
                showCurrentState(currentState,exampleInput);
                pcPlays(0,'O',indexIsTaken,currentState,&whoIsWinner);
            }
            if ((whoIsWinner==1) || (whoIsWinner==2)){
                break;
            }
        }
    }
    else{
        printf("PC plays first!\n");
        for (i=1;i<=9;i++){
            if ((i%2)!=0){
                printf("\nPCs turn! PC places X!\n");
                showCurrentState(currentState,exampleInput);
                pcPlays(1,'X',indexIsTaken,currentState,&whoIsWinner);
            }
            else{
                printf("\nIt's your turn! Place your O!\n");
                showCurrentState(currentState,exampleInput);
                playerPlays(playerUsername,1,'O',indexIsTaken,currentState,&whoIsWinner);
            }
            if ((whoIsWinner==1) || (whoIsWinner==2)){
                break;
            }
        }
    }

    if (whoIsWinner==1){
        printf("\nYou are the winner!\n");
    }
    else if (whoIsWinner==2){
        printf("\nPC is the winner! You lose!\n");
    }
    else{
        printf("\nGame is a draw!\n");
    }
    showEndingState(currentState);

    strcpy(username1,playerUsername);
    *winner=whoIsWinner;
}

void startNewGame2Players(char username1[],char username2[],int* winner,char* saveResultsOfGame,char** usernames, int totalUsers,char* thereIsANewUser1, char* thereIsANewUser2,int* whoIsNew,char* textFileIsEmpty){
    int i,j,whoIsWinner;
    char validUsername;
    char answer[3],tempUsername[256];
    char* playerUsername[2];
    char indexIsTaken[9]={0,0,0,0,0,0,0,0,0};
    char currentState[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char exampleInput[9]={'1','2','3','4','5','6','7','8','9'};
    whoIsWinner=0;
    *thereIsANewUser1=0;
    *thereIsANewUser2=0;

    do{
        printf("Do you wish to save results of this game? (Yes/No): ");
        fflush(stdin);
        gets(answer);
    }
    while (strcmp(answer,"Yes")!=0 && strcmp(answer,"No")!=0);
    if (strcmp(answer,"Yes")==0){
        *saveResultsOfGame=1;
    }
    else{
        *saveResultsOfGame=0;
    }

    if (*saveResultsOfGame==1){
        for (j=0;j<2;j++){
            do{
                printf("\nPlayer%d:\n",(j+1));
                printf("Please type your username below!\n");
                printf("Username: ");
                fflush(stdin);
                gets(tempUsername);
                printf("\n");
                if (strlen(tempUsername)>15){
                    printf("\nPlease type a username no longer than 15 characters!\n\n");
                    validUsername=0;
                }
                else{
                    if (!*textFileIsEmpty){
                        if (userFound(usernames,tempUsername,totalUsers)==0){
                            validUsername=1;
                            playerUsername[j]=(char*) malloc(sizeof(char) * strlen(tempUsername+1));
                            strcpy(playerUsername[j],tempUsername);
                            printf("Welcome %s! From now on you can save and see your stats!\n\n",playerUsername[j]);
                            if (*thereIsANewUser1==1){
                                *thereIsANewUser2=1;
                                *whoIsNew=0;
                            }
                            *thereIsANewUser1=1;
                            *whoIsNew=(j+1);
                        }
                        else{
                            validUsername=1;
                            playerUsername[j]=(char*) malloc(sizeof(char) * strlen(tempUsername+1));
                            strcpy(playerUsername[j],tempUsername);
                            printf("Welcome back %s!\n\n",playerUsername[j]);
                        }
                    }
                    else{
                        validUsername=1;
                        playerUsername[j]=(char*) malloc(sizeof(char) * strlen(tempUsername+1));
                        strcpy(playerUsername[j],tempUsername);
                        printf("Welcome %s! From now on you can save and see your stats!\n\n",playerUsername[j]);
                        if (*thereIsANewUser1==1){
                            *thereIsANewUser2=1;
                            *whoIsNew=0;
                        }
                        *thereIsANewUser1=1;
                        *whoIsNew=(j+1);
                        *textFileIsEmpty=0;
                    }
                }
            }
            while(!validUsername);
        }
    }
    else{
        playerUsername[0]="Player1";
        playerUsername[1]="Player2";
    }


    printf("------------------------------\n\n");
    printf("New Game! %s vs %s! Good Luck!\n\n",playerUsername[0],playerUsername[1]);
    printf("------------------------------\n\n");
    if (getRandomNumber()>0.5){
        printf("%s plays first!\n",playerUsername[0]);
        for (i=1;i<=9;i++){
            if ((i%2)!=0){
                printf("\n%s turn! Place your X!\n",playerUsername[0]);
                showCurrentState(currentState,exampleInput);
                playerPlays(playerUsername[0],0,'X',indexIsTaken,currentState,&whoIsWinner);
            }
            else{
                printf("\n%s turn! Place your O!\n",playerUsername[1]);
                showCurrentState(currentState,exampleInput);
                playerPlays(playerUsername[1],0,'O',indexIsTaken,currentState,&whoIsWinner);
            }
            if ((whoIsWinner==1) || (whoIsWinner==2)){
                break;
            }
        }
    }
    else{
        printf("%s plays first!\n",playerUsername[1]);
        for (i=1;i<=9;i++){
            if ((i%2)!=0){
                printf("\n%s turn! Place your X!\n",playerUsername[1]);
                showCurrentState(currentState,exampleInput);
                playerPlays(playerUsername[1],1,'X',indexIsTaken,currentState,&whoIsWinner);
            }
            else{
                printf("\n%s turn! Place your O!\n",playerUsername[0]);
                showCurrentState(currentState,exampleInput);
                playerPlays(playerUsername[0],1,'O',indexIsTaken,currentState,&whoIsWinner);
            }
            if ((whoIsWinner==1) || (whoIsWinner==2)){
                break;
            }
        }
    }

    if (whoIsWinner==1){
        printf("\n%s is the winner!\n",playerUsername[0]);
    }
    else if (whoIsWinner==2){
        printf("\n%s is the winner!\n",playerUsername[1]);
    }
    else{
        printf("\nGame is a draw!\n");
    }
    showEndingState(currentState);

    strcpy(username1,playerUsername[0]);
    strcpy(username2,playerUsername[1]);
    *winner=whoIsWinner;
}

/*
    shows users stats
*/
void showPlayerStats(char** usernames, int* userWins, int* userDraws, int* userDefeats,int totalUsers){
    int i;
    for (i=0;i<totalUsers;i++){
        printf("Username: %s.\tWins: %d.\tDraws: %d.\tDefeats: %d.\n",usernames[i],userWins[i],userDraws[i],userDefeats[i]);
    }
    printf("\n\n");
}

/*
    gets the users data from the text file and saves it in 4 dynamic arrays
*/
void loadData(char** usernames, int* userWins, int* userDraws, int* userDefeats, FILE *myFile){
    rewind(myFile);
    int counter=0;
    char line[20];
    while (fgets(line, sizeof(line), myFile)){
        sscanf(line,"%s %d %d %d",usernames[counter],&userWins[counter],&userDraws[counter],&userDefeats[counter]);
        counter++;
    }
    rewind(myFile);
}

/*
    if file is empty function returns 1, if not function returns 0
*/
char fileIsEmpty(FILE *myFile){
    int returnValue,characterRead;
    characterRead=fgetc(myFile);
    if (characterRead == EOF) {
        returnValue=1;
    }
    else{
        ungetc(characterRead, myFile);
        returnValue=0;
    }
    return returnValue;
}

/*
    finds the total users that are saved in the text file
*/
int findTotalUsers(FILE *myFile){
    int counter=0;
    char line[20];
    while (fgets(line, sizeof(line), myFile)){
        counter++;
    }
    return counter;
}

/*
    whoIsWinner -> 1 for username1, 2 for username2, 0 for draw
*/
void updateData(char** usernames, int* userWins, int* userDraws, int* userDefeats,int totalUsers,char username1[],char username2[],int whoIsWinner,char againstPC){
    int i;
    if (againstPC){
        for (i=0;i<totalUsers;i++){
            if (strcmp(usernames[i],username1)==0){
                if (whoIsWinner==1){
                    userWins[i]++;
                }
                else if (whoIsWinner==2){
                    userDefeats[i]++;
                }
                else{
                    userDraws[i]++;
                }
            }
        }
    }
    else{
        for (i=0;i<totalUsers;i++){
            if (strcmp(usernames[i],username1)==0){
                if (whoIsWinner==1){
                    userWins[i]++;
                }
                else if (whoIsWinner==2){
                    userDefeats[i]++;
                }
                else{
                    userDraws[i]++;
                }
            }
            else if (strcmp(usernames[i],username2)==0){
                if (whoIsWinner==2){
                    userWins[i]++;
                }
                else if (whoIsWinner==1){
                    userDefeats[i]++;
                }
                else{
                    userDraws[i]++;
                }
            }
            else{
                //do nothing
            }
        }
    }
}

void allocateNewMemory(int** userWins, int** userDraws, int** userDefeats,int totalUsers,int newUsers){
    int* tempWins;
    int* tempDraws;
    int* tempDefeats;

    if (newUsers==1){
        tempWins=(int*) realloc(*userWins,sizeof(int)*(totalUsers+1));
        tempDraws=(int*) realloc(*userDraws,sizeof(int)*(totalUsers+1));
        tempDefeats=(int*) realloc(*userDefeats,sizeof(int)*(totalUsers+1));
    }
    else{
        tempWins=(int*) realloc(*userWins,sizeof(int)*(totalUsers+2));
        tempDraws=(int*) realloc(*userDraws,sizeof(int)*(totalUsers+2));
        tempDefeats=(int*) realloc(*userDefeats,sizeof(int)*(totalUsers+2));
    }

    *userWins=tempWins;
    *userDraws=tempDraws;
    *userDefeats=tempDefeats;
}

char** allocateNewMemoryChar(char** usernames,int totalUsers,int newUsers){
    char** tempUsernames;

    if (newUsers==1){
        tempUsernames=realloc(usernames,sizeof(char*)*(totalUsers+1));
        tempUsernames[totalUsers]=malloc(sizeof(char)*15);
    }
    else{
        tempUsernames=realloc(usernames,sizeof(char*)*(totalUsers+2));
        tempUsernames[totalUsers]=malloc(sizeof(char)*15);
        tempUsernames[totalUsers+1]=malloc(sizeof(char)*15);
    }
    return tempUsernames;
}

void addNewUser(char** usernames, int* userWins, int* userDraws, int* userDefeats,int totalUsers,int newUsers,char newUsername1[],char newUsername2[],int whoIsNew){
    if (newUsers==1){
        userWins[totalUsers]=0;
        userDraws[totalUsers]=0;
        userDefeats[totalUsers]=0;
        if (whoIsNew==1){
            strcpy(usernames[totalUsers],newUsername1);
        }
        else{
            strcpy(usernames[totalUsers],newUsername2);
        }
    }
    else{
        userWins[totalUsers]=0;
        userDraws[totalUsers]=0;
        userDefeats[totalUsers]=0;
        userWins[totalUsers+1]=0;
        userDraws[totalUsers+1]=0;
        userDefeats[totalUsers+1]=0;
        strcpy(usernames[totalUsers],newUsername1);
        strcpy(usernames[totalUsers+1],newUsername2);
    }
}

/*
    saves data from memory to a text file
*/
void saveDataToFile(FILE* myFile,char filename[],char** usernames,int* userWins,int* userDraws,int* userDefeats,int totalUsers){
    int i;
    fclose(myFile);
    myFile=fopen(filename,"w");
    for (i=0;i<totalUsers;i++){
        fprintf(myFile,"%s %d %d %d\n",usernames[i],userWins[i],userDraws[i],userDefeats[i]);
    }
    fclose(myFile);
}

int* allocateNewMemoryINT(int* userStats, int totalUsers,int newUsers){
    int* tempStats;

    if (userStats==NULL){
        printf("NULL3");
    }
    if (newUsers==1){
        tempStats=(int*) realloc(userStats,sizeof(int)*(totalUsers+1));
    }
    else{
        tempStats=(int*) realloc(userStats,sizeof(int)*(totalUsers+2));
    }

    if (tempStats==NULL){
        printf("NULL2");
    }
    return tempStats;
}

int main()
{
    FILE *usersStats;
    char tempUsername1[15],tempUsername2[15];
    char fileName[15]="usersStats.txt";
    char againstPC,saveResultsOfGame,thereIsANewUser1,thereIsANewUser2,textFileIsEmpty,flag;
    int i,menu_choice,totalUsers,tempWinner,whoIsNew;
    int* userWins;
    int* userDraws;
    int* userDefeats;
    char** usernames;
    textFileIsEmpty=0;
    flag=0;

    usersStats = fopen(fileName,"r");
    if (usersStats==NULL){
        printf("File with user stats not found! Creating a new one..\n\n");
        usersStats = fopen(fileName,"w");
        fclose(usersStats);
        usersStats = fopen(fileName,"r+");
        textFileIsEmpty=1;
    }
    fclose(usersStats);
    usersStats = fopen(fileName,"r+");

    if (!fileIsEmpty(usersStats)){
        totalUsers=findTotalUsers(usersStats);
        userWins=(int*) malloc(sizeof(int)*totalUsers);
        userDraws=(int*) malloc(sizeof(int)*totalUsers);
        userDefeats=(int*) malloc(sizeof(int)*totalUsers);
        usernames=malloc(sizeof(char*)*totalUsers);
        for (i=0;i<totalUsers;i++){
            usernames[i]=malloc(sizeof(char)*15);
        }
        flag=1;
    }
    else{
        totalUsers=0;
    }

    loadData(usernames,userWins,userDraws,userDefeats,usersStats);

    showWelcomeMessage();
    do{
        showMenu();
        do{
            printf("\nPlease type your choice: ");
            scanf("%d",&menu_choice);
            if (menu_choice!=1 && menu_choice!=2 && menu_choice!=3 && menu_choice!=4){
                printf("Wrong Input!\n");
            }
        }
        while(menu_choice!=1 && menu_choice!=2 && menu_choice!=3 && menu_choice!=4);
        switch (menu_choice){
            case 1: startNewGame1Player(tempUsername1,&tempWinner,&saveResultsOfGame,usernames,totalUsers,&thereIsANewUser1,&textFileIsEmpty);
                    againstPC=1;
                    if (thereIsANewUser1){
                        if (totalUsers==0){
                            userWins=(int*) malloc(sizeof(int)*1);
                            userDraws=(int*) malloc(sizeof(int)*1);
                            userDefeats=(int*) malloc(sizeof(int)*1);
                            usernames=malloc(sizeof(char*)*1);
                            for (i=0;i<1;i++){
                                usernames[i]=malloc(sizeof(char)*15);
                            }
                            addNewUser(usernames,userWins,userDraws,userDefeats,totalUsers,1,tempUsername1,"no_username",1);
                            totalUsers++;
                        }
                        else{
                            allocateNewMemory(&userWins,&userDraws,&userDefeats,totalUsers,1);
                            usernames=allocateNewMemoryChar(usernames,totalUsers,1);
                            addNewUser(usernames,userWins,userDraws,userDefeats,totalUsers,1,tempUsername1,"no_username",1);
                            totalUsers++;
                        }
                        if (fileIsEmpty(usersStats)){
                            flag=1;
                        }
                    }
                    else{
                        //do nothing
                    }
                    if (saveResultsOfGame){
                        updateData(usernames,userWins,userDraws,userDefeats,totalUsers,tempUsername1,"no_username",tempWinner,againstPC);
                        printf("The results of the game have been saved! Returning to main menu..\n\n");
                    }
                    else{
                        printf("The results of the game have not been saved! Returning to main menu..\n\n");
                    }
                    break;
            case 2: startNewGame2Players(tempUsername1,tempUsername2,&tempWinner,&saveResultsOfGame,usernames,totalUsers,&thereIsANewUser1,&thereIsANewUser2,&whoIsNew,&textFileIsEmpty);
                    againstPC=0;
                    if (thereIsANewUser1 && thereIsANewUser2){
                        if (totalUsers==0){
                            userWins=(int*) malloc(sizeof(int)*2);
                            userDraws=(int*) malloc(sizeof(int)*2);
                            userDefeats=(int*) malloc(sizeof(int)*2);
                            usernames=malloc(sizeof(char*)*2);
                            for (i=0;i<2;i++){
                                usernames[i]=malloc(sizeof(char)*15);
                            }
                        }
                        else{
                            allocateNewMemory(&userWins,&userDraws,&userDefeats,totalUsers,2);
                            usernames=allocateNewMemoryChar(usernames,totalUsers,2);
                        }
                        addNewUser(usernames,userWins,userDraws,userDefeats,totalUsers,2,tempUsername1,tempUsername2,whoIsNew);
                        totalUsers+=2;
                        if (fileIsEmpty(usersStats)){
                            flag=1;
                        }
                    }
                    else if (thereIsANewUser1){
                        allocateNewMemory(&userWins,&userDraws,&userDefeats,totalUsers,1);
                        usernames=allocateNewMemoryChar(usernames,totalUsers,1);
                        addNewUser(usernames,userWins,userDraws,userDefeats,totalUsers,1,tempUsername1,tempUsername2,whoIsNew);
                        totalUsers++;
                    }
                    else{
                        // do nothing
                    }
                    if (saveResultsOfGame){
                        updateData(usernames,userWins,userDraws,userDefeats,totalUsers,tempUsername1,tempUsername2,tempWinner,againstPC);
                        printf("The results of the game have been saved! Returning to main menu..\n\n");
                    }
                    else{
                        printf("The results of the game have not been saved! Returning to main menu..\n\n");
                    }
                    break;
            case 3: if (fileIsEmpty(usersStats) && !flag){
                        printf("There are no user stats yet!\n\n");
                    }
                    else{
                        int tempChoice;
                        do{
                            printf("\nWould you like to see all users stats or a user of your choice?\n");
                            printf("1. All users\n2. A user of my choice\n");
                            printf("Please type your choice(1 or 2): ");
                            scanf("%d",&tempChoice);
                        }
                        while (tempChoice!=1 && tempChoice!=2);
                        if (tempChoice==1){
                            showPlayerStats(usernames,userWins,userDraws,userDefeats,totalUsers);
                        }
                        else{
                            char tempUsername[256];
                            int tempIndex;
                            printf("Please type the username below!\n");
                            printf("Username: ");
                            fflush(stdin);
                            gets(tempUsername);
                            printf("\n");
                            tempIndex=userFoundInIndex(usernames,tempUsername,totalUsers);
                            if (tempIndex==-1){
                                printf("User not found!\n\n");
                            }
                            else{
                                showPlayerStatsInIndex(usernames,userWins,userDraws,userDefeats,tempIndex);
                            }
                        }
                    }
                    break;
            case 4: showExitMessage();
        }
    }
    while (menu_choice!=4);

    if ((!fileIsEmpty(usersStats) && flag) || (fileIsEmpty(usersStats) && flag)){
        saveDataToFile(usersStats,fileName,usernames,userWins,userDraws,userDefeats,totalUsers);
        free(userWins);
        free(userDraws);
        free(userDefeats);
        for (i=0;i<totalUsers;i++){
            free(usernames[i]);
        }
        free(usernames);
        fclose(usersStats);
    }

    return 0;
}
