#pragma once
#include "pch.h"
#include "LexAnalyzer.h"
#include "Error.h"

namespace Poliz
{
	bool StartPoliz(Lexer::LEX& lex);
	bool Poliz(int i, Lexer::LEX& lex);
}
