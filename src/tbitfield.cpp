// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// bitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//
// Битовые поля
#include "tbitfield.h"

TBitField :: TBitField(int len) : BitLen(len) {
    MemLen = ( len + 15 ) >> 4; // в эл-те pМем 16 бит (TELEM==int)
    pMem = new TELEM[MemLen];

    if ( pMem != NULL ){
        for ( int i = 0; i < MemLen; i++ )
            pMem[i] = 0;
    }
}

TBitField :: TBitField(const TBitField &bf) { // конструктор копирования
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    BitLen = bf.BitLen;

    if ( pMem != NULL ){
        for ( int i = 0; i < MemLen; i++ )
            pMem[i] = bf.pMem[i];
    }
}

TBitField :: ~TBitField() {
    delete []pMem;
}

int TBitField :: GetMemIndex ( const int n ){ // индекс Мем для бита n
 // преобразовать к int и разделить на 16
    return n >> 4; // в эл-те pМем 16 бит
}

TELEM TBitField :: GetMemMask ( const int n ){ // битовая маска для бита

 // преобразовать к int, найти остаток от деления на 16 и сдвинуть
    return 1 << (n & 15);
}

// доступ к битам битового поля
int TBitField :: GetLength(void) const { // получить длину (к-во битов)
    return BitLen;
}

void TBitField :: SetBit ( const int n ) { // установить бит
    if ( (n > -1) && (n < BitLen) )
        pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField :: ClrBit ( const int n ) { // очистить бит


}

int TBitField :: GetBit ( const int n ) const { // получить значение бита



}

// битовые операции
TBitField & TBitField :: operator=(const TBitField &bf) { // присваивание









}

int TBitField :: operator==(const TBitField &bf) { // сравнение
    int res = 1;

    if ( BitLen != bf.BitLen ){
        res = 0;
    }
    else{
        for ( int i = 0; i < MemLen; i++ )
            if ( pMem[i] != bf.pMem[i] ){
                res = 0;
                break;
            }
    }
    return res;
}

TBitField TBitField :: operator| (const TBitField &bf) { // операция "или"
    int i, len = BitLen;

    if ( bf.BitLen > len )
        len = bf.BitLen;

    TBitField temp(len);
    for ( i = 0; i < MemLen; i++ )
        temp.pMem[i] = pMem[i];
    for ( i = 0; i < bf.MemLen; i++ )
        temp.pMem[i] |= bf.pMem[i];

    return temp;
}

TBitField TBitField :: operator& (const TBitField &bf) { // операция "и"






}

TBitField TBitField :: operator~ ( void ) { // отрицание




}

// ввод/вывод
istream &operator>>(istream &istr, TBitField &bf) {
    int i = 0;
    char ch;

    // поиск {
    do {
       istr >> ch;
    }
    while (ch != ' ');

    // ввод элементов и включение в множество
    while (1) {
        istr >> ch;
        if ( ch == '0' )
            bf.ClrBit(i++);
        else if ( ch == '1' )
            bf.SetBit(i++); else break;
    }
    return istr;
}
/*
 * ввод
 *  формат данных - последовательность из 0 и 1 без пробелов
 *  начальные пробелы игнорируются
 *  при получении не 0 или 1 - завершение ввода
 */

ostream &operator<<(ostream &ostr, const TBitField &bf) { // вывод






}
