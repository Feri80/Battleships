//               In The Name Of God
//                   BattleShips
//    Fundamentals Of Programming Final Project
//             Created By Farhad Aman
//                   Winter 2021
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>

typedef long long ll;

const int mod=1e9+7;
const ll inf=1000000000000000000L;
const double eps=1e-7;
const double pi=3.14159265359;

const int max_name_size=50;
const int max_map_size=30;
int map_size=10;

struct player
{
    char name[max_name_size];
    char visible_map[max_map_size][max_map_size];
    int hidden_map[max_map_size][max_map_size];
};
typedef struct player player;

struct ship
{
    int id;
    int x1;
    int y1;
    int x1;
    int y1;
    int sz;
    int cur;
    struct ship *next;
    
};
typedef struct ship ship;



struct game_info
{
    player player1;
    player player2;
    ship *ships1;
    ship *ships2;
};
typedef struct game_info game_info;



void show_menu1()
{
    
}

void show_menu2()
{
    
}

void show_menu3()
{
    
}

void show_menu4()
{
    
}

void show_settings()
{
    fflush(stdin);
    printf("\t\tSETTINGS\n------------------------------\n");
    int x;
    do
    {
        printf("1) Map Size \n2) Back To Main Menu");
        fflush(stdin);
        scanf("%d",&x);
        if(x==1)
        {
            fflush(stdin);
            printf("Your Current Map Size Is : %d \nPlease Enter New Map Size (10 - 30) : ")
        }
        else if(x==2)
        {
            fflush(stdin);
            return;
        }
        else
        {
            fflush(stdin);
            continue;
        }
    } while (x!=2);
    
}

void show_menu6()
{
    show_scoreboard();
}

void show_mainmenu()
{
    fflush(stdin);
    printf("\t\tMAIN MENU\n------------------------------\n");
    int x;
    do
    {
        printf("1) Play With A Friend \n2) Play With CPU \n3) Load Game \n4) Load Last Game \n5) Settings \n6) Score Board \n7) Exit \n");
        fflush(stdin);
        scanf("%d",&x);
        if(x==1)
        {
            
        }   
        else if(x==2)
        {

        }
        else if(x==3)
        {
            
        }
        else if(x==4)
        {
            
        }
        else if(x==5)
        {
            fflush(stdin);
            show_settings();
        }
        else if(x==6)
        {
            
        }
        else if(x==7)
        {
            exit(0);
        }
        else
        {
            fflush(stdin);
            continue;
        }
    } while (x!=7);
}


int main()
{
    show_mainmenu();
}