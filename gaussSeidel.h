#ifndef GAUSSSEIDEL_H
#define GAUSSSEIDEL_H

#include "gaussJordan.h"

bool Sassenfeld(const vector<double>& seidel, const vector<double>& antSeidel, int t){
    double Beta = 0.0;
    for (int i = 0; i < t; ++i) {
        double erro = abs(seidel[i] - antSeidel[i]) / abs(seidel[i]);
        if (erro > Beta) {
            Beta = erro;
        }
    }
    return Beta;
}

vector<double> gaussSeinel(const vector<vector<double>> &seidel, int t, double k, double ep){
    vector<double> a(t, 0.0); // Vetor de solução inicial

    for (int in = 0; in < k; ++in) {
        vector<double> antSeidel = a;

        for (int i = 0; i < t; ++i) {
            double s1 = 0.0;
            double s2 = 0.0;

            for (int j = 0; j < i; ++j) {
                s1 += seidel[i][j] * a[j];
            }

            for (int j = i + 1; j < t; ++j) {
                s2 += seidel[i][j] * antSeidel[j];
            }

            a[i] = (seidel[i][t] - s1 - s2) / seidel[i][i];
        }

        double erro = Sassenfeld(a, antSeidel, t);

        cout << "Iteracao " << in + 1 << ": " <<endl;
        for (int i = 0; i < t; ++i) {
            cout << "a" << i << " = " << a[i] << " "<<endl;
        }
        cout << "Erro relativo = " << erro << endl;

        if (erro < ep) {
            break;
        }
    }

    return a;
}


void preencheSeidel(){//insere os valores na matriz
    ifstream file("C:\\Users\\henri\\OneDrive\\Documentos\\Prat 2\\Gauss_Jordan_seidel\\seidel.txt");
    
    while (file)
    {
        int t;
        if (!( file >> t))
            break;
        
        vector<vector<double>> seidel(t, vector<double>(t+1, 0));
        for (int i = 0; i < t; i++){
            for (int j = 0; j < t; j++)
            {
                file >> seidel[i][j];//le termos da matriz
            }
        }

        // termo independente
        for (int i = 0; i < t; i++)
            file >> seidel[i][t];

        cout << "\n_______________________________________________________________\n[A | b]: "<<endl;
        mostra(seidel, t);

            double k, ep;
            file >> k;
            file >> ep;

            vector<double> S = gaussSeinel(seidel, t, k, ep);
            cout << "\n[A' | b']: "<<endl;
            mostra(seidel, t);

            cout << "\n_______________________________________________________________\nMax = {(";
            for (int i = 0; i < S.size(); ++i) {
                    cout << "x" << i << " = " << S[i] << endl;
            }
            
            getchar();
            getchar();
        
                
    }
    file.close();
}

#endif 