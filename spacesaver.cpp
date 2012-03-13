#include "spacesaver.hpp"
#include <iostream>

SpaceSaver::SpaceSaver(){
	max_pairs = 2000;
	initializeBimap();
	counter=0;
}

SpaceSaver::~SpaceSaver(){
	ClearAll();
}

void SpaceSaver::ClearAll(){
	bimap.clear();
}

void SpaceSaver::initializeBimap(){
	bimap.clear();
}

void SpaceSaver::updateBimapWithWord(std::string word){


	word_counter::left_map::iterator it = bimap.left.find(word);
	if(it != bimap.left.end() ){
		// Word is in the list - increment its count!
		bimap.left.modify_data(it,boost::bimaps::_data=it->second+1);
	}
	else{
		// Word is not in
		// Check to see if we have space
		if(bimap.size() < max_pairs){	// If so, add it in
			bimap.insert(word_counter::value_type(word,1));
		}
		else{ // If not, replace the last term
			word_counter::right_iterator it = bimap.right.end();
			--it;
			bimap.right.modify_data(it,boost::bimaps::_data=word);
			bimap.right.modify_key(it,boost::bimaps::_key=it->first+1);
		}
	}
}

void SpaceSaver::printWordListByFreq(){
	for( word_counter::right_const_iterator
            wit = bimap.right.begin(), wit_end = bimap.right.end();
         wit != wit_end; ++wit )
    {
		std::cout << wit->first << ": " << wit->second << std::endl;
    }
}
