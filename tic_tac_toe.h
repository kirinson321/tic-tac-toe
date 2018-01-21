/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/

#ifndef TIC_TAC_TOE_TIC_TAC_TOE_H
#define TIC_TAC_TOE_TIC_TAC_TOE_H

extern GtkWidget *grid;

typedef struct field
{
    int pos_x;
    int pos_y;
    char symbol;

} Field;




void create_grid(int size);


#endif //TIC_TAC_TOE_TIC_TAC_TOE_H
