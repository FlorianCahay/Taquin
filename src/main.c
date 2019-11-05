#include <MLV/MLV_all.h>
#include "../include/main.h"

int main(int argc, char const *argv[])
{
	MLV_Image *image;
	int win_width = 600, win_height = 600;
	int img_width, img_height;

	MLV_create_window("Taquin", "", win_width, win_height);
	image = MLV_load_image("arbre.jpg");
	MLV_get_image_size(image, &img_width, &img_height);

	int bloc_size = img_width / NB_COL;

	int i, j;
	struct plateau board;
	for (i = 0; i < NB_COL; i++) {
		for (j = 0; j < NB_LIG; j++) {
			struct carre case_game = { i, j };
			board.bloc[i][j] = case_game;
		}
	}
	MLV_draw_partial_image(image, 1*bloc_size, 2*bloc_size, bloc_size, bloc_size, 2*(bloc_size+5), 0*(bloc_size+5));
	/*
	MLV_draw_image(image, (win_width-img_width)/2, (win_height-img_height)/2);*/

	MLV_actualise_window();

	MLV_wait_seconds(5);

	MLV_free_image(image);
	MLV_free_window();
	return 0;
}