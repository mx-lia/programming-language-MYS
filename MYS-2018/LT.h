#pragma once

#include "Error.h"

#define LEXEMA_FIXSIZE		1																// фиксированный размер лексемы
#define LT_MAXSIZE			4096															// максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX		0xfffffff														// нет элемента таблицы идентификаторов

#define LEX_TYPE			't'																// лексема для типа
#define LEX_NEW				'n'																// лексема для New
#define LEX_ID				'i'																// лексема для идентификатора
#define LEX_LITERAL			'l'																// лексема для литерала
#define LEX_FUNCTION		'f'																// лексема для Function
#define LEX_PROCEDURE		'p'																// лексема для Procedure
#define LEX_RETRIEVE		'r'																// лексема для Retrieve
#define LEX_OUTPUT			'o'																// лексема для Output
#define LEX_MAIN			'm'																// лексема для Main
#define LEX_SEMICOLON		';'																// лексема для ;
#define LEX_COMMA			','																// лексема для ,
#define LEX_LEFTBRACE		'{'																// лексема для {
#define LEX_BRACELET		'}'																// лексема для }
#define LEX_LEFTTHESIS		'['																// лексема для [
#define LEX_RIGHTTHESIS		']'																// лексема для ]
#define LEX_LEFTBRACKET		'('																// лексема для (
#define LEX_RIGHTBRACKET	')'																// лексема для )
#define LEX_OPERATOR		'v'																// лексема для операторов
#define LEX_EQUAL			'='																// лексема для оператора присваивания
#define LEX_LOGOPERATOR		'g'																// лексема для логического оператора
#define LEX_UNTIL			'u'																// лексема для Until
#define LEX_WHEN			'w'																// лексема для When
#define LEX_OTHERWISE		'!'																// лексема для Otherwise
#define LEX_LINK			'+'																// лексема для Link
#define LEX_MEASURE			'%'																// лексема для Measure
#define LEX_GONEWSTR		'c'																// лексема для перехода на новую строку

namespace LT																				// таблица лексем
{
	enum OPER { NOT = -1, PLUS = 1, MINUS, MUL, DIR, MORE, LESS, EQU, NOEQU };

	struct Entry																			// строка таблицы лексем
	{
		unsigned char lexema;																// лексема
		int line;																			// номер строки в исходном тексте
		int idxTI;																			// индекс в таблице идентификаторов или LT_TI_NULLIDX
		int priority;																		// приоритет
		OPER operation;
	};

	struct LexTable																			// экземпляр таблицы лексем
	{
		int maxsize;																		// емкость таблицы лексем < LT_MAXSIZE
		int size;																			// текущий размер таблицы лексем < maxsize
		Entry* table;																		// массив строк таблицы лексем
	};

	LexTable Create(																		// создать таблицу лексем
		int size																			// емкость таблицы лексем < LT_MAXSIZE
	);

	void Add(																				// добавить строку в таблицу лексем
		LexTable& lextable,																	// экземпляр таблицы лексем
		Entry entry																			// строка таблицы лексем
	);

	Entry GetEntry(																			// получить строку таблицы лексем
		LexTable& lextable,																	// экземпляр таблицы лексем
		int n																				// номер получаемой строки
	);

	void Delete(LexTable& lextable);														// удалить таблицу лексем (освободить память)

	Entry writeEntry(																		// заполнить строку таблицы лексем
		Entry &entry,
		unsigned char lexema,
		int indx,
		int line,
		int priority = -1,
		OPER operation = NOT
	);

	void WriteLexTable(LexTable& lextable);

	void WriteTokens(LexTable lextable);
};