#include <stdio.h>

/* Function to initialize the game board with n stones in each cup, except for the large cups (last index) */
void initializeGame(int board[2][7], int n)
{
    /* Initialize the first 6 cups of the first row (player's side) with n stones */

    int i = 0;

    int j = 0;
    for (j = 0; j < 6; j++)
    {
        board[i][j] = n;
    }
    /* Initialize the first 6 cups of the second row (computer's side) with n stones */

    i = 1;

    j = 0;
    for (j = 0; j < 6; j++)
    {
        board[i][j] = n;
    }

    /* Leave the large cups (last index) empty */
    board[1][6] = 0; /*right - player's large cup*/
    board[0][6] = 0; /*left - computer's large cup*/
}

/* Function to print the current state of the game board */

void printBoard(int board[2][7])
{
    printf("+----+---+---+---+---+---+---+----+\n");
    printf("|    |%2d |%2d |%2d |%2d |%2d |%2d |    |\n", board[0][5], board[0][4], board[0][3], board[0][2], board[0][1], board[0][0]);
    printf("| %2d |---+---+---+---+---+---| %2d |\n", board[0][6], board[1][6]);
    printf("|    |%2d |%2d |%2d |%2d |%2d |%2d |    |\n", board[1][0], board[1][1], board[1][2], board[1][3], board[1][4], board[1][5]);
    printf("+----+---+---+---+---+---+---+----+\n");
}
/* Function for the computer to select a cup with stones */

int selectPcCup(int board[2][7])
{
    int i = 0;
    /* Loop through the computer's cups and return the index of the first cup with stones */

    for (i = 0; i < 6; i++)
    {
        if (board[0][i] != 0)
        {
            return i;
        }
    }

    /* If no cups have stones, return 0 (should not happen in normal gameplay) */

    return 0;
}

/* Function to move stones around the board */

int moveStones(int board[2][7], int selectedRow, int selected_cup, int isPlayer)
{
    int current_row = selectedRow;

    /* Pick up the stones from the selected cup */

    int stones = board[current_row][selected_cup];
    board[current_row][selected_cup] = 0; /*Empty the selected cup*/

    /* Distribute the stones */
    int current_cup = selected_cup + 1;

    while (stones > 0)
    {
        /* If the end of the row is reached */
        if (current_cup == 6)
        {
            /* If it's the player's turn and they are on their own side, add a stone to their large cup */

            if (isPlayer && current_row == 1)
            {
                board[current_row][current_cup]++;
                stones--;
            }

            /* If it's the computer's turn and they are on their own side, add a stone to their large cup */

            if (!isPlayer && current_row == 0)
            {
                board[current_row][current_cup]++;
                stones--;
            }

            /* Switch to the other row and start from the first cup */

            current_row = (current_row + 1) % 2;
            current_cup = 0;
        }
        /* If all stones have been distributed, break out of the loop */

        if (stones <= 0)
        {
            break;
        }
        /* Place a stone in the current cup */

        board[current_row][current_cup]++;
        stones--;
        current_cup++;
    }
    /* If the last stone landed in an empty cup, continue moving */

    if (board[current_row][current_cup] != 1 && current_cup < 6)
    {
        moveStones(board, current_row, current_cup, isPlayer);
    }

    /* If the player's turn ends with a stone in their large cup, let them choose another cup */

    if (isPlayer && current_row == 1 && current_cup == 6)
    {

        printBoard(board);
        printf("select a cup again\n");
        scanf("%d", &selected_cup);

        moveStones(board, current_row, selected_cup, isPlayer);
    }
    /* If the computer's turn ends with a stone in their large cup, let them choose another cup */

    if (!isPlayer && current_row == 0 && current_cup == 6)
    {
        printf("computer playing again..\n");
        selected_cup = selectPcCup(board);
        moveStones(board, current_row, selected_cup, isPlayer);
    }

    return 0;
}
/* Function to check if the game has ended */

int isFinish(int board[2][7])
{

    int i = 0;
    int sum0 = 0;
    int sum1 = 0;
    /* Calculate the total number of stones on each side (excluding large cups) */

    for (i = 0; i < 6; i++)
    {

        sum0 += board[0][i];
        sum1 += board[1][i];
    }
    /* If either side has no stones left, the game is over */

    if (sum0 == 0 || sum1 == 0)
    {
        return 1; /*game is finished*/
    }
    else
    {
        return 0; /*game is not finished*/
    }
}
/* Function to manage the gameplay loop */

void gamePlay(int board[2][7])
{
    int isPlayer = 1; /*Start with the player's turn*/
    int selectedCup = 0;
    while (1)
    {
        printf("Which cup do you choose?");
        scanf("%d", &selectedCup);

        moveStones(board, 1, selectedCup, isPlayer);

        printBoard(board);
        printf("turn to computer\n");
        isPlayer = !isPlayer; /*Switch to the computer's turn*/
        selectedCup = selectPcCup(board);

        moveStones(board, 0, selectedCup, isPlayer);
        printBoard(board);
        if (isFinish(board)) /*Check if the game has ended*/
        {
            break;
        }
    }
    /* Determine and print the winner based on the number of stones in the large cups */

    if (board[0][6] > board[1][6])
    {
        printf("comp win the game");
    }
    else if (board[1][6] > board[0][6])
    {
        printf("user win the game");
    }
    else
    {
        printf("the winner can not find");
    }
}

int main()
{
    int board[2][7];
    int n;

    /*
      board[0] represents the computer's side, with the last element being their large cup
      board[1] represents the player's side, with the last element being their large cup
      */

    printf("Enter the value for n \n");
    scanf("%d", &n);

    initializeGame(board, n);

    printBoard(board);

    gamePlay(board);

    return 0;
}