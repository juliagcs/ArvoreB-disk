/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/

#ifndef INTSERIAL_H
#define INTSERIAL_H

#include "serializable.h"

class intSerial : serializable { //Classe intserial
   public:
      intSerial(); //construtor default
      intSerial(int i); //construtor paramétrico
      intSerial(const intSerial &other); //construtor de cópia
      virtual ~intSerial(); //destrutor

      //metodos para sobrecarga de operadores
      intSerial operator=(const intSerial& other); //sobrecarga de = (atribuição)
      bool operator==(const intSerial &other) const; //sobrecarga de == (igualdade)
      bool operator<(const intSerial &other) const; //sobrecarga de < (menor)
      bool operator<=(const intSerial &other) const; //sobrecarga de <= (menor ou igual)
      bool operator>(const intSerial &other) const; //sobrecarga de > (maior)
      bool operator>=(const intSerial &other) const; //sobrecarga de >= (maior ou igual)
      bool operator!=(const intSerial &other) const; //sobrecarga de != (diferente de)
      intSerial operator+(const intSerial &other) const; //sobrecarga de + (adição)
      intSerial operator-(const intSerial &other) const; //sobrecarga de - (subtração)
      intSerial operator*(const intSerial &other) const; //sobrecarga de * (multiplicação)
      intSerial operator/(const intSerial &other) const; //sobrecarga de / (divisão)
      intSerial operator++(); //sobrecarga de ++ (incremento)
      intSerial operator--(); //sobrecarga de -- (decremento)

      //acessores
      void setValue(int v); //alteradores do valor
      int getValue() const; //consultor para o valor

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
      int value;
};

#endif // INTSERIAL_H
