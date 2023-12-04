/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/

#ifndef SERIALIZABLE_H_INCLUDED
#define SERIALIZABLE_H_INCLUDED
#include <string>

using namespace std;

class serializable { //Classe serialização
   public:
      serializable() {}
      virtual ~serializable() {}
      virtual string toString() = 0;
      virtual void fromString(string repr) = 0;
      virtual string toXML() = 0;
      virtual void fromXML(string repr) = 0;
      virtual string toCSV() = 0;
      virtual void fromCSV(string repr) = 0;
      virtual string toJSON() = 0;
      virtual void fromJSON(string repr) = 0;
      virtual unsigned long long int size() const = 0;
};

#endif // SERIALIZABLE_H_INCLUDED
