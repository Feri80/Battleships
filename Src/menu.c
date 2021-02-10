//                  Menu Functions
//***************************************************
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
    setTextColor(GREEN);
    printf("\n\t\t\t\tSCORE BOARD");
    setTextColor(PURPLE);
    printf("\n--------------------------------------------------------------------------------\n");
    for(int i=0;i<user_count-1;i++)
    {
        setTextColor(GREEN);
        printf("%d) %-50s\t\tScore : %d ",i+1,users[i].name,users[i].score);
        setTextColor(PURPLE);
        printf("\n--------------------------------------------------------------------------------\n");
    }
    setTextColor(WHITE);
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
        setTextColor(GREEN);
        printf("\n\t\tMAIN MENU\n-----------------------------------------\n");
        printf("1) Play With A Friend \n2) Play With CPU \n3) Load Game \n4) Load Last Game \n5) Score Board \n6) Exit \n");
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
            show_scoreboard();
            fflush(stdin);
        }
        else if(x==6)
        {
            system("cls");
            exit(0);
        }
        else
        {
            fflush(stdin);
            system("cls");
            continue;
        }

    } while (x!=6);
}
//***************************************************