#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include <iostream>
#include <fstream>
#include "iProduct.h"
#include "Status.h"
namespace sdds
{
	class Item :public iProduct
	{
		double m_price;
		int m_quantityInHand;
		int m_quantityReq;
		char* m_itemDescription;
		bool m_flag;
	protected:
		Status m_state;
		int m_sku;
		bool linear()const;
		int m_minSkuNum = 40000;
		int m_maxSkuNum = 99999;
	public:
		Item();
		Item(const Item& i);
		Item& operator=(const Item& i);
		~Item();
		// public queries
		virtual int qtyNeeded()const;
		virtual int qty()const;
		virtual operator double()const;
		virtual operator bool()const;
		//modifiers
		virtual int operator-=(int quantityInHand);
		virtual int operator+=(int quantityInHand);
		virtual void linear(bool flag);
		Item& clear();
		virtual bool operator==(int sku)const;
		virtual bool operator==(const char* description)const;
		virtual std::ofstream& save(std::ofstream& ofstr)const;
		virtual std::ifstream& load(std::ifstream& ifstr);
		virtual std::ostream& display(std::ostream& ostr)const;
		virtual std::istream& read(std::istream& istr);
		virtual int readSku(std::istream& istr);
	};
}
#endif // !SDDS_ITEM_H
