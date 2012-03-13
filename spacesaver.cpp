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
	// Initialize the 
}

void SpaceSaver::updateBimapWithWord(std::string word){


	word_counter::left_map::iterator it = bimap.left.find(word);
	if(it != bimap.left.end() ){
		// Word is in the list - increment its count!
		//printf("Incrementing %s\n",word.c_str());
		//printf("Incrementing %s\n",it->first.c_str());
		//printf("Incrementing %d\n",it->second);
		//it->second++;
		bimap.left.modify_data(it,boost::bimaps::_data=it->second+1);
		//printf("Incrementing %d\n",it->second);

	}
	else{
		// Word is not in
		//printf("Inserting %s\n",word.c_str());
		// Check to see if we have space
		if(bimap.size() < max_pairs){	// If so, add it in
			bimap.insert(word_counter::value_type(word,1));
		}
		else{ // If not, replace the last term
			word_counter::right_iterator it = bimap.right.end();
			--it;
			//printf("Checking %d\n",it->first);
			//printf("Changing %s:%d to ",it->second.c_str(),it->first);
			bimap.right.modify_data(it,boost::bimaps::_data=word);
			bimap.right.modify_key(it,boost::bimaps::_key=it->first+1);
			//printf("%s:%d\n",it->second.c_str(),it->first);
		}
	}
	//std::cout << it->first << std::endl;

	
	//printf("Bimap Size: %d\n",bimap.size());
	//printf("  Max Count: 

}

void SpaceSaver::printWordListByFreq(){
	for( word_counter::right_const_iterator
            wit = bimap.right.begin(), wit_end = bimap.right.end();
         wit != wit_end; ++wit )
    {
		std::cout << wit->first << ": " << wit->second << std::endl;
    }
}

void SpaceSaver::outputWordListByFreq(){

}