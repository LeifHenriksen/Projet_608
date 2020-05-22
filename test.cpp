#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <stdlib.h>
#include "naive.h"
#include "boyer_moore.h"
using namespace std;
using namespace std::chrono; 


void usage(const char *msg, char *progname) {
  printf("\n%s\n\n"
	 "usage : %s <fct> <n> <file> \"<string>\"\n"
	 "  Avec <fct> parmis:\n"
   "    - naive\n"
   "    - boyermoore\n"
   "  Et <n> : le nombre de test\n"
   "  Et <file> : le chemin du fichier à analyser\n"
   "  Et <string> : la chaine à tester entre \" \"\n"
	 , msg, progname);
}

bool existsFile(string& path) {
    if (FILE *file = fopen(path.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

typedef unsigned int (*sec_fct_t)(unsigned int);
typedef unsigned int (*secg_fct_t)(unsigned int, unsigned int);

int main(int argc, char* argv[]){
    if(argc != 5) {
        usage("Mauvaise utilisation !", argv[0]);
        return 1;
    }
    
    string chaine = argv[4];
    string path = argv[3];
    int nbTest = atoi(argv[2]);
    string fct = argv[1];

    int* line;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();

    if(!existsFile(path)) {
        usage("Fichier introuvable !", argv[0]);
        return 1;
    }

    if(nbTest<=0){
      usage("Le nombre de test doit être supérieur à zéro !", argv[0]);
      return 1;
    }

    if(fct == "naive"){
      cout<<"Utilisation de l'algo naïf"<<endl;
      cout<<"=================================="<<endl;
      start = high_resolution_clock::now();
      for(int i=0;i<nbTest;i++){
        line = searchN(path, chaine);
      }
      stop = high_resolution_clock::now(); 
    } else if (fct == "boyermoore"){
      cout<<"Utilisation de l'algo de Boyer Moore"<<endl;
      cout<<"=================================="<<endl;
      start = high_resolution_clock::now();
      for(int i=0;i<nbTest;i++){
        line = searchBM(path, chaine);
      } 
      stop = high_resolution_clock::now(); 
    } else {
      usage("Fonction/Algorithme incorrect !", argv[0]);
      return 1;
    }

    
    
    cout<<"Il y a "<<line[0]<<" occurence(s) de la chaine \""<<chaine<<"\""<<endl;
    for(int i=1;i<=line[0];i++){
        cout<<"..at line "<<line[i]<<endl;
    }

    auto duration = duration_cast<microseconds>(stop - start); 
    cout<<endl;
    cout<<"=================================="<<endl;
    cout<<"Temps d'execution : "<<duration.count()<<"nano-secondes."<<endl; 
}
