#ifndef LEXER_HPP
#define LEXER_HPP
#include <cctype>
#include <iostream>
#include <fstream>
//#include <boost/algorithm/string.hpp>

struct lexeme
{
    int token;
    std::string val;
};

class Lexer
{
private:
    constexpr static const char* reservada[] = {"entero","flotante","caracter","cadena","booleano","vacio","principal","clase","Funcion","llamar",
                                "objeto","para","mientras","si","sino","eleccion","break","caso","predeterminado","leer","escribir",
                                "rtrn","constante","true","false","nuevo"};
    constexpr static const char* operador[] = {".","++","--","*","/","-","+","<",">","=>","=<","==","!=","!","&&","||","(",")","[","]","{","}",
                                ",",";","<=",":"};
    std::string file;
    std::string buffer,aux[2];
    int index=0,i,j=0,token,e_principal=400;
    constexpr static int TABLA_TRANSICION_ID[4][4] = {
        {1,-1,-1,-1},//ESTADO INICIAL
        {1,2,3,4},//ESTADO LETRA
        {1,2,3,4},//ESTADO DIGITO
        {1,2,3,4}//ESTADO GUION BAJO
    };
    constexpr static int TABLA_TRANSICION_CONST[5][5] = {
        {1,-1,3,-1,4},
        {1,2,5,5,5},
        {1,5,5,5,5},//FILA ESTADO FLOAT
        {3,3,5,3,3},//ESTADO CADENA
        {4,4,4,4,5}//FILA ESTADO CARACTER
    };

    int AFD_ID(){
        int ESTADO_ACT = 0,ESTADO_SIG;
        aux[0]="",aux[1]="",j=0;
        char c = file[index];
        if (!isalpha(c)){
            return 300;
        }else{
            ESTADO_SIG = TABLA_TRANSICION_ID[ESTADO_ACT][scaner_id(c)];
            for(;;){
                if (ESTADO_SIG == 4){
                    j=0;return 400;
                }
                else{
                    buffer += c;
                    ++index;
                    token = buscar_pal_reserv(buffer);//buscar siempre palabras reservadas
                    if (token != 400){
                        aux[j] = buffer;
                        ++j;
                        buffer = "";
                        //return token;
                    }
                    c = file[index];
                    ESTADO_SIG = TABLA_TRANSICION_ID[ESTADO_SIG][scaner_id(c)];
                    //boost::trim(buffer);
                    trim(buffer);
                    //retorna el numero de AFD para seguir leyendo caracteres y continuar el loop del afd principal
                }
            }
        }
    }

    int AFD_CONST(){
        int ESTADO_ACT = 0, ESTADO_SIG,caracter=0;
        char c = file[index];
        if (!(isdigit(c)) && !(c == '"') && !(c == '@')) {// || c != '"' || c != '@'
            return 200;
        } else {
            ESTADO_SIG = TABLA_TRANSICION_CONST[ESTADO_ACT][scaner_const(c)];
            if(ESTADO_SIG == 4)
                caracter = 1;
            for (;;){
                if (ESTADO_SIG == 5)
                {
                    if (!checkfloat(buffer) && !(c=='"') && (c != '@'))
                        return 300;
                    else if (checkfloat(buffer) && !(c=='"') && (c != '@'))
                        return 301;
                    else if (c == '"')
                    {
                        ++index;
                        buffer += c;
                        return 303;
                    }
                    else if (c == '@' && buffer.length() > 1)
                        return 200;
                }
                else
                {
                    buffer += c;
                    ++index;
                    c = file[index];
                    ESTADO_SIG = TABLA_TRANSICION_CONST[ESTADO_SIG][scaner_const(c)];
                    //boost::trim(buffer);
                    trim(buffer);
                    
                    if(caracter == 1 && file[index+1] == '@' && buffer.length() <= 1)
                    {
                        char m = file[index];
                        buffer += m;
                        ++index;
                        m = file[index];
                        buffer += m;
                        ++index;
                        
                        caracter = 0;
                        return 302;
                    }
                    if(caracter == 1 && c == '@' && buffer.length() <= 1)
                    {
                        char m = file[index];
                        buffer += m;
                        ++index;
                        caracter = 0;
                        
                        return 302;
                    }
                }
                /*
                if (ESTADO_SIG == 5 && !checkfloat(buffer) && !(c=='"') && (c != '@'))
                    return 300;
                else if (ESTADO_SIG == 5 && checkfloat(buffer) && !(c=='"') && (c != '@'))
                    return 301;
                else if (ESTADO_SIG == 5 && c == '"')
                {
                    ++index;
                    buffer += c;
                    return 303;
                }
                else if (ESTADO_SIG == 5 && c == '@' && buffer.length() > 1)
                    return 200;
                else{
                    
                    buffer += c;
                    ++index;
                    c = file[index];
                    ESTADO_SIG = TABLA_TRANSICION_CONST[ESTADO_SIG][scaner_const(c)];
                    //boost::trim(buffer);
                    trim(buffer);
                    
                    if(caracter == 1 && file[index+1] == '@' && buffer.length() <= 1)
                    {
                        char m = file[index];
                        buffer += m;
                        ++index;
                        m = file[index];
                        buffer += m;
                        ++index;
                        
                        caracter = 0;
                        return 302;
                    }
                    if(caracter == 1 && c == '@' && buffer.length() <= 1)
                    {
                        char m = file[index];
                        buffer += m;
                        ++index;
                        caracter = 0;
                        
                        return 302;
                    }
                }*/
            }
        }
    }

    int AFD_SIMB(){
        char c = file[index];
        buffer += c;
        token = buscar_operador(buffer);
        c = file[++index];
        buffer += c;
        token = buscar_operador(buffer);
        if (token < 200 || token > 225){
            c = file[--index];
            buffer = "";
            buffer += c;
            token = buscar_operador(buffer);
        }
        return token;
    }

    inline int scaner_id(char c) const {
        if (isalpha(c)) return 0;
        else if (isdigit(c)) return 1;
        else if (c=='_') return 2;
        else return 3;
    }

    inline int scaner_const(char c) const {
        if (isdigit(c)) return 0;
        else if (c =='.') return 1;
        else if (c =='"') return 2; 
        else if (c =='@') return 4;
        else return 3;
    }

    int buscar_operador(const std::string& x) {
        for (i = 0; i < 26; i++) {
            if(x == operador[i])
                return 200+i;
        }
        return -666;
    }

    int buscar_pal_reserv(const std::string& x) {
        for (i = 0; i < 26; i++) {
            if(x == reservada[i])
                return 100+i;
        }
        return 400;
    }

    bool reserv_check() const {
        for (int k = 0; k < 2; k++)
        {
            if (aux[k]=="")
                return false;
        }
        return true;
    }

    bool checkfloat(const std::string& x) const {
        // char c;
        // for (size_t k = 0; k < x.length(); k++)
        // {
        //     c = x[k];
        //     if (c == '.')
        //         return true;
        // }
        return x.find('.') != std::string::npos;
    }

    void trim(std::string& line){
        // if(line.size() == 0) return;
        // if(line.size() == 1 && !std::isspace(line[0])) return;
        // int first = 0;
        // for(unsigned int k = 0; k < line.size(); ++k){
        //     if (!std::isspace(line[k])){
        //         first = k;
        //         break;
        //     }
        // }
        // int last = 0;
        // for(unsigned int k = line.size()-1; k >= 0; --k){
        //     if (!std::isspace(line[k])){
        //         last = k+1;
        //         break;
        //     }
        //     if(k == 0){
        //         last = 0;
        //         break;
        //     }
        // }
        // line = line.substr(first, last-first);
        if (line.empty()) return;
        size_t first = line.find_first_not_of(" \t\n\r\f\v");
        size_t last = line.find_last_not_of(" \t\n\r\f\v");
        if (first == std::string::npos || last == std::string::npos) {
            line.clear();
        } else {
            line = line.substr(first, (last - first + 1));
        }
    } 

public:
    std::string cadena;
    Lexer(std::string);
    lexeme AFD_MAIN();
};

#endif