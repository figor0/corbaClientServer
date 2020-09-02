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

class DBManager {
public:
	DBManager(const DBManager& copy) = delete;
	static DBManager& instance(){
		static DBManager db_manager;
		return db_manager;
	}
	std::vector<Entry> load(const QString& db_path);
	size_t save(const QString& db_path,
			  const std::vector<Entry>& entries);
private:
	DBManager();
	QString m_table_name = "Entries";
	QSqlDatabase m_db;
};

