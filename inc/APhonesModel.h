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
	APhonesModel(QObject* parent = nullptr);
	virtual ~APhonesModel() override = default;
	QHash<int, QByteArray> roleNames() const override;
};
