#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

#define Up 0
#define Down 11
#define Left 0
#define Right 11

void start();
void show();
void playerMove();
void eatCollection();
void randomGenerate();
void gotoxy(int x, int y);
void hideCursor();
void checkGameOver();

int collection_x;
int collection_y;

int playerMove_x;
int playerMove_y;

int player_x[81];
int player_y[81];

int playerLength;

int loop;
int row;
int column;
int speed;
int score;

void start()
{
    playerLength = 1;
    player_x[0] = 5;
    player_y[0] = 5;
    playerMove_x = 1;
    playerMove_y = 0;
    speed = 0;
    score = 0;
    srand((int)time(NULL));
    randomGenerate();
}

void show()
{
    gotoxy(0,0);
    for(row = Up; row < Down; row ++)
    {
        for(column = Left; column < Right; column ++)
        {
            if(row == Up || row == Down - 1 || column == Left || column == Right - 1)
                printf("¨€");
            else if(column == collection_x && row == collection_y)
                printf("¨ˆ");
            else
                printf("  ");
            for(loop = 0; loop < playerLength; loop++)
            {
                if(column == player_x[loop] && row == player_y[loop])
                {
                    gotoxy(player_x[loop]*2, player_y[loop]);
                    printf("¨€");
                }
            }
        }
        gotoxy(column*2, row);
        printf("\n");
    }
    printf("Score: %d", score);
}

void playerController()
{
    char input;
    if(kbhit())
    {
        input = getch();
        if(input == 'w')
        {
            if(playerMove_y != 1)
            {
                playerMove_x = 0;
                playerMove_y = -1;
            }
        }
        else if(input == 's')
        {
            if(playerMove_y != -1)
            {
                playerMove_x = 0;
                playerMove_y = 1;
            }
        }
        else if(input == 'a')
        {
            if(playerMove_x != 1)
            {
                playerMove_x = -1;
                playerMove_y = 0;
            }
        }
        else if(input == 'd')
        {
            if(playerMove_x != -1)
            {
                playerMove_x = 1;
                playerMove_y = 0;
            }
        }
    }
}

void playerMove()
{
    speed++;
    if(speed >= 20)
    {
        if(kbhit())
            playerController();
        if(player_x[playerLength - 1] + playerMove_x == collection_x && player_y[playerLength - 1] + playerMove_y == collection_y)
            eatCollection();
        else
        {
            for(loop = 0; loop < playerLength - 1; loop ++)
            {
                player_x[loop] = player_x[loop + 1];
                player_y[loop] = player_y[loop + 1];
            }
            player_x[playerLength - 1] += playerMove_x;
            player_y[playerLength - 1] += playerMove_y;
        }
        speed = 0;
    }
}

void checkGameOver()
{
    if(player_x[playerLength - 1] == Left || player_x[playerLength - 1] == Right || player_y[playerLength - 1] == Up || player_y[playerLength - 1] == Down)
    {
        system("cls");
        printf("Game over\nYou got a score: %d\n",score);
        system("pause");
        exit(0);
    }
    for(loop = 0; loop < playerLength - 1; loop++)
    {
        if(player_x[playerLength - 1] == player_x[loop] && player_y[playerLength - 1] == player_y)
        {
            system("cls");
            printf("Game over\nYou got a score: %d\n",score);
            system("pause");
            exit(0);
        }
    }
}

void eatCollection()
{
    score++;
    playerLength++;
    player_x[playerLength - 1] = collection_x;
    player_y[playerLength - 1] = collection_y;
    randomGenerate();
}

void randomGenerate()
{
    int difference = 0;
    collection_x = rand()%9 + 1;
    collection_y = rand()%9 + 1;
    while(TRUE)
    {
        for(loop = 0; loop < playerLength; loop ++)
        {
            if(collection_x != player_x[loop] && collection_y != player_y[loop])
                difference++;
            else
            {
                collection_x = rand()%9 + 1;
                collection_y = rand()%9 + 1;
            }
        }
        if(difference == playerLength)
            break;
    }
}


void gotoxy(int x,int y)
{
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(handle,pos);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

int main()
{
    hideCursor();
    start();
    while(1)
    {
        show();
        playerMove();
        checkGameOver();
    }
    return 0;
}
