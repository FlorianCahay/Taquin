#include <MLV/MLV_all.h>
#include "../include/main.h"

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

/* Affiche le message de victoire. */
void display_victory(int elapsed_time) {
	MLV_draw_text(10, 10, "YOU WIN !", MLV_COLOR_RED);
	MLV_draw_text(MLV_get_window_width()/3, 530, "Elapsed time: %.3f s", MLV_COLOR_RED, elapsed_time/1000.0);
	MLV_actualise_window();
}

/* Affiche le message de défaite. */
void display_defeat(int elapsed_time) {
	MLV_draw_text(10, 10, "YOU LOSE !", MLV_COLOR_RED);
	MLV_draw_text(MLV_get_window_width()/3, 530, "Elapsed time: %.3f s", MLV_COLOR_RED, elapsed_time/1000.0);
	MLV_actualise_window();
}