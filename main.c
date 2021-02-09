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

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef long long ll;

typedef enum
{
    BLACK = 0, BLUE = 1, GREEN = 2,
    AQUA = 3, RED = 4, PURPLE = 5,
    YELLOW = 6, WHITE = 7, GRAY = 8, 
    LIGHT_BLUE = 9, LIGHT_GREEN = 10,
    LIGHT_AQUA = 11, LIGHT_RED = 12, 
    LIGHT_PURPLE = 13, LIGHT_YELLOW = 14,
    LIGHT_WHITE = 15
} ConsoleColors;

const int mod=1e9+7;
const ll inf=1000000000000000000L;
const double eps=1e-7;
const double pi=3.14159265359;

#define max_name_size 50
#define map_size 10
int user_count=0;

typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;
short setTextColor(const ConsoleColors foreground)
{
    Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    BufferInfo bufferInfo;
    if(!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
        return 0;
    Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
    SetConsoleTextAttribute(consoleHandle, color);
    return 1;
}

struct player
{
    char name[max_name_size];
    int score;
    int delta_score;
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

ship total_ships[10];
ship *ships1=NULL;
ship *ships2=NULL;

int ship_count1=10;
int ship_count2=10;

struct save_info
{
    char name[max_name_size];
    player player1;
    player player2;
    int t;
    int type;
};
typedef struct save_info save_info;

bool save_game(save_info info)
{
    FILE *fin=fopen("Resources\\saves.bin","rb");
    save_info temp;
    if(fin==NULL)
    {
        fclose(fin);
    }
    else
    {
        while(fread(&temp,sizeof(save_info),1,fin)>=1)
        {   
            if(strcmp(info.name,temp.name)==0)
            {
                fclose(fin);
                return 0;
            }
        }
    }
    fclose(fin);

    FILE *fout=fopen("Resources\\saves.bin","ab");
    fwrite(&info,sizeof(save_info),1,fout);
    fclose(fout);
    return 1;
}

bool load_game(save_info *info,char *name)
{
    FILE *fin=fopen("Resources\\saves.bin","rb");
    if(fin==NULL)
    {
        printf("There Is Not Any Saved Game\n");
        fclose(fin);
        return 0;
    }
    while(fread(info,sizeof(save_info),1,fin)>=1)
    {
        if(strcmp(info->name,name)==0)
        {
            fclose(fin);
            return 1;
        }
    }
    fclose(fin);
    return 0;
}

void print_saves()
{
    save_info temp;
    FILE *fin=fopen("Resources\\saves.bin","rb");
    if(fin==NULL)
    {
        printf("There Is Not Any Saved Game\n");
        fclose(fin);
        return;
    }
    while(fread(&temp,sizeof(save_info),1,fin)>=1)
    {
        setTextColor(PURPLE);
        printf("------------------------------------------\n");
        setTextColor(GREEN);
        puts(temp.name);
        printf("%s VS %s\n",temp.player1.name,temp.player2.name);
        if(temp.t==1)
        {
            printf("Turn : %s\n",temp.player1.name);
        }
        else
        {
            printf("Turn : %s\n",temp.player2.name);
        }
        if(temp.type==1)
        {
            printf("Type : Play With CPU\n");
        }   
        else
        {
            printf("Type : Play With A Friend\n");
        }
        setTextColor(PURPLE);
        printf("------------------------------------------\n");
        setTextColor(WHITE);
    }
    fclose(fin);
}

void add_end(ship **pships,int id,int x1,int x2,int y1,int y2,int sz,int cur)
{
    ship *new_ship=(ship*)malloc(sizeof(ship));
    new_ship->id=id;
    new_ship->x1=x1;
    new_ship->x2=x2;
    new_ship->y1=y1;
    new_ship->y2=y2;
    new_ship->sz=sz;
    new_ship->cur=cur;
    new_ship->next=NULL;
    ship *current;
    if(*pships==NULL)
    {
        *pships=new_ship;
    }
    else
    {
        for(current=*pships;current->next!=NULL;current=current->next);
        current->next=new_ship;
    }
}

bool delete_ship(ship **pships,int id) 
{
    if(*pships==NULL)
    {
        return 0;
    }
    if((*pships)->id==id)
    {
        ship *new_ships=(*pships)->next;
        free(*pships);
        *pships=new_ships;
        return 1;
    }
    ship *current=NULL;
    for(current=*pships;current->next!=NULL;current=current->next)
    {
        if(current->next->id==id)
        {
            ship *new_next=current->next->next;
            free(current->next);
            current->next=new_next;
            return 1;
        }
    }
    return 0;
}

void print_ships(ship *ships)
{
    ship *current;
    for(current=ships;current!=NULL;current=current->next)
    {
        printf("%d (%d,%d) , (%d,%d) , (%d/%d)\n",current->id,current->x1,current->y1,current->x2,current->y2,current->sz,current->cur);
    }
}

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
    printf("\n  ");
    setTextColor(LIGHT_GREEN);
    for(int i=0;i<10;i++)
    {
        printf("  %d ",i);
    }
    printf("\n  ");
    setTextColor(WHITE);
    for(int i=0;i<10;i++)
    {
        printf(" ---");
    }
    for(int i=0;i<10;i++)
    {
        printf("\n");
        setTextColor(LIGHT_GREEN);
        printf("%d ",i);
        setTextColor(WHITE);
        printf("| ");
        for(int j=0;j<10;j++)
        {
            if(vis_player->visible_map[i][j]=='W')
            {
                setTextColor(AQUA);
            }
            else if(vis_player->visible_map[i][j]=='*')
            {
                setTextColor(RED);
            }
            else if(vis_player->visible_map[i][j]=='#')
            {
                setTextColor(PURPLE);
            }
            printf("%c",vis_player->visible_map[i][j]);
            setTextColor(WHITE);
            printf(" | ");
        }
        printf("\n  ");
        setTextColor(WHITE);
        for(int j=0;j<10;j++)
        {
            printf(" ---");
        }
    }
}

void show_hidden_map(player *vis_player)
{
    printf("\n  ");
    setTextColor(LIGHT_GREEN);
    for(int i=0;i<10;i++)
    {
        printf("  %d ",i);
    }
    printf("\n  ");
    setTextColor(WHITE);
    for(int i=0;i<10;i++)
    {
        printf(" ---");
    }
    for(int i=0;i<10;i++)
    {
        printf("\n");
        setTextColor(LIGHT_GREEN);
        printf("%d ",i);
        setTextColor(WHITE);
        printf("| ");
        for(int j=0;j<10;j++)
        {
            if(vis_player->hidden_map[i][j]==-1)
            {
                setTextColor(WHITE);
                printf("  | ");
            }   
            else if(vis_player->hidden_map[i][j]==-2)
            {
                setTextColor(RED);
                printf("L");
                setTextColor(WHITE);
                printf(" | ");
            }
            else
            {
                setTextColor(BLUE);
                printf("%d",vis_player->hidden_map[i][j]);
                setTextColor(WHITE);
                printf(" | ");
            }
        }
        printf("\n  ");
        setTextColor(WHITE);
        for(int j=0;j<10;j++)
        {
            printf(" ---");
        }
    }
}

//Username Functions

int search_name(char *name)
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
    user_count++;
    create_settings();
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
    fclose(fout);
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
    vis_player->delta_score=0;
    vis_player->is_special=0;
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
        vis_player->delta_score=0;
        vis_player->is_special=0;
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
            bool flag=0;
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

// Game Play Functions

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

bool check_valid_map(player *vis_player,int sz,int x1,int x2,int y1,int y2)
{
    if( (fabs(x1-x2)==(sz-1) && y1==y2) || (fabs(y1-y2)==(sz-1) && x1==x2) )
    {
        if(x1<0 || x1>9 || x2<0 || x2>9 || y1<0 || y1>9 || y2<0 || y2>9)
        {
            return 0;
        }
        else
        {
            if(x1==x2)
            {
                int l=fmin(y1,y2);
                int r=fmax(y1,y2);
                for(int i=l;i<=r;i++)
                {
                    if(vis_player->hidden_map[x1][i]!=-1)
                    {
                        return 0;
                    }
                }
                return 1;
            }
            else if(y1==y2)
            {
                int l=fmin(x1,x2);
                int r=fmax(x1,x2);
                for(int i=l;i<=r;i++)
                {
                    if(vis_player->hidden_map[i][y1]!=-1)
                    {
                        return 0;
                    }
                }
                return 1;
            }
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

void put_selected_ship(player *vis_player,int id,int x1,int x2,int y1,int y2)
{
    if(x1==x2)
    {
        int l=fmin(y1,y2);
        int r=fmax(y1,y2);
        for(int i=l;i<=r;i++)
        {
            vis_player->hidden_map[x1][i]=id;
            
        }
    }
    else if(y1==y2)
    {
        int l=fmin(x1,x2);
        int r=fmax(x1,x2);
        for(int i=l;i<=r;i++)
        {
            vis_player->hidden_map[i][y1]=id;
        }
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(vis_player->hidden_map[i][j]>=0)
            {
                if(vis_player->hidden_map[i+1][j]==-1)
                {
                    if(i+1>=0 && i+1<10 && j>=0 && j<10)
                    {
                        vis_player->hidden_map[i+1][j]=-2;
                    }
                }
                if(vis_player->hidden_map[i-1][j]==-1)
                {
                    if(i-1>=0 && i-1<10 && j>=0 && j<10)
                    {
                        vis_player->hidden_map[i-1][j]=-2;
                    }
                }
                if(vis_player->hidden_map[i][j+1]==-1)
                {
                    if(i>=0 && i<10 && j+1>=0 && j+1<10)
                    {
                        vis_player->hidden_map[i][j+1]=-2;
                    }
                }
                if(vis_player->hidden_map[i][j-1]==-1)
                {
                    if(i>=0 && i<10 && j-1>=0 && j-1<10)
                    {
                        vis_player->hidden_map[i][j-1]=-2;
                    }
                }
                if(vis_player->hidden_map[i+1][j+1]==-1)
                {
                    if(i+1>=0 && i+1<10 && j+1>=0 && j+1<10)
                    {
                        vis_player->hidden_map[i+1][j+1]=-2;
                    }
                }
                if(vis_player->hidden_map[i+1][j-1]==-1)
                {
                    if(i+1>=0 && i+1<10 && j-1>=0 && j-1<10)
                    {
                        vis_player->hidden_map[i+1][j-1]=-2;
                    }
                }
                if(vis_player->hidden_map[i-1][j+1]==-1)
                {
                    if(i-1>=0 && i-1<10 && j+1>=0 && j+1<10)
                    {
                        vis_player->hidden_map[i-1][j+1]=-2;
                    }
                }
                if(vis_player->hidden_map[i-1][j-1]==-1)
                {
                    if(i-1>=0 && i-1<10 && j-1>=0 && j-1<10)
                    {
                        vis_player->hidden_map[i-1][j-1]=-2;
                    }
                }
            }
        }
    }
}

bool make_map(player *vis_player)
{
    init_map(vis_player);
    int id=0;
    //-----------------------------------------------------------------------------------------
    // 1)
    show_hidden_map(vis_player);
    fflush(stdin);
    int x1,x2,y1,y2;
    do
    {
        printf("\nPlaese Enter Your Size 5 Ship Coordinates (Like)  x1 y1 x2 y2 : \n (If You Want To Reset Map Enter -1 -1 -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        if(x1==-1 && x2==-1 && y1==-1 && y2==-1)
        {
            return 0;
        }
    }while(check_valid_map(vis_player,5,x1,x2,y1,y2)==0);
    put_selected_ship(vis_player,id,x1,x2,y1,y2);
    total_ships[id].x1=x1;
    total_ships[id].x2=x2;
    total_ships[id].y1=y1;
    total_ships[id].y2=y2;
    total_ships[id].id=id;
    total_ships[id].sz=5;
    total_ships[id].cur=5;
    total_ships[id].next=NULL;
    system("pause");
    system("cls");
    //-----------------------------------------------------------------------------------------
    // 2)
    show_hidden_map(vis_player);
    fflush(stdin);
    id++;
    do
    {
        printf("\nPlaese Enter Your First Size 3 Ship Coordinates (Like)  x1 y1 x2 y2 : \n (If You Want To Reset Map Enter -1 -1 -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        if(x1==-1 && x2==-1 && y1==-1 && y2==-1)
        {
            return 0;
        }
    }while(check_valid_map(vis_player,3,x1,x2,y1,y2)==0);
    put_selected_ship(vis_player,id,x1,x2,y1,y2);
    total_ships[id].x1=x1;
    total_ships[id].x2=x2;
    total_ships[id].y1=y1;
    total_ships[id].y2=y2;
    total_ships[id].id=id;
    total_ships[id].sz=3;
    total_ships[id].cur=3;
    total_ships[id].next=NULL;
    system("pause");
    system("cls");
    //-----------------------------------------------------------------------------------------
    // 3)
    show_hidden_map(vis_player);
    fflush(stdin);
    id++;
    do
    {
        printf("\nPlaese Enter Your Second Size 3 Ship Coordinates (Like)  x1 y1 x2 y2 : \n (If You Want To Reset Map Enter -1 -1 -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        if(x1==-1 && x2==-1 && y1==-1 && y2==-1)
        {
            return 0;
        }
    }while(check_valid_map(vis_player,3,x1,x2,y1,y2)==0);
    put_selected_ship(vis_player,id,x1,x2,y1,y2);
    total_ships[id].x1=x1;
    total_ships[id].x2=x2;
    total_ships[id].y1=y1;
    total_ships[id].y2=y2;
    total_ships[id].id=id;
    total_ships[id].sz=3;
    total_ships[id].cur=3;
    total_ships[id].next=NULL;
    system("pause");
    system("cls");
    //-----------------------------------------------------------------------------------------
    // 4)
    show_hidden_map(vis_player);
    fflush(stdin);
    id++;
    do
    {
        printf("\nPlaese Enter Your First Size 2 Ship Coordinates (Like)  x1 y1 x2 y2 : \n (If You Want To Reset Map Enter -1 -1 -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        if(x1==-1 && x2==-1 && y1==-1 && y2==-1)
        {
            return 0;
        }
    }while(check_valid_map(vis_player,2,x1,x2,y1,y2)==0);
    put_selected_ship(vis_player,id,x1,x2,y1,y2);
    total_ships[id].x1=x1;
    total_ships[id].x2=x2;
    total_ships[id].y1=y1;
    total_ships[id].y2=y2;
    total_ships[id].id=id;
    total_ships[id].sz=2;
    total_ships[id].cur=2;
    total_ships[id].next=NULL;
    system("pause");
    system("cls");
    //-----------------------------------------------------------------------------------------
    // 5)
    show_hidden_map(vis_player);
    fflush(stdin);
    id++;
    do
    {
        printf("\nPlaese Enter Your Second Size 2 Ship Coordinates (Like)  x1 y1 x2 y2 : \n (If You Want To Reset Map Enter -1 -1 -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        if(x1==-1 && x2==-1 && y1==-1 && y2==-1)
        {
            return 0;
        }
    }while(check_valid_map(vis_player,2,x1,x2,y1,y2)==0);
    put_selected_ship(vis_player,id,x1,x2,y1,y2);
    total_ships[id].x1=x1;
    total_ships[id].x2=x2;
    total_ships[id].y1=y1;
    total_ships[id].y2=y2;
    total_ships[id].id=id;
    total_ships[id].sz=2;
    total_ships[id].cur=2;
    total_ships[id].next=NULL;
    system("pause");
    system("cls");
    //-----------------------------------------------------------------------------------------
    // 6)
    show_hidden_map(vis_player);
    fflush(stdin);
    id++;
    do
    {
        printf("\nPlaese Enter Your Third Size 2 Ship Coordinates (Like)  x1 y1 x2 y2 : \n (If You Want To Reset Map Enter -1 -1 -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        if(x1==-1 && x2==-1 && y1==-1 && y2==-1)
        {
            return 0;
        }
    }while(check_valid_map(vis_player,2,x1,x2,y1,y2)==0);
    put_selected_ship(vis_player,id,x1,x2,y1,y2);
    total_ships[id].x1=x1;
    total_ships[id].x2=x2;
    total_ships[id].y1=y1;
    total_ships[id].y2=y2;
    total_ships[id].id=id;
    total_ships[id].sz=2;
    total_ships[id].cur=2;
    total_ships[id].next=NULL;
    system("pause");
    system("cls");
    //-----------------------------------------------------------------------------------------
    // 7)
    show_hidden_map(vis_player);
    fflush(stdin);
    id++;
    do
    {
        printf("\nPlaese Enter Your First Size 1 Ship Coordinates (Like)  x1 y1 x2 y2 : \n (If You Want To Reset Map Enter -1 -1 -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        if(x1==-1 && x2==-1 && y1==-1 && y2==-1)
        {
            return 0;
        }
    }while(check_valid_map(vis_player,1,x1,x2,y1,y2)==0);
    put_selected_ship(vis_player,id,x1,x2,y1,y2);
    total_ships[id].x1=x1;
    total_ships[id].x2=x2;
    total_ships[id].y1=y1;
    total_ships[id].y2=y2;
    total_ships[id].id=id;
    total_ships[id].sz=1;
    total_ships[id].cur=1;
    total_ships[id].next=NULL;
    system("pause");
    system("cls");
    //-----------------------------------------------------------------------------------------
    // 8)
    show_hidden_map(vis_player);
    fflush(stdin);
    id++;
    do
    {
        printf("\nPlaese Enter Your Second Size 1 Ship Coordinates (Like)  x1 y1 x2 y2 : \n (If You Want To Reset Map Enter -1 -1 -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        if(x1==-1 && x2==-1 && y1==-1 && y2==-1)
        {
            return 0;
        }
    }while(check_valid_map(vis_player,1,x1,x2,y1,y2)==0);
    put_selected_ship(vis_player,id,x1,x2,y1,y2);
    total_ships[id].x1=x1;
    total_ships[id].x2=x2;
    total_ships[id].y1=y1;
    total_ships[id].y2=y2;
    total_ships[id].id=id;
    total_ships[id].sz=1;
    total_ships[id].cur=1;
    total_ships[id].next=NULL;
    system("pause");
    system("cls");
    //-----------------------------------------------------------------------------------------
    // 9)
    show_hidden_map(vis_player);
    fflush(stdin);
    id++;
    do
    {
        printf("\nPlaese Enter Your Third Size 1 Ship Coordinates (Like)  x1 y1 x2 y2 : \n (If You Want To Reset Map Enter -1 -1 -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        if(x1==-1 && x2==-1 && y1==-1 && y2==-1)
        {
            return 0;
        }
    }while(check_valid_map(vis_player,1,x1,x2,y1,y2)==0);
    put_selected_ship(vis_player,id,x1,x2,y1,y2);
    total_ships[id].x1=x1;
    total_ships[id].x2=x2;
    total_ships[id].y1=y1;
    total_ships[id].y2=y2;
    total_ships[id].id=id;
    total_ships[id].sz=1;
    total_ships[id].cur=1;
    total_ships[id].next=NULL;
    system("pause");
    system("cls");
    //-----------------------------------------------------------------------------------------
    // 10)
    show_hidden_map(vis_player);
    fflush(stdin);
    id++;
    do
    {
        printf("\nPlaese Enter Your Fourth Size 1 Ship Coordinates (Like)  x1 y1 x2 y2 : \n (If You Want To Reset Map Enter -1 -1 -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        scanf("%d",&x2);
        scanf("%d",&y2);
        if(x1==-1 && x2==-1 && y1==-1 && y2==-1)
        {
            return 0;
        }
    }while(check_valid_map(vis_player,1,x1,x2,y1,y2)==0);
    put_selected_ship(vis_player,id,x1,x2,y1,y2);
    total_ships[id].x1=x1;
    total_ships[id].x2=x2;
    total_ships[id].y1=y1;
    total_ships[id].y2=y2;
    total_ships[id].id=id;
    total_ships[id].sz=1;
    total_ships[id].cur=1;
    total_ships[id].next=NULL;
    system("pause");
    system("cls");
    fflush(stdin);

    show_hidden_map(vis_player);
    fflush(stdin);
    char c;
    do
    {
        printf("\nAre You Accept This Map ? (y/n) / (Y/N)");
        fflush(stdin);
        scanf("%c",&c);
        if(c=='Y' || c=='y')
        {
            fflush(stdin);
            return 1;
        }
        else if(c=='N' || c=='n')
        {
            fflush(stdin);
            return 0;
        }
        else
        {
            fflush(stdin);
            continue;
        }
    }while(c!='Y' && c!='N' && c!='y' && c!='n');
    return 0;
}

void get_map(player *vis_player)
{
    fflush(stdin);
    while(make_map(vis_player)==0)
    {

        system("cls");
        fflush(stdin);
    }
    fflush(stdin);
    system("cls");
    fflush(stdin);
    printf("Your Map Successfully Created \n");
    system("pause");
    system("cls");
    fflush(stdin);
}

void make_lists(int player_number)
{
    if(player_number==1)
    {
        for(int i=0;i<10;i++)
        {
            if(total_ships[i].cur>0)
            {
                add_end(&ships1,i,total_ships[i].x1,total_ships[i].x2,total_ships[i].y1,total_ships[i].y2,total_ships[i].sz,total_ships[i].cur);
            }
           
        }
    }
    else
    {
        for(int i=0;i<10;i++)
        {
            if(total_ships[i].cur>0)
            {
                add_end(&ships2,i,total_ships[i].x1,total_ships[i].x2,total_ships[i].y1,total_ships[i].y2,total_ships[i].sz,total_ships[i].cur);
            }
            
        }
    }
    
}

bool init_player(player *vis_player,int ch,char *first)
{
    fflush(stdin);
    get_name(vis_player);
    if(ch==2)
    {
        if(strcmp(first,vis_player->name)==0)
        {
            return 0;
        }
    }
    fflush(stdin);
    get_map(vis_player);
    fflush(stdin);
    return 1;
}

bool check_valid_target(player *op_player,int x,int y)
{
    if(op_player->visible_map[x][y]!=' ')
    {
        return 0;
    }
    return 1;
}

void update_list(player *op_player,int x,int y,int t)
{
    int id=op_player->hidden_map[x][y];
    ship *current;
    if(t==1)
    {
        for(current=ships2;current->id!=id;current=current->next);
        (current->cur)--;
        if((current->cur)==0)
        {
            int x1,x2,y1,y2;
            x1=current->x1;
            x2=current->x2;
            y1=current->y1;
            y2=current->y2;
            delete_ship(&ships2,current->id);
            if(x1==x2)
            {
                for(int i=fmin(y1,y2);i<=fmax(y1,y2);i++)
                {
                    op_player->visible_map[x1][i]='#';
                    if(x1<10 && x1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[x1][i+1]==' ')
                    {
                        op_player->visible_map[x1][i+1]='W';
                    }
                    if(x1<10 && x1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[x1][i-1]==' ')
                    {
                        op_player->visible_map[x1][i-1]='W';
                    }
                    if(x1+1<10 && x1+1>=0 && i<10 && i>=0 && op_player->visible_map[x1+1][i]==' ')
                    {
                        op_player->visible_map[x1+1][i]='W';
                    }
                    if(x1-1<10 && x1-1>=0 && i<10 && i>=0 && op_player->visible_map[x1-1][i]==' ')
                    {
                        op_player->visible_map[x1-1][i]='W';
                    }
                    if(x1+1<10 && x1+1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[x1+1][i+1]==' ')
                    {
                        op_player->visible_map[x1+1][i+1]='W';
                    }
                    if(x1-1<10 && x1-1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[x1-1][i+1]==' ')
                    {
                        op_player->visible_map[x1-1][i+1]='W';
                    }
                    if(x1+1<10 && x1+1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[x1+1][i-1]==' ')
                    {
                        op_player->visible_map[x1+1][i-1]='W';
                    }
                    if(x1-1<10 && x1-1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[x1-1][i-1]==' ')
                    {
                        op_player->visible_map[x1-1][i-1]='W';
                    }
                }
            }
            else if(y1==y2)
            {
                for(int i=fmin(x1,x2);i<=fmax(x1,x2);i++)
                {
                    op_player->visible_map[i][y1]='#';
                    if(y1<10 && y1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[i][y1+1]==' ')
                    {
                        op_player->visible_map[i][y1+1]='W';
                    }
                    if(y1-1<10 && y1-1>=0 && i<10 && i>=0 && op_player->visible_map[i][y1-1]==' ')
                    {
                        op_player->visible_map[i][y1-1]='W';
                    }
                    if(y1<10 && y1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[i+1][y1]==' ')
                    {
                        op_player->visible_map[i+1][y1]='W';
                    }
                    if(y1<10 && y1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[i-1][y1]==' ')
                    {
                        op_player->visible_map[i-1][y1]='W';
                    }
                    if(y1+1<10 && y1+1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[i+1][y1+1]==' ')
                    {
                        op_player->visible_map[i+1][y1+1]='W';
                    }
                    if(y1+1<10 && y1+1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[i-1][y1+1]==' ')
                    {
                        op_player->visible_map[i-1][y1+1]='W';
                    }
                    if(y1-1<10 && y1-1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[i+1][y1-1]==' ')
                    {
                        op_player->visible_map[i+1][y1-1]='W';
                    }
                    if(y1-1<10 && y1-1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[i-1][y1-1]==' ')
                    {
                        op_player->visible_map[i-1][y1-1]='W';
                    }
                }
            }
        }
    }
    else if(t==2)
    {
        for(current=ships1;current->id!=id;current=current->next);
        (current->cur)--;
        if((current->cur)==0)
        {
            int x1,x2,y1,y2;
            x1=current->x1;
            x2=current->x2;
            y1=current->y1;
            y2=current->y2;
            delete_ship(&ships1,current->id);
            if(x1==x2)
            {
                for(int i=fmin(y1,y2);i<=fmax(y1,y2);i++)
                {
                    op_player->visible_map[x1][i]='#';
                    if(x1<10 && x1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[x1][i+1]==' ')
                    {
                        op_player->visible_map[x1][i+1]='W';
                    }
                    if(x1<10 && x1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[x1][i-1]==' ')
                    {
                        op_player->visible_map[x1][i-1]='W';
                    }
                    if(x1+1<10 && x1+1>=0 && i<10 && i>=0 && op_player->visible_map[x1+1][i]==' ')
                    {
                        op_player->visible_map[x1+1][i]='W';
                    }
                    if(x1-1<10 && x1-1>=0 && i<10 && i>=0 && op_player->visible_map[x1-1][i]==' ')
                    {
                        op_player->visible_map[x1-1][i]='W';
                    }
                    if(x1+1<10 && x1+1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[x1+1][i+1]==' ')
                    {
                        op_player->visible_map[x1+1][i+1]='W';
                    }
                    if(x1-1<10 && x1-1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[x1-1][i+1]==' ')
                    {
                        op_player->visible_map[x1-1][i+1]='W';
                    }
                    if(x1+1<10 && x1+1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[x1+1][i-1]==' ')
                    {
                        op_player->visible_map[x1+1][i-1]='W';
                    }
                    if(x1-1<10 && x1-1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[x1-1][i-1]==' ')
                    {
                        op_player->visible_map[x1-1][i-1]='W';
                    }
                }
            }
            else if(y1==y2)
            {
                for(int i=fmin(x1,x2);i<=fmax(x1,x2);i++)
                {
                    op_player->visible_map[i][y1]='#';
                    if(y1<10 && y1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[i][y1+1]==' ')
                    {
                        op_player->visible_map[i][y1+1]='W';
                    }
                    if(y1-1<10 && y1-1>=0 && i<10 && i>=0 && op_player->visible_map[i][y1-1]==' ')
                    {
                        op_player->visible_map[i][y1-1]='W';
                    }
                    if(y1<10 && y1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[i+1][y1]==' ')
                    {
                        op_player->visible_map[i+1][y1]='W';
                    }
                    if(y1<10 && y1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[i-1][y1]==' ')
                    {
                        op_player->visible_map[i-1][y1]='W';
                    }
                    if(y1+1<10 && y1+1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[i+1][y1+1]==' ')
                    {
                        op_player->visible_map[i+1][y1+1]='W';
                    }
                    if(y1+1<10 && y1+1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[i-1][y1+1]==' ')
                    {
                        op_player->visible_map[i-1][y1+1]='W';
                    }
                    if(y1-1<10 && y1-1>=0 && i+1<10 && i+1>=0 && op_player->visible_map[i+1][y1-1]==' ')
                    {
                        op_player->visible_map[i+1][y1-1]='W';
                    }
                    if(y1-1<10 && y1-1>=0 && i-1<10 && i-1>=0 && op_player->visible_map[i-1][y1-1]==' ')
                    {
                        op_player->visible_map[i-1][y1-1]='W';
                    }
                }
            }
        }
    }
}

bool turn(player *player1,player *player2,int t)
{
    fflush(stdin);
    bool sw=0;
    player *op_player;
    if(t==1)
    {
        printf("%s This Is Your Turn \n",player1->name);
        op_player=player2;
        show_visible_map(player2);
        fflush(stdin);
    }
    if(t==2)
    {
        printf("%s This Is Your Turn \n",player2->name);
        op_player=player1;
        show_visible_map(player1);
        fflush(stdin);
    }
    int x,y;
    do
    {
        printf("\nPlaese Enter Your Target Coordinates : \n(-1 -1 To Use ROCKET Needs 100 Scores)\n(-2 -2 To Save Your Game)\n");
        fflush(stdin);
        scanf("%d",&x);
        scanf("%d",&y);
        fflush(stdin);
        if(x==-1 && y==-1)
        {
            fflush(stdin);
            continue;
        }
        else if(x==-2 && y==-2)
        {
            fflush(stdin);
            save_info info;
            info.t=t;
            info.type=2;
            info.player1=*player1;
            info.player2=*player2;
            char temp[max_name_size];
            do
            {
                printf("Please Enter A Name For Your Save : ");
                fflush(stdin);
                scanf("%s",&temp);
                strcpy(info.name,temp);
                fflush(stdin);
            }while(save_game(info)==0);
            printf("The Game Successfully Saved\n");
            fflush(stdin);
            char c;
            do
            {
                printf("Do You Want Quit (y/n) / (Y/N) : ");
                fflush(stdin);
                scanf("%c",&c);
                if(c=='Y' || c=='y')
                {
                    system("pause");
                    exit(0);
                }
                fflush(stdin);
            }while(c!='y' && c!='Y' && c!='n' && c!='N');
            fflush(stdin);
        }
        else if(x>=0 && x<10 && y>=0 && y<10)
        {
            if(check_valid_target(op_player,x,y)==0)
            {
                fflush(stdin);
                continue;
            }
            if(op_player->hidden_map[x][y]<0)
            {
                op_player->visible_map[x][y]='W';
            }
            else
            {
                op_player->visible_map[x][y]='*';
                sw=1;
                fflush(stdin);
                update_list(op_player,x,y,t);
                fflush(stdin);
            }
            break;
        }
        else
        {
            fflush(stdin);
            continue;
        }
    }while(1);
    fflush(stdin);
    Sleep(1000);
    system("cls");
    system("cls");
    printf("This Is %s Map After Your Turn \n",op_player->name);
    show_visible_map(op_player);
    printf("\n");
    system("pause");
    system("cls");
    system("cls");
    fflush(stdin);
    return sw;
}

void play(player *player1,player *player2,int t)
{
    fflush(stdin);
    while(ships1!=NULL && ships2!=NULL)
    {
        fflush(stdin);
        bool sw=turn(player1,player2,t);
        fflush(stdin);
        if(sw==0)
        {
            if(t==1)
            {
                t=2;
            }
            else
            {
                t=1;
            }
        }
    }
    int a=search_name(player1->name);
    fflush(stdin);
    int b=search_name(player2->name);
    fflush(stdin);
    if(ships2==NULL)
    {
        player1->delta_score+=178;
        int nscore=178;
        while(ships1!=NULL)
        {   
            nscore-=ships1->cur;
            if(ships1->sz==5)
            {
                nscore-=5;
            }
            else if(ships1->sz==3)
            {
                nscore-=8;
            }
            else if(ships1->sz==2)
            {
                nscore-=12;
            }
            else if(ships1->sz==1)
            {
                nscore-=25;
            }
            delete_ship(&ships1,ships1->id);
        }
        player2->delta_score+=nscore;
        add_score(a,player1->delta_score);
        fflush(stdin);    
        add_score(b,player2->delta_score/2);
        fflush(stdin);        
        system("cls");
        printf("\t%s WON THE GAME !!!\n\n",player1->name);
        system("pause");
        system("cls");
        system("cls");
        fflush(stdin);
    }
    else if(ships1==NULL)
    {
        player2->delta_score+=178;
        int nscore=178;
        while(ships2!=NULL)
        {   
            nscore-=ships2->cur;
            if(ships2->sz==5)
            {
                nscore-=5;
            }
            else if(ships2->sz==3)
            {
                nscore-=8;
            }
            else if(ships2->sz==2)
            {
                nscore-=12;
            }
            else if(ships2->sz==1)
            {
                nscore-=25;
            }
            delete_ship(&ships2,ships2->id);
        }
        player1->delta_score+=nscore;
        add_score(a,player1->delta_score/2);
        fflush(stdin);    
        add_score(b,player2->delta_score);
        fflush(stdin);
        system("cls");
        printf("\t%s WON THE GAME !!!\n\n",player2->name);
        system("pause");
        system("cls");
        system("cls");
        fflush(stdin);
    }
}

bool turn_bot(player *player1,player *CPU,int t)
{
    fflush(stdin);
    bool sw=0;
    player *op_player;
    
    if(t==1)
    {
        printf("%s This Is Your Turn \n",player1->name);
        op_player=CPU;
        show_visible_map(CPU);
        fflush(stdin);
        int x,y;
        do
        {
            printf("\nPlaese Enter Your Target Coordinates : \n(-1 -1 To Use ROCKET Needs 100 Scores)\n(-2 -2 To Save Your Game)\n");
            fflush(stdin);
            scanf("%d",&x);
            scanf("%d",&y);
            fflush(stdin);
            if(x==-1 && y==-1)
            {
                fflush(stdin);
                continue;
            }
            else if(x==-2 && y==-2)
            {
                fflush(stdin);
                save_info info;
                info.t=t;
                info.type=1;
                info.player1=*player1;
                info.player2=*CPU;
                char temp[max_name_size];
                do
                {
                    printf("Please Enter A Name For Your Save : ");
                    fflush(stdin);
                    scanf("%s",&temp);
                    strcpy(info.name,temp);
                    fflush(stdin);
                }while(save_game(info)==0);
                printf("The Game Successfully Saved\n");
                fflush(stdin);
                char c;
                do
                {
                    printf("Do You Want Quit (y/n) / (Y/N) : ");
                    fflush(stdin);
                    scanf("%c",&c);
                    if(c=='Y' || c=='y')
                    {
                        system("pause");
                        exit(0);
                    }
                    fflush(stdin);
                }while(c!='y' && c!='Y' && c!='n' && c!='N');
                fflush(stdin);
            }
            else if(x>=0 && x<10 && y>=0 && y<10)
            {
                if(check_valid_target(op_player,x,y)==0)
                {
                    fflush(stdin);
                    continue;
                }
                if(op_player->hidden_map[x][y]<0)
                {
                    op_player->visible_map[x][y]='W';
                }
                else
                {
                    op_player->visible_map[x][y]='*';
                    sw=1;
                    fflush(stdin);
                    update_list(op_player,x,y,t);
                    fflush(stdin);
                }
                break;
            }
            else
            {
                fflush(stdin);
                continue;
            }
        }while(1);
    }
    else if(t==2)
    {
        op_player=player1;
        fflush(stdin);
        int x,y;
        int star_cnt=0;
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(op_player->visible_map[i][j]=='*')
                {
                    star_cnt++;
                }
            }
        }
        while(1)
        {
            x=rand()%10;
            y=rand()%10;
            if(op_player->visible_map[x][y]!=' ')
            {
                fflush(stdin);
                continue;
            }
            if(star_cnt==1)
            {
                if(x-1>=0 && op_player->visible_map[x-1][y]=='*')
                {
                    fflush(stdin);
                    break;
                }
                if(x+1<10 && op_player->visible_map[x+1][y]=='*')
                {
                    fflush(stdin);
                    break;
                }
                if(y-1>=0 && op_player->visible_map[x][y-1]=='*')
                {
                    fflush(stdin);
                    break;
                }
                if(y+1<10 && op_player->visible_map[x][y+1]=='*')
                {
                    fflush(stdin);
                    break;
                }
                fflush(stdin);
                continue;
            }
            else if(star_cnt>1)
            {
                if(x-1>=0 && op_player->visible_map[x-1][y]=='*')
                {
                    fflush(stdin);
                    break;
                }
                if(x+1<10 && op_player->visible_map[x+1][y]=='*')
                {
                    fflush(stdin);
                    break;
                }
                if(y-1>=0 && op_player->visible_map[x][y-1]=='*')
                {
                    fflush(stdin);
                    break;
                }
                if(y+1<10 && op_player->visible_map[x][y+1]=='*')
                {
                    fflush(stdin);
                    break;
                }
                fflush(stdin);
                continue;
            }
            else
            {
                fflush(stdin);
                break;
            }
        }
        if(op_player->hidden_map[x][y]<0)
        {
            op_player->visible_map[x][y]='W';
        }
        else
        {
            op_player->visible_map[x][y]='*';
            sw=1;
            fflush(stdin);
            update_list(op_player,x,y,t);
            fflush(stdin);
        }
    }
    fflush(stdin);
    Sleep(1000);
    system("cls");
    system("cls");
    if(t==1)
    {
        printf("This Is CPUs Map After Your Turn \n");
    }
    else
    {
        printf("This Is Your Map After CPUs Turn \n");
    }
    show_visible_map(op_player);
    printf("\n");
    system("pause");
    system("cls");
    system("cls");
    fflush(stdin);
    return sw;
}

void play_bot(player *player1,player *CPU,int t)
{
    fflush(stdin);
    while(ships1!=NULL && ships2!=NULL)
    {
        fflush(stdin);
        bool sw=turn_bot(player1,CPU,t);
        fflush(stdin);
        if(sw==0)
        {
            if(t==1)
            {
                t=2;
            }
            else
            {
                t=1;
            }
        }
    }
    int a=search_name(player1->name);
    fflush(stdin);
    if(ships2==NULL)
    {
        player1->delta_score+=178;
        while(ships1!=NULL)
        {   
            delete_ship(&ships1,ships1->id);
        }
        add_score(a,player1->delta_score);
        fflush(stdin);       
        system("cls");
        printf("\t%s WON THE GAME !!!\n\n",player1->name);
        system("pause");
        system("cls");
        system("cls");
        fflush(stdin);
    }
    else if(ships1==NULL)
    {
        int nscore=178;
        while(ships2!=NULL)
        {   
            nscore-=ships2->cur;
            if(ships2->sz==5)
            {
                nscore-=5;
            }
            else if(ships2->sz==3)
            {
                nscore-=8;
            }
            else if(ships2->sz==2)
            {
                nscore-=12;
            }
            else if(ships2->sz==1)
            {
                nscore-=25;
            }
            delete_ship(&ships2,ships2->id);
        }
        player1->delta_score+=nscore;
        add_score(a,player1->delta_score/2);
        fflush(stdin);   
        system("cls");
        printf("\t%s WON THE GAME !!!\n\n",CPU->name);
        system("pause");
        system("cls");
        system("cls");
        fflush(stdin);
    }
}

// Menu Functions

void play_with_friend()
{
    fflush(stdin);
    player player1;
    player player2;

    init_player(&player1,1,"a");
    fflush(stdin);
    make_lists(1);
    fflush(stdin);
    while(init_player(&player2,2,player1.name)==0)
    {
        fflush(stdin);
    }
    fflush(stdin);
    make_lists(2);
    fflush(stdin);
    play(&player1,&player2,1);
    fflush(stdin);
}

void play_with_cpu()
{
    fflush(stdin);
    player player1;
    player CPU;

    init_player(&player1,1,"a");
    fflush(stdin);
    make_lists(1);

    fflush(stdin);
    strcpy(CPU.name,"CPU");
    CPU.score=0;
    CPU.delta_score=0;
    CPU.is_special=0;

    init_map(&CPU);
    
    //Ship 0
    put_selected_ship(&CPU,0,1,1,1,5);
    total_ships[0].x1=1;
    total_ships[0].x2=1;
    total_ships[0].y1=1;
    total_ships[0].y2=5;
    total_ships[0].id=0;
    total_ships[0].sz=5;
    total_ships[0].cur=5;
    total_ships[0].next=NULL;
    //Ship 1
    put_selected_ship(&CPU,1,6,8,8,8);
    total_ships[1].x1=6;
    total_ships[1].x2=8;
    total_ships[1].y1=8;
    total_ships[1].y2=8;
    total_ships[1].id=1;
    total_ships[1].sz=3;
    total_ships[1].cur=3;
    total_ships[1].next=NULL;
    //Ship 2
    put_selected_ship(&CPU,2,5,5,2,4);
    total_ships[2].x1=5;
    total_ships[2].x2=5;
    total_ships[2].y1=2;
    total_ships[2].y2=4;
    total_ships[2].id=2;
    total_ships[2].sz=3;
    total_ships[2].cur=3;
    total_ships[2].next=NULL;
    //Ship 3
    put_selected_ship(&CPU,3,9,9,1,2);
    total_ships[3].x1=9;
    total_ships[3].x2=9;
    total_ships[3].y1=1;
    total_ships[3].y2=2;
    total_ships[3].id=3;
    total_ships[3].sz=2;
    total_ships[3].cur=2;
    total_ships[3].next=NULL;
    //Ship 4
    put_selected_ship(&CPU,4,5,6,0,0);
    total_ships[4].x1=5;
    total_ships[4].x2=6;
    total_ships[4].y1=0;
    total_ships[4].y2=0;
    total_ships[4].id=4;
    total_ships[4].sz=2;
    total_ships[4].cur=2;
    total_ships[4].next=NULL;
    //Ship 5
    put_selected_ship(&CPU,5,2,2,8,9);
    total_ships[5].x1=2;
    total_ships[5].x2=2;
    total_ships[5].y1=8;
    total_ships[5].y2=9;
    total_ships[5].id=5;
    total_ships[5].sz=2;
    total_ships[5].cur=2;
    total_ships[5].next=NULL;
    //Ship 6
    put_selected_ship(&CPU,6,0,0,8,8);
    total_ships[6].x1=0;
    total_ships[6].x2=0;
    total_ships[6].y1=8;
    total_ships[6].y2=8;
    total_ships[6].id=6;
    total_ships[6].sz=1;
    total_ships[6].cur=1;
    total_ships[6].next=NULL;
    //Ship 7
    put_selected_ship(&CPU,7,3,3,2,2);
    total_ships[7].x1=3;
    total_ships[7].x2=3;
    total_ships[7].y1=2;
    total_ships[7].y2=2;
    total_ships[7].id=7;
    total_ships[7].sz=1;
    total_ships[7].cur=1;
    total_ships[7].next=NULL;
    //Ship 8
    put_selected_ship(&CPU,8,8,8,5,5);
    total_ships[8].x1=8;
    total_ships[8].x2=8;
    total_ships[8].y1=5;
    total_ships[8].y2=5;
    total_ships[8].id=8;
    total_ships[8].sz=1;
    total_ships[8].cur=1;
    total_ships[8].next=NULL;
    //Ship 9
    put_selected_ship(&CPU,9,4,4,6,6);
    total_ships[9].x1=4;
    total_ships[9].x2=4;
    total_ships[9].y1=6;
    total_ships[9].y2=6;
    total_ships[9].id=9;
    total_ships[9].sz=1;
    total_ships[9].cur=1;
    total_ships[9].next=NULL;

    fflush(stdin);
    make_lists(2);
    fflush(stdin);
    
    play_bot(&player1,&CPU,1);
    fflush(stdin);
}

void load_all_games()
{
    print_saves();
    fflush(stdin);
    save_info info;
    char temp[max_name_size];
    printf("Please Enter Your Save Name : ");
    fflush(stdin);
    scanf("%s",&temp);
    if(load_game(&info,temp)==0)
    {
        printf("Can't Load This Save \n");
        fflush(stdin);
        return;
    }
    player player1=info.player1;
    player player2=info.player2;
    fflush(stdin);
    for(int k=0;k<10;k++)
    {
        int x1,x2,y1,y2;
        int sz=0;
        int cur=0;
        int id=k;
        int sw=1;
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                int cnt=0;
                if(player1.hidden_map[i][j]==id)
                {
                    sz++;
                    if(player1.visible_map[i][j]=='*' || player1.visible_map[i][j]=='#')
                    {
                        cur--;
                    }
                    if(j+1>=0 && j+1<10 && player1.hidden_map[i][j+1]==id)
                    {
                        cnt++;
                    }
                    if(j-1>=0 && j-1<10 && player1.hidden_map[i][j-1]==id)
                    {
                        cnt++;
                    }
                    if(i+1>=0 && i+1<10 && player1.hidden_map[i+1][j]==id)
                    {
                        cnt++;
                    }
                    if(i-1>=0 && i-1<10 && player1.hidden_map[i-1][j]==id)
                    {
                        cnt++;
                    }
                    if(cnt<2)
                    {
                        if(sw==1)
                        {
                            sw++;
                            x1=i;
                            y1=j;
                        }
                        else
                        {
                            x2=i;
                            y2=j;
                        }
                    }
                }
            }
        }
        cur+=sz;
        if(sz==1)
        {
            x2=x1;
            y2=y1;
        }
        total_ships[k].x1=x1;
        total_ships[k].x2=x2;
        total_ships[k].y1=y1;
        total_ships[k].y2=y2;
        total_ships[k].id=id;
        total_ships[k].sz=sz;
        total_ships[k].cur=cur;
    }
    make_lists(1);

    fflush(stdin);
    for(int k=0;k<10;k++)
    {
        int x1,x2,y1,y2;
        int sz=0;
        int cur=0;
        int id=k;
        int sw=1;
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                int cnt=0;
                if(player2.hidden_map[i][j]==id)
                {
                    sz++;
                    if(player2.visible_map[i][j]==' ')
                    {
                        cur++;
                    }
                    if(j+1>=0 && j+1<10 && player2.hidden_map[i][j+1]==id)
                    {
                        cnt++;
                    }
                    if(j-1>=0 && j-1<10 && player2.hidden_map[i][j-1]==id)
                    {
                        cnt++;
                    }
                    if(i+1>=0 && i+1<10 && player2.hidden_map[i+1][j]==id)
                    {
                        cnt++;
                    }
                    if(i-1>=0 && i-1<10 && player2.hidden_map[i-1][j]==id)
                    {
                        cnt++;
                    }
                    if(cnt<2)
                    {
                        if(sw==1)
                        {
                            sw++;
                            x1=i;
                            y1=j;
                        }
                        else
                        {
                            x2=i;
                            y2=j;
                        }
                    }
                }
            }
        }
        if(sz==1)
        {
            x2=x1;
            y2=y1;
        }
        total_ships[k].x1=x1;
        total_ships[k].x2=x2;
        total_ships[k].y1=y1;
        total_ships[k].y2=y2;
        total_ships[k].id=id;
        total_ships[k].sz=sz;
        total_ships[k].cur=cur;
    }
    make_lists(2);

    fflush(stdin);
    if(info.type==2)
    {
        play(&player1,&player2,info.t);
    }
    else if(info.type==1)
    {
        play_bot(&player1,&player2,info.t);
    }
}

void load_last_game()
{
    fflush(stdin);
    save_info info;
    FILE *fin=fopen("Resources\\saves.bin","rb");
    if(fin==NULL)
    {
        printf("There Is Not Any Saved Game\n");
        fflush(stdin);
        system("pause");
        system("cls");
        fclose(fin);
        return;
    }
    int i=0;
    while(fread(&info,sizeof(save_info),1,fin)>=1)
    {
        i++;
    }
    rewind(fin);
    fseek(fin,(i-1)*sizeof(save_info),SEEK_SET);
    fread(&info,sizeof(save_info),1,fin);
    fclose(fin);

    player player1=info.player1;
    player player2=info.player2;
    fflush(stdin);
    for(int k=0;k<10;k++)
    {
        int x1,x2,y1,y2;
        int sz=0;
        int cur=0;
        int id=k;
        int sw=1;
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                int cnt=0;
                if(player1.hidden_map[i][j]==id)
                {
                    sz++;
                    if(player1.visible_map[i][j]=='*' || player1.visible_map[i][j]=='#')
                    {
                        cur--;
                    }
                    if(j+1>=0 && j+1<10 && player1.hidden_map[i][j+1]==id)
                    {
                        cnt++;
                    }
                    if(j-1>=0 && j-1<10 && player1.hidden_map[i][j-1]==id)
                    {
                        cnt++;
                    }
                    if(i+1>=0 && i+1<10 && player1.hidden_map[i+1][j]==id)
                    {
                        cnt++;
                    }
                    if(i-1>=0 && i-1<10 && player1.hidden_map[i-1][j]==id)
                    {
                        cnt++;
                    }
                    if(cnt<2)
                    {
                        if(sw==1)
                        {
                            sw++;
                            x1=i;
                            y1=j;
                        }
                        else
                        {
                            x2=i;
                            y2=j;
                        }
                    }
                }
            }
        }
        cur+=sz;
        if(sz==1)
        {
            x2=x1;
            y2=y1;
        }
        total_ships[k].x1=x1;
        total_ships[k].x2=x2;
        total_ships[k].y1=y1;
        total_ships[k].y2=y2;
        total_ships[k].id=id;
        total_ships[k].sz=sz;
        total_ships[k].cur=cur;
    }
    make_lists(1);

    fflush(stdin);
    for(int k=0;k<10;k++)
    {
        int x1,x2,y1,y2;
        int sz=0;
        int cur=0;
        int id=k;
        int sw=1;
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                int cnt=0;
                if(player2.hidden_map[i][j]==id)
                {
                    sz++;
                    if(player2.visible_map[i][j]==' ')
                    {
                        cur++;
                    }
                    if(j+1>=0 && j+1<10 && player2.hidden_map[i][j+1]==id)
                    {
                        cnt++;
                    }
                    if(j-1>=0 && j-1<10 && player2.hidden_map[i][j-1]==id)
                    {
                        cnt++;
                    }
                    if(i+1>=0 && i+1<10 && player2.hidden_map[i+1][j]==id)
                    {
                        cnt++;
                    }
                    if(i-1>=0 && i-1<10 && player2.hidden_map[i-1][j]==id)
                    {
                        cnt++;
                    }
                    if(cnt<2)
                    {
                        if(sw==1)
                        {
                            sw++;
                            x1=i;
                            y1=j;
                        }
                        else
                        {
                            x2=i;
                            y2=j;
                        }
                    }
                }
            }
        }
        if(sz==1)
        {
            x2=x1;
            y2=y1;
        }
        total_ships[k].x1=x1;
        total_ships[k].x2=x2;
        total_ships[k].y1=y1;
        total_ships[k].y2=y2;
        total_ships[k].id=id;
        total_ships[k].sz=sz;
        total_ships[k].cur=cur;
    }
    make_lists(2);

    fflush(stdin);
    if(info.type==2)
    {
        play(&player1,&player2,info.t);
    }
    else if(info.type==1)
    {
        play_bot(&player1,&player2,info.t);
    }
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

void show_mainmenu()
{
    system("cls");
    system("cls");
    fflush(stdin);
    int x;
    do
    {
        printf("\n\t\tMAIN MENU\n-----------------------------------------\n");
        printf("1) Play With A Friend \n2) Play With CPU \n3) Load Game \n4) Load Last Game \n5) Play Back \n6) Score Board \n7) Exit \n");
        fflush(stdin);
        scanf("%d",&x);
        if(x==1)
        {
            fflush(stdin);
            play_with_friend();
            fflush(stdin);
        }   
        else if(x==2)
        {
            fflush(stdin);
            play_with_cpu();
            fflush(stdin);
        }
        else if(x==3)
        {
            fflush(stdin);
            load_all_games();
            fflush(stdin);
        }
        else if(x==4)
        {
            fflush(stdin);
            load_last_game();
            fflush(stdin);
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
            system("cls");
            continue;
        }

    } while (x!=7);
}


int main()
{
    load_settings();
    srand(time(NULL));
    show_mainmenu();
}