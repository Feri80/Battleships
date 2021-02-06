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
const int map_size=10;
int user_count=0;

struct player
{
    char name[max_name_size];
    int score;
    char visible_map[map_size][map_size];
    int hidden_map[map_size][map_size];
    bool is_special;
};
typedef struct player player;

struct ship
{
    int id;
    int x1;
    int y1;
    int x2;
    int y2;
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

void create_settings()
{
    FILE *fout=fopen("Resources\\settings.bin","wb");
    fwrite(&user_count,sizeof(int),1,fout);
    fclose(fout);
}

void load_settings()
{
    FILE *fin=fopen("Resources\\settings.bin","rb");
    if(fin==NULL)
    {
        printf("Missing File Resources\\settings.bin \n");
        system("pause");
        exit(0);
    }
    fread(&user_count,sizeof(int),1,fin);
    fclose(fin);
}

void show_map(player *cur_player)
{

}

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

void show_menu6()
{
    //show_scoreboard();
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
    load_settings();
    //show_mainmenu();
}