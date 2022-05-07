#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"
namespace sdds
{
	class Perishable:public Item
	{
		Date m_expiry;
		char* m_instructions{};
	public:
		Perishable();
		Perishable(const Perishable& p);
		Perishable& operator=(const Perishable& p);
		operator bool()const;
		~Perishable();
		const Date& expiry()const;
		virtual int readSku(std::istream& istr);
		virtual std::ofstream& save(std::ofstream& ofstr)const;
		virtual std::ifstream& load(std::ifstream& ifstr);
		virtual std::ostream& display(std::ostream& ostr)const;
		virtual std::istream& read(std::istream& istr);
	};
}
#endif // !SDDS_PERISHABLE_H
