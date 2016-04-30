//
//  fonctions.cpp
//  proj_langage_compilation
//
//  Created by Edouard Soares on 11/03/16.
//  Copyright © 2016 Edouard Soares. All rights reserved.
//

#include "F08fonctions.hpp"

//--------Fonctions de l'objet symbole-------------

void Symbole::setLettre(char c) {
    
    lettre.symb[0] = c;
    lettre.symb[1] = '\0';
    
    if (lettre.symb[0] < 'A' || lettre.symb[0] > 'Z' || lettre.symb[0] != '#') {
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
        
        else if (ligne[i] == '|') {
            
            indice ++;
        }
        
        else if (ligne[i] != '|' && ligne[i] != '=') {
            
            e.symb[0] = ligne[i];
            e.symb[1] = '\0';
            
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
            if (testeur[j][0].symb[0] == l.symb[0]) {
              
                return true;
            }
        }
    }
    return false;
}




vector<Symbole> eliminationRecursiviteGauche(vector<Symbole> grammaire, bool recursivite){
    
    if (recursivite == false) {
        
        return grammaire;
    }
    else {
        
        
        int j;
        unsigned long taille;
        vector<Symbole> grammaireSansRecursivite;
        
        vector<vector<etat>> testeur, nouvelleDefinition;
        etat l, hash;
        
        bool isRecursif;
        
        hash.symb[0] = '#';
        hash.symb[1] = '\0';

        
        for (int i = 0; i < grammaire.size(); i++) {
            
            testeur = grammaire[i].getDefinition();
            l = grammaire[i].getLettre();
            nouvelleDefinition = testeur;
            taille = testeur.size();
            
            j = 0;
            isRecursif = false;
            
            
            while (j < testeur.size()){
                
                if (testeur[j][0].symb[0] == l.symb[0]) { // Si il y a récursivité à Gauche
                    
                    isRecursif = true;
                    l.symb[1] = '\''; // On crée la lettre X'
                    
                    while ( testeur[j].size()) { //On supprime la définition où il y a la récursivité à Gauche
                        testeur[j].pop_back();
                    }
                    testeur.erase(testeur.begin()+j);
                    
                }
                
                else {
                    
                    if (taille != testeur.size()) { //Si il y a bien eu récursivité à gauche d'un symbole, sa taille a été modifiée, donc on peut ajouter le X' à la fin de chaque définition restante
                        testeur[j].push_back(l);
                    }
                    j++;
                }
            }
            
            
            for (int k = 0 ; k < nouvelleDefinition.size(); k++) {
                
                
                if (nouvelleDefinition[k][0].symb[0] == l.symb[0]) { // On met en place le nouveau symbole X' en enlevant le X à gauche de ses définitions et en rajoutant X' à la fin
                    
                    nouvelleDefinition[k].erase(nouvelleDefinition[k].begin());
                    nouvelleDefinition[k].push_back(l);
                    
                }
                
                else { // On remplace les autres définitions par #
                    
                    nouvelleDefinition[k].erase(nouvelleDefinition[k].begin(), nouvelleDefinition[k].end());
                    nouvelleDefinition[k].push_back(hash);
                }
                
            }
            
            if (isRecursif) {
                
                grammaireSansRecursivite.push_back(*new Symbole(nouvelleDefinition, l));
            }
            
            grammaireSansRecursivite.push_back(*new Symbole(testeur, grammaire[i].getLettre())); //On modifie la définition de l'Etat
        }
        
        return grammaireSansRecursivite;
    }
    
}









