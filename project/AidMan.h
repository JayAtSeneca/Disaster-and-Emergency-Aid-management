#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
#include "iProduct.h"
#include "Perishable.h"
namespace sdds
{
	const int sdds_max_num_items = 100;
	class AidMan :public Menu
	{
		char* m_file{};
		iProduct* m_ptr[sdds_max_num_items]{};
		int m_numIProdItems{};
		unsigned int menu()const;

	public:
		AidMan(unsigned int num = 7, const char* str = "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n");
		AidMan(const AidMan& a) = delete;
		AidMan& operator=(const AidMan& a) = delete;
		virtual ~AidMan();
		void run();
		int list(const char* sub_desc = nullptr);
		AidMan& save();
		AidMan& deallocate();
		bool load(const char* tempFileName);
		int search(int sku)const;
		AidMan& addItem();
		AidMan& remove();
		AidMan& updateQuantity();
		AidMan& sort();
		AidMan& shipOrderFile();
		int removeByIndex(int index);
	};
}
#endif // !SDDS_AIDMAN_H
