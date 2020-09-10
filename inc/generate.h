#pragma once
#include <QString>
#include <Entry.h>
#include <vector>
#include <object.hh>
namespace generator
{
	using Sequence = _CORBA_Unbounded_Sequence<EntryIdl>;
	QString wordGenerator(const size_t word_size);

	QString numberGenerator();

	EntryIdl entryGenerator();

	Sequence entriesGenerator(size_t amount);
}
