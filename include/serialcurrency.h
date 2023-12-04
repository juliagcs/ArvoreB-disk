/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/

#ifndef SERIALCURRENCY_H
#define SERIALCURRENCY_H
#include "serializable.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>


class serialcurrency : serializable{
    friend ostream &operator << (ostream &output, const serialcurrency &s);
    public:
        serialcurrency(); //construtor default
        serialcurrency(float s); //construtor paramétrico
        serialcurrency(const serialcurrency &other); //construtor de cópia
        virtual ~serialcurrency(); //destrutor

        //metodos para sobrecarga de operadores
        serialcurrency operator=(const serialcurrency& other); //sobrecarga de = (atribuição)
        bool operator==(const serialcurrency &other) const; //sobrecarga de == (igualdade)
        bool operator<(const serialcurrency &other) const; //sobrecarga de < (menor)
        bool operator<=(const serialcurrency &other) const; //sobrecarga de <= (menor ou igual)
        bool operator>(const serialcurrency &other) const; //sobrecarga de > (maior)
        bool operator>=(const serialcurrency &other) const; //sobrecarga de >= (maior ou igual)
        bool operator!=(const serialcurrency &other) const; //sobrecarga de != (diferente de)

        //acessores
        void setX(int xs); //alteradores do x
        int getX() const; //consultor para y
        void setY(int ys); //alteradores do y
        int getY() const; //consultor para y

        virtual string toString(); //método serialização
        virtual void fromString(string repr); //método desserialização
        virtual string toXML();
        virtual void fromXML(string repr);
        virtual string toCSV();
        virtual void fromCSV(string repr);
        virtual string toJSON();
        virtual void fromJSON(string repr);
        virtual unsigned long long int size() const; //método do tamanho
    protected:
        int x;
        int y;
       // vector<string> split (const string &value, char delimiter);

};

#endif // SERIALCURRENCY_H
