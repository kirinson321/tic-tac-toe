/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/

#ifndef TIC_TAC_TOE_TIC_TAC_TOE_H
#define TIC_TAC_TOE_TIC_TAC_TOE_H

#include <gtk/gtk.h>

typedef struct
{
    int x;
    int y;
    char sign;
    GtkButton *clicked_button;

    //GtkWidget *test_label;

} coordinates;

typedef struct
{
    int x;
    int y;
    char sign;

} field;


extern GtkWidget *grid;
extern field game_data[4][4];
extern int size;

void create_grid();
int check_for_win(coordinates *data);
int click_parser(GtkWidget *widget, gpointer click_data);

/*
 * first, an A or B function should be called
 * then, this function should wait for data with button position;
 */


#endif //TIC_TAC_TOE_TIC_TAC_TOE_H
