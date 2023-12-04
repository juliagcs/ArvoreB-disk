/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/

#ifndef HEADER_H
#define HEADER_H
#include "serializable.h"

class header : public serializable { //Classe cabeçalho
   public:
      header(); //construtor default
      header(const string t, unsigned int v); //construtor paramétrico
      header(const header &h); //construtor de cópia
      virtual ~header(); //destrutor

      //metodos para sobrecarga de operadores
      header operator=(const header &h); //sobrecarga de = (atribuição)
      bool operator==(const header &h); //sobrecarga de == (igualdade)

      //acessores
      unsigned long long int getFirstDeleted() const; //consultor do primeiro deletado
      void setFirstDeleted(unsigned long long int r); //alterador do primeiro deletado
      unsigned long long int getFirstValid() const; //consultor do primeiro valido
      void setFirstValid(unsigned long long int r); //alterador do primeiro valido
      unsigned long long int getRoot() const; //consultor da raiz da árvore
      void setRoot(unsigned long long int r); //alterador da raz da árvore
      string getType() const; //consultor do tipo do cabeçalho
      void setType(string t); //alterador do tipo do cabeçalho
      unsigned int getVersion() const; //consultor da versão do cabeçalho
      void setVersion(unsigned int v); //alterador da versão do cabeçalho

      virtual string toString(); //método serialização
      virtual void fromString(string repr); //método desserialização
      virtual string toXML() { return ""; };
      virtual void fromXML(string repr) {};
      virtual string toCSV() { return ""; };
      virtual void fromCSV(string repr){};
      virtual string toJSON() { return ""; };
      virtual void fromJSON(string repr) {};
      virtual unsigned long long int size() const; //método do tamanho
   protected:
      string type;
      unsigned int version;
      unsigned long long int rootR;
      unsigned long long int firstValid;
      unsigned long long int firstDeleted;
};

#endif // HEADER_H
