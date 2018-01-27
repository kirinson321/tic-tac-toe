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
    GtkWidget *function_button;


    //

    GtkWidget *position;
    position = gtk_label_new("test");
    gtk_grid_attach(GTK_GRID(grid), position, 1, 7, 2, 1);

    //

//    coordinates *test = (coordinates*)malloc(sizeof(coordinates));

//    coordinates *test[4] = (coordinates*)malloc(sizeof(coordinates)*4);

    coordinates **array = malloc(size * sizeof(coordinates));

    //field field_grid[size][size];

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

            array[i] = malloc(sizeof(coordinates));

            //field_grid[i][j].pos_x = j;
            //field_grid[i][j].pos_y = i;

            array[i]->x = j;
            array[i]->y = i;
            array[i]->test_label = position;

            g_signal_connect(G_OBJECT(buttons[i][j]), "clicked", G_CALLBACK(click_parser), array[i]);
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], j+1, i+1, 1, 1);
        }
    }

    free(str);

    function_button = gtk_button_new_with_label("A");
    gtk_grid_attach(GTK_GRID(grid), function_button, 1, size+1, 2, 1);

    function_button = gtk_button_new_with_label("B");
    gtk_grid_attach(GTK_GRID(grid), function_button, 3, size+1, 2, 1);


    return;
}