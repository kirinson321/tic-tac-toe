/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/

//#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *grid;

static struct button
{
    int pos_x;
    int pos_y;
    char symbol;

};

void create_grid(int size)
{
    GtkWidget *label;
    int var;
    gchar *str;
    GtkWidget *button;

    for(int i=0; i<size; i++)
    {
        var = i+1;
        str = g_strdup_printf("%d", var);
        label = gtk_label_new(str);
        gtk_grid_attach(GTK_GRID(grid), label, i+1, 0, 1, 1);
    }

    for(int i=0; i<size; i++)
    {
        var = i+1;
        str = g_strdup_printf("%d", var);
        label = gtk_label_new(str);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i+1, 1, 1);

        for(int j=0; j<size; j++)
        {
            button = gtk_button_new_with_label(" ");
            //g_signal_connect();
            gtk_grid_attach(GTK_GRID(grid), button, j+1, i+1, 1, 1);
        }

    }

    free(str);
}


int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Kółko i krzyżyk");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 60);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    create_grid(4);

    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}