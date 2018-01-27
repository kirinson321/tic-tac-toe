/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/

#ifndef TIC_TAC_TOE_TIC_TAC_TOE_H
#define TIC_TAC_TOE_TIC_TAC_TOE_H

#include <gtk/gtk.h>

typedef struct
{
    int pos_x;
    int pos_y;
    char symbol;

} field;


typedef struct
{
    int x;
    int y;
    GtkWidget *test_label;

} coordinates;

extern GtkWidget *grid;

extern field *field_grid[];

void create_grid(int size);
int click_parser(GtkWidget *widget, gpointer click_data);

/*
 * first, an A or B function should be called
 * then, this function should wait for data with button position;
 */


#endif //TIC_TAC_TOE_TIC_TAC_TOE_H
