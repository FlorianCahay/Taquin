#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

void select_case(int x_click, int y_click, int *x_case, int *y_case, int bloc_size);
int check_move(Plateau *board, int x_case, int y_case);
void swap_case(Plateau *board, int x_case, int y_case, int direction);
int same_carre(Carre one, Carre two);
void shuffle_board(Plateau *board);

#endif