//
//  main.cpp
//  proj_langage_compilation
//
//  Created by Edouard Soares on 11/03/16.
//  Copyright © 2016 Edouard Soares. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "F08fonctions.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    vector<Symbole> grammaire;
    
    ifstream fichier("/Users/Eddy/Documents/Programming/XCode/proj_langage_compilation/proj_langage_compilation/test.txt", ios::in);
    
    if(fichier)
    {
        
        string ligne;
        
        
        while (! fichier.eof()) {
            
            getline(fichier, ligne);
            
            grammaire.push_back(miseEnMemoire(ligne));
        }
        fichier.close();
    }
    else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    
    for (int i =0; i < grammaire.size(); i++) {
        affichageSymbole(grammaire[i]);
    }
    
    bool test = isGrammairerecursiveGauche(grammaire);
    
    if (test) {
        cout << endl << "Récursivité détectée" << endl << endl;
        
        vector<Symbole> grammSansRec = eliminationRecursiviteGauche(grammaire);
        
        for (int i =0; i < grammSansRec.size(); i++) {
            affichageSymbole(grammSansRec[i]);
        }
    }
    
    else cout << endl << "Pas de récursivité détectée" << endl;
    
    
    cout << endl;
    

    return 0;
}
