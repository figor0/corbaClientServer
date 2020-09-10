#include <DBManager.h>
#include <QDebug>


QString EntryType2Str(EntryType type){
	static std::map<EntryType, QString> type_mapping{
		{EntryType::FirstName, "first_name"},
		{EntryType::LastName, "last_name"},
		{EntryType::FatherName, "father_name"},
		{EntryType::Phone, "phone"}
	};
	return type_mapping[type];
}

DBManager::DBManager():
	m_db(QSqlDatabase::addDatabase("QSQLITE"))
{}

DBManager::Sequence DBManager::load(const QString &db_path)
{
	DBManager::Sequence result;
	m_db.setDatabaseName(db_path);
	if (m_db.open() == false){
		qDebug() << "Error db open";
	} else{
		QSqlQuery query;
		if (query.exec("select * from Entries;")){
			QSqlRecord record = query.record();
			while(query.next() == true){
				result.length(result.length() + 1);
				result[result.length()-1] = readEntry(query, record);
			}
		}
	}
	m_db.close();
	return result;
}

size_t DBManager::save(const QString &db_path, const Sequence &entries)
{
	QString read_request_template("Select from Entries WHERE phone == %1");
	QString insert_request_template("Insert into Entries (first_name, last_name,"
									"father_name, phone) "
									"values('%1','%2', '%3', '%4')");
	QSqlQuery query;
	QSqlRecord record;
	QString command;
	size_t saved_size = 0;
	m_db.setDatabaseName(db_path);
	if (m_db.open() == false){
		return 0;
		qDebug() << "Error db open";
	}
	if (m_db.tables().size() == 0){
		QString create_command =
				"create table %1 ("
				"first_name VARCHAR(20) NOT NULL, "
				"last_name VARCHAR(20) NOT NULL, "
				"father_name VARCHAR(20), "
				"phone VARCHAR(12) NOT NULL UNIQUE"
				");";
		if ( !query.exec(create_command.arg(m_table_name))){
			qDebug() << "Can't create table " << m_table_name;
		}
	}
	for (size_t i = 0; i < entries.length(); i++){
		command = insert_request_template
				.arg(QString(entries[i].first_name))
				.arg(QString(entries[i].last_name))
				.arg(QString(entries[i].father_name))
				.arg(QString(entries[i].phone));
		if (!query.exec(command)) {
			qDebug() << "Fail input";
		} else{
			saved_size++;
		}
	}
	m_db.close();
	return saved_size;
}

QString readString(const QSqlQuery &query,
				   const QSqlRecord& record,
				   const EntryType type)
{
	return query.value(record.indexOf(EntryType2Str(type))).toString();
}

EntryIdl readEntry(const QSqlQuery &query, const QSqlRecord &record){
	EntryIdl result;
	result.first_name = CORBA::string_dup(
				readString(query, record, EntryType::FirstName).toStdString().data());
	result.last_name = CORBA::string_dup(
				readString(query, record, EntryType::LastName).toStdString().data());
	result.father_name = CORBA::string_dup(
				readString(query, record, EntryType::FatherName).toStdString().data());
	result.phone = CORBA::string_dup(
				readString(query, record, EntryType::Phone).toStdString().data());
	return result;
}
