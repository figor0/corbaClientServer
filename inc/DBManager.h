#pragma once
#include <vector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <object.hh>

enum class EntryType{
	FirstName,
	LastName,
	FatherName,
	Phone
};

QString EntryType2Str(EntryType type);
EntryIdl readEntry(const QSqlQuery& query, const QSqlRecord& record);

class DBManager {
public:
	using Sequence = _CORBA_Unbounded_Sequence<EntryIdl>;
	DBManager(const DBManager& copy) = delete;
	static DBManager& instance(){
		static DBManager db_manager;
		return db_manager;
	}
	Sequence load(const QString& db_path);
	size_t save(const QString& db_path,
			  const Sequence& entries);
private:
	DBManager();
	QString m_table_name = "Entries";
	QSqlDatabase m_db;
};

