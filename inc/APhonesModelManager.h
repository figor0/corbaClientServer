#pragma once
#include <QObject>
#include <memory>

class APhonesModel;

class APhonesModelManager: public QObject
{
	Q_OBJECT
public:
	using Model_ptr = std::shared_ptr<APhonesModel>;
	APhonesModelManager(QObject* parent = nullptr);
	virtual ~APhonesModelManager() override = default;
	bool setModel(Model_ptr model_ptr);
	Q_INVOKABLE bool load(int action = 0);
	Q_INVOKABLE bool change(const int action);
protected:
	virtual bool private_load(int action = 0) = 0;
	virtual bool private_chagne(const int action) = 0;
	Model_ptr m_model_ptr;
};
