#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define ESC 27

#define F4 62

#define F2 60

struct
{
    char password[20];

    char username[20];
} s;

FILE *fp;

COORD cursorPosition;

void delay(int No_Of_time)
{
    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + No_Of_time)
        ;
}

void gotoxy(int x, int y)
{

    cursorPosition.X = x;
    cursorPosition.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void signup(void)
{
    char c;

    fp = fopen("record.bin", "ab");

    system("cls");

    gotoxy(23, 5);
    printf("__________SIGN UP __________");

    gotoxy(23, 7);
    printf("SET USER-NAME :  ");
    gets(s.username);

    gotoxy(23, 9);
    printf("SET PASSWORD :  ");
    for (int i = 0; c = getche() != 13; i++)
    {
        s.password[i] = c;
    }

    gotoxy(23, 11);
    printf("Press Enter Key to continue .......");

    if (getch() == 13)
    {
        fwrite(&s, sizeof(s), 1, fp);

        gotoxy(23, 13);
        printf("Signned in successfully\n");
    }
    else
    {
        fclose(fp);
        return;
    }
    fclose(fp);

    getch();
}

void login(void)
{
    int n;
    char user[20];
    char pass[20];
    char check_user;
    char check_pass;

    fp = fopen("record.bin", "rb");

    system("cls");

    gotoxy(23, 5);
    printf("____Log-In____");

    gotoxy(23, 7);
    printf("Enter Username : ");
    gets(user);

    gotoxy(23, 9);
    printf("Enter Password : ");
    int i;
    for (i = 0; n = getch() != 13; i++)
    {
        pass[i] = n;
        printf("*");
    }
    pass[i] = '\0';

    while (!feof(fp))
    {

        fread(&s, sizeof(s), 1, fp);

        check_user = strcmp(user, s.username);
        check_pass = strcmp(pass, s.password);

        if (check_pass == 0 && check_user != 0)
        {
            gotoxy(23, 10);
            printf("Invalid Username !!!!!!!");
            break;
        }
        else if (check_user == 0 && check_pass != 0)
        {
            gotoxy(23, 10);
            printf("Invalid Password !!!!!!!!");
            break;
        }
        else if (check_pass == 0 && check_user == 0)
        {
            system("cls");

            gotoxy(20, 10);
            printf("Hey , %s you are successfully logged in !", user);

            break;
        }
    }
    getch();
}

int main()
{
    int ch;

    while (1)
    {
        system("cls");

        gotoxy(27, 5);
        printf("__________Login System__________");

        gotoxy(28, 7);
        printf("You are welcomed here ...");

        gotoxy(28, 9);
        printf("Press F2 to Sign-up");

        gotoxy(28, 11);
        printf("Press F4 to log-in");

        gotoxy(28, 13);
        printf("Press ESC to exit");

        gotoxy(26, 15);
        printf("_*_*_*_*_*_*_*_*_*_*_*_*_");

        ch = getch();
        switch (ch)
        {
        case F2:

            system("cls");

            gotoxy(16, 13);
            printf("LOADING....");
            gotoxy(10, 14);

            for (int i = 0; i < 40; i++)
            {
                printf("_");
                delay(40);
            }

            signup();
            break;
        case F4:

            system("cls");

            gotoxy(16, 13);
            printf("LOADING....");
            gotoxy(10, 14);

            for (int i = 0; i < 40; i++)
            {
                printf("_");
                delay(40);
            }

            login();
            break;
        case ESC:
            gotoxy(10, 19);
            for (int i = 0; i < 56; i++)
            {
                printf("_");
                delay(40);
            }
            system("cls");
            exit(0);
        }
    }
    getch();
    return 0;
}