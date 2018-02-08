/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/
#include <gtk/gtk.h>
#include <stdlib.h>
#include "tic_tac_toe.h"

field *game_data[11][11];
GtkWidget *buttons[11][11];


void create_grid()
{
    GtkWidget *label;
    gchar *str;
    coordinates **array = malloc(size * sizeof(coordinates));

    for(int i=0; i<size; i++)
    {
        str = g_strdup_printf("%d", i+1);
        label = gtk_label_new(str);
        gtk_grid_attach(GTK_GRID(grid), label, i+1, 0, 1, 1);
    }

    for(int i=0; i<size; i++)
    {
        str = g_strdup_printf("%d", i+1);
        label = gtk_label_new(str);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i+1, 1, 1);

        for(int j=0; j<size; j++)
        {
            game_data[i][j]= malloc(sizeof(game_data));
            game_data[i][j]->sign = ' ';

            buttons[i][j] = gtk_button_new_with_label(" ");

            array[i] = malloc(sizeof(coordinates));

            array[i]->x = j;
            array[i]->y = i;
            array[i]->sign =(' ');
            array[i]->clicked_button = buttons[i][j];

            g_signal_connect(G_OBJECT(buttons[i][j]), "clicked", G_CALLBACK(click_parser), array[i]);
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], j+1, i+1, 1, 1);
        }
    }

    free(str);
}


void board_update()
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(game_data[i][j]->sign == 'X')
                gtk_button_set_label(GTK_BUTTON(buttons[i][j]), "X");
            else if(game_data[i][j]->sign =='O')
                gtk_button_set_label(GTK_BUTTON(buttons[i][j]), "O");
            else
                gtk_button_set_label(GTK_BUTTON(buttons[i][j]), " ");
        }

    }
}