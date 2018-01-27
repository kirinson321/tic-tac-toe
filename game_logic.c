/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/
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
            if(game_data[j][i].sign == 'X')
                vertical_counter++;

            if(game_data[i][j].sign == 'X')
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
        if(game_data[i][i].sign == 'X')
            left_diagonal++;

        if(game_data[size-i-1][i].sign == 'X')
            right_diagonal++;

    }

    if(left_diagonal == size || right_diagonal == size)
    {
        gtk_button_set_label(GTK_BUTTON(data->clicked_button), "DUPA");
    }

}



int click_parser(GtkWidget *widget, gpointer user_data)
{
    coordinates *data = user_data;

    gint x_pos = data->x;
    gint y_pos = data->y;

    //gchar *str = g_strdup_printf("%d %d", x_pos, y_pos);

    GtkButton *clicked = data->clicked_button;
    //gtk_button_set_label(GTK_BUTTON(clicked), "X");


    if(data->sign == ' ')
    {
        gtk_button_set_label(GTK_BUTTON(clicked), "X");
        game_data[y_pos][x_pos].sign = 'X';
        check_for_win(data);
    }

}
