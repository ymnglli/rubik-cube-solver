#include "Cube.h"

Cube::Cube() {}

void Cube::rotate(uint8_t move) {
	switch (move) {
	case 0:
		FCW();
		break;
	case 1:
		FCCW();
		break;
	case 2:
		F2();
		break;
	case 3:
		BCW();
		break;
	case 4:
		BCCW();
		break;
	case 5:
		B2();
		break;
	case 6:
		UCW();
		break;
	case 7:
		UCCW();
		break;
	case 8:
		U2();
		break;
	case 9:
		DCW();
		break;
	case 10:
		DCCW();
		break;
	case 11:
		D2();
		break;
	case 12:
		RCW();
		break;
	case 13:
		RCCW();
		break;
	case 14:
		R2();
		break;
	case 15:
		LCW();
		break;
	case 16:
		LCCW();
		break;
	case 17:
		L2();
		break;
	}
}

void Cube::setMoves(uint8_t group) {
	switch (group) {
	case 1:
		moves[0] = false;
		moves[1] = false;
		moves[3] = false;
		moves[4] = false;
		break;
	case 2:
		moves[0] = false;
		moves[1] = false;
		moves[3] = false;
		moves[4] = false;
		moves[12] = false;
		moves[13] = false;
		moves[15] = false;
		moves[16] = false;
		break;
	case 3:
		moves[0] = false;
		moves[1] = false;
		moves[3] = false;
		moves[4] = false;
		moves[12] = false;
		moves[13] = false;
		moves[15] = false;
		moves[16] = false;
		moves[6] = false;
		moves[7] = false;
		moves[9] = false;
		moves[10] = false;
		break;
	}
}

void Cube::UCW() {
	corner cpt = cp[ufr];
	cp[ufr] = cp[ubr];
	cp[ubr] = cp[ubl];
	cp[ubl] = cp[ufl];
	cp[ufl] = cpt;

	char cot = co[ufr];
	co[ufr] = co[ubr];
	co[ubr] = co[ubl];
	co[ubl] = co[ufl];
	co[ufl] = cot;
	
	edge ept = ep[uf];
	ep[uf] = ep[ur];
	ep[ur] = ep[ub];
	ep[ub] = ep[ul];
	ep[ul] = ept;

	char eot = eo[uf];
	eo[uf] = eo[ur];
	eo[ur] = eo[ub];
	eo[ub] = eo[ul];
	eo[ul] = eot;
}

void Cube::UCCW() {
	for (int i = 0; i < 3; i++) {
		UCW();
	}
}

void Cube::U2() {
	for (int i = 0; i < 2; i++) {
		UCW();
	}
}

void Cube::DCW() {
	corner cpt = cp[dfr];
	cp[dfr] = cp[dfl];
	cp[dfl] = cp[dbl];
	cp[dbl] = cp[dbr];
	cp[dbr] = cpt;

	char cot = co[dfr];
	co[dfr] = co[dfl];
	co[dfl] = co[dbl];
	co[dbl] = co[dbr];
	co[dbr] = cot;

	edge ept = ep[df];
	ep[df] = ep[dl];
	ep[dl] = ep[db];
	ep[db] = ep[dr];
	ep[dr] = ept;

	char eot = eo[df];
	eo[df] = eo[dl];
	eo[dl] = eo[db];
	eo[db] = eo[dr];
	eo[dr] = eot;
}

void Cube::DCCW() {
	for (int i = 0; i < 3; i++) {
		DCW();
	}
}

void Cube::D2() {
	for (int i = 0; i < 2; i++) {
		DCW();
	}
}

void Cube::FCW() {
	corner cpt = cp[ufr];
	cp[ufr] = cp[ufl];
	cp[ufl] = cp[dfl];
	cp[dfl] = cp[dfr];
	cp[dfr] = cpt;

	char cot = co[ufr];
	co[ufr] = (co[ufl] + 2) % 3;
	co[ufl] = (co[dfl] + 1) % 3;
	co[dfl] = (co[dfr] + 2) % 3;
	co[dfr] = (cot + 1) % 3;

	edge ept = ep[uf];
	ep[uf] = ep[fl];
	ep[fl] = ep[df];
	ep[df] = ep[fr];
	ep[fr] = ept;

	char eot = eo[uf];
	eo[uf] = (eo[fl] + 1) % 2;
	eo[fl] = (eo[df] + 1) % 2;
	eo[df] = (eo[fr] + 1) % 2;
	eo[fr] = (eot + 1) % 2;
}

void Cube::FCCW() {
	for (int i = 0; i < 3; i++) {
		FCW();
	}
}

void Cube::F2() {
	for (int i = 0; i < 2; i++) {
		FCW();
	}
}

void Cube::BCW() {
	corner cpt = cp[ubl];
	cp[ubl] = cp[ubr];
	cp[ubr] = cp[dbr];
	cp[dbr] = cp[dbl];
	cp[dbl] = cpt;

	char cot = co[ubl];
	co[ubl] = (co[ubr] + 2) % 3;
	co[ubr] = (co[dbr] + 1) % 3;
	co[dbr] = (co[dbl] + 2) % 3;
	co[dbl] = (cot + 1) % 3;

	edge ept = ep[ub];
	ep[ub] = ep[br];
	ep[br] = ep[db];
	ep[db] = ep[bl];
	ep[bl] = ept;

	char eot = eo[ub];
	eo[ub] = (eo[br] + 1) % 2;
	eo[br] = (eo[db] + 1) % 2;
	eo[db] = (eo[bl] + 1) % 2;
	eo[bl] = (eot + 1) % 2;
}

void Cube::BCCW() {
	for (int i = 0; i < 3; i++) {
		BCW();
	}
}

void Cube::B2() {
	for (int i = 0; i < 2; i++) {
		BCW();
	}
}

void Cube::RCW() {
	corner cpt = cp[ubr];
	cp[ubr] = cp[ufr];
	cp[ufr] = cp[dfr];
	cp[dfr] = cp[dbr];
	cp[dbr] = cpt;

	char cot = co[ubr];
	co[ubr] = (co[ufr] + 2) % 3;
	co[ufr] = (co[dfr] + 1) % 3;
	co[dfr] = (co[dbr] + 2) % 3;
	co[dbr] = (cot + 1) % 3;

	edge ept = ep[ur];
	ep[ur] = ep[fr];
	ep[fr] = ep[dr];
	ep[dr] = ep[br];
	ep[br] = ept;

	char eot = eo[ur];
	eo[ur] = eo[fr];
	eo[fr] = eo[dr];
	eo[dr] = eo[br];
	eo[br] = eot;
}

void Cube::RCCW() {
	for (int i = 0; i < 3; i++) {
		RCW();
	}
}

void Cube::R2() {
	for (int i = 0; i < 2; i++) {
		RCW();
	}
}

void Cube::LCW() {
	corner cpt = cp[ufl];
	cp[ufl] = cp[ubl];
	cp[ubl] = cp[dbl];
	cp[dbl] = cp[dfl];
	cp[dfl] = cpt;
	
	char cot = co[ufl];
	co[ufl] = (co[ubl] + 2) % 3;
	co[ubl] = (co[dbl] + 1) % 3;
	co[dbl] = (co[dfl] + 2) % 3;
	co[dfl] = (cot + 1) % 3;

	edge ept = ep[ul];
	ep[ul] = ep[bl];
	ep[bl] = ep[dl];
	ep[dl] = ep[fl];
	ep[fl] = ept;

	char eot = eo[ul];
	eo[ul] = eo[bl];
	eo[bl] = eo[dl];
	eo[dl] = eo[fl];
	eo[fl] = eot;
}

void Cube::LCCW() {
	for (int i = 0; i < 3; i++) {
		LCW();
	}
}

void Cube::L2() {
	for (int i = 0; i < 2; i++) {
		LCW();
	}
}