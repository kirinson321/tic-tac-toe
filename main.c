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
PipesPtr potoki;

void kill_process()
{
    closePipes(potoki);
    gtk_main_quit();
}



int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 60);

    if((potoki = initPipes(argc, argv)) == NULL)
        return 1;

    if(argc<3 && *argv[1] == 'A')
    {
        pokazBlad("Za mało argumentów - argument pierwszy to symbol gracza, drugi (okreslany TYLKO przez gracza A) to rozmiar planszy");
        return 1;
    } else if(argc<2)
    {
        pokazBlad("Za mało argumentów - podaj symbol 'B' ");
        return 1;
    } else
    {
        if(argc==3 && argv[1][0]=='A')
        {
            size = atoi(argv[2]);
        } else if(argc==3 && argv[1][0] != 'A')
        {
            pokazBlad("Tylko gracz A moze okreslic rozmiar planszy");
            return 1;
        }

        player_indicator = *argv[1];

        if(player_indicator=='A')
        {
            char *str;
            str = g_strdup_printf("%d", size);
            sendStringToPipe(potoki, str);
        } else if(player_indicator=='B')
        {
            char *str;
            str = g_strdup_printf("%s", "5");
            if(getStringFromPipe(potoki, str, sizeof(int)))
            {
                size = atoi(str);
            } else
            {
                pokazBlad("Najpierw swoja kopie gry powinien uruchomic gracz A");
                return 1;
            }

        }


        gchar title[50];
        sprintf(title, "Kółko i krzyżyk - gracz %c", player_indicator);
        gtk_window_set_title(GTK_WINDOW(window), title);

        grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(window), grid);
        g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(kill_process), NULL);

        create_grid();

        // testing new functionalities here

        //debugger will be used to display debug messages;
        //should write a new function to change its message when a button is pressed
//    char *str;
//    str = g_strdup_printf("%c", player_indicator);
//    //str = player_indicator;
//GtkWidget *debugger = gtk_label_new(str);
//    gtk_grid_attach(GTK_GRID(grid), debugger, 1, 10, 1, 1);
//    //pokazBlad("test");
        //

        //GtkWidget *dater = gtk_button_new_with_label("send data");
        //g_signal_connect(G_OBJECT(dater), "clicked", G_CALLBACK(send_data), NULL);
        //gtk_grid_attach(GTK_GRID(grid), dater, 1, 10, 1, 1);
        g_timeout_add(100, update_data, NULL);
        g_timeout_add(500, win_loop, NULL);

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