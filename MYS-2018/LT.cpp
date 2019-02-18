#include "pch.h"
#include "LT.h"

namespace LT
{
	Entry writeEntry(Entry &entry, unsigned char lexema, int indx, int line, int priority, OPER operation)
	{
		entry.lexema = lexema;
		entry.idxTI = indx;
		entry.line = line;
		entry.priority = priority;
		entry.operation = operation;
		return entry;
	}

	LexTable Create(int size)
	{
		if (size > LT_MAXSIZE)
			throw ERROR_THROW(201);
		LexTable lexTable;
		lexTable.maxsize = size;
		lexTable.size = NULL;
		lexTable.table = new Entry[size];
		return lexTable;
	}

	void Add(LexTable& lexTable, Entry entry)
	{
		if (lexTable.size >= lexTable.maxsize)
			throw ERROR_THROW(202);
		lexTable.table[lexTable.size++] = entry;
	}

	Entry GetEntry(LexTable& lexTable, int n)
	{
		return lexTable.table[n];
	}

	void Delete(LexTable& lexTable)
	{
		delete[] lexTable.table;
	}

	void WriteLexTable(LT::LexTable& lextable)
	{
		int i;
		std::cout << std::endl << std::setfill('-') << std::setw(31) << '-' << " ÒÀÁËÈÖÀ ËÅÊÑÅÌ " << std::setfill('-') << std::setw(42) << '-' << std::endl;
		std::cout << std::setfill('-') << std::setw(89) << '-' << std::endl;
		std::cout << "   ¹" << " | " << "Ëåêñåìà" << std::setfill(' ') << std::setw(20) << ' ' << std::left << " | " << "Ñòðîêà" << std::setw(21) << ' ' << std::left << " | " << "Èíäåêñ â ÒÈ" << std::endl;
		std::cout << std::setfill('-') << std::setw(89) << '-' << std::endl;
		for (i = 0; i < lextable.size; i++)
		{
			std::cout << std::setfill('0') << std::setw(4) << std::right << i << " | " << std::setfill(' ') << std::setw(24) << std::left << lextable.table[i].lexema << "    | " << std::setw(24) << std::left
				<< lextable.table[i].line + 1 << "    | ";
			if (lextable.table[i].idxTI == LT_TI_NULLIDX)
				std::cout << "-" << std::endl;
			else
				std::cout << std::setw(23) << lextable.table[i].idxTI << std::endl;
		}
		std::cout << std::setfill('-') << std::setw(89) << '-' << std::endl;
		std::cout << "     | Êîëè÷åñòâî ëåêñåì: " << i << std::endl;
		std::cout << std::setfill('-') << std::setw(89) << '-' << std::endl;
	}

	void WriteTokens(LexTable lextable)	
	{
		int number = 0;
		std::cout << std::endl << std::setfill('-') << std::setw(31) << '-' << " ÏÐÎÌÅÆÓÒÎ×ÍÎÅ ÏÐÅÄÑÒÀÂËÅÍÈÅ ÊÎÄÀ " << std::setfill('-') << std::setw(24) << '-' << std::endl;
		std::cout << "0001 | ";
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].line != number && lextable.table[i].line != 0)
			{
				while (lextable.table[i].line - number > 1)
					number++;
				if (number < 9)
					std::cout << std::endl << std::setfill('0') << std::setw(4) << std::right << lextable.table[i].line + 1 << " |" << std::setfill(' ') << std::ends;
				else
					std::cout << std::endl << std::setfill('0') << std::setw(4) << std::right << lextable.table[i].line + 1 << " |" << std::setfill(' ') << std::ends;
				number++;
			}
			std::cout << lextable.table[i].lexema;
			if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
				std::cout << "(" << lextable.table[i].idxTI << ")";
		}
		std::cout << std::endl;
		std::cout << std::setfill('-') << std::setw(89) << '-' << std::endl;
	}
}