#pragma once
#include <QAbstractTableModel>
#include <QHash>
#include <QByteArray>

class APhonesModel: public QAbstractTableModel
{
	Q_OBJECT
public:
	enum PhoneEntryRoles{
		FirstName = Qt::UserRole + 1,
		LastName,
		FatherName,
		Phone
	};
	virtual ~APhonesModel() = 0;
	QHash<int, QByteArray> roleNames() const;
};
