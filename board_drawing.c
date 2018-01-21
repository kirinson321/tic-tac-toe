/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/
#include <gtk/gtk.h>
#include <stdlib.h>
#include "tic_tac_toe.h"


void create_grid(int size)
{
    GtkWidget *label;
    gchar *str;
    GtkWidget *buttons[size][size];

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
            buttons[i][j] = gtk_button_new_with_label(" ");
            //g_signal_connect();
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], j+1, i+1, 1, 1);
        }
    }

    free(str);
    return;
}