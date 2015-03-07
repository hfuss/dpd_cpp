#include "polymerBlock.h"

class CopolymerChain {
	public:
		idx chain_length;
		PosVect* com;
		DPDFrame* frame;
		Micelle* micelle;
    unsigned short id;
    virtual void printChain( FILE* stream ) {}
		// Calclength is not needed
		virtual void calcLength () {}
		virtual ~CopolymerChain() {}
};

enum TriblockConfiguration { stem, petal, neither };

class PECTriblock : public CopolymerChain {
	public:
		
    PolymerBlock* pec_block;
		HydrophobicTail* tail1;
		HydrophobicTail* tail2;
		TriblockConfiguration config;
		idx tail_length;
		idx pec_length;
		// Should I add a void ptr to the frame as a parameter?
		PECTriblock();
		PECTriblock( idx* box_length, float* bond_length, idx pec_length, idx tail_length, idx length,
                       unsigned int* idTracker, unsigned short id);
		PECTriblock( idx tail_length, idx pec_length );
		PECTriblock( idx tail_length, idx pec_length, std::ifstream* inFile, idx* box_length );
		~PECTriblock();
		void printChain( FILE *stream );
		void calcLength();
		void determineConfiguration(); // THIS IS WRONG
};