// Mark Fuge
// CountMin Sketch Implementation
#include <string>
#include <boost/functional/hash.hpp>
#include <vector>
#include <deque>

//#define NUM_BINS 4194304
//#define NUM_HASH 20

//#define NUM_BINS 2097152
//#define NUM_HASH 8

#define NUM_BINS 512
#define NUM_HASH 4 

using namespace std;

/*int hashCode(string word)
{
    boost::hash<string> string_hash;
    return string_hash(word);
}*/


class CountMin{
public:
	CountMin();		// Initializes the data structures
	~CountMin();		// Cleans up remaining data structures

	void ClearAll();	// Clean Up Memory Structures

	void updateSketchWithWord(string word);
	vector<int> returnHashFunctionsOfString(string word);
	int queryCountOfString(std::string word);
	void outputCountsOfWordList(std::deque<string> wordlist);
	deque<int> returnCountsOfWordList(std::deque<string> wordlist);
protected:
	vector<vector<int>> table;
	
};


class InsertCountMin: public CountMin {
public:
	void updateSketchWithWord(string word);
};
