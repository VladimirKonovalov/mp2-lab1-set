// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw "Negative len";

	BitLen = len;
	MemLen = len / sizeof(TELEM) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int temp;
	temp = n / sizeof(TELEM);
	return temp;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int temp;
	temp = n % sizeof(TELEM);
	return 1 << temp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0) 
		throw "Negative len";
	if (n > BitLen) 
		throw "Out of memory";
	
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0)
	        throw "Negative len";
	if (n > BitLen)
		throw "Out of memory";

	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
        if (n < 0)
                throw "Negative len";
        if (n > BitLen)
                throw "Out of memory";

	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (pMem != NULL)
	{
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	else
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int temp = 1;
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i< BitLen; i++)
		{
			if (GetBit(i) != bf.GetBit(i))
			{
				temp = 0;
				return temp;
			}
		}
	}
	else temp = 0;
	return temp;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
		return 0;
	else
		return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int maxLen;
	if (BitLen >= bf.BitLen)
	{
		maxLen = BitLen;
	}
	else
	{
		maxLen = bf.BitLen;
	}

	TBitField temp(maxLen);

	for (int i = 0; i < MemLen; i++)
	{
		temp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i]  = temp.pMem[i] | bf.pMem[i];
	}

	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int maxLen;
	if (BitLen >= bf.BitLen)
	{
		maxLen = BitLen;
	}
	else
	{
		maxLen = bf.BitLen;
	}

	TBitField temp(maxLen);

	for (int i = 0; i < MemLen; i++)
	{
		temp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i]  = temp.pMem[i] & bf.pMem[i];
	}

	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = ~pMem[i];
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char str;
	int temp = 0;
	istr >> str;
	do
	{
	switch (str)
	{
		case '1':
			bf.SetBit(temp++);
			break;
		case '0':
			bf.ClrBit(temp++);
			break;
		default: 
			throw "Incorrect data";
	}
	} while ((str == '1') || (str == '0'));
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
