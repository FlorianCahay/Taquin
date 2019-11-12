#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define NB_COL 4
#define NB_LIG 4

typedef struct carre {
	int ligne;
	int colonne;
} Carre;
typedef struct plateau {
	Carre bloc[NB_LIG][NB_COL];
} Plateau;

void init_board(Plateau *board);
int isFinish(Plateau *board);
int get_random_int(int a, int b);

#endif