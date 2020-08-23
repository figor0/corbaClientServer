#pragma once
#include <vector>
#include <Entry.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

enum class EntryType{
	FirstName,
	LastName,
	FatherName,
	Phone
};

QString EntryType2Str(EntryType type);
Entry readEntry(const QSqlQuery& query, const QSqlRecord& record);

class DBManager{
public:
	DBManager();
	std::vector<Entry> load(const QString& db_path);
	size_t save(const QString& db_path,
			  const std::vector<Entry>& entries);
private:
	QString m_table_name = "Entries";
	QSqlDatabase m_db;
};

