/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/
#include "serialcurrency.h"
#include <cmath>

serialcurrency::serialcurrency() : serializable() {
    x = 0;
    y = 0;
}

serialcurrency::serialcurrency(float s) : serializable(){
    x = s;
    y = abs((s - x) * 100);
}

serialcurrency::serialcurrency(const serialcurrency &other) {
    x = other.getX();
    y = other.getY();
}

serialcurrency::~serialcurrency() {}

serialcurrency serialcurrency::operator=(const serialcurrency &other) {
    serialcurrency aux(other);
    x = other.getX();
    y = other.getY();
    return aux;
}

bool serialcurrency::operator==(const serialcurrency &other) const {
    x == other.getX() && y == other.getY();
    return true;
}

bool serialcurrency::operator<(const serialcurrency &other) const {
    if(x < other.getX()){
        return true;
    }
    if(x == other.getX() && y < other.getY()){
        return true;
    }
}

bool serialcurrency::operator<=(const serialcurrency &other) const {
    if(x < other.getX()){
        return true;
    }
    if(x == other.getX() && y == other.getY()){
        return true;
    }
}

bool serialcurrency::operator>(const serialcurrency &other) const {
    if(x > other.getX()){
        return true;
    }
    if(x == other.getX() && y > other.getY()){
        return true;
    }
}

bool serialcurrency::operator>=(const serialcurrency &other) const {
    if(x > other.getX()){
        return true;
    }
    if(x == other.getX() && y == other.getY()){
        return true;
    }
}

bool serialcurrency::operator!=(const serialcurrency &other) const {
    x != other.getX() && y != other.getY();
    return true;
}

ostream &operator << (ostream &output, const serialcurrency &s) {
    output << "(" << s.getX() << ", " << s.getY() << ")";
    return output;
}

void serialcurrency::setX(int xs) {
    x = xs;
}

int serialcurrency::getX() const {
    return x;
}

void serialcurrency::setY(int ys) {
    y = ys;
}

int serialcurrency::getY() const {
    return y;
}

string serialcurrency::toString() { //método para serializar o objeto
    string aux = "";
    //fazendo com que os dados sejam vistos como caracteres pelo compilador atraves da função reinterpret_cast<char*>()
    aux += string(reinterpret_cast<char*>(&x), sizeof(int));
    aux += string(reinterpret_cast<char*>(&y), sizeof(int));
    return aux;
}

void serialcurrency::fromString(string repr) { //método para desserializar o objeto
    int pos = 0;

    //fazendo com que os dados sejam vistos como caracteres pelo compilador atraves da função reinterpret_cast<char*>()
    repr.copy(reinterpret_cast<char*>(&x), sizeof(x), pos);
    pos += sizeof(x);
    repr.copy(reinterpret_cast<char*>(&y), sizeof(y), pos);
}

string serialcurrency::toXML() {
    return "";
}

void serialcurrency::fromXML(string repr) {
}

string serialcurrency::toCSV() {
    return "";
}

void serialcurrency::fromCSV(string repr) {
}

string serialcurrency::toJSON() {
    return "";
}

void serialcurrency::fromJSON(string repr) {
}

unsigned long long int serialcurrency::size() const { //metodo para retornar o tamanho total do objeto
    return sizeof(int) + sizeof(int);
}
