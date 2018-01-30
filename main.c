/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/

#include <gtk/gtk.h>
#include <stdlib.h>
#include "tic_tac_toe.h"
GtkWidget *window;
GtkWidget *grid;
int size;
char player_indicator;

//
void pokazBlad(char *komunikat);

//

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Kółko i krzyżyk");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 60);

    if(argc<3)
    {
        pokazBlad("Za mało argumentów - argument pierwszy to symbol gracza, drugi to rozmiar planszy");
        return 1;
    } else
    {
        player_indicator = *argv[1];
        size = atoi(argv[2]);


        grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(window), grid);

        create_grid();

        // testing new functionalities here

        //debugger will be used to display debug messages;
        //should write a new function to change its message when a button is pressed
//    char *str;
//    str = g_strdup_printf("%c", player_indicator);
//    //str = player_indicator;
//    GtkWidget *debugger = gtk_label_new(str);
//    gtk_grid_attach(GTK_GRID(grid), debugger, 1, 10, 1, 1);
//    //pokazBlad("test");
        //

        gtk_widget_show_all(window);

        gtk_main();

        return 0;
    }
}


void pokazBlad(char *komunikat)
{
    GtkWidget *dialog;
    dialog=gtk_message_dialog_new (GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"%s",komunikat);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}