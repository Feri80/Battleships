//                      Show Map
//***************************************************
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
//***************************************************