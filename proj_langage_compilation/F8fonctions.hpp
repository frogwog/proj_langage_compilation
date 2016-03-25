//
//  fonctions.hpp
//  proj_langage_compilation
//
//  Created by Edouard Soares on 11/03/16.
//  Copyright © 2016 Edouard Soares. All rights reserved.
//

#ifndef F8fonctions_hpp
#define F8fonctions_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//------Classes et structures -----------

class Symbole {
    
    vector < vector<struct etat> > definition;
    char lettre;
    
public:
    
    void setLettre(char c); // Définit la lettre d'un symbole
    void setDefinition(struct etat e, int indice); //Ajoute la définition possible pour un symbole
    
    
    char getLettre();
     vector < vector<struct etat> > getDefinition();
    
    Symbole();
    
};


typedef struct etat {
    
    bool isTerminal;
    char symb;
    
}etat;

// ---------Fonctions-----------------

Symbole miseEnMemoire(string ligne);

void affichageSymbole(Symbole s);

bool isGrammairerecursiveGauche(vector<Symbole> grammaire);

#endif /* fonctions_hpp */
