#include <MLV/MLV_all.h>
#include "../include/main.h"
#include "../include/events.h"
#include "../include/view.h"

/*
AJouter nombre de coups 
Proposer plusieurs images
Vérifier si partie finie - OK
*/


int main(int argc, char const *argv[])
{
	MLV_Image *image;
	MLV_Event event = MLV_NONE;
	MLV_Button_state state;
	MLV_Keyboard_button sym;
	int win_width = 512, win_height = 560, x_click = 0, y_click = 0;
	int img_width, img_height, x_select, y_select;

	MLV_create_window("Taquin", "Taquin", win_width, win_height);
	image = MLV_load_image("media/arbre.jpg");
	MLV_get_image_size(image, &img_width, &img_height);
	int bloc_size = img_width / NB_COL;

	Plateau *board = NULL;
	board = malloc(sizeof(Plateau));
	if (board == NULL) {
		fprintf(stderr, "Erreur lors l'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	init_board(board);
	shuffle_board(board);

	do {
		event = MLV_get_event(&sym, NULL, NULL, NULL, NULL, &x_click, &y_click, NULL, &state);
		if (event == MLV_MOUSE_BUTTON) {
			if (state == MLV_PRESSED) {
				select_case(x_click, y_click, &x_select, &y_select, bloc_size);
				int result = check_move(board, x_select, y_select);
				if (result > 0) {
					swap_case(board, x_select, y_select, result);
				}
			}
		}
		if (event == MLV_KEY) {
			if (sym == MLV_KEYBOARD_ESCAPE) {
				break;
			}
		}

		display_image(image, bloc_size, board);
	} while (!isFinish(board));
	int elapsed_time = MLV_get_time();
	display_victory(elapsed_time);

	MLV_wait_seconds(3);
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
			if ((i == NB_COL-1) && (j == NB_LIG-1)) {
				Carre case_empty = { -1, -1 };
				(board->bloc)[i][j] = case_empty;
			} else {
				Carre case_game = { i, j };
				(board->bloc)[i][j] = case_game;
			}
		}
	}
}
/* Vérifie si le taquin a été résolu. */
int isFinish(Plateau *board) {
	Carre case_empty = { -1, -1 };
	int i, j;
	for (i = 0; i < NB_LIG; i++) {
		for (j = 0; j < NB_COL; j++) {
			Carre case_select = { i, j };
			if (!same_carre((board->bloc)[i][j], case_select)) {
				if (!same_carre((board->bloc)[i][j], case_empty)) {
					return 0;
				}
			}
		}
	}
	return 1;
}
/* Retourne un entier aléatoire inclus dans [a, b[ */
int get_random_int(int a, int b) {
	return MLV_get_random_integer(a, b);
}
