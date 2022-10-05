#include <iostream> 
#include <vector> 
#include <fstream> 
#include <sstream>
#include <stdlib.h>
#include <time.h>


int main(int argc, char ** argv){
   
    std::ofstream write, matix; 
    std::string new_file_name(argv[5]); 
    std::string new_file_name_dois(argv[6]);  
    write.open(new_file_name);
    
/*
    for(auto i{1}; i < argc; ++i){
       std::cout<< argv[i]<< "\n"; 
    } */

    int m_um, n_um, m_dois, n_dois; 

    m_um = std::stoi(argv[1]); 
    n_um = std::stoi(argv[2]);
    m_dois = std::stoi(argv[3]);
    n_dois = std::stoi(argv[4]); 

    std::vector<std::vector<unsigned long long int>> M1(m_um);
    std::vector<std::vector<unsigned long long int>> M2(m_dois);

     
    //matrix(m_um); 

    write << m_um << " " << n_um<< std::endl;
 
   
    srand(time(NULL));
    for(auto i{0}; i < m_um; ++i){
        for(auto j{0}; j < n_um; ++j){
            
            //std::cout << "FOI AQUI?????" << std::endl;
            M1[i].push_back(rand()%100); 
            //std::cout<< M1[i][j] << std::endl;  
            write << M1[i][j] << " "; 
        }
        write << std::endl;
    }  

    write.close(); 

    matix.open(new_file_name_dois);
    matix << m_dois<< " " << n_dois <<std::endl; 
    srand(time(NULL));
    for(auto i{0}; i < m_dois; ++i){
        for(auto j{0}; j < n_dois; ++j){
            
            //std::cout << "FOI AQUI?????" << std::endl;
            M2[i].push_back(rand()%100); 
            //std::cout<< M2[i][j] << std::endl; 
            matix << M2[i][j]<<" "; 

        }
        matix << std::endl; 
    } 
    matix.close(); 

}