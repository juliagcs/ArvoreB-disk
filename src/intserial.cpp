/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/
#include "intserial.h"

intSerial::intSerial() : serializable() {
    value = 0;
}

intSerial::intSerial(int i) : serializable() {
    value = i;
}

intSerial::intSerial(const intSerial &other) {
    value = other.getValue();
}

intSerial::~intSerial() {}

intSerial intSerial::operator=(const intSerial &other) {
    intSerial aux(other);
    value = other.getValue();
    return aux;
}

bool intSerial::operator==(const intSerial &other) const {
    return value == other.getValue();
}

bool intSerial::operator<(const intSerial &other) const {
    return value < other.getValue();
}

bool intSerial::operator<=(const intSerial &other) const {
    return value <= other.getValue();
}

bool intSerial::operator>(const intSerial &other) const {
    return value > other.getValue();
}

bool intSerial::operator>=(const intSerial &other) const {
    return value >= other.getValue();
}

bool intSerial::operator!=(const intSerial &other) const {
    return value != other.getValue();
}

intSerial intSerial::operator+(const intSerial& other) const {
    intSerial aux(value + other.getValue());
    return aux;
}

intSerial intSerial::operator-(const intSerial& other) const {
    intSerial aux(value - other.getValue());
    return aux;
}

intSerial intSerial::operator*(const intSerial& other) const {
    intSerial aux(value * other.getValue());
    return aux;
}

intSerial intSerial::operator/(const intSerial& other) const {
    intSerial aux(value / other.getValue());
    return aux;
}

intSerial intSerial::operator++() {
    return value+1;
}

intSerial intSerial::operator--() {
    return value-1;
}

void intSerial::setValue(int v) {
    value = v;
}

int intSerial::getValue() const {
    return value;
}

string intSerial::toString() { //método para serializar o objeto
    string aux = "";
    //fazendo com que os dados sejam vistos como caracteres pelo compilador atraves da função reinterpret_cast<char*>()
    aux += string(reinterpret_cast<char*>(&value), sizeof(int));
    return aux;
}

void intSerial::fromString(string repr) { //método para desserializar o objeto
    //fazendo com que os dados sejam vistos como caracteres pelo compilador atraves da função reinterpret_cast<char*>()
    repr.copy(reinterpret_cast<char*>(&value), sizeof(int), 0);
}

string intSerial::toXML() {
    return "";
}

void intSerial::fromXML(string repr) {
}

string intSerial::toCSV() {
    return "";
}

void intSerial::fromCSV(string repr) {
}

string intSerial::toJSON() {
    return "";
}

void intSerial::fromJSON(string repr) {
}

unsigned long long int intSerial::size() const { //metodo para retornar o tamanho total do objeto
    return sizeof(int);
}
