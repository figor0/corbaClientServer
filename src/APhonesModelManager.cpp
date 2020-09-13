#include <APhonesModelManager.h>
#include <APhonesModel.h>

APhonesModelManager::APhonesModelManager(QObject *parent): QObject(parent)
{}

bool APhonesModelManager::load(int action){
	bool right_flag = false;
	if (m_model_ptr != nullptr)
		right_flag = private_load(action);
	return  right_flag;
}

bool APhonesModelManager::change(const int action){
	bool right_flag = false;
	if (m_model_ptr != nullptr)
		right_flag = private_chagne(action);
	return right_flag;
}
