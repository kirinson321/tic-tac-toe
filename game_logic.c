/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/

//#include <gtk/gtk.h>
#include "tic_tac_toe.h"
//#include <stdio.h>

int click_parser(GtkWidget *widget, gpointer user_data)
{
    //user_data = (coordinates)user_data;
    //int number = user_data->x;

    coordinates *test_struct = (coordinates*)g_malloc(sizeof(coordinates));

    test_struct = user_data;
    gint number;
    number = test_struct->x;
    gchar *str;
    str = g_strdup_printf("%d", number);

    GtkWidget *lab = test_struct->test_label;
    //gtk_button_set_label(GTK_BUTTON(click_data), );
    gtk_label_set_text(GTK_LABEL(lab), str);
}
