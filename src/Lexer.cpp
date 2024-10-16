#include "Lexer.hpp"

Lexer::Lexer(std::string path){
    file = "";buffer = "";
    std::string copyfrom;
    std::ifstream source(path);
    if(!source){
        std::cout<<"Error abriendo archivo source"<<std::endl;
        std::cout<<"ENTRADA: ";
        std::getline(std::cin,file);
    }
    else
    {
        while (getline(source,copyfrom))
        {
            //boost::trim(copyfrom);
            trim(copyfrom);
            file += copyfrom;
            //file += "^";
        }
        source.close();
    }
    
    file += "$";
    cadena = file;
    std::cout<<file<<"\n";
}
/**
 * Devuelve tokens en forma de int de acuerdp al los simbolos definidos
*/
lexeme Lexer::AFD_MAIN(){
    lexeme l;
    for(;;){
        char c = file[index];
        if (c == '$'){
            //std::cout<<"\nFin del programa\n";
            l.token = -666;
            l.val = c;
            return l;
        }
        else{
            if (c == ' ')
                ++index;
            switch (e_principal)
            {
            case 400: //identificadores
                //token = AFD_ID();
                /*if (c == '"' && buffer.length() >= 2 && c != '$')
                {
                    buffer = "";
                    ++index;
                    return 303;
                }
                else{*/
                    if (reserv_check()){
                        buffer = aux[j];
                        token = buscar_pal_reserv(buffer);
                        //std::cout<<buffer<<"\t"<<token<<"\n";
                        l.val = buffer;
                        buffer = "";
                        ++j;
                        if(j==2){
                            aux[0]="";
                            aux[1]="";
                        }
                        l.token = token;
                        return l;
                    }
                    else{
                        //j=0;
                        token = AFD_ID();
                        if (token == 300)
                            e_principal	= 300;
                        else if (!reserv_check()){//aceptacion
                            buffer = aux[0]+aux[1]+buffer;
                            token = buscar_pal_reserv(buffer);
                            //std::cout<<buffer<<"\t"<<token<<"\n";
                            l.val = buffer;
                            buffer = "";
                            l.token = token;
                            return l;
                        }
                    }
                //}
                break;
            case 300: //constantes
                token = AFD_CONST();
                if (token == 200)
                    e_principal = 200;// aca deberia ir al estado 200, reconocedor de simbolos
                else{//aceptacion
                    //std::cout<<buffer<<"\t"<<token<<"\n";
                    l.val = buffer;
                    buffer = "";
                    e_principal = 400;
                    l.token = token;
                    return l;
                }
                break;
            case 1200: //palabras reservadas
                //std::cout<<buffer<<" "<<token;
                buffer = "";
                break;
            case 200: //simbolos
                token = AFD_SIMB();
                if(token == -666)
                    e_principal = -666;
                else{
                    //std::cout<<buffer<<"\t"<<token<<"\n";
                    l.val = buffer;
                    buffer = "";
                    ++index;
                    e_principal = 400;
                    l.token = token;
                    return l;
                }
                break;
            case -666:
                if(buffer!="$")
                    e_principal = -1;
                else{
                    //std::cout<<buffer<<"\t"<<token<<"\n";
                    l.val = buffer;
                    buffer = "";
                    std::cout<<"\nFin del programa";
                    l.token = token;
                    return l;
                }
                break;
            case -1:
                std::cout<<"\nFinalizo por error, simbolo incorrecto";
                l.token = token;
                return l;
                break;
            }
        }
    }
}
/*
public static void main(String[] args) {
        Lexer lexer = new Lexer();

        Analyzer AN = new Analyzer("ALexico\\src\\alexico\\lexertest.txt");
        int comp=0;
        System.out.println("buffer\ttoken\n");
        while (comp!=-1) {
            AN.AFD_MAIN();
        }

        //para -> palabra reservada
        //entero -> palabra reservada (tipo de dato)
        //<= -> operador asignacion
        //x -> identificador
        //x -> identificador
        //

}
*/