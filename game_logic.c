/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/
#include <stdlib.h>
#include "tic_tac_toe.h"

int check_for_win(coordinates *data)
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
            gtk_button_set_label(GTK_BUTTON(data->clicked_button), "DUPA");
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
        gtk_button_set_label(GTK_BUTTON(data->clicked_button), "DUPA");
    }

}

void set_on_bottom(int column, coordinates *data)
{
    game_data[size-1][column]->sign = player_indicator;
    char *str = g_strdup_printf("%c", player_indicator);
    gtk_button_set_label(GTK_BUTTON(buttons[size-1][column]), str);
    free(str);
}

void set_on_top(int column, coordinates *data)
{
    int i=0;
    while(game_data[i+1][column]->sign == ' ')
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
    if(game_data[size-1][column]->sign == ' ')
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
        while(game_data[top+1][column]->sign == ' ')
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

int click_parser(GtkWidget *widget, gpointer user_data)
{
    coordinates *data = user_data;

    gint x_pos = data->x;
    gint y_pos = data->y;

    //gchar *str = g_strdup_printf("%d %d", x_pos, y_pos);

    GtkWidget *clicked = data->clicked_button;


    if(game_data[size-1][x_pos]->sign == ' ')
    {
        set_on_bottom(x_pos, data);
        check_for_win(data);

    } else if(game_data[y_pos][x_pos]->sign == ' ')
    {
        set_on_top(x_pos, data);
        check_for_win(data);
    } else
    {
        complex_move(x_pos, data);
        check_for_win(data);
    }

/*
    if(data->sign == ' ')
    {
        gtk_button_set_label(GTK_BUTTON(clicked), "X");
        game_data[y_pos][x_pos]->sign = 'X';
        check_for_win(data);
    }
*/
}
