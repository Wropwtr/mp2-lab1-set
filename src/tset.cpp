// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField( mp )
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField( s.BitField )
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField( bf )
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField buf(this->BitField);
	return buf;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.GetMaxPower();
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return ( BitField == s.BitField );
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return ( BitField != s.BitField );
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet buf( BitField | s.BitField );

	return buf;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if ( Elem >= BitField.GetLength() ){
		throw("Index of element out of range");
	}

	TSet buf( BitField );
	buf.InsElem( Elem );

	return buf;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet buf(BitField);
	buf.DelElem(Elem);

	return buf;
}

TSet TSet::operator*(const TSet &s) // пересечение
{	
	TSet buf(BitField & s.BitField);

	return buf;	
}

TSet TSet::operator~(void) // дополнение
{
	TSet buf(~BitField);

	return buf;
}
// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i = 0;
	char ch;

	// поиск {
	do {
		istr >> ch;
	} while (ch != ' ');

	// ввод элементов и включение в множество
	while (1) {
		istr >> ch;

		if (ch == '0'){
			s.BitField.ClrBit(i++);
		}
		else{
			if (ch == '1')
				s.BitField.SetBit(i++);
			else
				break;
		}
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i, k = 0;

	for (i = 0; i < s.GetMaxPower(); i++){
		if (s.IsMember(i)){
			ostr << i << " ";
			k++;
		}

		if ((k + 1) % 10 == 0){
			ostr << endl;
			k = 0;
		}
	}
	ostr << endl;

	return ostr;

}

