// Mark Fuge
// SpaceSaver Algorithm Implementation
#include <boost/bimap.hpp>
#include <string>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/support/lambda.hpp> 
//typedef boost::bimap< std::string,int > bm_type;

struct counter {
    counter() : c(0) {}
    counter& operator++() { ++c; return *this; }
    unsigned int operator++(int) { return c++; }
    operator const unsigned int() const { return c; }
    private:
    unsigned int c;
};

using namespace boost::bimaps;
typedef bimap
<
	unordered_set_of< std::string >,
	multiset_of< int,std::greater<int> > /*< `counter` is an integer that is initialized 
							in zero in the constructor >*/
> word_counter;

class SpaceSaver{
public:
	SpaceSaver();		// Initializes the data structures
	~SpaceSaver();		// Cleans up remaining data structures

	void ClearAll();	// Clean Up Memory Structures

	void initializeBimap();

	void updateBimapWithWord(std::string word);
	void printWordListByFreq();
	void outputWordListByFreq();

private:
	int max_pairs;
	word_counter bimap;
	int counter;
};
