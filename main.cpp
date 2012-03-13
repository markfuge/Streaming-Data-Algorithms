/* Mark Fuge
CS 281B Assignment 2
Implementation and comparison of the 
CountMin Sketch, the insert-only CountMin Sketch, and the SpaceSaving Algorithms
*/
#include <stdio.h>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <iostream>
#include <fstream>
#include<boost/tokenizer.hpp>
#include "spacesaver.hpp"
#include "countmin.hpp"
#include <algorithm>


std::string DATA_PATH = "..\\..\\data\\";

struct InvalidChar
{
    bool operator()(char c) const {
		if(c<=0){
			return true;
		}
		else{
			return !(isalpha(c)||(c == ' '));
		}
        //return !isprint((unsigned)c);
    }
};

void tokenizeLine(std::string line,std::vector<std::string>* tokens){
	line.erase(std::remove_if(line.begin(),line.end(),InvalidChar()), line.end());
	std::transform(line.begin(), line.end(), line.begin(), ::tolower);
	using namespace boost;
	tokenizer<> tok(line);
	for(tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
		std::string word (*beg);
		tokens->push_back(word);
	}
}

deque<int> returnActualCountsOfWordList(std::deque<string> wordlist,map<std::string , int> actual_counts){
	deque<int> counts;
	while(!wordlist.empty()){
		std::string word = wordlist.front();
		int count = actual_counts[word];
		counts.push_back(count);
		wordlist.pop_front();
	}
	return counts;
}

void printCountComparison(deque<std::string> top_words, deque<int> actual_result, deque<int> countmin_result,deque<int> insertcountmin_result){
	while(!top_words.empty()){
		printf("%s,%d,%d,%d\n",top_words.front().c_str(),actual_result.front(),countmin_result.front(),insertcountmin_result.front());
		top_words.pop_front();
		actual_result.pop_front();
		countmin_result.pop_front();
		insertcountmin_result.pop_front();
	}
}

void outputCountComparison(deque<std::string> top_words, deque<int> actual_result, deque<int> countmin_result,deque<int> insertcountmin_result){
	FILE* outputfile;
	outputfile = fopen ("results_insertcountmin3.txt","w");
	while(!top_words.empty()){
		fprintf(outputfile,"%s,%d,%d,%d\n",top_words.front().c_str(),actual_result.front(),countmin_result.front(),insertcountmin_result.front());
		top_words.pop_front();
		actual_result.pop_front();
		countmin_result.pop_front();
		insertcountmin_result.pop_front();
	}
	fclose(outputfile);
}

int main()
{
	//printf("Hello World");   
	
	// Load in dataset
	std::vector<std::string> filenames;
	filenames.push_back("enwikiaa");
	filenames.push_back("enwikiab");
	filenames.push_back("enwikiac");
	filenames.push_back("enwikiad");
	filenames.push_back("enwikiae");
	filenames.push_back("enwikiaf");
	filenames.push_back("enwikiag");
	filenames.push_back("enwikiah");
	filenames.push_back("enwikiai");

	std::string line;
	std::string filepath;

	// Now load in the top 1000 SpaceSaver words
	deque<std::string> top_words;
	filepath = "SStop1000.txt";
	std::ifstream myfile (filepath.c_str());
	if (myfile.is_open()){
		while ( myfile.good() ){
			getline (myfile,line);
			top_words.push_back(line);
		}
	}
	myfile.close();
	
	map<std::string , int> actual_counts;
	for(int i =0; i<top_words.size();i++){
		actual_counts[top_words.at(i)]=0;
	}
	
	SpaceSaver spacesaver;
	CountMin countmin;
	InsertCountMin insertcountmin;
	
	while(filenames.size()>0){
		filepath= DATA_PATH + filenames.back();
		printf("Parsing file %s\n",filenames.back().c_str());
		

		std::vector<std::string> tokens;
		std::ifstream myfile (filepath.c_str());
		int linecounter = 0;
		if (myfile.is_open()){
			while ( myfile.good() ){
				getline (myfile,line);

				// Now Tokenize the line
				tokens.clear();
				tokenizeLine(line,&tokens);
				while(tokens.size()>0){
					//spacesaver.updateBimapWithWord(tokens.back());
					std::string word = tokens.back();
					countmin.updateSketchWithWord(word);
					insertcountmin.updateSketchWithWord(word);
					if(actual_counts.count(word)>0){
						actual_counts[word]+=1;
					}
					tokens.pop_back();
				}
				linecounter++;

				if(linecounter%1000000==0){
					printf("Lines processed: %dM\n",linecounter/1000000);
				}
			}
			myfile.close();
			
		}
		else printf("Unable to open file\n"); 

		// Clear off this file
		filenames.pop_back();
	}
	//spacesaver.printWordListByFreq();
	//countmin.outputCountsOfWordList(top_words);
	deque<int> countmin_result = countmin.returnCountsOfWordList(top_words);
	deque<int> insertcountmin_result = insertcountmin.returnCountsOfWordList(top_words);
	deque<int> actual_result = returnActualCountsOfWordList(top_words,actual_counts);
	//printCountComparison(top_words,actual_result,countmin_result,insertcountmin_result);
	outputCountComparison(top_words,actual_result,countmin_result,insertcountmin_result);
	return 0;
}