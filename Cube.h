#ifndef CUBE_H
#define CUBE_H

#include <cstdint>

enum edge { uf, df, ub, db, fl, fr, br, bl, ur, dr, dl, ul };
enum corner { ufl, dfr, dbl, ubr, ufr, dfl, dbr, ubl };

class Cube {
	public:
		/*
		* Cube model:
		*   - edge permutation (0 - 12)
		*   - edge orientation (0 = correct, 1 = flipped)
		*   - corner permutation (0 - 8)
		*   - corner orientation (0 = correct, 1 = twisted cw, 2 = twisted ccw)
		*/
		edge ep[12] = { uf, df, ub, db, fl, fr, br, bl, ur, dr, dl, ul };
		char eo[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		corner cp[8] = { ufl, dfr, dbl, ubr, ufr, dfl, dbr, ubl };
		char co[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		/*
		* index: 0 | 1 | 2  | 3 | 4 | 5  | 6 | 7 | 8  | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17
		* move:  F | F'| F2 | B | B'| B2 | U | U'| U2 | D | D' | D2 | R  | R' | R2 | L  | L' | L2
		*/
		bool moves[18] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};	
		Cube();
		void	rotate(uint8_t move);
		void	setMoves(uint8_t group);
		void	UCW();
		void	UCCW();
		void	U2();
		void	DCW();
		void	DCCW();
		void	D2();
		void	FCW();
		void	FCCW();
		void	F2();
		void	BCW();
		void	BCCW();
		void	B2();
		void	RCW();
		void	RCCW();
		void	R2();
		void	LCW();
		void	LCCW();
		void	L2();
};

#endif