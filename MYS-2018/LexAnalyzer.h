#pragma once
#include "In.h"
#include "Error.h"
#include "Log.h"
#include "IT.h"
#include "LT.h"
#include "FST.h"
#include "Graphs.h"

namespace Lexer
{
	struct LEX
	{
		IT::IdTable idtable;;
		LT::LexTable lextable;
	};

	LEX Analyze(In::IN in, Log::LOG log);

	void clearSpace(unsigned char source[], int size);

	unsigned char** GetWord(unsigned char source[], int size);
}