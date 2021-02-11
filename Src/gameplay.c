//              Gameplay Functions
//***************************************************
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
        printf("\nPlaese Enter Your First Size 1 Ship Coordinates (Like)  x1 y1 : \n (If You Want To Reset Map Enter -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        x2=x1;
        y2=y1;
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
        printf("\nPlaese Enter Your Second Size 1 Ship Coordinates (Like)  x1 y1 : \n (If You Want To Reset Map Enter -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        x2=x1;
        y2=y1;
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
        printf("\nPlaese Enter Your Third Size 1 Ship Coordinates (Like)  x1 y1 : \n (If You Want To Reset Map Enter -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        x2=x1;
        y2=y1;
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
        printf("\nPlaese Enter Your Fourth Size 1 Ship Coordinates (Like)  x1 y1 : \n (If You Want To Reset Map Enter -1 -1) \n");
        fflush(stdin);
        scanf("%d",&x1);
        scanf("%d",&y1);
        x2=x1;
        y2=y1;
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
    system("cls");
    system("cls");
    system("cls");
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

int turn(player *player1,player *player2,int t)
{
    fflush(stdin);
    bool sw=0;
    player *op_player;
    player *vis_player;
    if(t==1)
    {
        printf("%s This Is Your Turn \n",player1->name);
        op_player=player2;
        vis_player=player1;
        show_visible_map(player2);
        fflush(stdin);
    }
    if(t==2)
    {
        printf("%s This Is Your Turn \n",player2->name);
        op_player=player1;
        vis_player=player2;
        show_visible_map(player1);
        fflush(stdin);
    }
    int x,y;
    do
    {
        printf("\nPlaese Enter Your Target Coordinates : \n(-1 -1 To Use ROCKET Needs 100 Scores)\n(-2 -2 To Save Your Game)\n(-3 -3 To Show Main Menu)\n");
        fflush(stdin);
        scanf("%d",&x);
        scanf("%d",&y);
        fflush(stdin);
        if(x==-1 && y==-1)
        {
            if(vis_player->score<100)
            {
                printf("You Do Not Have Enough Scores\n");
                fflush(stdin);
                continue;
            }
            if(vis_player->is_special==1)
            {
                printf("You Have Already Used Your Rocket\n");
                fflush(stdin);
                continue;
            }
            char w;
            int r;
            char c;
            fflush(stdin);
            do
            {
                do
                {
                    printf("Please Enter The Rocket Way (H/V) / (h/v) : ");
                    fflush(stdin);
                    scanf("%c",&w);
                    fflush(stdin);
                }while(w!='H' && w!='V' && w!='h' && w!='v');
                do
                {
                    printf("Please Enter The Rocket Row/Column (0-9) : ");
                    fflush(stdin);
                    scanf("%d",&r);
                    fflush(stdin);
                }while(r<0 || r>9);
                do
                {
                    printf("%c %d Are Your Sure (Y/N) / (y/n) : ",w,r);
                    fflush(stdin);
                    scanf("%c",&c);
                    fflush(stdin);
                }while(c!='Y' && c!='N' && c!='y' && c!='N');
                
                if(c=='Y' || c=='y')
                {
                    fflush(stdin);
                    break;
                }
                else if(c=='N' || c=='n')
                {
                    fflush(stdin);
                    continue;
                }
                else
                {
                    fflush(stdin);
                    continue;
                }
            }while(1);
            fflush(stdin);
            vis_player->is_special=1;
            if(w=='H' || w=='h')
            {
                for(int i=0;i<10;i++)
                {
                    if(op_player->hidden_map[r][i]<0)
                    {
                        op_player->visible_map[r][i]='W';
                    }
                    else if(op_player->visible_map[r][i]==' ')
                    {
                        op_player->visible_map[r][i]='*';
                        sw=1;
                        fflush(stdin);
                        update_list(op_player,r,i,t);
                        fflush(stdin);
                        break;
                    }
                }
            }
            else if(w=='V' || w=='v')
            {
                for(int i=0;i<10;i++)
                {
                    if(op_player->hidden_map[i][r]<0)
                    {
                        op_player->visible_map[i][r]='W';
                    }
                    else if(op_player->visible_map[i][r]==' ')
                    {
                        op_player->visible_map[i][r]='*';
                        sw=1;
                        fflush(stdin);
                        update_list(op_player,i,r,t);
                        fflush(stdin);
                        break;
                    }
                }
            }
            fflush(stdin);
            break;
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
                printf("Do You Want To Exit The Game (y/n) / (Y/N) : ");
                fflush(stdin);
                scanf("%c",&c);
                if(c=='Y' || c=='y')
                {
                    system("pause");
                    system("cls");
                    return 2;
                }
                fflush(stdin);
            }while(c!='y' && c!='Y' && c!='n' && c!='N');
            fflush(stdin);
        }
        else if(x==-3 && y==-3)
        {
            fflush(stdin);
            system("cls");
            return 2;
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
    if(sw==0)
    {
        Sleep(200);
        Beep(250,500);
    }
    else
    {
        Sleep(200);
        Beep(600,500);
    }
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
    int sw;
    while(ships1!=NULL && ships2!=NULL)
    {
        fflush(stdin);
        sw=turn(player1,player2,t);
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
        if(sw==2)
        {
            break;
        }
    }
    int a=search_name(player1->name);
    fflush(stdin);
    int b=search_name(player2->name);
    fflush(stdin);
    if(ships1!=NULL)
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
        if(sw!=2)
        {
            add_score(a,player1->delta_score);
            if(player1->is_special==1)
            {
               add_score(a,-100);
            }
        }
        fflush(stdin);
        if(sw!=2)
        {
            add_score(b,player2->delta_score/2);
            if(player2->is_special==1)
            {
               add_score(b,-100);
            }
        }    
        fflush(stdin);        
        system("cls");
        if(sw!=2)
        {
            printf("\t%s WON THE GAME !!!\n\n",player1->name);
        }
        system("pause");
        system("cls");
        system("cls");
        fflush(stdin);
    }
    if(ships2!=NULL)
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
        if(sw!=2)
        {
            add_score(a,player1->delta_score/2);
            if(player1->is_special==1)
            {
               add_score(a,-100);
            }
        }
        fflush(stdin);
        if(sw!=2)
        {
            add_score(b,player2->delta_score);
            if(player2->is_special==1)
            {
               add_score(b,-100);
            }
        }    
        fflush(stdin);
        system("cls");
        if(sw!=2)
        {
            printf("\t%s WON THE GAME !!!\n\n",player2->name);
        }
        system("pause");
        system("cls");
        system("cls");
        fflush(stdin);
    }
}

int turn_bot(player *player1,player *CPU,int t)
{
    fflush(stdin);
    bool sw=0;
    player *op_player;
    player *vis_player;
    if(t==1)
    {
        printf("%s This Is Your Turn \n",player1->name);
        op_player=CPU;
        vis_player=player1;
        show_visible_map(CPU);
        fflush(stdin);
        int x,y;
        do
        {
            printf("\nPlaese Enter Your Target Coordinates : \n(-1 -1 To Use ROCKET Needs 100 Scores)\n(-2 -2 To Save Your Game)\n(-3 -3 To Show Main Menu)\n");
            fflush(stdin);
            scanf("%d",&x);
            scanf("%d",&y);
            fflush(stdin);
            if(x==-1 && y==-1)
            {
                if(vis_player->score<100)
                {
                    printf("You Do Not Have Enough Scores\n");
                    fflush(stdin);
                    continue;
                }
                if(vis_player->is_special==1)
                {
                    printf("You Have Already Used Your Rocket\n");
                    fflush(stdin);
                    continue;
                }
                char w;
                int r;
                char c;
                fflush(stdin);
                do
                {
                    do
                    {
                        printf("Please Enter The Rocket Way (H/V) / (h/v) : ");
                        fflush(stdin);
                        scanf("%c",&w);
                        fflush(stdin);
                    }while(w!='H' && w!='V' && w!='h' && w!='v');
                    do
                    {
                        printf("Please Enter The Rocket Row/Column (0-9) : ");
                        fflush(stdin);
                        scanf("%d",&r);
                        fflush(stdin);
                    }while(r<0 || r>9);
                    do
                    {
                        printf("%c %d Are Your Sure (Y/N) / (y/n) : ",w,r);
                        fflush(stdin);
                        scanf("%c",&c);
                        fflush(stdin);
                    }while(c!='Y' && c!='N' && c!='y' && c!='N');
                
                    if(c=='Y' || c=='y')
                    {
                        fflush(stdin);
                        break;
                    }
                    else if(c=='N' || c=='n')
                    {
                        fflush(stdin);
                        continue;
                    }
                    else
                    {
                        fflush(stdin);
                        continue;
                    }
                }while(1);
                fflush(stdin);
                vis_player->is_special=1;
                if(w=='H' || w=='h')
                {
                    for(int i=0;i<10;i++)
                    {
                        if(op_player->hidden_map[r][i]<0)
                        {
                            op_player->visible_map[r][i]='W';
                        }
                        else if(op_player->visible_map[r][i]==' ')
                        {
                            op_player->visible_map[r][i]='*';
                            sw=1;
                            fflush(stdin);
                            update_list(op_player,r,i,t);
                            fflush(stdin);
                            break;
                        }
                    }
                }
                else if(w=='V' || w=='v')
                {
                    for(int i=0;i<10;i++)
                    {
                        if(op_player->hidden_map[i][r]<0)
                        {
                            op_player->visible_map[i][r]='W';
                        }
                        else if(op_player->visible_map[i][r]==' ')
                        {
                            op_player->visible_map[i][r]='*';
                            sw=1;
                            fflush(stdin);
                            update_list(op_player,i,r,t);
                            fflush(stdin);
                            break;
                        }
                    }
                }
                fflush(stdin);
                break;
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
                    printf("Do You Want To Exit The Game (y/n) / (Y/N) : ");
                    fflush(stdin);
                    scanf("%c",&c);
                    if(c=='Y' || c=='y')
                    {
                        system("pause");
                        system("cls");
                        return 2;
                    }
                    fflush(stdin);
                }while(c!='y' && c!='Y' && c!='n' && c!='N');
                fflush(stdin);
            }
            else if(x==-3 && y==-3)
            {
                fflush(stdin);
                system("cls");
                return 2;
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
                if(x-2>=0 && op_player->visible_map[x-1][y]=='*' && op_player->visible_map[x-2][y]=='*')
                {
                    fflush(stdin);
                    break;
                }
                if(x+2<10 && op_player->visible_map[x+1][y]=='*' && op_player->visible_map[x+2][y]=='*')
                {
                    fflush(stdin);
                    break;
                }
                if(y-2>=0 && op_player->visible_map[x][y-1]=='*' && op_player->visible_map[x][y-2]=='*')
                {
                    fflush(stdin);
                    break;
                }
                if(y+2<10 && op_player->visible_map[x][y+1]=='*' && op_player->visible_map[x][y+2]=='*')
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
    if(sw==0)
    {
        Sleep(200);
        Beep(250,400);
    }
    else
    {
        Sleep(200);
        Beep(600,400);
    }
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
    int sw;
    while(ships1!=NULL && ships2!=NULL)
    {
        fflush(stdin);
        sw=turn_bot(player1,CPU,t);
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
        if(sw==2)
        {
            break;
        }
    }
    int a=search_name(player1->name);
    fflush(stdin);
    if(ships1!=NULL)
    {
        player1->delta_score+=178;
        while(ships1!=NULL)
        {   
            delete_ship(&ships1,ships1->id);
        }
        if(sw!=2)
        {
            add_score(a,player1->delta_score);
            if(player1->is_special==1)
            {
                add_score(a,-100);
            }
        }
        fflush(stdin);       
        system("cls");
        if(sw!=2)
        {
            printf("\t%s WON THE GAME !!!\n\n",player1->name);
        }
        system("pause");
        system("cls");
        system("cls");
        fflush(stdin);
    }
    if(ships2!=NULL)
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
        if(sw!=2)
        {
            add_score(a,player1->delta_score/2);
            if(player1->is_special==1)
            {
                add_score(a,-100);
            }
        }
        fflush(stdin);   
        system("cls");
        if(sw!=2)
        {
            printf("\t%s WON THE GAME !!!\n\n",CPU->name);
        }
        system("pause");
        system("cls");
        system("cls");
        fflush(stdin);
    }
}
//***************************************************