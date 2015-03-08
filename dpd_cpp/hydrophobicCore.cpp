#include "hydrophobicCore.h"

HydrophobicCore::HydrophobicCore() {
	this->aggregation_num = 0;
	this->num_tails = 0;
	this->com = new PosVect();
}

HydrophobicCore::~HydrophobicCore() {}

void HydrophobicCore::addBin( Bin* bin ) {
	this->aggregation_num += bin->num_chains;
	this->num_tails += bin->tailList.size();
	this->binList.push_back( bin );
	bin->grouped = true;
	bin->core = this;
}

void HydrophobicCore::calcCenterOfMass( idx* box_length ) {
	this->com->reset();
	// First bead in core
	Bead* base = this->binList[ 0 ]->tailList[ 0 ]->beadList;
	for ( auto bin = std::begin( this->binList ) ; bin != std::end( this->binList ) ; bin++ ) {
		for ( auto tail = std::begin( ( *bin )->tailList ) ; tail != std::end( ( *bin )->tailList ) ; tail++ ) {
			( *tail )->beadList->pbcCorrectBeadInChain( base, box_length );
			( *tail )->calcCenterOfMass( box_length );
      this->com->addCoords( (*tail )->com );
		}
	}
  int numberTails = this->num_tails;
  this->com->divideCoords( &numberTails );
}

void HydrophobicCore::printCore( FILE* stream ) {
  for ( auto bin = std::begin( this->binList ) ; bin != std::end( this->binList ) ; bin++ ) {
		( *bin )->printBin( stream );
  }
}

bool HydrophobicCore::groupCores( HydrophobicCore* core ) {
	// Finish
	Bin* other;
	for ( auto bin = std::begin( this->binList ) ; bin != std::end( this->binList ) ; bin++ ) {
		for ( auto tail = std::begin( ( *bin )->tailList ) ; tail != std::end( ( *bin )->tailList ) ; tail++ ) {
		 	other = ( *tail )->other->bin;
			if ( other && other->core != ( *bin )->core && other->core == core )
				return true;
		}
	}
	return false;
}

#if defined( TESTING )
#include <iostream>

int main() {

	std::ifstream infile( "bin_test.txt" );
	idx box_length = 36;
	// Make two triblocks from file
	std::cout << "Chain1: " << std::endl;
	PECTriblock* chain1 = new PECTriblock( 50, 4, &infile, &box_length );
	chain1->printChain( stdout );
	std::cout << ( short ) chain1->chain_length << std::endl;
	std::cout << "Chain1 Tail1 com: ";
	chain1->tail1->com->print( stdout );
	std::cout << "Chain1 Tail2 com: ";
	chain1->tail2->com->print( stdout );	

	std::cout << "Chain2: " << std::endl;
	PECTriblock* chain2 = new PECTriblock( 50, 4, &infile, &box_length );
	chain2->printChain( stdout );
	std::cout << ( short ) chain2->chain_length << std::endl;
	std::cout << "Chain2 Tail1 com: ";
	chain2->tail1->com->print( stdout );
	std::cout << "Chain2 Tail2 com: ";
	chain2->tail2->com->print( stdout );

	// Initialize two bins
	Bin* b1 = new Bin();
	Bin* b2 = new Bin();

	b1->init( NULL, 2, 0, 0, 0 );
	b2->init( NULL, 2, 0, 1, 0 );

	//Add tails
	b1->addTail( chain1->tail1 );
	b1->addTail( chain1->tail2 );

	b2->addTail( chain2->tail1 );
	b2->addTail( chain2->tail2 );

	// Make core and add bins
	HydrophobicCore* core = new HydrophobicCore();

	core->addBin( b1 );
	core->addBin( b2 );

    chain1->determineConfiguration();
    if ( chain1->config != petal )
        std::cout << "Fail" << std::endl;
    
    chain2->determineConfiguration();
    if ( chain2->config != petal)
        std::cout << "Fail" << std::endl;
    
	// Should be 2 and 4 ( two chains, four tails/blocks )
	std::cout << "Core agg num: " << core->aggregation_num << std::endl;
	std::cout << "Core num of blocks: " << core->num_tails << std::endl;

	core->calcCenterOfMass( &box_length );

	std::cout << "Core com: ";
	core->com->print( stdout );

	std::cout << "Chain1 Tail1 com: ";
	chain1->tail1->com->print( stdout );
	std::cout << "Chain1 Tail2 com: ";
	chain1->tail2->com->print( stdout );

	std::cout << "Chain2 Tail1 com: ";
	chain2->tail1->com->print( stdout );
	std::cout << "Chain2 Tail2 com: ";
	chain2->tail2->com->print( stdout );

	std::cout << "Core:" << std::endl;
	core->printCore( stdout );

///////////////////////////////////////////////////////////////////
	// Test group cores
	HydrophobicCore* core1 = new HydrophobicCore();
	HydrophobicCore* core2 = new HydrophobicCore();

	// Initialize two new bins
	Bin* b3 = new Bin();
	Bin* b4 = new Bin();

	b3->init( NULL, 2, 0, 0, 0 );
	b4->init( NULL, 2, 0, 1, 0 );

	// Reset tails
	chain1->tail1->bin = NULL;
	chain1->tail2->bin = NULL;
	chain2->tail1->bin = NULL;
	chain2->tail2->bin = NULL;

	b3->addTail( chain1->tail1 );
	b3->addTail( chain1->tail2 );
	b3->addTail( chain2->tail1 );
	core1->addBin( b3 );

	if ( !core1->groupCores( core2 ) )
		std::cout << "Group works" << std::endl;

	b4->addTail( chain2->tail2 );;
	core2->addBin( b4 );

	if ( core1->groupCores( core2 ) )
		std::cout << "Group works again" << std::endl;
    
    chain2->determineConfiguration();
    if ( chain2->config != stem )
        std::cout << "Fail" << std::endl;
    
    chain1->determineConfiguration();
    if ( chain1->config != petal )
        std::cout << "Fail" << std::endl;

	return 0;
}

#endif
