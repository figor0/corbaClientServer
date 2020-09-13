#include <APhonesModel.h>

QHash<int, QByteArray> APhonesModel::roleNames() const
{
	return {
		{FirstName, "first_name"},
		{LastName, "last_name"},
		{FatherName, "father_name"},
		{Phone, "phone"}
	};
}
