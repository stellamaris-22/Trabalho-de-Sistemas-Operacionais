#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

std::chrono::duration<double, std::milli> time_passed;

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
 * Executes product between two matrixes
 * @param A first matrix
 * @param B second matrix
 * @param alin number of lines in A
 * @param acbl number of A columns and B lines (must be equal so product will exist)
 * @param bcol number of B's columns
 * @return matrix that is equals to A*B.
 */
std::vector<std::vector<unsigned short>> MatProd(std::vector<std::vector<unsigned short>> A, 
                                      std::vector<std::vector<unsigned short>> B, 
                                      int alin, int acbl, int bcol){
    time_passed = time_passed - time_passed;
    auto start = std::chrono::steady_clock::now();
    std::vector<std::vector<unsigned short>> result;
    std::vector<unsigned short> row;
    for(auto i{0}; i<alin; ++i){
        row.clear();
        for(auto j{0}; j<bcol; ++j){
            unsigned short sum{0};
            for(auto k{0}; k<acbl; ++k){
                sum+=A[i][k]*B[k][j];
            }
            row.push_back(sum);
            //std::cout<<sum<<std::endl;
        }
        result.push_back(row);
    }
    auto end = std::chrono::steady_clock::now();
    time_passed += end-start;
    return result;
}

/*
 * Records the requested matrix in output file
 * @param mat the matrix to be printed in file
 */
void record(std::vector<std::vector<unsigned short>> mat, std::string file_name){
    std::ofstream file;
    file.open(file_name);
    /*if(!file.is_open()){ 
        std::cout<<"404 on record!\n";
        //abort
    }*/
    file << mat.size()<<' '<<mat[0].size()<<std::endl;
    //std::cout << mat.size()<<' '<<mat[0].size()<<std::endl;
    for(unsigned long long int i{0}; i<mat.size(); ++i){
        for(unsigned long long int j{0}; j<mat[i].size(); ++j){
            file <<'c'<<i+1<<','<<j+1<<' '<<mat[i][j]<<std::endl;
            //std::cout<<'c'<<i+1<<j+1<<' '<<mat[i][j]<<std::endl;
        }
    }
    file << time_passed.count();
    //std::cout<<time_passed.count();
}



int main(int argc, char* argv[]){
    if(argc<3){
        std::cout<<"You forgot the files!"<<std::endl;
        return 1;
    }
    std::vector<std::vector<unsigned short>> mat1{matrix_generator(argv[1])};
    std::vector<std::vector<unsigned short>> mat2{matrix_generator(argv[2])};
    for(auto i{0}; i<10; ++i){
        std::vector<std::vector<unsigned short>> matprod{MatProd(mat1, mat2, mat1.size(), mat1[0].size(), mat2[0].size())};
        std::string name{"src/result_test_"};
        name+=std::to_string(i+1);
        name+=".txt";
        record(matprod, name);
    }
    
    return 0;
}