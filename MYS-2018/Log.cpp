#include "pch.h"
#include "Log.h"

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new std::ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open())
			throw ERROR_THROW(103);
		wcscpy_s(log.logfile, logfile);
		return log;
	}

	void WriteLine(LOG log, char* c, ...)
	{
		char** pointer = &c;
		int len = 0;
		while (*pointer != "")
		{
			len += strlen(*pointer);
			pointer++;
		}
		char *string = new char[len + 1];
		string[0] = 0;
		pointer = &c;
		while (*pointer != "")
		{
			strcat(string, *pointer);
			pointer++;
		}
		log.stream->write(string, len);
		delete[] string;
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t** pointer = &c;
		int len = 0;
		while (*pointer != L"")
		{
			len += wcslen(*pointer);
			pointer++;
		}
		wchar_t *wstring = new wchar_t[len + 1];
		wstring[0] = 0;
		pointer = &c;
		while (*pointer != L"")
		{
			wcscat(wstring, *pointer);
			pointer++;
		}
		char* string = new char[len + 1];
		wcstombs(string, wstring, len + 1);
		log.stream->write(string, len);
		delete[] string, wstring;
	}

	void WriteLog(LOG log)
	{
		time_t curTime;
		tm timeStruct;
		time(&curTime);
		char strTime[30];
		localtime_s(&timeStruct, &curTime);
		strftime(strTime, 1024, "%d.%m.%Y %H:%M:%S", &timeStruct);
		*log.stream << "---- Протокол -------" << std::setfill('-') << std::setw(49) << '-' << strTime << std::endl;
		std::cout << "---- Протокол -------" << std::setfill('-') << std::setw(49) << '-' << strTime << std::endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		*log.stream << "\n---- Параметры ------" << std::setfill('-') << std::setw(68) << '-' << std::endl;
		std::cout << "\n---- Параметры ------" << std::setfill('-') << std::setw(68) << '-' << std::endl;

		char temp[PARM_MAX_SIZE + 1];
		wcstombs(temp, PARM_LOG, wcslen(PARM_LOG) + 1);
		*log.stream << temp << " ";
		std::cout << temp << " ";
		wcstombs(temp, parm.log, wcslen(parm.log) + 1);
		*log.stream << temp << std::endl;
		std::cout << temp << std::endl;

		wcstombs(temp, PARM_OUT, wcslen(PARM_OUT) + 1);
		*log.stream << temp << " ";
		std::cout << temp << " ";
		wcstombs(temp, parm.out, wcslen(parm.out) + 1);
		*log.stream << temp << std::endl;
		std::cout << temp << std::endl;

		wcstombs(temp, PARM_IN, wcslen(PARM_IN) + 1);
		*log.stream << temp << "  ";
		std::cout << temp << "  ";
		wcstombs(temp, parm.in, wcslen(parm.in) + 1);
		*log.stream << temp << std::endl;
		std::cout << temp << std::endl;
		*log.stream << (parm.idtable ? "-id  " : "") << (parm.lextable ? "-lex  " : "")
			<< (parm.tokens ? "-tokens  " : "") << (parm.rules ? "-rules " : "") << std::endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "\n---- Исходные данные ------" << std::setfill('-') << std::setw(62) << '-' << std::endl;
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Проигнорировано    : " << in.ignor << std::endl;
		*log.stream << "Количество строк   : " << in.lines << std::endl;

		std::cout << "\n---- Исходные данные ------" << std::setfill('-') << std::setw(62) << '-' << std::endl;
		std::cout << "Количество символов: " << in.size << std::endl;
		std::cout << "Проигнорировано    : " << in.ignor << std::endl;
		std::cout << "Количество строк   : " << in.lines << std::endl;
	}

	void WriteError(LOG log, Error::ERROR error)											//вывод ошибок в файл и на консоль
	{
		if (log.stream != NULL)
		{
			if (error.inext.line == -1)
				*log.stream << "| ERR" << error.id << " | " << error.message << std::endl;
			else if (error.inext.position == NULL || error.inext.position == -1)
				*log.stream << "| ERR" << error.id << " | " << error.message << std::endl << "| Строка: " << error.inext.line + 1 << std::endl;
			else
				*log.stream << "| ERR" << error.id << " | " << error.message << std::endl << "| Строка: " << error.inext.line + 1 << " | Позиция в строке: " << error.inext.position << std::endl;
			*log.stream << std::endl;
		}
	
		if (error.inext.line == -1)
			std::cout << "| ERR" << error.id << " | " << error.message << std::endl;
		else if (error.inext.position == NULL || error.inext.position == -1)
			std::cout << "| ERR" << error.id << " | " << error.message << std::endl << "| Строка: " << error.inext.line + 1 << std::endl;
		else
			std::cout << "| ERR" << error.id << " | " << error.message << std::endl << "| Строка: " << error.inext.line + 1 << " | Позиция в строке: " << error.inext.position << std::endl;
		
		std::cout << std::endl;
		system("pause");
		exit(-1);
	}

	void WriteIDTableLog(IT::IdTable& idtable, LOG log)
	{
		int i, numberNoneId = 0;
		*log.stream << std::endl << std::setfill('-') << std::setw(31) << '-' << " ТАБЛИЦА ИДЕНТИФИКАТОРОВ " << std::setfill('-') << std::setw(33) << '-' << std::endl;
		*log.stream << std::setfill('-') << std::setw(89) << '-' << std::endl;
		*log.stream << "   №" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << "Значение/Параметры" << std::endl;
		*log.stream << std::setw(89) << '-' << std::endl;
		for (i = 0; i < idtable.size; i++)
		{
			*log.stream << std::setfill('0') << std::setw(4) << std::right << i << " | ";
			*log.stream << std::setfill(' ') << std::setw(13) << std::left << idtable.table[i].id << " | ";
			switch (idtable.table[i].iddatatype)
			{
			case IT::INT: 
				*log.stream << std::setw(10) << std::left;
				*log.stream << "int_" << " | "; 
				break;
			case IT::STR: 
				*log.stream << std::setw(10) << std::left;
				*log.stream << "str_" << " | "; 
				break;
			case IT::PROC:
				*log.stream << std::setw(10) << std::left;
				*log.stream << "-" << " | ";
				break;
			case IT::BOOL:
				*log.stream << std::setw(10) << std::left;
				*log.stream << "bool_" << " | ";
				break;
			}
			switch (idtable.table[i].idtype)
			{
			case IT::V: *log.stream << std::setw(18) << std::left << "переменная" << " | "; break;
			case IT::F: *log.stream << std::setw(18) << std::left << "функция" << " | "; break;
			case IT::P: *log.stream << std::setw(18) << std::left << "параметр" << " | "; break;
			case IT::L: *log.stream << std::setw(18) << std::left << "литерал" << " | ";
				numberNoneId++;
				break;
			case IT::S: *log.stream << std::setw(18) << std::left << "библ. функция" << " | ";
				numberNoneId++;
				break;
			}
			*log.stream << std::setw(11) << std::left << idtable.table[i].idxfirstLE << " | ";
			if (idtable.table[i].iddatatype == IT::INT && (idtable.table[i].idtype == IT::V || idtable.table[i].idtype == IT::L))
				*log.stream << std::setw(18) << std::left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == IT::BOOL && (idtable.table[i].idtype == IT::V || idtable.table[i].idtype == IT::L))
				*log.stream << std::setw(18) << std::left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == IT::STR && (idtable.table[i].idtype == IT::V || idtable.table[i].idtype == IT::L))
				*log.stream << "[" << idtable.table[i].value.vstr.len << "]\"" << idtable.table[i].value.vstr.str << "\"";
			else if (idtable.table[i].idtype == IT::F || idtable.table[i].idtype == IT::S)
			{
				for (int k = 0; k < idtable.table[i].value.params.count; k++)
				{
					*log.stream << std::left << "P" << k << ":";
					switch (idtable.table[i].value.params.types[k])
					{
					case IT::INT:*log.stream << std::left << "I|"; break;
					case IT::STR:*log.stream << std::left << "S|"; break;
					case IT::BOOL:*log.stream << std::left << "B|"; break;
					}
				}
				if(idtable.table[i].value.params.count == NULL)
					*log.stream << "-";
			}
			else
				*log.stream << "-";
			*log.stream << std::endl;
		}
		*log.stream << std::setfill('-') << std::setw(89) << '-' << std::endl;
		*log.stream << "     | Количество идентификаторов: " << i - numberNoneId << std::endl;
		*log.stream << std::setw(89) << '-' << std::endl;
	}

	void WriteLexTableLog(LT::LexTable& lextable, LOG log)
	{
		int i;
		*log.stream << std::endl << std::setfill('-') << std::setw(31) << '-' << " ТАБЛИЦА ЛЕКСЕМ " << std::setfill('-') << std::setw(42) << '-' << std::endl;
		*log.stream << std::setfill('-') << std::setw(89) << '-' << std::endl;
		*log.stream << "   №" << " | " << "Лексема" << std::setfill(' ') << std::setw(20) << ' ' << std::left << " | " << "Строка" << std::setw(21) << ' ' << std::left << " | " << "Индекс в ТИ" << std::endl;
		*log.stream << std::setfill('-') << std::setw(89) << '-' << std::endl;
		for (i = 0; i < lextable.size; i++)
		{
			*log.stream << std::setfill('0') << std::setw(4) << std::right << i << " | " << std::setfill(' ') << std::setw(24) << std::left << lextable.table[i].lexema << "    | " << std::setw(24) << std::left
				<< lextable.table[i].line + 1 << "    | ";
			if (lextable.table[i].idxTI == LT_TI_NULLIDX)
				*log.stream << "-" << std::endl;
			else
				*log.stream << std::setw(23) << lextable.table[i].idxTI << std::endl;
		}
		*log.stream << std::setfill('-') << std::setw(89) << '-' << std::endl;
		*log.stream << "     | Количество лексем: " << i << std::endl;
		*log.stream << std::setfill('-') << std::setw(89) << '-' << std::endl;
	}

	void WriteTokensLog(LT::LexTable& lextable, LOG log)
	{
		int number = 0;
		*log.stream << std::endl << std::setfill('-') << std::setw(31) << '-' << " ПРОМЕЖУТОЧНОЕ ПРЕДСТАВЛЕНИЕ КОДА " << std::setfill('-') << std::setw(24) << '-' << std::endl;
		*log.stream << "0001 | ";
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].line != number && lextable.table[i].line != 0)
			{
				while (lextable.table[i].line - number > 1)
					number++;
				if (number < 9)
					*log.stream << std::endl << std::setfill('0') << std::setw(4) << std::right << lextable.table[i].line + 1 << " |" << std::setfill(' ') << std::ends;
				else
					*log.stream << std::endl << std::setfill('0') << std::setw(4) << std::right << lextable.table[i].line + 1 << " |" << std::setfill(' ') << std::ends;
				number++;
			}
			*log.stream << lextable.table[i].lexema;
			if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
				*log.stream << "(" << lextable.table[i].idxTI << ")";
		}
		*log.stream << std::endl;
		*log.stream << std::setfill('-') << std::setw(89) << '-' << std::endl;
	}

	void WriteTraceLog(LOG log)
	{
		std::cout << std::endl << std::setw(25) << '-' << " ТРАССИРОВКА СИНТАКСИЧЕСКОГО АНАЛИЗА " << std::setw(27) << '-' << std::endl << std::setw(89) << '-' << std::endl \
			<< " Шаг" << " | " << std::setfill(' ') \
			<< std::setw(25) << std::left << "Правило" << " | " \
			<< std::setw(30) << std::left << "Входная лента" << " | " \
			<< std::setw(20) << std::left << "Стек" \
			<< std::endl << std::setfill('-') << std::setw(89) << '-' << std::endl;
	}

	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
		log.stream = NULL;
	}
}