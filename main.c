//***************************************************
//               In The Name Of God
//                   BattleShips
//    Fundamentals Of Programming Final Project
//             Created By Farhad Aman
//                   Winter 2021
//***************************************************

#include "Src\\preprocessor.c"
#include "Src\\struct.c"
#include "Src\\linked_list.c"
#include "Src\\user_settings.c"
#include "Src\\show_map.c"
#include "Src\\username.c"
#include "Src\\gameplay.c"
#include "Src\\menu.c"

int main()
{
    load_settings();
    srand(time(NULL));
    show_mainmenu();
}