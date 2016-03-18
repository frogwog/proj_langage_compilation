//
//  main.cpp
//  proj_langage_compilation
//
//  Created by Edouard Soares on 11/03/16.
//  Copyright © 2016 Edouard Soares. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "F8fonctions.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    vector<Symbole> symboles;
    
    ifstream fichier("/Users/Eddy/Desktop/test.txt", ios::in);
    
    if(fichier)
    {
        
        string ligne;
        
        
        while (! fichier.eof()) {
            
            getline(fichier, ligne);
            
            symboles.push_back(miseEnMemoire(ligne));
        }
        fichier.close();
    }
    else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    
    for (int i =0; i < symboles.size(); i++) {
        affichageSymbole(symboles[i]);
    }
    

    
    
    
    
    
    return 0;
}
