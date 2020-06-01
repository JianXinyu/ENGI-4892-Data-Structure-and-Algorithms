#include "Expression.h"
#include <iostream>

using namespace std;
using namespace calc;

int main(){
        if((Expression::Parse("3.1415926"))->evaluate() - 3.1415926 < 0.01){
            cout<< "Pass test 1"<<endl;
        }

        if((Expression::Parse("12 +123"))->evaluate() == (12 + 123)){
                cout<< "Pass test 2"<<endl;
        }

        if((Expression::Parse("1 + 1.2 +34"))->evaluate() - (1 + 1.2 +34) < 000.1){
                cout<< "Pass test 3"<<endl;
        }
        if((Expression::Parse("1 + 3*4"))->evaluate() == (1+3*4)){
            cout<< "Pass test 4"<<endl;
        }
}