#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void usage(const char *msg, char *progname) {
  printf("\n%s\n\n"
	 "usage : %s <file> \"<string>\"\n"
	 "  Avec <file> : le chemin du fichier à analyser\n"
     "  Et <string> : la chaine à tester entre \" \"\n"
	 , msg, progname);
}

bool existsFile (string& path) {
    if (FILE *file = fopen(path.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

int* search(string pathRead, string search){
    ifstream fileRead;                  // On ouvre le ficier en lecture
    string toFind = search;
    fileRead.open(pathRead);
    
    unsigned int sameChar=0;            // Nombre de caractère identique (on commence à zéro)
    int line=1;                         // Compteur de ligne (on commence à 1)
    int nbOcc = 0;                      // Nombre d'occurence de la chaine (on commence à zéro)
    vector<int> listeLine;              // Liste des lignes où il y a une occurence
    char c = fileRead.get();
    while(c != EOF){                     // Tant qu'on a pas parcouru tout le fichier
        if(sameChar == toFind.length()){ // Si le nombre de caractère identique
            nbOcc++;                       // est égal à la taille de la chaine,
            listeLine.push_back(line);     // alors on a trouvé une occurence
            sameChar=0;
        }
        if(c == '\n') line++;           // Test si fin de ligne
        if(toFind[sameChar] == c){      // Si le caractère est identique à celui de la chaine
            sameChar++;                 // on incrémente la taille du buffer identique
        } else {
            sameChar=0;                 // Sinon on le remet à zéro
        }
        c = fileRead.get();             // On prend le caractère suivant
    }

    int* tabLine = new int[nbOcc];
    tabLine[0] = nbOcc;

    for(unsigned int i=0;i<listeLine.size();i++){
        tabLine[i+1] = listeLine[i];
    }
    
    fileRead.close();
    return tabLine;
}

int main(int argc, char* argv[]){
    if(argc != 3) {
        usage("Mauvaise utilisation !", argv[0]);
        return 1;
    }
    
    string chaine = argv[2];
    string path = argv[1];

    if(!existsFile(path)) {
        usage("Fichier introuvable !", argv[0]);
        return 1;
    }

    int* line = search(path, chaine);
    cout<<"Il y a "<<line[0]<<" occurence(s) de la chaine \""<<chaine<<"\""<<endl;
    for(int i=1;i<=line[0];i++){
        cout<<"..at line "<<line[i]<<endl;
    }


}
