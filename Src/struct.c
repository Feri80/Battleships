//                      Struct
//***************************************************
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
//***************************************************

//                       Game Saves
//***************************************************
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
//***************************************************