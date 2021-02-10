//                 Username Functions
//***************************************************
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
//***************************************************
