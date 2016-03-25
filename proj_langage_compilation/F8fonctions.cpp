//
//  fonctions.cpp
//  proj_langage_compilation
//
//  Created by Edouard Soares on 11/03/16.
//  Copyright © 2016 Edouard Soares. All rights reserved.
//

#include "F8fonctions.hpp"

//--------Fonctions de l'objet symbole-------------

void Symbole::setLettre(char c) {
    
    lettre = c;
}

void Symbole::setDefinition(struct etat e, int indice) {
    
    definition.resize(indice+1);
    
    definition[indice].push_back(e);
}


Symbole::Symbole() {
    
    
}


char Symbole::getLettre(){
    return lettre;
}


vector<vector<struct etat>> Symbole::getDefinition() {
    return definition;
}


//-------------------------------------------------------------


Symbole miseEnMemoire(string ligne) {
    
    int indice = 0;
    
    etat e;
    Symbole symbole = *new Symbole();
    
    for (int i = 0; i < ligne.size(); i++) {
        
        if (i == 0) {
            symbole.setLettre(ligne[i]);
        }
        
        else if (ligne[i] == ' ' && i != 1) {
            
            indice ++;
        }
        
        else if (ligne[i] != ' ') {
            
            e.symb = ligne[i];
            
            if (ligne[i] < 'A' || ligne[i] > 'Z') {
                e.isTerminal = true;
            }
            else e.isTerminal = false;
            
            symbole.setDefinition( e, indice);
        }
    }
    
    return symbole;
}


void affichageSymbole(Symbole s) {
    
    char x = s.getLettre();
    vector<vector<etat>> afficheur = s.getDefinition();
    
    cout << x << " = ";
    
    for (int i = 0; i < afficheur.size(); i++) {
        
        for (int j = 0; j < afficheur[i].size(); j++) {
            
            cout << afficheur[i][j].symb;
        }
        
        if (i < (afficheur.size() - 1) ) cout << " | ";
        else cout << endl;
        
        
    }
    
}



bool isGrammairerecursiveGauche(vector<Symbole> grammaire) {
    
    vector<vector<etat>> testeur;
    char l;
    
    for (int i = 0; i < grammaire.size(); i++) {
        
        testeur = grammaire[i].getDefinition();
        l = grammaire[i].getLettre();
        
        for (int j=0; j < testeur.size(); j++) {
            if (testeur[j][0].symb == l) {
                return true;
            }
        }
    }
    return false;
}






