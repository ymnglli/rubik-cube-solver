#ifndef SOLVER_H
#define SOLVER_H

#include <cstdint>
#include <list>
#include <string>
#include <random>
#include <queue>
#include "Cube.h"
#include "Database.h"

using namespace std;

struct Node {
	Cube cube;
	uint8_t move;
};

class Solver {
	public:
		queue<uint8_t> getSolutionQueue();
		queue<uint8_t> getScrambleQueue();
		string		solve(Cube cube, Database& d);
		string 		generateScramble(uint8_t len);
	private:
		queue<uint8_t> solutionQueue;
		queue<uint8_t> scrambleQueue;
		uint8_t		search(list<Node> &path, uint8_t g, uint8_t bound, uint8_t group, Database& d);
		list<Node>	idaStar(Cube& unsolvedCube, uint8_t group, Database &d);
		uint8_t		heuristic(Cube cube, uint8_t group, Database &d);
		string		mapIntegerToMove(uint8_t move);
		string		solveGivenSequence(string sequence, Database& d);
		uint8_t		moveToInteger(string move);
};
#endif