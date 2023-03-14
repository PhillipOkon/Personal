//Phillip Okon
//Sorts through a csv file and stores data in a nested vector
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>
#include <iomanip>

int main(){
    std::string line, word, t,fname = "ex9csv.txt";
    //Line = current read line, word = current word being read, fname = file name

    std::vector <std::vector<std::string>> words;
    std::vector <std::string> row;
    // words = holds a vector that contains strings which are the words read in 

    std::ifstream file(fname);
    std::ofstream ofile("ex9output.txt");
    //Open file by the name included and creates a output file by the given name

    std::stringstream obj; 
    double tmp, avg = 0, mavg = 0, wavg = 0;
    //tmp = placeholder, avg = average, mavg = moving average, wavg = weighted average
    
    if(file.is_open()){ 
    //Checks if the file is present

        while(std::getline(file, line)){
            // Will read from input file while it has lines to read

            row.clear();
            //Removes all elements to add new vector to the nested vector

            std::stringstream str(line);
            //Holds current line

            while(std::getline(str, word, ',')){
                //Removes commas from the CSV file and inputs each element in the vector 
                row.push_back(word);
            }
            words.push_back(row);
            //Adds newly created vector to the base vector
        }

        char w [line.length() +1];
        char* ptr;
        //Char array to hold vector strings so they can be converted to a double

        for(int i = 1; i < words.size(); i ++){
            for(int j = 1; j == 1; j++){

                strcpy(w, words[i][j].c_str()); 
                tmp = strtod(w, &ptr);
                avg += tmp;
                // Goes through temperatures and adds them together where it will be divided by the total number of months later

                if (i > 2){
                //Checks if there are atleast 3 months to get a moving and weighted average

                    for(int k = 0; k < 3 ; k ++){
                        strcpy(w, words[i-k][j].c_str()); 
                        tmp = strtod(w, &ptr);
                        mavg += tmp;
                    }
                    word = std::to_string(mavg/3);
                    words[i].push_back(word);
                    mavg = 0;
                    //This will add the average of 3 months and add the average as a string back to the vector

                    int weight = 3; 
                    //Variable for the weight of the month
                    for(int k = 0; k < 3 ; k ++){
                        strcpy(w, words[i-k][j].c_str()); 
                        tmp = strtod(w, &ptr);
                        wavg += (tmp*weight);
                        weight --;
                    }
                    word = std::to_string(wavg/6);
                    words[i].push_back(word);
                    wavg = 0;
                    //This will add the average of 3 months times their weight and add the average as a string back to the vector
                }
            }
        }
        ofile << std::fixed;
        ofile << std::setprecision(2);
        ofile << std::left << std::setw(10) << "Month"
              << std::left << std::setw(10) << "Temp (F)"
              << std::left << std::setw(10) << "M Avg"
              << std::left << std:: setw(10) << "W Avg" << std::endl;

        //Adds a header for the table to the output file

        for(int i = 1; i < words.size(); i++){
            for(int j = 0; j < words[i].size(); j++){
                ofile << std::left << std::setw(10) << words[i][j];
            }
        ofile << std::endl;
        }
        //Prints every element of the nested vectors

        ofile << std::endl << "The average across all months is " << avg/(words.size() -1) << std::endl;

        ofile.close();
        file.close();
        //Closes input and output files
    }
    else{
        std::cout << "No such file present" << std::endl;
        //Prints a message telling the user that it can't find input file
    }
    return 0;
}