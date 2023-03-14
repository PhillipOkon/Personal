//Phillip OKon
// Code to read through a CSV file and reorganize data
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iterator>

struct films{ //Data type films which holds all variables of the input
    int year, length, popularity;
    std::string title, subject, actor, actress, director, awards, image;
};

struct compare{//Predicate function for sorting films
    inline bool operator() (const films& fil1, const films& fil2){
        return (fil1.popularity > fil2.popularity);
    }
};

struct findYr{//Predicate function for find earliest element of searched year
    int yr;
    findYr(int yr) : yr(yr){}
    bool operator()(const films& fil) const {
        return fil.year == yr;
    } 
};
//Function header

int accumulate(std::vector<films>);

//Main function

int main(){

    //Variables
    std::string line;
    int count = 0;

    std::ifstream file("film.csv.txt");
    std::ofstream ofile, ofile2;
    ofile.open("sorted.txt");

    std::vector <films> vec;
    std::vector <films>::iterator it;
    films fil;

    // Checks if the file is open

    if(file.is_open()){
        while(std::getline(file, line)){ // Reads until end of file
            std::stringstream str(line);
            while( count <= 9){ //Sorts each variable into data type then stores in a vector, since data is sorted
            if(str.peek() == ';'){
                str.ignore();
            }
            switch(count){
                case 0:
                    str >> fil.year;
                    break;
                case 1:
                    str >> fil.length;
                    break;
                case 2:
                    std::getline(str,fil.title,';');
                    break;
                case 3:
                    std::getline(str,fil.subject,';');
                    break;
                case 4:
                    std::getline(str,fil.actor,';');
                    break;
                case 5:
                    std::getline(str,fil.actress,';');
                    break;
                case 6:
                    std::getline(str,fil.director,';');
                    break;
                case 7:
                    str >> fil.popularity;
                    break;
                case 8:
                    std::getline(str,fil.awards,';');
                    break;
                case 9:
                    std::getline(str,fil.image,';');
                    break;
            }
            count ++;
            }
            vec.push_back(fil);
            count = 0;
        }
    }

    std::cout << "The total length of all movies: " << accumulate(vec) << std::endl;
    
    //Calls sort and sorts vector in descending order and prints into "sorted.txt"
    std::sort(vec.begin(),vec.end(),compare());

    for(int i =0; i < vec.size(); i++){
        ofile << vec[i].year << " " << vec[i].length << " " << vec[i].title << " " << vec[i].subject 
              << " " << vec[i].actor << " " << vec[i].actress << " " << vec[i].director 
              << " " << vec[i].popularity << " " << vec[i].awards << " " << vec[i].image <<std::endl;
    }

    //Asks for year you would like to find, takes console input and returns appropiate answer
    int yr;
    std::cout << "What year would you like to find ?" << std::endl;
    std:: cin >> yr;
    it = std::find_if(vec.begin(),vec.end(),findYr(yr));
    if(it!= vec.end()){
        std::cout << "First instance of " << yr << " is at element: " << (it - vec.begin())+1 << std::endl;

    }else{
        std::cout << "Year not found" << std::endl;
    }

    file.close();
    ofile.close();
    return 0;
}//End of main

//Accumulate - adds all movies lengths and returns a total
int accumulate(std::vector<films> vec){
    int total = 0;

    for(int i = 0; i < vec.size(); i++){
        total += vec[i].length;
    }

    return total;
}
