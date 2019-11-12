#include <stdio.h>
#include "../include/main.h"

/* Sélectionne la case qui sur laquelle l'utilisateur a cliqué. */
void select_case(int x_click, int y_click, int *x_case, int *y_case, int bloc_size) {
	*x_case = x_click/bloc_size;
	*y_case = y_click/bloc_size;
}
/* Vérifie si deux Carres sont égaux. */
int same_carre(Carre one, Carre two) {
	if ( (one.ligne == two.ligne) && (one.colonne == two.colonne) ) {
		return 1;
	}
	return 0;
}
/* 	Vérifie si la case vide touche horizontalement ou verticalement la case ciblée.
	Si c'est le cas, retourne un numéro indiquant la direction où se trouve la case vide:
		1 => gauche, 2 => haut, 3 => droite, 4 => bas
*/
int check_move(Plateau *board, int x_case, int y_case) {
	Carre case_empty = { -1, -1 };
	int i;
	int pos = 1;
	for (i = -1; i < 2; i += 2) {
		/* Horizontal */
		if ( ((x_case+i) >= 0) && ((x_case+i) < NB_LIG) ) {
			if (same_carre((board->bloc)[x_case+i][y_case], case_empty)) {
				return pos+1;
			}
		}
		/* Vertical */
		if ( ((y_case+i) >= 0) && ((y_case+i) < NB_COL) ) {
			if (same_carre((board->bloc)[x_case][y_case+i], case_empty)) {
				return pos;
			}
		}
		pos += 2;
	}
	return 0;
}
/* Echange de place la case sélectionnée et la case vide.
	1 => gauche, 2 => haut, 3 => droite, 4 => bas
*/
void swap_case(Plateau *board, int x_case, int y_case, int direction) {
	Carre temp;
	switch (direction) {
		case 1:
			temp = (board->bloc)[x_case][y_case-1];
			(board->bloc)[x_case][y_case-1] = (board->bloc)[x_case][y_case];
			break;
		case 2:
			temp = (board->bloc)[x_case-1][y_case];
			(board->bloc)[x_case-1][y_case] = (board->bloc)[x_case][y_case];
			break;
		case 3:
			temp = (board->bloc)[x_case][y_case+1];
			(board->bloc)[x_case][y_case+1] = (board->bloc)[x_case][y_case];
			break;
		case 4:
			temp = (board->bloc)[x_case+1][y_case];
			(board->bloc)[x_case+1][y_case] = (board->bloc)[x_case][y_case];
			break;
		default:
			printf("Direction invalide.\n");
			break;
	}
	(board->bloc)[x_case][y_case] = temp;
}
/* Mélange le plateau. */
void shuffle_board(Plateau *board) {
	int x_empty = 3, y_empty = 3;
	int i;
	for (i = 0; i < 120; i++) {
		int random = get_random_int(1, 5);
		switch (random) {
			case 1:
				if (y_empty-1 >= 0) {
					swap_case(board, x_empty, y_empty, random);
					y_empty--;
				} else {
					i--;
				}
				break;
			case 2:
				if (x_empty-1 >= 0) {
					swap_case(board, x_empty, y_empty, random);
					x_empty--;
				} else {
					i--;
				}
				break;
			case 3:
				if (y_empty+1 < NB_COL) {
					swap_case(board, x_empty, y_empty, random);
					y_empty++;
				} else {
					i--;
				}
				break;
			case 4:
				if (x_empty+1 < NB_LIG) {
					swap_case(board, x_empty, y_empty, random);
					x_empty++;
				} else {
					i--;
				}
				break;
			default:
				printf("Nombre aléatoire invalide.\n");
				break;
		}
	}
}