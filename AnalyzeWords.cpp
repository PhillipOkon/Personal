/*Phillip Okon*/
//Code using threads to stimulataneously read words from a file and analyze them
#define _OPEN_THREADS
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
#include <pthread.h> 
 
void *avgLength(void *arg){
    std::ifstream myfile; 
    myfile.open("english_words.txt"); //Opens File stream
    std::string word; // Keeps track of current word being read from file
    int wordCount = 0; // Counter to show how many words are in the file
    int totalChar = 0; // Counter tracking the character length of all words in file
    int avgCharLength;

    while(myfile >> word){ // Loops until file has no more words to read
        totalChar += word.length(); 
        wordCount++;  
    }

    avgCharLength = totalChar / wordCount; //Takes combined length of all words in the file divides by word count to return the average length

    myfile.close(); // Close file stream
    std::cout << "Average length = " << avgCharLength << std::endl;
    return NULL;
 }

 void *lngLength (void *arg){
    std::ifstream myfile;
    myfile.open("english_words.txt"); //Opens File stream
    std::string word;
    int len;

    while(myfile >> word){
        if(len < word.length()){ // Conditional that checks if recorded word is shorter than the current read word
            len = word.length(); // If so replace recorded word length with current word length
        }
    }

    myfile.close(); //Closes Files stream
    std::cout << "Longest word's length = " << len << std::endl;
    return NULL;   
 }

void *mstFreq(void *arg){
    std::ifstream myfile;
    myfile.open("english_words.txt");
    std::string word;
    int count = 0; //Variable to track the frequency of characters
    int alphabet[26] = {0}; // Array holding frequency of characters
    int j; //Variable to adjust characters into a int since 'a' starts from one, we -'a' to get the index nummber for that char
    char myChar;

    while(getline(myfile, word)){ // Loops while it has words to read
        int size = word.length();    
        char str[size+1];
        strcpy(str, word.c_str());
        for(int i = 0; i < size; i++){ //Loops for the length of the word
            str[i] = tolower(str[i]); //changes the character to lowercase
            if ((str[i] >= 'a') && (str[i] <= 'z')){ //Checks if the character is between a and z 
                j = str[i] - 'a'; 
                alphabet[j]++;
            }
        }
    }

    for(int i = 0; i < 26; i++){
        if(count < alphabet[i]){
            count = alphabet[i];
            myChar = 'a' + i;
        }
    }

    myfile.close();
    std::cout << "Most frequent letter = " << myChar << std::endl;
    return NULL;
}

int main(int argc, char* argv[]){
    std::string input = argv[1];
    if(input != "english_words.txt"){
        std::cout << "Please enter english_words.txt to continue" << std::endl;
        return 1;
    }
    int ret;

    pthread_t th1, th2, th3;
    if (( ret = pthread_create(&th1, NULL, avgLength, &input)) != 0){
        std::cout << "Error creating thread: " << strerror(ret) << std:: endl;
        exit(1);
    }
    if (( ret = pthread_create(&th2, NULL, lngLength, &input)) != 0){
        std::cout << "Error creating thread: " << strerror(ret) << std:: endl;
        exit(1);
    }
    if (( ret = pthread_create(&th3, NULL, mstFreq, &input)) != 0){
        std::cout << "Error creating thread: " << strerror(ret) << std:: endl;
        exit(1);
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    
    return 0;
}
