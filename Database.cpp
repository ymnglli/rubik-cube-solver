#include "Database.h"

using namespace std;

Database::Database() {}

/* returns unique id for edge orientation
* 0 <= index <= 2047
*/
uint16_t Database::edgeOrientationState(Cube cube) {
	uint16_t id = 0;
	for (int i = 0; i < 11; i++) {
		id *= 2;
		id += cube.eo[i];
	}
	return id;
}

/* returns unique id for corner orientation
* 0 <= index <= 2186
*/
uint16_t Database::cornerOrientationState(Cube cube) {
	uint16_t co = 0;
	for (int i = 0; i < 7; i++) {
		co *= 3;
		co += cube.co[i];
	}
	return co;
}


/* returns true if corners {ufl, dfr, dbl, ubr} and
*  {ufr, dfl, dbr, ubl} are in their correct orbits.
*  In other words, can be solved with only 180 degree twists in Group 3
*/
bool cornersInOrbit(Cube cube) {
	for (int i = 0; i < 4; i++) {
		if (cube.cp[i] > 3)
			return false;
	}
	return true;
}

/* returns true if edges are in their correct slices.
*/
bool edgesInSlice(Cube cube) {
	for (int i = 0; i < 4; i++) {
		if (cube.ep[i] > 3)
			return false;
	}
	for (int i = 4; i < 8; i++) {
		if (cube.ep[i] > 7)
			return false;
	}
	return true;
}

/* returns unique id for corner permutation state
* 0 <= index <= 40319
*/
uint16_t Database::cornerPermutationStateToId(Cube cube) {
	uint16_t id = 0;

	for (int i = 0; i < 7; i++) {
		id *= (8 - i);
		for (int j = i + 1; j < 8; j++) {
			if (cube.cp[i] > cube.cp[j]) {
				id++;
			}
		}
	}
	return id;
}

// slice 0 = "M", 1 = "E", 2 = "S"
uint8_t Database::edgePermutationSliceToId(Cube cube, uint8_t slice) {
	int id = 0;
	switch (slice) {
	case 0:
		for (int i = 0; i < 4; i++) {
			id *= 10;
			id += cube.ep[i];
		}
		break;
	case 1:
		for (int i = 4; i < 8; i++) {
			id *= 10;
			id += (cube.ep[i] - 4);
		}
		break;
	case 2:
		for (int i = 8; i < 12; i++) {
			id *= 10;
			id += (cube.ep[i] - 8);
		}
		break;
	}

	switch (id) {
	case 123:
		return 0;
	case 132:
		return 1;
	case 213:
		return 2;
	case 231:
		return 3;
	case 312:
		return 4;
	case 321:
		return 5;
	case 1023:
		return 6;
	case 1032:
		return 7;
	case 1203:
		return 8;
	case 1230:
		return 9;
	case 1302:
		return 10;
	case 1320:
		return 11;
	case 2013:
		return 12;
	case 2031:
		return 13;
	case 2103:
		return 14;
	case 2130:
		return 15;
	case 2301:
		return 16;
	case 2310:
		return 17;
	case 3012:
		return 18;
	case 3021:
		return 19;
	case 3102:
		return 20;
	case 3120:
		return 21;
	case 3201:
		return 22;
	case 3210:
		return 23;
	}
}

/* generates unique index for "E" slice permutation
* 0 <= index <= 2047, with a total of 495 possible permutations
*/
void Database::g1fillPermutationArray() {
	uint16_t index = 0;
	for (int i = 0; i < 2048; i++) {
		int copy = i;
		int count = 0;
		while (copy > 0) {
			count++;
			copy = copy & (copy - 1);
		}
		if (count == 3 || count == 4) {
			g1PermutationStateToId[i] = index;
			index++;
		}
	}
}

/* generates unique index for edge permutations in "M" and "S" slice
* 0 <= index <= 255, with a total of 70 possible permutations
*/
void Database::g2fillPermutationArray() {
	uint8_t index = 0;
	for (int i = 0; i < 256; i++) {
		int copy = i;
		int count = 0;
		while (copy > 0) {
			count++;
			copy = copy & (copy - 1);
		}
		if (count == 4) {
			g2PermutationStateToId[i] = index;
			index++;
		}
	}
}

void Database::resetCornerStateOccupied() {
	for (int i = 0; i < 40320; i++) {
		cornerStateOccupied[i] = false;
	}
}

void Database::g3fillPermutationArray() {
	uint8_t count = 0;
	queue<Cube> parents;
	Cube root;
	parents.push(root);
	int d = 0;
	Cube curr;

	while (d < 4) {
		d++;
		queue<Cube> children;
		while (parents.size() > 0) {
			curr = parents.front();
			parents.pop();
			curr.setMoves(3);
			for (char i = 0; i < 18; i++) {
				if (curr.moves[i]) {
					Cube child = curr;
					child.rotate(i);
					uint16_t id = cornerPermutationStateToId(child);
					if (!cornerStateOccupied[id] && cornersInOrbit(child)) {
						g3CornerPermutationStateToId[id] = count;
						count++;
						children.push(child);
						cornerStateOccupied[id] = true;
					}
				}
			}
		}
		parents = children;
	}
	resetCornerStateOccupied();
}

// returns index of "E" slice edge permutation state
uint16_t Database::getG1PermutationState(Cube cube) {
	uint16_t state = 0;
	for (int i = 0; i < 11; i++) {
		state *= 2;
		if (cube.ep[i] >= 4 && cube.ep[i] <= 7) {
			state++;
		}
	}
	return g1PermutationStateToId[state];
}

// returns index of edge permutation state in "M" and "S" slices
uint8_t Database::getG2PermutationState(Cube cube) {
	uint16_t state = 0;
	for (int i = 0; i < 4; i++) {
		state *= 2;
		if (cube.ep[i] > 7)
			state++;
	}
	for (int i = 8; i < 12; i++) {
		state *= 2;
		if (cube.ep[i] > 7)
			state++;
	}
	return g2PermutationStateToId[state];
}

uint8_t Database::getG3CornerPermutationState(Cube cube) {
	uint16_t id = cornerPermutationStateToId(cube);
	return g3CornerPermutationStateToId[id];
}

bool Database::setOccupied2D(uint32_t x, uint32_t y, bool** phaseOccupied) {
	if (phaseOccupied[x][y] == true)
		return true;
	phaseOccupied[x][y] = true;
	return false;
}

bool Database::setOccupied4D(uint8_t x, uint8_t y, uint8_t z, uint8_t w) {
	if (g3Occupied[x][y][z][w] == true)
		return true;
	g3Occupied[x][y][z][w] = true;
	return false;
}

void Database::setInitialOccupied(Cube root, uint8_t phase) {
	if (phase == 1) {
		uint16_t p = getG1PermutationState(root);
		uint16_t o = cornerOrientationState(root);
		setOccupied2D(p, o, g1Occupied);
	}
	else if (phase == 3) {
		uint8_t cp = getG3CornerPermutationState(root);
		setOccupied4D(cp, 0, 0, 0);
	}
}

void Database::bfs(uint8_t maxMoves, uint8_t phase, bool (Database::* func) (Cube cube, uint8_t d)) {
	uint8_t d = 0;
	queue<Cube> parents;
	Cube curr;
	if (phase == 2) {
		init();
		parents = initialCorners;
	}
	else if (phase == 4) { // use for init()
		phase = 2;
		Cube root;
		parents.push(root);
	}
	else {
		Cube root;
		parents.push(root);
		setInitialOccupied(root, phase);
	}
	while (d < maxMoves) {
		d++;
		queue<Cube> children;
		while (parents.size() > 0) {
			curr = parents.front();
			curr.setMoves(phase);
			parents.pop();
			for (uint8_t i = 0; i < 18; i++) {
				if (curr.moves[i]) {
					Cube child = curr;
					child.rotate(i);
					if ((this->*func)(child, d)) {
						children.push(child);
					}
				}
			}
		}
		parents = children;
	}
}

void Database::generateG0() {
	bfs(7, 0, &Database::checkG0State);
}

void Database::generateG1() {
	bfs(10, 1, &Database::checkG1State);
}

void Database::generateG2() {
	resetCornerStateOccupied();
	bfs(13, 2, &Database::checkG2State);
}

void Database::generateG3() {
	bfs(15, 3, &Database::checkG3State);
}

void Database::init() {
	bfs(4, 4, &Database::checkInitState);
}

bool Database::checkG0State(Cube cube, uint8_t d) {
	uint16_t id = edgeOrientationState(cube);
	if (id != 0 && G0[id] == 0) {
		Database::G0[id] = d;
		return true;
	}
	return false;
}

bool Database::checkG1State(Cube cube, uint8_t d) {
	uint16_t p = getG1PermutationState(cube);
	uint16_t o = cornerOrientationState(cube);
	if (!setOccupied2D(p, o, g1Occupied)) {
		G1[p][o] = d;
		return true;
	}
	return false;
}

bool Database::checkG2State(Cube cube, uint8_t d) {
	uint8_t ep = getG2PermutationState(cube);
	uint16_t cp = cornerPermutationStateToId(cube);
	if (!setOccupied2D(ep, cp, g2Occupied)) {
		G2[ep][cp] = d;
		return true;
	}
	return false;
}

bool Database::checkG3State(Cube cube, uint8_t d) {
	uint8_t cp = getG3CornerPermutationState(cube);
	uint8_t m = edgePermutationSliceToId(cube, 0);
	uint8_t e = edgePermutationSliceToId(cube, 1);
	uint8_t s = edgePermutationSliceToId(cube, 2);
	if (!setOccupied4D(cp, m, e, s)) {
		G3[cp][m][e][s] = d;
		return true;
	}
	return false;
}

bool Database::checkInitState(Cube cube, uint8_t d) {
	uint16_t cp = cornerPermutationStateToId(cube);
	uint16_t ep = getG2PermutationState(cube);
	if (!cornerStateOccupied[cp] && cornersInOrbit(cube)) {
		initialCorners.push(cube);
		cornerStateOccupied[cp] = true;
		setOccupied2D(ep, cp, g2Occupied);
		return true;
	}
	return false;
}

void Database::initializeArrays() {
	g1fillPermutationArray();
	g2fillPermutationArray();
	g3fillPermutationArray();
}

void Database::generateDatabase() {
	initializeArrays();
	generateG0();
	generateG1();
	generateG2();
	generateG3();
	writeToFileG0();
	writeToFileG1();
	writeToFileG2();
	writeToFileG3();
}

void Database::writeToFileG0() {
	fstream file;
	file.open("g0.bin", ios::out | ios::binary);
	file.write((char*)&G0, (2048) * sizeof(uint8_t));
	file.close();
}

void Database::writeToFileG1() {
	fstream file;
	file.open("g1.bin", ios::out | ios::binary);
	for (int i = 0; i < 495; i++) {
		for (int j = 0; j < 2187; j++) {
			file.write((char*)&G1[i][j], sizeof(uint8_t));
		}
	}
	file.close();
}

void Database::writeToFileG2() {
	fstream file;
	file.open("g2.bin", ios::out | ios::binary);
	for (int i = 0; i < 70; i++) {
		for (int j = 0; j < 40320; j++) {
			file.write((char*)&G2[i][j], sizeof(uint8_t));
		}
	}
	file.close();
}

void Database::writeToFileG3() {
	fstream file;
	file.open("g3.bin", ios::out | ios::binary);
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 24; j++) {
			for (int k = 0; k < 24; k++) {
				for (int s = 0; s < 24; s++) {
					file.write((char*)&G3[i][j][k][s], sizeof(uint8_t));
				}
			}
		}
	}
	file.close();
}

int Database::loadG0() {
	fstream g0;
	g0.open("g0.bin", ios::in | ios::binary);
	g0.read((char*)&G0, 2048 * sizeof(uint8_t));
	g0.close();
	return EXIT_SUCCESS;
}

int Database::loadG1() {
	fstream g1;
	g1.open("g1.bin", ios::in | ios::binary);
	for (int i = 0; i < 495; i++) {
		for (int j = 0; j < 2187; j++) {
			g1.read((char*)&G1[i][j], sizeof(uint8_t));
		}
	}
	g1.close();
	return EXIT_SUCCESS;
}

int Database::loadG2() {
	fstream g2;
	g2.open("g2.bin", ios::in | ios::binary);
	for (int i = 0; i < 70; i++) {
		for (int j = 0; j < 40320; j++) {
			g2.read((char*)&G2[i][j], sizeof(uint8_t));
		}
	}
	g2.close();
	return EXIT_SUCCESS;
}

int Database::loadG3() {
	fstream g3;
	g3.open("g3.bin", ios::in | ios::binary);
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 24; j++) {
			for (int k = 0; k < 24; k++) {
				for (int s = 0; s < 24; s++) {
					g3.read((char*)&G3[i][j][k][s], sizeof(uint8_t));
				}
			}
		}
	}
	g3.close();
	return EXIT_SUCCESS;
}

void Database::loadDatabase() {
	thread t1(&Database::loadG0, this);
	thread t2(&Database::loadG1, this);
	thread t3(&Database::loadG2, this);
	thread t4(&Database::loadG3, this);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	initializeArrays();
	cout << "...loaded database" << endl;
}

void Database::allocateMemory() {
	G1 = new uint8_t * [495]{};
	g1Occupied = new bool* [495]{};
	for (int i = 0; i < 495; i++) {
		G1[i] = new uint8_t[2187]{};
		g1Occupied[i] = new bool[2187]{};
	}
	G2 = new uint8_t * [70]{};
	g2Occupied = new bool* [70]{};
	for (int i = 0; i < 70; i++) {
		G2[i] = new uint8_t[40320]{};
		g2Occupied[i] = new bool[40320]{};
	}
	g3CornerPermutationStateToId = new uint8_t[40320]{};
	G3 = new uint8_t * **[96]{};
	g3Occupied = new bool*** [96]{};
	for (int i = 0; i < 96; i++) {
		G3[i] = new uint8_t * *[24]{};
		g3Occupied[i] = new bool** [24]{};
	}
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 24; j++) {
			G3[i][j] = new uint8_t * [24]{};
			g3Occupied[i][j] = new bool* [24]{};
		}
	}
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 24; j++) {
			for (int k = 0; k < 24; k++) {
				G3[i][j][k] = new uint8_t[24]{};
				g3Occupied[i][j][k] = new bool[24]{};
			}
		}
	}
}

void Database::destroy() {
	for (int i = 0; i < 495; i++) {
		delete[] G1[i];
		delete[] g1Occupied[i];
	}
	delete[] G1;
	delete[] g1Occupied;

	for (int i = 0; i < 70; i++) {
		delete[] G2[i];
		delete[] g2Occupied[i];
	}
	delete[] G2;
	delete[] g2Occupied;
	delete[] g3CornerPermutationStateToId;
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 24; j++) {
			for (int k = 0; k < 24; k++) {
				delete[] G3[i][j][k];
				delete[] g3Occupied[i][j][k];
			}
		}
	}
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 24; j++) {
			delete[] G3[i][j];
			delete[] g3Occupied[i][j];
		}
	}
	for (int i = 0; i < 96; i++) {
		delete[] G3[i];
		delete[] g3Occupied[i];
	}
	delete[] G3;
	delete[] g3Occupied;
}