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
    
    lettre.symb = c;
    
    if (lettre.symb < 'A' || lettre.symb > 'Z') {
        lettre.isTerminal = true;
    }
    else lettre.isTerminal = false;
    
    
}

void Symbole::setDefinition(struct etat e, int indice) {
    
    definition.resize(indice+1);
    
    definition[indice].push_back(e);
}

Symbole::Symbole() {
    
}

Symbole::Symbole(vector<vector<etat>> definition, etat lettre) {
    
    this->definition = definition;
    this->lettre = lettre;
}


etat Symbole::getLettre(){
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
    
    etat x = s.getLettre();
    vector<vector<etat>> afficheur = s.getDefinition();
    
    cout << x.symb << " = ";
    
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
    etat l;
    
    for (int i = 0; i < grammaire.size(); i++) {
        
        testeur = grammaire[i].getDefinition();
        l = grammaire[i].getLettre();
        
        for (int j=0; j < testeur.size(); j++) {
            if (testeur[j][0].symb == l.symb) {
              
                return true;
            }
        }
    }
    return false;
}




vector<Symbole> eliminationRecursiviteGauche(vector<Symbole> grammaire, bool recursivite){ //Work in progress
    
    if (recursivite == false) {
        
        return grammaire;
    }
    else {
        
        vector<Symbole> grammaireSansRecursivité;
        
        vector<vector<etat>> testeur;
        etat l, prime, hash;
        
        prime.isTerminal = true;
        prime.symb = '\'';;
        
        hash.isTerminal = true;
        hash.symb = '#';

        
        for (int i = 0; i < grammaire.size(); i++) {
            
            testeur = grammaire[i].getDefinition();
            l = grammaire[i].getLettre();
            
            for (int j=0; j < testeur.size(); j++) {
                
                if (testeur[j][0].symb == l.symb) {
                    
                    while ( testeur[j].size()) {
                        testeur[j].pop_back();
                    }
                    
                    
                    j++;
                    testeur[j].push_back(l); // On rajoute l'etat de base
                    
                    
                    testeur[j].push_back(prime); // + l'apostrophe à la fin de la definition
                    
                }
                    
                    
                    
                
                
            }
            
            grammaireSansRecursivité.push_back(*new Symbole(testeur, l));
        }
        
        return grammaireSansRecursivité;
    }
    
}









