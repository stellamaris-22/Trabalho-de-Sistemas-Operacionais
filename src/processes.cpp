#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

std::chrono::duration<double, std::milli> time_passed;
unsigned long long int n_elements, p_number;

/*
 *Tokenizes a string according to a character
 * @param line the string to be tokenized
 * @param token the character to tokenize the sring over
 * @return a vector with all strings formed
*/
std::vector<std::string> tokenizer(std::string line, char token=' '){
    std::vector<std::string> tokens;//keeps tokens
    std::string curr_token;//token we're reading
    for(auto i : line){//for each character in our string
        if(i!=token){//if it's not the separating token
            curr_token+=i;//adds character to current token
        } else {// if it is
            tokens.push_back(curr_token); //adds token to vector
            curr_token = "";//resets token
        }
    }
    tokens.push_back(curr_token);//adds last token
    return tokens;//returns all tokens' vector
}


/* Reads a file with all elements of a matrix and 
 * generates the described matrix.
 * @param f_name name of the file with requested matrix.
 * @return ready matrix.
*/
std::vector<std::vector<unsigned short>> matrix_generator(std::string f_name){
    std::fstream reader; //File where our matrix is
    reader.open(f_name); //Opens file
    if(!reader.is_open()){//If file wasn't found, generates error
//----->        //generate error here
        std::cout<<"Oop! 404\n";
    } 
    std::string line; //string where each line on file will be
    std::getline(reader, line); //reads first line in file (matrix's dimensions)
    std::vector<std::string> numbs{tokenizer(line)}; //Tokenizes each number
    p_number = ceil((std::stoi(numbs[0])*std::stoi(numbs[1]))/((float)(n_elements)));
    int n_lin{std::stoi(numbs[0])}, n_col{std::stoi(numbs[1])}; //Keeps matrix's dimensions
    std::vector<std::vector<unsigned short>> matrix(n_lin); //Initializes matrix with suitable number of lines
    
    
    for(auto i{0}; i<n_lin; ++i){//for each line in the matrix
        std::getline(reader, line); //reads the elements in that line
        numbs = tokenizer(line); //Tokenizes them (separates each element)
        for(auto j{0}; j<n_col; ++j){//for each column in the matrix
            matrix[i].push_back(std::stoi(numbs[j])); //adds read element to matrix
            //std::cout<<j<<std::endl;
        }
    }
    reader.close();
    return matrix; //returns the ready matrix
}


/*
 * Records the requested matrix in output file
 * @param mat the matrix to be printed in file
 */
void record(std::vector<std::vector<unsigned short>> mat, std::string file_name){
    std::fstream file;
    file.open(file_name);
    if(!file.is_open()){ 
        std::cout<<"404 on record!\n";
        //abort
    }
    file << mat.size()<<' '<<mat[0].size()<<std::endl;
    //std::cout << mat.size()<<' '<<mat[0].size()<<std::endl;
    for(unsigned long long int i{0}; i<mat.size(); ++i){
        for(unsigned long long int j{0}; j<mat[i].size(); ++j){
            file <<'c'<<i+1<<j+1<<' '<<mat[i][j]<<std::endl;
            //std::cout<<'c'<<i+1<<j+1<<' '<<mat[i][j]<<std::endl;
        }
    }
    file << time_passed.count();
}


//Calculates & records
void calculations(std::vector<std::vector<unsigned short>> A, std::vector<std::vector<unsigned short>> B, unsigned long long int idx, std::string file_name){
    time_passed = time_passed - time_passed;
    auto start = std::chrono::steady_clock::now();
    std::ofstream file;
    file.open(file_name);
    for(unsigned long long int j{0}; j<n_elements && idx<A.size()*B[0].size(); ++j, ++idx){
        unsigned short sum{0};
        for(auto k{0}; k<(int)A[0].size(); ++k){
            sum+=A[idx/A[0].size()][k]*B[k][idx%A[0].size()];
        }
        file <<'c'<<idx/A[0].size()+1<<','<<idx%A[0].size()+1<<' '<<sum<<std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    time_passed += end-start;
    //std::cout<<time_passed.count()<<' '<<getpid()<<std::endl;
    file << time_passed.count();
}

int main(int argc, char* argv[]){
    if(argc<4){
        std::cout<<"You forgot the files or P!"<<std::endl;
        return 1;
    }
    
    n_elements = std::stoi(argv[3]);
    std::vector<std::vector<unsigned short>> mat1{matrix_generator(argv[1])};
    std::vector<std::vector<unsigned short>> mat2{matrix_generator(argv[2])};
    pid_t pid{1};
    for(auto t{0}; t<5; ++t){
        for(unsigned long long int i{0}; i<p_number; ++i){ //this creates the number requested of processes
            if(pid != 0){
                //std::cout<<getpid()<<" if"<<std::endl;
                time_passed = time_passed - time_passed;
                std::string name{"src/result_test"};
                name+=std::to_string(t+1);
                name+="_process_";
                name+=std::to_string(i+1);
                name+=".txt";
                //start[i] = std::chrono::steady_clock::now();
                pid = fork();
                if(pid == 0){
                    
                    calculations(mat1, mat2, i*n_elements, name);
                }
            }
            else break;
        }
        for(unsigned long long int i{0}; i<p_number-1; ++i) wait(NULL);
    }
    return 0;
}