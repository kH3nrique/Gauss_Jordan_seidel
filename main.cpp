#include "gaussJordan.h"
#include "gaussSeidel.h"

int main(){
    int op = 3;
    while (op != 0){
        cout <<"1 - Jordan\n2 - Seidel"<<endl;
            cin >> op;
        if (op == 1)
            preencheJordan();
            else if (op == 2)
                preencheSeidel();
        
        getchar();
        getchar();
    }
    return 0;
}