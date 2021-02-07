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
int user_count=5;

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


int scoreboard_cmp(const void *a,const void *b)
{
    return ((*(username*)b).score - (*(username*)a).score);
}
void show_scoreboard()
{
    FILE *fin=fopen("Resources\\usernames.bin","rb");
    if(fin==NULL)
    {
        printf("Missing File Resources\\usernames.bin \n");
        system("pause");
        exit(0);
    }
    fseek(fin,sizeof(username),SEEK_SET);
    username users[user_count-1];
    for(int i=0;i<user_count-1;i++)
    {
        fread(&users[i],sizeof(username),1,fin);
    }
    qsort(users,user_count-1,sizeof(username),scoreboard_cmp);
    printf("\n\t\t\t\tSCORE BOARD\n--------------------------------------------------------------------------------\n");
    for(int i=0;i<user_count-1;i++)
    {
        printf("%d) %-50s\t\tScore : %d \n--------------------------------------------------------------------------------\n",i+1,users[i].name,users[i].score);
    }
    system("pause");
    system("cls");
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
            printf("%d) %s\n",i,u.name);
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
    FILE *fin=fopen("Resources\\usernames.bin","rb");
    if(fin==NULL)
    {
        printf("Missing File Resources\\usernames.bin \n");
        system("pause");
        exit(0);
    }
    fseek(fin,x*sizeof(username),SEEK_SET);
    username new_username;
    fread(&new_username,sizeof(username),1,fin);
    strcpy(vis_player->name,new_username.name);
    vis_player->score=new_username.score;
    fclose(fin);
}

int use_new_name(player *vis_player)
{
    char new_name[max_name_size];
    printf("Please Enter Your New Name (Up To 50 Characters) : ");
    fflush(stdin);
    gets(new_name);
    if(search_name(new_name)==-1)
    {
        add_name(new_name);
        strcpy(vis_player->name,new_name);
        vis_player->score=0;
        fflush(stdin);
        return 1;
    }
    else
    {
        printf("This Username Is Already In Use \n");
        system("pause");
        return 0;
    }
}

void get_name(player *vis_player)
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
            fflush(stdin);
            use_existing_name(vis_player);
            fflush(stdin);
            break;
        }
        else if(x==2)
        {
            fflush(stdin);
            bool flag=0
            flag=use_new_name(vis_player);
            fflush(stdin);
            if(flag)
            {
                break;
            }
        }
        else
        {   
            fflush(stdin);
            continue;
        }
    }while(1);
}

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

int make_random_map(player *vis_player)
{

}

int make_map(player *vis_player)
{

}

void get_map(player *vis_player)
{
    fflush(stdin);
    int x;
    do
    {
        printf("1) Make Your Own Map \n2) Choose A Random Map \n");
        fflush(stdin);
        scanf("%d",&x);
        if(x==1)
        {
            fflush(stdin);
            while(make_map(vis_player)==0)
            {
                fflush(stdin);
            }
            fflush(stdin);
        }
        else if(x==2)
        {
            fflush(stdin);
            while(make_random_map(vis_player)==0)
            {
                fflush(stdin);
            }
            fflush(stdin);
        }
        else
        {
            fflush(stdin);
            continue;
        }
    }while(x<1 || x>2);
}

void init_player(player *vis_player)
{
    fflush(stdin);
    get_name(vis_player);
    get_map(vis_player);
}

void play_with_friend()
{
    player player1;
    player player2;
    init_player(&player1);
    init_player(&player2);

}

void player_with_cpu()
{
    player player1;
    init_player(&player1);
}

void show_menu3()
{
    
}

void show_menu4()
{
    
}


void show_mainmenu()
{
    fflush(stdin);
    printf("\t\tMAIN MENU\n------------------------------\n");
    int x;
    do
    {
        printf("1) Play With A Friend \n2) Play With CPU \n3) Load Game \n4) Load Last Game \n5) Play Back \n6) Score Board \n7) Exit \n");
        fflush(stdin);
        scanf("%d",&x);
        if(x==1)
        {
            play_with_friend();
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
            fflush(stdin);
            show_scoreboard();
            fflush(stdin);
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