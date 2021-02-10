//                     Linked List
//***************************************************
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
//***************************************************