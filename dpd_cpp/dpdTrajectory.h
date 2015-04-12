#include "copolymerMicelleFrame.h"

class DPDTrajectory : public ObjDPD {
  public:
    std::string* fileNames;
    std::string outFile;
    unsigned int numFiles;
    unsigned int num_atoms;
    idx box_length;
    idx bin_length;
    unsigned int numFrames;
    unsigned int startFile;
    unsigned int startFrameOffset;
    unsigned int framesAnalyzed;
    unsigned long numBytesInFile( std::string filename );
    void determineNumFrames();
    DPDTrajectory();
    ~DPDTrajectory();
    void unlink();
    void process();
    virtual void analyze( std::ifstream& inFile, FILE* fp );
    virtual void setupOutputFile( FILE* fp );
    void skip( std::ifstream& inFile );
};

class TriblockTrajectory : public DPDTrajectory {
  public:
    std::vector< TriblockFrameData* > frameData;
    idx pec_length;
    idx tail_length;
    idx chain_length;
    float micelle_cutoff;
    void analyze( std::ifstream& inFile, FILE* fp );
    void setupOutputFile( FILE* fp );
    TriblockTrajectory();
    ~TriblockTrajectory();
};
