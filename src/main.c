#include <MLV/MLV_all.h>
#include "../include/main.h"

void init_board(Plateau *board);
void display_image(MLV_Image *image, int bloc_size, Plateau *board);
void select_case(int x_click, int y_click, int *x_case, int *y_case, int bloc_size);
int check_move(Plateau *board, int x_case, int y_case);
void move_case(Plateau *board, int x_case, int y_case, int direction);

int main(int argc, char const *argv[])
{
	MLV_Image *image;
	MLV_Event event = MLV_NONE;
	MLV_Button_state state;
	int win_width = 512, win_height = 512;
	int img_width, img_height;
	int x_click = 0, y_click = 0;
	int x_select, y_select;
	int quit = 0;

	MLV_create_window("Taquin", "", win_width, win_height);
	image = MLV_load_image("arbre.jpg");
	MLV_get_image_size(image, &img_width, &img_height);
	int bloc_size = img_width / NB_COL;

	Plateau *board = NULL;
	board = malloc(sizeof(Plateau));
	if (board == NULL) {
		fprintf(stderr, "Erreur lors l'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	init_board(board);

	do {
		event = MLV_get_event(NULL, NULL, NULL, NULL, NULL, &x_click, &y_click, NULL, &state);
		
		display_image(image, bloc_size, board);

		if (event == MLV_MOUSE_BUTTON) {
			if (state == MLV_PRESSED) {
				select_case(x_click, y_click, &x_select, &y_select, bloc_size);
				printf("click [%d, %d], case [%d, %d]\n", x_click, y_click, x_select, y_select);
				int result = check_move(board, x_select, y_select);
				printf("case voisine: %d\n", result);
				if (result > 0) {
					move_case(board, x_select, y_select, result);
				}
			}
		}
		
	} while (!quit);
	free(board);
	MLV_free_image(image);
	MLV_free_window();
	return 0;
}
/* Initialise le plateau du jeu avant le mélange. */
void init_board(Plateau *board) {
	int i, j;
	for (i = 0; i < NB_LIG; i++) {
		for (j = 0; j < NB_COL; j++) {

			/* MODIF POUR TEST */

			if ((i == NB_COL-2) && (j == NB_LIG-2)) {
				Carre case_empty = { -1, -1 };
				(board->bloc)[i][j] = case_empty;
			} else {
				Carre case_game = { i, j };
				(board->bloc)[i][j] = case_game;
			}
		}
	}
}/*
void free_board(Plateau *board) {
	int i, j;
	for (i = 0; i < NB_COL; i++) {
		for (j = 0; j < NB_LIG; j++) {
			free(*(board->bloc)[i][j]);
		}
	}
}*/
/* Affiche l'image dans la fenêtre du jeu. */
void display_image(MLV_Image *image, int bloc_size, Plateau *board) {
	int i, j;
	for (i = 0; i < NB_LIG; i++) {
		for (j = 0; j < NB_COL; j++) {
			if ( (((board->bloc)[i][j]).ligne == -1) && (((board->bloc)[i][j]).colonne == -1)) {
				MLV_draw_filled_rectangle(i*(bloc_size), j*(bloc_size), bloc_size, bloc_size, MLV_COLOR_BLACK);
			} else {
				MLV_draw_partial_image(image, (((board->bloc)[i][j]).ligne)*bloc_size, (((board->bloc)[i][j]).colonne)*bloc_size, bloc_size, bloc_size, i*(bloc_size), j*(bloc_size));
			}
		}
	}
	MLV_actualise_window();
}
/* Sélectionne la case qui sur laquelle l'utilisateur a cliqué. */
void select_case(int x_click, int y_click, int *x_case, int *y_case, int bloc_size) {
	int i, j;
	for (i = 0; i < NB_LIG*bloc_size; i += bloc_size) {
		if ((x_click <= i+bloc_size) && (x_click >= i)) {
			*x_case = i/bloc_size;
		}
	}
	for (j = 0; j < NB_COL*bloc_size; j += bloc_size) {
		if ((y_click <= j+bloc_size) && (y_click >= j)) {
			*y_case = j/bloc_size;
		}
	}
}
/* 	Vérifie si la case vide touche horizontalement ou verticalement la case ciblée.
	Si c'est le cas, retourne un numéro indiquant la direction où se trouve la case vide:
		1 => gauche, 2 => haut, 3 => droite, 4 => bas
*/
int check_move(Plateau *board, int x_case, int y_case) {
	int i;
	int pos = 1;
	for (i = -1; i < 2; i += 2) {
		printf("x=%d y=%d\n", x_case+i, y_case);
		printf("x=%d y=%d\n", x_case, y_case+i);
		/* Horizontal */
		if ( ((x_case+i) >= 0) && ((x_case+i) < NB_LIG) ) {
			if ((((board->bloc)[x_case+i][y_case]).ligne == -1) && ((board->bloc)[x_case+i][y_case]).colonne == -1) {
				return pos+1;
			}
		}
		/* Vertical */
		if ( ((y_case+i) >= 0) && ((y_case+i) < NB_COL) ) {
			if ((((board->bloc)[x_case][y_case+i]).ligne == -1) && ((board->bloc)[x_case][y_case+i]).colonne == -1) {
				return pos;
			}
		}
		pos += 2;
	}
	return 0;
}
/* Echange de place la case sélectionnée et la case vide. */
void move_case(Plateau *board, int x_case, int y_case, int direction) {
	Carre case_empty = { -1, -1 };
	switch (direction) {
		case 1:
			(board->bloc)[x_case][y_case-1] = (board->bloc)[x_case][y_case];
			(board->bloc)[x_case][y_case] = case_empty;
			break;
		case 2:
			(board->bloc)[x_case-1][y_case] = (board->bloc)[x_case][y_case];
			(board->bloc)[x_case][y_case] = case_empty;
			break;
		case 3:
			(board->bloc)[x_case][y_case+1] = (board->bloc)[x_case][y_case];
			(board->bloc)[x_case][y_case] = case_empty;
			break;
		case 4:
			(board->bloc)[x_case+1][y_case] = (board->bloc)[x_case][y_case];
			(board->bloc)[x_case][y_case] = case_empty;
			break;
		default:
			break;
	}
}