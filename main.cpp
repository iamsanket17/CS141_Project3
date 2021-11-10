/* ------------------------------------------------
 * main.cpp
 *
 * Class: Program #3 for CS 141, Fall 2019
 * System: Codio
 * Author: Kevin Rula, Sanket Patel
 *
*/
#include <iostream>
#include <string>
#include <fstream>      // For file input
#include <vector>                // For dictionary vector
#include <iomanip>                // For setw()
#include <cctype>       // For tolower()
using namespace std;




//---------------------------------------------------------------
// Display ID info
//
void displayIdInfo()
{
    cout << "\n"
         << "Program #3: Word Play\n"
         << "Author: Dale Reed\n"
         << "Lab: Tues 8am\n"
         << "System:  Codio\n"
         << "\n";
        


}//end displayIDInfo()


//-----------------------------------------------------------------------------------------
//  You should use parameters for the dictionary, the word lengths array, 
//  the length of words to use, and the total number of words.
void readInWordsFromFile(int lengthOfWordsToUse,vector<string> &dictionary, int &totalWords,vector<int>&numChar,vector<int>&tempNum)
{
        ifstream inputFileStream;
   // vector<int> numChar;
   // vector<int> tempNum;
   //totalWords = 0;
   
    for (int i = 3; i < 18; i++) {
        tempNum.push_back(i);
    }
    for (int i = 0; i < 15; i++) {
        numChar.push_back(0);
    }
    
    string fileName = "dictionary.txt"; // C string (array of char) to store filename
    string inputWord;                                    // stores each word as it is read


        // Open input file
        inputFileStream.open( fileName.c_str() );
            
   // Verify that the open worked
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file " << fileName << "  Exiting..." << endl;
        exit( -1);
    }
    
    
        // Read all the words from the file, and display them
    while( inputFileStream >> inputWord) {
        totalWords ++;                  // incrementing totalWords.
        int size = inputWord.size();
        for (int j = 0; j < tempNum.size(); j++) {
            if (size == tempNum.at(j)) {
                numChar.at(j)++;
            }
        }
        if (inputWord.size()==lengthOfWordsToUse)
        {
            for(int i=0;i<lengthOfWordsToUse;i++)
            {
                inputWord.at(i)=tolower(inputWord.at(i));
            }
            dictionary.push_back(inputWord);
        }
    }
    
   
    
    
    
  
    inputFileStream.close();    // Close the input file.
}


//--------------------------------------------------------------------------------------
// Use binary search to look up the search word in the dictionary vector, returning
// the word's index if found, -1 otherwise.
//
long binarySearch(
            string searchWord,            // word to be looked up
            vector< string> &dictionary)   // the dictionary of words
{
    long low, mid, high;     // array indices for binary search
    long searchResult = -1;  // Stores index of word if search succeeded, else -1
    
    // Binary search for word
    low = 0;
    high = dictionary.size() - 1;
    while ( low <= high)  {
        mid = (low + high) / 2;
        // SearchResult negative value means word is to the left, positive value means
        // word is to the right, value of 0 means word was found
        searchResult = searchWord.compare( dictionary[ mid] );
        if ( searchResult == 0)  {
            // Word IS in dictionary, so return the index where the word was found
            return mid;
        }
        else if (searchResult < 0)  {
            high = mid - 1; // word should be located before the mid location
        }
        else  {
            low = mid + 1; // word should be located after the mid location
        }
    }


    
    // Word was not found
    return -1;
}//end binarySearch()






//-----------------------------------------------------------------------------------------
//3 START: function to select startWord and endWord
//-----------------------------------------------------------------------------------------
void wordSelection(string &startWord,string &endWord,int &lengthOfWordsToUse,vector< string> &dictionary)
{
     string startinput=" ";
     //to iterate while loop if length is not matched or word is not found in dictionary.
            
     while(startWord!=startinput) {
         cout<<"Enter starting word, or 'r' for a random word: ";
         cin>>startinput; 
             
         if(startinput=="r") {
             startWord=dictionary.at(rand()%dictionary.size()); // selecting random strat word from dictionary.
             break;
         }
         else if (startinput == "exit"){
             cout << "Exiting program." << endl;
             exit(-1);
         }
         else {           
             if (startinput.size()==lengthOfWordsToUse) {//Check length of startinput is
                 if (binarySearch(startinput,dictionary)!=-1) {  
                     startWord=startinput; 
                 }
                 else {
                     cout<<"*** "<<"\'"<<startinput<<"\'"<<" is not in the dictionary. Please retry."<<endl;
                     cout<<endl;
                 }
             }
             else {
                 cout<<"*** "<<"\'"<<startinput<<"\'"<<" is not of length "<<lengthOfWordsToUse<<". Please retry."<<endl; 
                 cout<<endl;
             }
         }
     }
     string endinput=" ";
     while(endWord!=endinput) { 
         cout<<"Enter ending word, or 'r' for a random word: ";
         cin>>endinput;
         if(endinput=="r") {
             endWord=dictionary.at(rand()%dictionary.size());  //selecting random end word from dictionary.
             break;
         }
         else {    
             if (endinput.size()==lengthOfWordsToUse) {
                 if (binarySearch(endinput,dictionary)!=-1) {
                     endWord=endinput; 
                 }
                 else {
                     cout<<"*** "<<"\'"<<endinput<<"\'"<<" is not in the dictionary. Please retry."<<endl;
                     cout<<endl;
                 }
             }
         }
     }
}
//-----------------------------------------------------------------------------------------
//Case 4: Play the game to change the start-word to end-word.
//-----------------------------------------------------------------------------------------


int playGame(string startWord , string endWord , int lengthOfWordsToUse , vector<string>dictionary)
{
    string nextWord; //hold the string that user enter to play the word change game.
    int counter = 1; 
    while(nextWord != endWord) {
        int letterChanged=0;//hold the count for number of letters changed in user input nextWord.
        cout << counter <<". Previous word is '"<<startWord<<"'. Next word:";
        cin>>nextWord;
        cout<<endl;
        
        if (nextWord == "exit") {
            return -1;
        }
       
        if(nextWord.size()==lengthOfWordsToUse) {// comparing length of nextWord and startWord.
            for(int i=0; i<lengthOfWordsToUse; i++) { 
                if(startWord.at(i) != nextWord.at(i)) { // comparing each index letter.
                    letterChanged++; //increase the count for each different letter.
                }
                else {
                    continue;
                }
            }
            if(letterChanged == 1) {
                if (binarySearch(nextWord,dictionary)!=-1) {// checking condition: if the nextWord exist in dictionary or not.
                    counter++;
                    startWord=nextWord; // assigning startWord to nextWord in order to play game
                    if(nextWord==endWord)
                    {
                        cout<<"Congratulations, you did it!"<<endl;
                        cout<<endl;
                        break;
                    }
                }
                else {
                    cout<<"    *** "<<"\'"<<nextWord<<"\'"<<" is not in the dictionary. Please retry."<<endl;
                    continue;
                }
            }
            else {
                cout<<"    *** '"<<nextWord<<"' must be exactly 1 character different.  Please retry."<<endl;
                continue;
            }
        }
        else {
            cout<<"    *** '"<<nextWord<<"' is not of length "<<lengthOfWordsToUse<<". Please retry."<<endl;
            continue;
        }
    }
}




bool checkVec(vector<string> list, string searchWord){
    int check = -1;
    for (int i =0; i < list.size(); i++) {
        if (searchWord == list.at(i)){
            check++;
            break;
        }
    }
    if (check != -1){
        return true;
    }
    return false;
}
//-------------------------------------------------------------------------------------------------------
//CASE-5,6 Finding endWord with Debug
//-------------------------------------------------------------------------------------------------------
void debug(string &startWord , string& endWord , int lengthOfWordsToUse , vector<string>&dictionary,vector<string>endWords, bool print, vector<string> &tree, vector<int> &indexTree)
{
    int i,j,k;
    int pos = 0;
    //vector<string> tree;
    //vector<int> indexTree;
    string word = " ";
    const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
    string newWord = startWord; //hold the string obtained automatically by changing 1 letter at a time.
    
    tree.push_back(startWord);
    indexTree.push_back(pos);
    pos++;
    for (k=0; k < tree.size(); k++){
        if (print){
            cout << indexTree.at(k) << ". "<< tree.at(k) << ":   ";
        }
        for (i=0; i < startWord.length(); i++)
        {
            word = tree.at(k);
            for (j=0; j < ALPHABET.length(); j++)
            {
                word[i] = ALPHABET[j];
                if (binarySearch(word, dictionary) > -1 && word != startWord)
                {
                    if (!(checkVec(tree, word))){
                        if (word == endWord){
                            tree.push_back(word);
                            indexTree.push_back(pos);
                            if (print) {
                                cout << pos << ": "<< word << "\n\n Winning sequence was found!\n\n";
                            }
                            else {
                                cout << "Winning sequence was found!\n\n";
                            }
                            return;
                        }
                        else {
                            tree.push_back(word);
                            indexTree.push_back(pos);
                            if (print) {
                                cout << pos << ": "<< word << " ";
                            }
                            pos++;
                        }
                    }
                }
            }
        }
        if (print) {
            cout << endl;
        }
    }
    cout << "It is not possible to go from spherular to irksomely using the current dictionary.\n\n";
}
//-----------------------------------------------------------------------------------------------------
//Case-7
//-----------------------------------------------------------------------------------------------------
/*string sequence(string startWord, string endWord, vector<int> &tree, vector<string> &indexTree)
{
    string currentWord=endWord;
    bool print = true;
    while(print==true)
    {
        for(int i=tree.size()-1; i>-1; i--)
        {
            if(currentWord==tree.at(i))
            {
                cout<<i<<tree.at(i);
                currentWord=tree.at(indexTree.at(i));
            }
            if (currentWord==startWord)
            {
                print=false;
            }
        }
    }
    
}*/




int main()
{
    vector< string> dictionary;                    // Vector of dictionary words read in from file
    int lengthOfWordsToUse = 3;         // Default length of word to use in word transformation
    string startWord = "dog";           // The start word for transformation
    string endWord = "cat";             // The end word for transformation
    int menuOption = -1;                // User menu option selection
    int startNum, endNum;               // To display some words in menu option 2
    vector<string> endWords;            // Vector of enwords store the end values generated 
    int wordSize[15];
    vector<int> numChar;
    vector<int> tempNum;
    int totalWords = 0;
    vector<string> tree;                
    vector<int> indexTree;  
    
    
    // Display ID info
    displayIdInfo();
    
    // Read words in file
    readInWordsFromFile(lengthOfWordsToUse,dictionary,totalWords,numChar,tempNum);
    
     cout << "Total number of words in dictionary file: " << totalWords << endl;
    cout << endl;
    cout << "Word lengths where there are more than 1400 words:" << endl;
    
    cout << "Length  How Many\n------  --------\n";
    for (int i = 0; i < numChar.size(); i++) {
           cout << setw(5) << tempNum.at(i) << setw(10) << numChar.at(i) << endl;
    }
    cout << endl;
    
    // Seed the random number generator
    srand( 1);  // Change 1 to time(0) for non-predictable results, but leave as 1 for testing


    // Menu display and handling infinite loop
    do {
        cout << "Currently we have " << dictionary.size() << " words of length "
             << lengthOfWordsToUse << " in the dictionary.  \n"
             << "Changing from '" << startWord << "' to '" << endWord << "'" << endl
             << endl;
        
        cout << "Choose from the following options:\n"
             << "   1. Change the word length\n"
             << "   2. Display some dictionary words\n"
             << "   3. Get start and end words\n"
             << "   4. Play the word change game\n"
             << "   5. Find the end word with debug\n"
             << "   6. Find the end word\n"
             << "   7. Display an answer sequence\n"
             << "   8. Exit the program\n"
             << "Your choice -> ";
        cin >> menuOption;
        cout<<endl;
        
        // Menu option handling should go here
                if(menuOption==8)
        {
          cout<<"Exiting the program"<<endl;
          exit(0); //breaking enclosing loop.  
        }
        else if(menuOption==1)
        {
         cout << "What length words do you want to use? ";
         cin >> lengthOfWordsToUse;
         startWord = "";
            endWord = "";
         dictionary.clear();
         readInWordsFromFile(lengthOfWordsToUse,dictionary,totalWords,numChar,tempNum);   
        }


        else if(menuOption==2)
        {
         cout<<"Enter the start and end index values of words to display: ";
         cin>> startNum >> endNum;
         cout<<endl;
         cout<<"About to display dictionary words from "<<startNum<<" to "<<endNum;
         cout<<endl;
         for(int i=startNum; i<=endNum; i++)
         {
             cout << "    " << i << " "<< (dictionary[i]) << endl;
         }
         cout<<endl;
        }
        else if(menuOption==3)
        {
            wordSelection(startWord,endWord,lengthOfWordsToUse,dictionary);
        }
        else if(menuOption==4)
        {
            playGame(startWord,endWord,lengthOfWordsToUse,dictionary);
        }
        else if(menuOption==5)
        {
            debug(startWord,endWord,lengthOfWordsToUse,dictionary,endWords, true, tree, indexTree);
        }
        else if(menuOption==6)
        {
            debug(startWord, endWord, lengthOfWordsToUse, dictionary, endWords, false, tree, indexTree);
        }
        else if(menuOption==7)
        {
            //sequence(startWord, endWord, tree, indexTree);
        }
        else
        {
          cout<<"Invalid menu option.  Please retry."<<endl;  
        }


    } while( true);
        
    return 0;
}//end main()
