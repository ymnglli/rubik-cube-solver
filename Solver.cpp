#include "Solver.h"

using namespace std;

bool inPath(Node node, list<Node> path) {
	Cube curr;
	for (int j = 0; j < path.size(); j++) {
		curr = path.front().cube;
		path.pop_front();
		for (int i = 0; i < 12; i++) {
			if (curr.ep[i] != node.cube.ep[i])
				return false;
			if (curr.eo[i] != node.cube.eo[i])
				return false;
		}
		for (int i = 0; i < 8; i++) {
			if (curr.cp[i] != node.cube.cp[i])
				return false;
			if (curr.co[i] != node.cube.co[i])
				return false;
		}
	}
	return true;
}

uint8_t Solver::search(list<Node>& path, uint8_t g, uint8_t bound, uint8_t group, Database& d) {
	Node curr = path.back();
	uint8_t f = g + heuristic(curr.cube, group, d);
	if (f > bound)
		return f;
	if (heuristic(curr.cube, group, d) == 0)
		return 255;
	uint8_t min = 255;
	curr.cube.setMoves(group);
	for (uint8_t i = 0; i < 18; i++) {
		if (curr.cube.moves[i]) {
			Cube child = curr.cube;
			child.rotate(i);
			Node successor = Node{ child, i };
			if (!inPath(successor, path)) {
				path.push_back(successor);
				uint8_t t = search(path, g + heuristic(child, group, d), bound, group, d);
				if (t == 255)
					return t;
				if (t < min)
					min = t;
				path.pop_back();
			}
		}
	}
	return min;
}

list<Node> Solver::idaStar(Cube& unsolvedCube, uint8_t group, Database& d) {
	uint8_t bound = heuristic(unsolvedCube, group, d);
	list<Node> path;
	path.push_back({ unsolvedCube, 18 }); // 18 represents no move
	bool solved = false;
	while (!solved) {
		uint8_t t = search(path, 0, bound, group, d);
		if (t == 255)
			return path;
		bound = t;
	}
}

string Solver::solve(Cube unsolvedCube, Database& d) {
	string solution = "";
	solutionQueue = queue<uint8_t>();
	for (int i = 0; i < 4; i++) {
		list<Node> partialSolution = idaStar(unsolvedCube, i, d);
		unsolvedCube = partialSolution.back().cube;
		while (partialSolution.size() > 0) {
			Node curr = partialSolution.front();
			partialSolution.pop_front();
			string move = mapIntegerToMove(curr.move);
			if (move.compare("") == 0) {
				// do nothing
			}
			else {
				solution += move + " ";
				solutionQueue.push(curr.move);
			}
		}
	}
	return solution;
}

uint8_t Solver::moveToInteger(string move) {
	if (move.compare("F") == 0)
		return 0;
	else if (move.compare("F'") == 0)
		return 1;
	else if (move.compare("F2") == 0)
		return 2;
	else if (move.compare("B") == 0)
		return 3;
	else if (move.compare("B'") == 0)
		return 4;
	else if (move.compare("B2") == 0)
		return 5;
	else if (move.compare("U") == 0)
		return 6;
	else if (move.compare("U'") == 0)
		return 7;
	else if (move.compare("U2") == 0)
		return 8;
	else if (move.compare("D") == 0)
		return 9;
	else if (move.compare("D'") == 0)
		return 10;
	else if (move.compare("D2") == 0)
		return 11;
	else if (move.compare("R") == 0)
		return 12;
	else if (move.compare("R'") == 0)
		return 13;
	else if (move.compare("R2") == 0)
		return 14;
	else if (move.compare("L") == 0)
		return 15;
	else if (move.compare("L'") == 0)
		return 16;
	else if (move.compare("L2") == 0)
		return 17;
}

string Solver::solveGivenSequence(string sequence, Database& d) {
	uint8_t move;
	Cube scrambledCube;
	string delimiter = " ";
	int start = 0;
	int end = sequence.find(delimiter);
	while (end != -1) {
		move = moveToInteger(sequence.substr(start, end - start));
		scrambledCube.rotate(move);
		start = end + delimiter.size();
		end = sequence.find(delimiter, start);
	}
	move = moveToInteger(sequence.substr(start, end - start));
	scrambledCube.rotate(move);
	return solve(scrambledCube, d);
}

queue<uint8_t> Solver::getSolutionQueue() {
	return solutionQueue;
}

queue<uint8_t> Solver::getScrambleQueue() {
	return scrambleQueue;
}

string Solver::mapIntegerToMove(uint8_t move) {
	switch (move) {
	case 0:
		return "F";
	case 1:
		return "F'";
	case 2:
		return "F2";
	case 3:
		return "B";
	case 4:
		return "B'";
	case 5:
		return "B2";
	case 6:
		return "U";
	case 7:
		return "U'";
	case 8:
		return "U2";
	case 9:
		return "D";
	case 10:
		return "D'";
	case 11:
		return "D2";
	case 12:
		return "R";
	case 13:
		return "R'";
	case 14:
		return "R2";
	case 15:
		return "L";
	case 16:
		return "L'";
	case 17:
		return "L2";
	case 18:
		return "";
	}
}

uint8_t Solver::heuristic(Cube cube, uint8_t group, Database& d) {
	int x = 0;
	int y = 0;
	int z = 0;
	int s = 0;
	switch (group) {
	case 0:
		x = d.edgeOrientationState(cube);
		return d.G0[x];
	case 1:
		x = d.getG1PermutationState(cube);
		y = d.cornerOrientationState(cube);
		return d.G1[x][y];
	case 2:
		x = d.getG2PermutationState(cube);
		y = d.cornerPermutationStateToId(cube);
		return d.G2[x][y];
	case 3:
		x = d.getG3CornerPermutationState(cube);
		y = d.edgePermutationSliceToId(cube, 0);
		z = d.edgePermutationSliceToId(cube, 1);
		s = d.edgePermutationSliceToId(cube, 2);
		return d.G3[x][y][z][s];
	}
	return 0;
}
	
string Solver::generateScramble(uint8_t len) {
	uint8_t prevMove;
	scrambleQueue = queue<uint8_t>(); 
	string scramble = "";
	/*
	To avoid scrambles generating less than the desired number of moves
	such as "F F" (equivalent to F2) or "F F'" (equivalent to no move), 
	I will first generate moves of different types and then apply variations 
	to each move.
	
	0 = "F", 1 = "B", 2 = "U", 3 = "D", 4 = "R", 5 = "L"
	*/
	uint8_t mix[6] = {0, 1, 2, 3, 4, 5};
	
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 5); // distribution in range [0, 5]
	std::uniform_int_distribution<std::mt19937::result_type> var_dist(0, 2); // distribution in range [0, 2]

	for (uint8_t i = 0; i < len; i++) {
		uint8_t move = dist(rng);
		if (i > 0) {
			while (move == prevMove) {
				move = dist(rng);
			}
		}
		uint8_t updatedMove = move * 3 + var_dist(rng);
		scramble += mapIntegerToMove(updatedMove) + " ";
		scrambleQueue.push(updatedMove);
		prevMove = move;
	}
	
	return scramble;
}