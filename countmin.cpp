#include "countmin.hpp"
#include <iostream>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

CountMin::CountMin(){
	//Initialize the table to zero
	table.resize(NUM_HASH);
	for(int i =0; i<table.size(); i++){
		table.at(i).resize(NUM_BINS,0);
	}
	
}

CountMin::~CountMin(){
	ClearAll();
}

void CountMin::ClearAll(){
	
}

void CountMin::updateSketchWithWord(std::string word){
	vector<int> hashes = returnHashFunctionsOfString(word);
	for(int i =0;i<hashes.size();i++){
		//printf("%s=>H%d:%d\n",word.c_str(),i,hashes.at(i));
		table[i][hashes.at(i)]+=1;
	}
}

vector<int> CountMin::returnHashFunctionsOfString(std::string word){
	// First we hash the string to generate seeds for a random number generator
	boost::hash<std::string> string_hash;
	boost::mt19937 randGen(string_hash(word));
	boost::uniform_int<> numrange(0, NUM_BINS-1);
	boost::variate_generator< boost::mt19937&, boost::uniform_int<> > GetRand(randGen, numrange);
	vector<int> hashes;
	for(int i =0;i<NUM_HASH;i++){
		hashes.push_back(GetRand());
	}
	return hashes;
}

int CountMin::queryCountOfString(std::string word){
	vector<int> hashes = returnHashFunctionsOfString(word);
	int mincount = 1000000000;	// This seems high enough
	for(int i = 0; i<hashes.size();i++){
		if(mincount>table[i][hashes.at(i)]){
			mincount = table[i][hashes.at(i)];
		}
	}
	return mincount;
}

void CountMin::outputCountsOfWordList(std::deque<string> wordlist){
	
	while(!wordlist.empty()){
		std::string word = wordlist.front();
		int count = queryCountOfString(word);
		printf("%d,%s\n",count,word.c_str());
		wordlist.pop_front();
	}
}

deque<int> CountMin::returnCountsOfWordList(std::deque<string> wordlist){
	deque<int> counts;
	while(!wordlist.empty()){
		std::string word = wordlist.front();
		int count = queryCountOfString(word);
		counts.push_back(count);
		wordlist.pop_front();
	}
	return counts;
}



void InsertCountMin::updateSketchWithWord(std::string word){
	vector<int> hashes = returnHashFunctionsOfString(word);
	int mincount = queryCountOfString(word);
	for(int i =0;i<hashes.size();i++){
		if(table[i][hashes.at(i)]< mincount+1){
			table[i][hashes.at(i)]+=1;
		}
	}
}
