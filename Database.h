#ifndef DATABASE_H
#define DATABASE_H

#include <cstdint>
#include <queue>
#include <iostream>
#include <fstream>
#include <iterator>
#include <thread>
#include "Cube.h"

class Database {
	public:
		uint8_t G0[2048] = {};
		uint8_t** G1;		// G1 [495][2187]
		uint8_t** G2; 		// G2 [70][40320]
		uint8_t**** G3; 	// G3 [96][24][24][24]
		bool** g1Occupied;
		bool** g2Occupied;
		bool**** g3Occupied;
		bool cornerStateOccupied[40320] = {};
		uint8_t* g3CornerPermutationStateToId;
		uint16_t g1PermutationStateToId[2048] = {};
		uint8_t g2PermutationStateToId[256] = {};
		std::queue<Cube> initialCorners;
		Database();
		uint8_t		edgePermutationSliceToId(Cube cube, uint8_t slice);
		bool		setOccupied4D(uint8_t x, uint8_t y, uint8_t z, uint8_t w);
		void        resetCornerStateOccupied();
		uint16_t    edgeOrientationState(Cube cube);
		uint16_t    cornerOrientationState(Cube cube);
		uint16_t    cornerPermutationStateToId(Cube cube);
		bool		setOccupied2D(uint32_t ep, uint32_t cp, bool** phase);
		void		initializeArrays();
		void		g1fillPermutationArray();
		void		g2fillPermutationArray();
		void		g3fillPermutationArray();
		uint16_t	getG1PermutationState(Cube cube);
		uint8_t		getG2PermutationState(Cube cube);
		uint8_t		getG3CornerPermutationState(Cube cube);
		void		setInitialOccupied(Cube root, uint8_t phase);
		void		bfs(uint8_t maxMoves, uint8_t phase, bool (Database::* func) (Cube cube, uint8_t d));
		void		generateDatabase();
		void		generateG0();
		void		generateG1();
		void		generateG2();
		void		generateG3();
		void		init();
		bool		checkG0State(Cube cube, uint8_t d);
		bool		checkG1State(Cube cube, uint8_t d);
		bool		checkG2State(Cube cube, uint8_t d);
		bool		checkG3State(Cube cube, uint8_t d);
		bool		checkInitState(Cube cube, uint8_t d);
		void		writeToFileG0();
		void		writeToFileG1();
		void		writeToFileG2();
		void		writeToFileG3();
		void		loadDatabase();
		int			loadG0();
		int			loadG1();
		int			loadG2();
		int			loadG3();
		void        allocateMemory();
		void        destroy();
};

#endif