/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/

#ifndef TIC_TAC_TOE_TIC_TAC_TOE_H
#define TIC_TAC_TOE_TIC_TAC_TOE_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <stddef.h>

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
extern GtkWidget *buttons[11][11];
extern int size;
extern field *game_data[11][11];
extern char player_indicator;
extern char this_player_turn;

void create_grid();
//gboolean check_for_win(gpointer data);
void set_on_bottom(int , coordinates *data);
void set_on_top(int column, coordinates *data);
void complex_move(int column, coordinates *data);
void click_parser(GtkWidget *widget, gpointer click_data);
void pokazBlad(char *komunikat);
void board_update();
void kill_process();
gboolean win_loop(gpointer data);
bool check_for_win(char player_indicator);

//communication
typedef struct pipes *PipesPtr;
void send_data();
gboolean update_data(gpointer data);

PipesPtr initPipes(int argc, char *argv[]);
void     sendStringToPipe(PipesPtr channel, const char *data);
bool     getStringFromPipe(PipesPtr channel, char *buffer, size_t size);
void     closePipes(PipesPtr channel);

extern PipesPtr potoki;

#endif //TIC_TAC_TOE_TIC_TAC_TOE_H
