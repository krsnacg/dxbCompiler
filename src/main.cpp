#include "Lexer.hpp"
#include "LL1Parser.hpp"


int main(){
    /*
    Lexer l("../src/test.txt");
    int comp = 0;
    std::cout<<"\nbuffer\ttoken\n";

    while((comp != 1 )&&( comp != -1)){
        comp = l.AFD_MAIN();
    }*/

    LL1Parser P("../src/test.txt");

    if(!P.Parse())
        std::cout<<"El programa finalizó con exito.";
    else
        std::cout<<"El programa finalizó con errores.";

    return 0;
}