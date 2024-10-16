#ifndef TABLA_HPP
#define TABLA_HPP
#include <iostream>

struct atributo
{
    int tipo;
    std::string lex;
    std::string valor;
};

struct atrib_n
{
    int tipo;
    std::string lex;
    int valor1;
    std::string valor2;
};

class Tabla
{
private:
    int token;
    std::string lex;
    int type;
    std::string val;
public:
    void Reg(int t, std::string l, int ty, std::string v){
        token = t;
        lex = l;
        type = ty;
        this->val = v;
    }
    void update(int ty, std::string v){
        type = ty;
        this->val = v;
    }
    int getType(){
        return type;
    }
    std::string getVal(){
        return val;
    }

    std::string getLex(){
        return lex;
    }

    void ver(std::string typeo){
        std::cout<<token<<"    "<<lex<<"    "<<typeo<<"    "<<val<<"\n";
    }

};
#endif