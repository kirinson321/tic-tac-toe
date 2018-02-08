/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/

#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>
#include "tic_tac_toe.h"
GtkWidget *window;
GtkWidget *grid;
int size;
int segfault_protection[11];
char player_indicator;

PipesPtr potoki;

void kill_process()
{
    closePipes(potoki);
    unlink("AtoB");
    unlink("BtoA");
    gtk_main_quit();
}



int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 60);
    char player_sign;

    if((potoki = initPipes(argc, argv)) == NULL)
        return 1;

    if(argc<3 && *argv[1] == 'A')
    {
        pokazBlad("Za mało argumentów - argument pierwszy to symbol gracza, drugi (okreslany TYLKO przez gracza A) to rozmiar planszy");
        kill_process();
        return 1;
    } else if(argc<2)
    {
        pokazBlad("Za mało argumentów - podaj symbol 'B' ");
        kill_process();
        return 1;
    } else
    {
        if(argc==3 && argv[1][0]=='A')
        {
            size = atoi(argv[2]);
            this_player_turn='0';
            if(size>9 || size<3)
            {
                pokazBlad("Rozmiar powinien miescic sie w przedziale od 3 do 9 wlacznie");
                kill_process();
                return 1;
            }
        } else if(argc==3 && argv[1][0] != 'A')
        {
            pokazBlad("Tylko gracz A moze okreslic rozmiar planszy");
            //kill_process();
            return 1;
        }

        player_sign= *argv[1];
        if(player_sign == 'A')
        {
            player_indicator = 'X';
        } else
            player_indicator = 'O';


        if(player_sign=='A')
        {
            char *str;
            str = g_strdup_printf("%d", size);
            sendStringToPipe(potoki, str);
        } else if(player_sign=='B')
        {
            char *str;
            str = g_strdup_printf("%s", "5");
            if(getStringFromPipe(potoki, str, sizeof(int)))
            {
                size = atoi(str);
            } else
            {
                pokazBlad("Najpierw swoja kopie gry powinien uruchomic gracz A");
                kill_process();
                return 1;
            }

        }

        for(int i=0; i<size; i++)
        {
            segfault_protection[i]=0;
        }

        gchar title[50];
        sprintf(title, "Kółko i krzyżyk - gracz %c", player_indicator);
        gtk_window_set_title(GTK_WINDOW(window), title);

        grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(window), grid);
        g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(kill_process), NULL);

        create_grid();

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