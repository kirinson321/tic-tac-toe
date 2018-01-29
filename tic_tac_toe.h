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
    GtkWidget *clicked_button;

} coordinates;

typedef struct
{
    int x;
    int y;
    char sign;

} field;

extern GtkWidget *grid;
extern GtkWidget *buttons[4][4];
extern int size;
extern field *game_data[4][4];
extern char player_indicator;


void create_grid();
int check_for_win(coordinates *data);
void set_on_bottom(int , coordinates *data);
void set_on_top(int column, coordinates *data);
void complex_move(int column, coordinates *data);
int click_parser(GtkWidget *widget, gpointer click_data);
void pokazBlad(char *komunikat);

#endif //TIC_TAC_TOE_TIC_TAC_TOE_H
