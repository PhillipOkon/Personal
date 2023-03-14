#include <vector> 
#include <pthread.h>
#include <iostream>
#include <unistd.h>

//Variable grandTotal is a global var that tracks the added sum of all members in the vector
//Varaible count tracks which element pos we are in the vector
int grandTotal, count, n = 5; 

void *calculateSum(void *args){
    int timer = 0;
    std::vector<int>* vec = (std::vector<int>*) args;
    while(timer < 200){
        int temp = grandTotal + vec->at(count);
        usleep(200);
        grandTotal = temp;
        count ++;
        timer ++;
    }

    return NULL;
}


int main(){
    //Creates vector that holds 1000 ints
    std::vector <int> vec(1000, 0);

    //FIlls vector with ints from 1-1000 in ascending order
    for(int i = 0; i < vec.size(); i++){
        vec.at(i) = i+1;
    }

    //Creates 5 threads and runs it through method "calculateSum" if there is a error
    //it prints a error message and exits program
    int ret;
    pthread_t thread[n];

    for(int id = 1; id <= n; id++){
        ret = pthread_create(&thread[id], NULL, calculateSum, &vec);

        if(ret!=0){
            std::cout << "Error creating thread: " << ret << std:: endl;
            exit(EXIT_FAILURE);
        }
    }

    //Joins all existing threads
    for(int id = 1; id <= n; id++){
        pthread_join(thread[id], NULL);
    }


    std::cout << "Grand Total: " << grandTotal << std::endl;

    return 0;

}