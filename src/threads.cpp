#include <iostream> 
#include <vector> 
#include <fstream> 
#include <sstream>
#include <stdlib.h>
#include <time.h> 
#include <pthread.h> 
#include <chrono>
#include <math.h>
#include <thread>


std::chrono::duration<double, std::milli> time_passed;
unsigned long long int P, p_number;


struct Argumento{
    std::vector<std::vector<unsigned short>> A;
    std::vector<std::vector<unsigned short>> B;
    unsigned long long int idx;
    std::string file_name; 
};


std::vector<std::string> split(const std::string & input_str, char delimiter=' '){
    // Store the tokens.
    std::vector<std::string> tokens;
    // read tokens from a string buffer.
    std::istringstream iss;
    iss.str(input_str);
    // This will hold a single token temporarily.
    std::string token;
    while (std::getline(iss >> std::ws, token, delimiter))
        tokens.emplace_back(token);
    return tokens;
}

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

void* calculations(void* arg){
    time_passed = time_passed - time_passed;
    auto start = std::chrono::steady_clock::now();

    Argumento args{*((Argumento *) arg)};

    std::ofstream file;
    

    file.open(args.file_name);
    
    //std::cout<<args.file_name<<std::endl;
    //std::cout<<P<<std::endl;
    for(unsigned long long  j{0}; j<P && args.idx<args.A.size()*args.B[0].size(); ++j, ++args.idx){
        unsigned short sum{0};
        //+std::cout<<"Sum was resetted!"<<std::endl;
        for(unsigned long int k{0}; k<(unsigned long long int)args.A[0].size(); ++k){

            sum+=args.A[(unsigned long long int)args.idx/(unsigned long long int)args.A[0].size()][k]*args.B[k][(unsigned long long int)args.idx%(unsigned long long int)args.A[0].size()];

        }
        
        //std::cout<<"Sum is about to be recorded as:\n"<<'c'<<(unsigned long long int)args.idx/(unsigned long long int)args.A[0].size()+1<<','<<(unsigned long long int)args.idx%(unsigned long long int)args.A[0].size()+1<<' '<<sum<<std::endl;
        file <<'c'<<(unsigned long long int)args.idx/(unsigned long long int)args.A[0].size()+1<<','<<(unsigned long long int)args.idx%(unsigned long long int)args.A[0].size()+1<<' '<<sum<<std::endl;
    }
    
    auto end = std::chrono::steady_clock::now();
    time_passed += end-start;

    file << time_passed.count();
    //std::cout<<time_passed.count()<<std::endl;

    file.close();
    pthread_exit(NULL);
}


int main (int argc, char* argv[]){
    //std::cout << "O B.O É AQUI????" << std::endl;
    P = std::stoi(argv[3]);

    std::ifstream Mum, Mdois;
    std::string fileMum(argv[1]);
    std::string fileMdois(argv[2]);
    std::string tamanho, tamanhod; 
    std::string linha, linhad;
    std::vector<std::string> infosMatriz; 
    std::vector<std::string> infosSmatriz;
    std::vector<std::string> matrizUm; 
    std::vector<std::string> matrizDois; 
    
    Mum.open(fileMum);
    std::getline(Mum, tamanho); 

    infosMatriz = split(tamanho); 

    std::vector<std::vector<unsigned short>> M1 (std::stoi(infosMatriz[0])); 
   
    //std::cout << infosMatriz[0] << std::endl;
    //std::cout << "E AI FILHO???" << std::endl;
    
    for(int i{0}; i < std::stoi(infosMatriz[0]); ++i){

        std::getline(Mum, linha);

        matrizUm = split(linha);
        
        for(unsigned long int j{0}; j < matrizUm.size(); ++j){
            M1[i].push_back(std::stoi(matrizUm[j]));
        }
        
    } 

    //std::cout << "AQUI???" << std::endl;
/*
    for(unsigned long int i{0}; i < M1.size(); ++i){
        
        std::cout << "O B.O É AQUI????" << std::endl; 
        std::cout << M1[i][0] << std::endl; 
    
    }
*/time_passed = time_passed - time_passed;
    Mum.close();

    std::vector<std::vector<unsigned short>> matrizResultado (std::stoi(infosMatriz[0]));

    //std::cout << "O tamanho da matriz 1 é : " << tamanho<< std::endl; 
    //std::cout << fileMdois <<std::endl;

    Mdois.open(fileMdois);
    std::getline(Mdois, tamanhod);

    infosSmatriz = split(tamanhod);

    //std::cout << infosSmatriz[0] <<std::endl;

    std::vector<std::vector<unsigned short>> M2 (std::stoi(infosSmatriz[0])); 

    //std::cout << infosSmatriz[0] <<std::endl;

    for(int i{0}; i < std::stoi(infosSmatriz[0]); ++i){
        std::getline(Mdois, linhad);
        matrizDois = split(linhad);
        
        for(unsigned long int j{0}; j < matrizDois.size(); ++j){
            M2[i].push_back(std::stoi(matrizDois[j]));
        }
        
    } 
    Mdois.close(); 
    p_number = ceil((std::stoi(infosMatriz[0])*std::stoi(infosSmatriz[1]))/((float)(P)));

    //pthread_t thread[p_number];
    //int error;

    Argumento arg; 
    arg.A = M1; 
    arg.B = M2;

    //std::cout<<"To aqui?"<<std::endl;
    for(auto t{0}; t<5; ++t){
        for(unsigned long long int i{0}; i<p_number; ++i){ //this creates the number requested of threads
            arg.idx = i*P;

            //std::cout<<"Struct montada!"<<std::endl;

            

            std::string name{"src/result_test"};
            name+=std::to_string(t+1);
            name+="_thread_";
            name+=std::to_string(i+1);
            name+=".txt";

            arg.file_name = name;

            //std::cout<<i<<" thread sent to calculate"<<std::endl;

            std::thread function (calculations, (void*)(Argumento*) &arg);
            function.join();
        }
    }
    return 0;
}
     