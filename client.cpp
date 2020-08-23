#include <fstream>
#include <iostream>
#include <CORBA.h>
#include <Server.h>
#include <assert.h>

int main(int argc, char* argv[])
{
   try
   {
	  std::ifstream inp_file ("MyORef.ior");
	  if (!inp_file)
	  {
		  std::cout << "File MyORef.ior not found.\n";
		  return 1;
	  }
	  // Чтение объектной ссылки в строковом
	  // виде из файла
	  char str[1000];
	  inp_file >> str;
	  inp_file.close();
	  // Инициализация взаимодействия с CORBA
	  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
	  // Получение объектной ссылки преобразованием
	  // из строки
	  CORBA::Object_var obj = orb->string_to_object (str);
	  MyInterface_var oRef = MyInterface::_narrow (obj);
	  if (CORBA::is_nil(oRef))
	  {
		 std::cout << "Failure during getting of object"
				 " reference\n";
	  }
	  else
	  {
		  auto entries = oRef->load();
			std::cout << "Entries: " << '\n';
		  for (size_t i = 0; i < entries->length(); i++)
		  {
			  std::cout << " First_name: " << entries->operator[](i).first_name
						<< " Last_name: " << entries->operator[](i).last_name
						<< " Father_name: " << entries->operator[](i).father_name
						<< " Phone: " << entries->operator[](i).phone << '\n';
		  }
	  }
   }
   catch(const CORBA::Exception& e)
   {
	   std::cerr << e._name() << std::endl;
	   return(1);
   }
   return 0;
}
