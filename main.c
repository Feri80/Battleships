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
int user_count=3;

struct player
{
    char name[max_name_size];
    int score;
    char visible_map[map_size][map_size];
    int hidden_map[map_size][map_size];
    bool is_special;
};
typedef struct player player;

struct username
{
    char name[max_name_size];
    int score;
};
typedef struct username username;

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

void show_visible_map(player *vis_player)
{
    for(int i=0;i<10;i++)
    {
        printf(" ---");
    }
    for(int i=0;i<10;i++)
    {
        printf("\n");
        printf("| ");
        for(int j=0;j<10;j++)
        {
            printf("%c | ",vis_player->visible_map[i][j]);
        }
        printf("\n");
        for(int j=0;j<10;j++)
        {
            printf(" ---");
        }
    }
}

void show_hidden_map(player *vis_player)
{
    for(int i=0;i<10;i++)
    {
        printf(" ---");
    }
    for(int i=0;i<10;i++)
    {
        printf("\n");
        printf("| ");
        for(int j=0;j<10;j++)
        {
            if(vis_player->hidden_map[i][j]==-1)
            {
                printf("  | ",vis_player->hidden_map[i][j]);
            }   
            else if(vis_player->hidden_map[i][j]==-2)
            {
                printf("L | ",vis_player->hidden_map[i][j]);
            }
            else
            {
                printf("%d | ",vis_player->hidden_map[i][j]);
            }
        }
        printf("\n");
        for(int j=0;j<10;j++)
        {
            printf(" ---");
        }
    }
}

int search_name(char *name)
{
    FILE *fin=fopen("Resources\\usernames.bin","rb");
    if(fin==NULL)
    {
        printf("Missing File Resources\\usernames.bin \n");
        system("pause");
        exit(0);
    }
    fseek(fin,sizeof(username),SEEK_SET);
    for(int i=1;i<user_count;i++)
    {
        username new_username;
        fread(&new_username,sizeof(username),1,fin);
        if(strcmp(name,new_username.name)==0)
        {
            fclose(fin);
            return i;
        }
    }
    fclose(fin);
    return -1;
}

void show_names()
{
    FILE *fin=fopen("Resources\\usernames.bin","rb");
    if(fin==NULL)
    {
        printf("Missing File Resources\\usernames.bin \n");
        system("pause");
        exit(0);
    }
    for(int i=0;i<user_count;i++)
    {
        username u;
        fread(&u,sizeof(username),1,fin);
        if(i!=0)
        {
            printf("%d) %s %d \n",i,u.name,u.score);
        }
    }
    fclose(fin);
}

void add_name(char *name)
{
    FILE *fout=fopen("Resources\\usernames.bin","ab");
    username new_username;
    strcpy(new_username.name,name);
    new_username.score=0;
    fwrite(&new_username,sizeof(username),1,fout);
    fclose(fout);
}

void add_score(int id,int x)
{
    FILE *fin=fopen("Resources\\usernames.bin","rb");
    if(fin==NULL)
    {
        printf("Missing File Resources\\usernames.bin \n");
        system("pause");
        exit(0);
    }
    username new_username;
    fseek(fin,id*sizeof(username),SEEK_SET);
    fread(&new_username,sizeof(username),1,fin);
    fclose(fin);
    new_username.score+=x;
    FILE *fout=fopen("Resources\\usernames.bin","r+b");
    fseek(fin,id*sizeof(username),SEEK_SET);
    fwrite(&new_username,sizeof(username),1,fin);
}

void use_existing_name(player *vis_player)
{
    fflush(stdin);
    show_names();
    int x;
    do
    {
        printf("Please Choose A Username : ");
        fflush(stdin);
        scanf("%d",&x);
    }while(x<1 || x>(user_count-1));
    
}

void use_new_name(player *vis_player)
{

}

/*void get_name(player *vis_player)
{
    fflush(stdin);
    int x;
    do
    {
        printf("1) Choose An Existing User \n2) Add A New User \n");
        fflush(stdin);
        scanf("%d",&x);
        if(x==1)
        {

        }
        else if(x==2)
        {

        }
        else
        {

        }
    }while()
}*/

void init_map(player *vis_player)
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            vis_player->visible_map[i][j]=' ';
            vis_player->hidden_map[i][j]=-1;
        }
    }
}

void init_player(player *vis_player)
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
    
}