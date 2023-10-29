#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H

#define tam 100

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void mostra(vector<vector<double>> &jordan, int t){
    for (int i = 0; i < t; i++){
        for (int j = 0; j < t; j++)
            cout << jordan[i][j] << "\t";

        cout << " | " << jordan[i][t] << "\t"<<endl;
    }
}

void pivotamento(std::vector<std::vector<double>> &s, int &h, int &i, int &t) {
    double aux = 0;
    for (int a = i; a < h; a++) {
        if (fabs(s[a][i]) > aux) { 
            aux = fabs(s[a][i]); 
            t = a;
        }
    }

    if (t != i) {
        for (int j = 0; j <= h; j++) {
            aux = s[i][j];
            s[i][j] = s[t][j];
            s[t][j] = aux;
        }
    }
}

void outputJordan(vector<vector<double>> &jordan, int t, bool inf, bool nan){
    //termo independente
    cout << "\n_______________________________________________________________\nS = {(";
    if (nan)
    {
        cout << "SPI ";
    }else if (inf){
        cout << "SI ";
    }else{
        for (int i = 0; i < t; i++) {
            if (abs(jordan[i][t]) < 1e-10)
                jordan[i][t] = 0;

            cout << " " << jordan[i][t] << " ";
            if (i < t - 1) {
                cout << " ;";
            }
        }
    }
    
    cout << " )}\n" << endl;
}

void gaussJordan(vector<vector<double>> &jordan, int t) {
    for (int j = 0; j < t; j++) {
        int aPIV = j;
        pivotamento(jordan, t, j, aPIV);
        double piv = jordan[j][j];
        // Divisão da linha pelo pivô
        for (int a = 0; a < t; a++) {
            jordan[j][a] /= piv;
        }
        
        jordan[j][t] /= piv; //divisão do termo indepedente
        // Redução as outras linhas
        for (int i = 0; i < t; i++) {
            if (i != j) {
                double aux = jordan[i][j];
                for (int b = 0; b < t; b++) {
                    jordan[i][b] -= aux * jordan[j][b];
                }
                jordan[i][t] -= aux * jordan[j][t];// Redução do termo independente das outras linhas
            }
        }                
        cout << "\nPivotamento da matriz" <<endl;
        mostra(jordan, t);
    }
} 

void preencheJordan(){//insere os valores na matriz
    ifstream file("C:\\Users\\henri\\OneDrive\\Documentos\\Prat 2\\jordan.txt");
    while (file){
        int t;
        if (!( file >> t))
            break;
        
        vector<vector<double>> jordan(t, vector<double>(t+1, 0));

        for (int i = 0; i < t; i++){
            for (int j = 0; j < t; j++)
                file >> jordan[i][j];//le termos da matriz
        }

        // termo independente
        for (int i = 0; i < t; i++)
            file >> jordan[i][t];

        cout << "\n_______________________________________________________________\n[A | b]: "<<endl;
        mostra(jordan, t);
        system("pause");

        gaussJordan(jordan, t);

        bool inf = false;
        bool nan = false;
        for (int i = 0; i < t; i++) {
            if (isnan(jordan[i][t])){
                nan=true;
            }
            else if (isinf(jordan[i][t])){
                inf = true;
                break;
            }
            else{
                cout << " " << jordan[i][t] << " ";
                if (i < t - 1) {
                    cout << " ;";
                }
            }
        }

        cout << "\n[A' | b']: "<<endl;
        mostra(jordan, t);
        outputJordan(jordan, t, inf, nan);

        getchar();
        getchar();
    }
    file.close();
}

#endif