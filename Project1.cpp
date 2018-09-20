/*
 * Project1.cpp
 * 
 * Name: Raiyan Chowdhury
 * EE312 Spring 2016
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent 
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

char misspelledWords[1000] = {0};//once this gets filled, a 0 will mark the end of the string

/***************************checkDictionary***********************************
This function goes through the dictionary, checking to see if the word passed
to it matches any word in the dictionary.
Inputs: array holding dictionary, array holding the word in question
Output: true/false value indicating whether or not the word was misspelled (true if misspelled, false if not)
*/

char checkDictionary(char dictionary[], char word[]){
    int dictionaryIdx;
    int wordIdx = 0;
    char misspelled = 1;
    //first make all letters in word lower-case to make case-insensitive matching less messy, and make the printing look nicer
    for(int i = 0; word[i] != 0; i++){
        if(word[i]>='A'&&word[i]<='Z'){
            word[i] += ('z'-'Z');
        }
    }

    for(dictionaryIdx = 0; dictionary[dictionaryIdx] != 0; dictionaryIdx++){
        if((word[wordIdx] == dictionary[dictionaryIdx]) || (word[wordIdx] == (dictionary[dictionaryIdx]+('z'-'Z')))) {
            if(dictionary[dictionaryIdx+1]=='\n' && word[wordIdx+1]==0){//this means letters have continued to match until the end of the word
                misspelled = 0;
                break;
            }
            else{
                wordIdx++;
            }
        }
        else{//if the letters don't match, reset the index of the word to start over
            wordIdx = 0;
            while(dictionary[dictionaryIdx] != '\n'){
                dictionaryIdx++;//move over to the next word in the dictionary if the index isn't there already
            }
        }
    }
    return misspelled;
}

/**********************************spellCheck**********************************
This function serves to correct the article. It finds all 
the words in the article and upon doing so calls checkDictionary to see if the spelling
is correct. If it isn't, it prints the word followed by a newline.
Inputs: article and dictionary arrays
Output: none
*/

void spellCheck(char article[], char dictionary[]){
    int articleIdx;
    char word[100] = {0};
    int wordIdx = 0;
    char letterCount = 0; //used to keep track of word length, since words must be 2+ letters long
    char newline = '\n';

    for(articleIdx = 0; article[articleIdx] != 0; articleIdx++){
        if((article[articleIdx]>='a' && article[articleIdx]<='z') || (article[articleIdx]>='A' && article[articleIdx]<='Z')){
            word[wordIdx] = article[articleIdx];
            wordIdx++;
            letterCount++;
        }
        else{
            if(letterCount==1){//if there was only 1 letter, then what got stored before wasn't a word, so we remove it
                wordIdx--;
                word[wordIdx] = 0;
                letterCount = 0;
            }
            else if(letterCount > 1){
                //if there's more than 1 letter, then we have a word, so we must check to see if it is misspelled

                if(checkDictionary(dictionary, word)){//returns true if misspelled
                    printf("%s", word);
                    printf("%c", newline);                    
                }
                letterCount = 0;
                wordIdx = 0;
                for(int i = 0; i<100; i++){//clear array to prepare for next word
                    word[i] = 0;
                }
            }
        }
    }

    //once the for loop has been terminated, we have to check letterCount one last time to see if we found one last word before reaching the end
    if(letterCount > 1){
        if(checkDictionary(dictionary, word)){//returns true if misspelled
            printf("%s", word);
            printf("%c", newline);
        }
    }
    return;
}