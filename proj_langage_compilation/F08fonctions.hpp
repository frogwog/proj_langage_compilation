//
//  fonctions.hpp
//  proj_langage_compilation
//
//  Created by Edouard Soares on 11/03/16.
//  Copyright © 2016 Edouard Soares. All rights reserved.
//

#ifndef F08fonctions_hpp
#define F08fonctions_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//------Classes et structures -----------

typedef struct etat {
    
    bool isTerminal;
    char symb;
    
}etat;


class Symbole {
    
    vector < vector<struct etat> > definition;
    etat lettre;
    
public:
    
    void setLettre(char c); // Définit la lettre d'un symbole
    void setDefinition(struct etat e, int indice); //Ajoute la définition possible pour un symbole
    
    
    etat getLettre();
    vector < vector<struct etat> > getDefinition();
    
    Symbole();
    Symbole(vector<vector<etat>> definition, etat lettre);
    
};




// ---------Fonctions-----------------

Symbole miseEnMemoire(string ligne);

void affichageSymbole(Symbole s);

bool isGrammairerecursiveGauche(vector<Symbole> grammaire);

vector<Symbole> eliminationRecursiviteGauche(vector<Symbole> grammaire, bool recursivite);

#endif /* fonctions_hpp */
