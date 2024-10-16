#ifndef LL1PARSER_HPP
#define LL1PARSER_HPP
#include "LL1TAS.hpp"
#include "Lexer.hpp"
#include "Tabla.hpp"
#include <iomanip>
class LL1Parser
{
private:
    Tabla TS[100];
    LL1TAS T;
    Lexer L;
    std::vector<int> stack;
    int exit_code = 0;
    int error(int code){
        switch (code)
        {
        case 1:std::cout<<"\nError de sintaxis"<<std::endl;
            break;
        case 2:
            std::cout<<"\nError de redeclaracion"<<std::endl;
            //return 1;
            break;
        case 3:
            std::cout<<"\nError de tipo. No existe conversion."<<std::endl;
            //return 1;
            break;
        case 4:
            std::cout<<"\nError identificador no declarado"<<std::endl;
            //return 1;
            break;
        }
        return 1;
    }
    int error(int code,atributo t,atributo c){
        switch (code)
        {
        case 1:std::cout<<"\nError de sintaxis"<<std::endl;
            break;
        case 2:
            std::cout<<"\nError de redeclaracion"<<std::endl;
            //return 1;
            break;
        case 3:
            std::cout<<"\nError de tipo. No existe conversion de "<<symbol(c.tipo)<< " a "<<symbol(t.tipo)<<"."<<std::endl;
            //return 1;
            break;
        case 4:
            std::cout<<"\nError identificador no declarado"<<std::endl;
            //return 1;
            break;
        }
        return 1;
    }
public:
    LL1Parser(std::string);
    lexeme getToken();
    int Parse();
    void printStack();
    std::string symbol(int);
    void entrada(int);
    bool comprobarTipo(atributo,atributo);
    bool buscarRedecl(int,std::string);
    float calcularValor(int,std::string,std::string);
    int calcularTipo(int,int);
};

#endif