#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>
#include "boyer_moore.h"

extern "C"
{
#define ALPHABET_LEN 256
  
  void make_bad_character_table(int* bad_char, const char *motif)
  {
    int taille = strlen(motif);
    for (int i=0; i < ALPHABET_LEN; i++)
      {
	bad_char[i] = taille;
      }
    for (int i=0; i < taille - 1; i++)
      {
	bad_char[motif[i]] = taille - 1 - i;
      }
  }

  void make_good_suffix(int* good_suffix, const char *motif)
  {
    int taille_motif = strlen(motif);
    for(int i = 0; i<taille_motif; i++)
      {
	int debut_suffixe = taille_motif - 1 - i;
	int taille_suffixe = i + 1;
	int decalage = 1;
	int trouve = 0;
	
	while(decalage < taille_motif && !trouve)
	  {
	    if(debut_suffixe - decalage < 0)
	      {
		debut_suffixe++;
		taille_suffixe--;
		if(strncmp(&motif[debut_suffixe], &motif[debut_suffixe - decalage], taille_suffixe))
		  {
		    decalage++;
		  }
		else
		  {
		    trouve = 1;
		  }
	      }
	    else
	      {
		if(motif[debut_suffixe] == motif[debut_suffixe - decalage] ||
		   strncmp(&motif[debut_suffixe + 1], &motif[debut_suffixe - decalage + 1], taille_suffixe - 1))
		  {
		    decalage++;
		  }
		else
		  {
		    trouve = 1;
		  }
	      }
	  }
	good_suffix[i] = decalage;
      }
  }

  int boyer_moore_string(char *str, char *motif)
  {
    int taille_motif = strlen(motif);
    int taille_string = strlen(str);
    int bad_char[ALPHABET_LEN];
    int good_suffix[taille_motif];
    
    make_bad_character_table(bad_char, motif);
    make_good_suffix(good_suffix, motif);
    
    for (int i=0; i <taille_motif; i++) {
      printf("good_suffix[%i] = %i \n", i, good_suffix[i]);
    }
    
    if (taille_motif == 0)
      {
	return 0;
      }

    int i = taille_motif - 1;
    while (i < taille_string)
      {
	int j = taille_motif - 1; 
	int debut = i;
	while (j >= 0 && (str[i] == motif[j]))
	  {
	    printf("%c == %c\n", str[i], motif[j]);
	    --i;
	    --j;
	  }
	printf("%c == %c\n", str[i], motif[j]);
	printf("str = %s \n", &str[i+1]);
	if (j < 0)
	  {
	    return i+1;
	  }
	
	int shift = 0;
	if(bad_char[str[debut]] > good_suffix[taille_motif - j - 1])
	  {
	    shift = bad_char[str[debut]];
	  }
	else
	  {
	    shift = good_suffix[taille_motif - j - 1];
	  }
	
	printf("taille_motif - j = %i, j = %i, bad_char = %i, good_suffix = %i, shift = %i\n",
	       taille_motif - j, j, bad_char[str[debut]], good_suffix[taille_motif - j - 1], shift);

	i = debut + shift;

	printf("i = %i\n", i);
      }
    return -1;
  }

  void boyer_moore_fichier(const char *fichier, const char *motif, int *tab_occu)
  {
    int nb_occu = 0;
    tab_occu[0] = nb_occu;
    
    int c;
    FILE *file;
    file = fopen(fichier, "r");
    int taille_fichier = 0;
    if (file)
      {
	while ((c = getc(file)) != EOF)
	  taille_fichier++;
	fclose(file);
      }

    char *str = (char*)malloc(sizeof(char) * taille_fichier);//A modifier
    file = fopen(fichier, "r");
    if (file)
      {
	int i = 0;
	while ((c = getc(file)) != EOF)
	  {
	    str[i] = c;
	    i++;
	  }
	fclose(file);
      }
    
    int taille_motif = strlen(motif);
    int taille_string = strlen(str);
    int bad_char[ALPHABET_LEN];
    int good_suffix[taille_motif];
    
    make_bad_character_table(bad_char, motif);
    make_good_suffix(good_suffix, motif);
    
    /*for (int i=0; i <taille_motif; i++) {
      printf("table2[%i] = %i \n", i, good_suffix[i]);
      }*/
    
    if (taille_motif == 0)
      {
	tab_occu[0] = nb_occu;
	return;
      }

    int i = taille_motif - 1;
    while (i < taille_string)
      {
	int j = taille_motif - 1; 
	int debut = i;
	while (j >= 0 && (str[i] == motif[j]))
	  {
	    //printf("%c == %c\n", str[i], motif[j]);
	    --i;
	    --j;
	  }
	//printf("%c == %c\n", str[i], motif[j]);
	//printf("str = %s \n", &str[i+1]);
	if (j < 0)
	  {
	    nb_occu++;
	    tab_occu[nb_occu] = i+1; 
	  }
	
	int shift = 0;
	if(bad_char[str[debut]] > good_suffix[taille_motif - j - 1])
	  {
	    shift = bad_char[str[debut]];
	  }
	else
	  {
	    shift = good_suffix[taille_motif - j - 1];
	  }
	
	//printf("patlen - j = %i, j = %i, delta1 = %i, delta2 = %i, shift = %i\n",
	//     taille_motif - j, j, bad_char[str[debut]], good_suffix[taille_motif - j - 1], shift);

	i = debut + shift;

	//printf("i = %i\n", i);
      }

    tab_occu[0] = nb_occu;
  }
}

int* searchBM(std::string pathRead, std::string search)
{
  int* tabIndice = new int[5000]; //A modifier
  boyer_moore_fichier(pathRead.c_str(), search.c_str(), tabIndice);

  return tabIndice;
}
