#include <generate.h>

using Sequence = _CORBA_Unbounded_Sequence<EntryIdl>;
QString generator::wordGenerator(const size_t word_size)
{
	QString result;
	int a_code = static_cast<int>('a');
	int z_code = static_cast<int>('z');
	for (size_t i = 0; i < word_size; i++){
		int code = rand()%(z_code - a_code);
		result.push_back(static_cast<char>(code + a_code));
	}
	assert(result.size() == word_size);
	return result;
}

QString generator::numberGenerator()
{
	QString result("+");
	for (size_t i = 0; i < 11; i++){
		int number = rand()%10;
		result.push_back(QString::number(number));
	}
	assert(result.size() == 12);
	return result;
}

EntryIdl generator::entryGenerator()
{
	using namespace generator;
	return {
		wordGenerator(8).toStdString().data(),
		wordGenerator(8).toStdString().data(),
		wordGenerator(8).toStdString().data(),
		numberGenerator().toStdString().data()
	};
}

Sequence generator::entriesGenerator(size_t amount)
{
	Sequence result;
	result.length(amount);
	for ( size_t i = 0; i < result.length(); i++)
	{
		result[i] = entryGenerator();
	}
	assert(result.length() == amount);
	return result;
}
