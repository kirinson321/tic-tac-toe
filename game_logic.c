/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/
#include <stdlib.h>
#include "tic_tac_toe.h"

char this_player_turn = '1';

void send_data()
{
    gchar output[(size*size)+2];

    output[0] = this_player_turn;
    this_player_turn = '0';
    int k=1;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            output[k] = game_data[i][j]->sign;
            k++;
        }
    }
    output[k] = '\0';
    sendStringToPipe(potoki, output);
}

gboolean update_data(gpointer data)
{
    gchar input[(size*size)+2];
    int input_size = size*size+2;

    if(getStringFromPipe(potoki, input, input_size))
    {
        int i=0;
        int j=0;

        this_player_turn = input[0];

        for(int k=1; k<=size*size; k++)
        {
            if(j==size)
            {
                j=0;
                i++;
                printf("\n");
            }

            game_data[i][j]->sign = input[k];
            printf("%c", game_data[i][j]->sign);
            j++;
        }
        board_update();
    }

    return TRUE;
}


gboolean win_loop(gpointer data)
{
    bool first = check_for_win('A');
    bool second = check_for_win('B');

    if(first==true && second==true)
    {
        pokazBlad("Remis");
        kill_process();
    } else if(first == true)
    {
        pokazBlad("Wygrywa gracz A");
        kill_process();
    } else if(second == true)
    {
        pokazBlad("Wygrywa gracz B");
        kill_process();
    }

    return TRUE;
}

bool check_for_win(char player_indicator)
{
    int vertical_counter = 0;
    int horizontal_counter = 0;
    int left_diagonal = 0;
    int right_diagonal = 0;

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(game_data[j][i]->sign == player_indicator)
                vertical_counter++;

            if(game_data[i][j]->sign == player_indicator)
                horizontal_counter++;
        }

        if(horizontal_counter == size || vertical_counter == size)
        {
            return true;
//            char *message;
//            message = g_strdup_printf("Wygrywa gracz %c!", player_indicator);
//            pokazBlad(message);
//            gtk_main_quit();
        }

        vertical_counter = 0;
        horizontal_counter = 0;
    }

    for(int i=0; i<size; i++)
    {
        if(game_data[i][i]->sign == player_indicator)
            left_diagonal++;

        if(game_data[size-i-1][i]->sign == player_indicator)
            right_diagonal++;

    }

    if(left_diagonal == size || right_diagonal == size)
    {
        return true;
//        char *message;
//        message = g_strdup_printf("Wygrywa gracz %c!", player_indicator);
//        pokazBlad(message);
//        gtk_main_quit();
    }

    return false;
}

void set_on_bottom(int column, coordinates *data)
{
    game_data[size-1][column]->sign = player_indicator;
    char *str = g_strdup_printf("%c", player_indicator);
    gtk_button_set_label(GTK_BUTTON(buttons[size-1][column]), str);
    //pass_game_data();
    free(str);
}

void set_on_top(int column, coordinates *data)
{
    int i=0;
    while(game_data[i+1][column]->sign == 'E')
        i++;


    game_data[i][column]->sign = player_indicator;
    char *str = g_strdup_printf("%c", player_indicator);
    gtk_button_set_label(GTK_BUTTON(buttons[i][column]), str);
    free(str);
}


/*
 * if any segfaults are to happen
 * it's gonna be somwhere 'round here
 * since I'm not sure whether the complex_move() works for full column
 */
void complex_move(int column, coordinates *data)
{
//remove the lowest sign, no need to check since the function conditions
    char buff = game_data[size-1][column]->sign;

    gchar *str;
//move the whole column;
    for(int i=size-1; i>0; i--)
    {
        str = g_strdup_printf("%c", game_data[i - 1][column]->sign);
        gtk_button_set_label(GTK_BUTTON(buttons[i][column]), str);
        game_data[i][column]->sign = game_data[i - 1][column]->sign;
    }

//put the removed sign on top of moved column
    if(game_data[size-1][column]->sign == 'E')
    {
        game_data[size-1][column]->sign = buff;
        //game_data[top][column]->sign = buff;
        str = g_strdup_printf("%c", buff);
        gtk_button_set_label(GTK_BUTTON(buttons[size-1][column]), str);

        //put your own sign on top of the column
        game_data[size-2][column]->sign = player_indicator;
        str = g_strdup_printf("%c", player_indicator);
        gtk_button_set_label(GTK_BUTTON(buttons[size-2][column]), str);

    } else
    {
        //enters only if there is just one sign in column
        int top=0;
        while(game_data[top+1][column]->sign == 'E')
            top++;

        game_data[top][column]->sign = buff;
        str = g_strdup_printf("%c", buff);
        gtk_button_set_label(GTK_BUTTON(buttons[top][column]), str);

        //put your own sign on top of the column
        game_data[top-1][column]->sign = player_indicator;
        str = g_strdup_printf("%c", player_indicator);
        gtk_button_set_label(GTK_BUTTON(buttons[top-1][column]), str);
    }



    free(str);
}

void click_parser(GtkWidget *widget, gpointer user_data)
{
    coordinates *data = user_data;

    gint x_pos = data->x;
    gint y_pos = data->y;

    //gchar *str = g_strdup_printf("%d %d", x_pos, y_pos);

    //GtkWidget *clicked = data->clicked_button;

    if(this_player_turn=='0')
    {
        pokazBlad("Teraz trwa tura drugiego gracza");
        return;
    }

    if(game_data[size-1][x_pos]->sign == 'E')
    {
        set_on_bottom(x_pos, data);
        //check_for_win(data);

    } else if(game_data[y_pos][x_pos]->sign == 'E')
    {
        set_on_top(x_pos, data);
        //check_for_win(data);
    } else
    {
        complex_move(x_pos, data);
        //check_for_win(data);
    }

    send_data();

/*
    if(data->sign == ' ')
    {
        gtk_button_set_label(GTK_BUTTON(clicked), "X");
        game_data[y_pos][x_pos]->sign = 'X';
        check_for_win(data);
    }
*/
}
