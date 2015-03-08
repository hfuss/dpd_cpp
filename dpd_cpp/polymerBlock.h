#include "bead.h"
#include <fstream>

class PolymerBlock {
	public:
		idx bead_type;
		idx length;
		idx cursor;
		Bead* beadList;
		PosVect* com;
		CopolymerChain* chain;
		PolymerBlock( CopolymerChain* chain, idx type, 
	                idx length, DirVect* d, 
	                idx* box_length, PosVect* r, unsigned int* id, 
	                unsigned int mold_id );
		PolymerBlock( CopolymerChain *chain, idx type, idx length );
		PolymerBlock();
		PolymerBlock( CopolymerChain *chain, idx type, idx length, 
			std::ifstream* inFile, idx* box_length );
		~PolymerBlock();
		void printBlock( FILE *stream );
		void printData( FILE* stream );
		void calcCenterOfMass( idx* box_length );
		bool addBead( Bead* bead );
		Bead* getBead( idx idx );
};

class HydrophobicTail : public PolymerBlock {
	public:
		HydrophobicTail* other;
		Bin* bin;
		HydrophobicTail( CopolymerChain* chain, idx length,
		                 DirVect* d, idx* box_length, 
		                 PosVect* r, unsigned int* idTracker,
		                 unsigned int mold_id );
		HydrophobicTail( CopolymerChain* chain, idx length );
		HydrophobicTail( CopolymerChain* chain, idx length, 
			std::ifstream* inFile, idx* box_length );
		HydrophobicTail();
		~HydrophobicTail();
};