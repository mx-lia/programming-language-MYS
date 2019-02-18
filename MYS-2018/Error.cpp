#include "pch.h"
#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =																	// таблица ошибок
	{
		ERROR_ENTRY(0, "SYS | Недопустимый код ошибки"),											// код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "SYS | Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "SYS | Параметр -in должен быть задан"),
		ERROR_ENTRY(101, "SYS | Превышена длина входного параметра"), 
		ERROR_ENTRY(102, "SYS | Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(103, "SYS | Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "LEX | Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(201, "LEX | Превышен размер таблицы лексем"),
		ERROR_ENTRY(202, "LEX | Переполнение таблицы лексем"),
		ERROR_ENTRY(203, "LEX | Превышен размер таблицы идентификаторов"),
		ERROR_ENTRY(204, "LEX | Переполнение таблицы идентификаторов"),
		ERROR_ENTRY(205, "LEX | Неизвестная последовательность символов"),
		ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250),
		ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "SEM | Не закрыт строковый литерал"),
		ERROR_ENTRY(301, "SEM | Ожидается тип bool_"),
		ERROR_ENTRY(302, "SEM | Отсутствует точка входа Main"), 
		ERROR_ENTRY(303, "SEM | Обнаружено несколько точек входа Main"),
		ERROR_ENTRY(304, "SEM | Превышен размер строкового литерала"),
		ERROR_ENTRY(305, "SEM | Объявление переменной без ключевого слова New недопустимо"), 
		ERROR_ENTRY(306, "SEM | Необъявленный идентификатор"), 
		ERROR_ENTRY(307, "SEM | Недопустимо объявление переменной без указания типа"),
		ERROR_ENTRY(308, "SEM | Попытка реализовать уже существующую функцию"),
		ERROR_ENTRY(309, "SEM | Попытка переопределить формальный параметр функции"), 
		ERROR_ENTRY(310, "SEM | Попытка переопределить переменную"),
		ERROR_ENTRY(311, "SEM | Не указан тип функции"),
		ERROR_ENTRY(312, "SEM | Процедура не должна иметь тип"),
		ERROR_ENTRY(313, "SEM | Тип функции и тип возвращаемого значения должны совпадать"),
		ERROR_ENTRY(314, "SEM | Превышено максимально допустимое (3) количество параметров функции"),
		ERROR_ENTRY(315, "SEM | Несовпадение типов передаваемых параметров"),
		ERROR_ENTRY(316, "SEM | Слишком много аргументов в вызове функции"),
		ERROR_ENTRY(317, "SEM | Слишком мало аргументов в вызове функции"),
		ERROR_ENTRY(318, "SEM | Использование пустого строкового литерала недопустимо"),
		ERROR_ENTRY(319, "SEM | Недопустимый целочисленный литерал"),
		ERROR_ENTRY(320, "SEM | Типы данных в выражении не совпадают"),
		ERROR_ENTRY(321, "SEM | Арифметические операторы могут применяться только с целочисленными типами"),
		ERROR_ENTRY(322, "SEM | Логические операторы могут применяться только с целочисленными типами"),
		ERROR_ENTRY(323, "SEM | Деление на нуль"),
		ERROR_ENTRY_NODEF(324), ERROR_ENTRY_NODEF(325), ERROR_ENTRY_NODEF(326),
		ERROR_ENTRY_NODEF(327), ERROR_ENTRY_NODEF(328), ERROR_ENTRY_NODEF(329),
		ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360),
		ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF10(500), ERROR_ENTRY_NODEF10(510), ERROR_ENTRY_NODEF10(520), ERROR_ENTRY_NODEF10(530), ERROR_ENTRY_NODEF10(540),
		ERROR_ENTRY_NODEF10(550), ERROR_ENTRY_NODEF10(560), ERROR_ENTRY_NODEF10(570), ERROR_ENTRY_NODEF10(580), ERROR_ENTRY_NODEF10(590),
		ERROR_ENTRY(600, "SYN | Неверная структура программы"),
		ERROR_ENTRY(601, "SYN | Отсутствует список параметров функции при её объявлении"),
		ERROR_ENTRY(602, "SYN | Ошибка в параметрах функции при её объявлении"), 
		ERROR_ENTRY(603, "SYN | Возможно отсутствует тело функции"),
		ERROR_ENTRY(604, "SYN | Недопустимое выражение. Ожидаются только литералы и идентификаторы"),
		ERROR_ENTRY(605, "SYN | Возможно отсутствует тело процедуры"), 
		ERROR_ENTRY(606, "SYN | Неверная конструкция в теле функции"), 
		ERROR_ENTRY(607, "SYN | Ошибка в условном выражении"),
		ERROR_ENTRY(608, "SYN | Ошибка в вызове функции"),
		ERROR_ENTRY(609, "SYN | Ошибка в арифметическом выражении"), 
		ERROR_ENTRY(610, "SYN | Ошибка в списке параметров при вызове функции"),
		ERROR_ENTRY(611, "SYN | Неверная конструкция в теле цикла/условного выражения"),
		ERROR_ENTRY(612, "SYN | Требуется закрывающаяся фигурная скобка"), 
		ERROR_ENTRY(613, "SYN | Требуется открывающаяся фигурная скобка"),
		ERROR_ENTRY_NODEF(614), ERROR_ENTRY_NODEF(615), ERROR_ENTRY_NODEF(616), ERROR_ENTRY_NODEF(617), ERROR_ENTRY_NODEF(618), ERROR_ENTRY_NODEF(619),
		ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		if (id > 0 && id < ERROR_MAX_ENTRY)
			return errors[id];
		else
			return errors[0];
	}

	ERROR geterrorin(int id, int line, int position)
	{
		ERROR error = geterror(id);
		error.inext.position = position;
		error.inext.line = line;
		return error;
	}
}