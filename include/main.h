#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define NB_COL 4
#define NB_LIG 4

struct carre {
	int ligne;
	int colonne;
};
struct plateau {
	Carre bloc[NB_COL][NB_LIG];
};

#endif