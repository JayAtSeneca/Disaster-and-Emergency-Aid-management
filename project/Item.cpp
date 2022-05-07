#include <cstring>
#include "Item.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
	bool Item::linear() const
	{
		return m_flag;
	}
	Item::Item()
	{
		m_itemDescription = nullptr;
		m_flag = false;
		m_price = 0.0;
		m_quantityInHand = 0;
		m_quantityReq = 0;
		m_sku = 0;
	}
	Item::Item(const Item& i)
	{
		operator=(i);
	}
	Item& Item::operator=(const Item& i)
	{
		if (this != &i)
		{
			ut.alocpy(m_itemDescription, i.m_itemDescription);
			m_flag = i.m_flag;
			m_price = i.m_price;
			m_quantityInHand = i.m_quantityInHand;
			m_quantityReq = i.m_quantityReq;
			m_sku = i.m_sku;
		}
		return *this;
	}
	Item::~Item()
	{
		delete[] m_itemDescription;
	}
	int Item::qtyNeeded() const
	{
		return m_quantityReq;
	}
	int Item::qty() const
	{
		return m_quantityInHand;
	}
	Item::operator double() const
	{
		return m_price;
	}
	Item::operator bool() const
	{
		return m_state;
	}
	int Item::operator-=(int quantityInHand)
	{
		m_quantityInHand -= quantityInHand;
		return 0;
	}
	int Item::operator+=(int quantityInHand)
	{
		m_quantityInHand += quantityInHand;
		return 0;
	}
	void Item::linear(bool flag)
	{
		m_flag = flag;
	}
	Item& Item::clear()
	{
		m_state.clear();
		return *this;
	}
	bool Item::operator==(int sku) const
	{
		bool done = false;
		if (sku == m_sku)
		{
			done = true;
		}
		return done;
	}
	bool Item::operator==(const char* description) const
	{
		bool done = false;
		if (description != NULL)
		{
			char* ptr;
			ptr = strstr(m_itemDescription, description);
			if (ptr)
			{
				done = true;
			}
		}
		return done;
	}
	std::ofstream& Item::save(std::ofstream& ofstr) const
	{
		if (m_state)
		{
			ofstr << m_sku << "\t";
			ofstr << m_itemDescription << "\t";
			ofstr << m_quantityInHand << "\t";
			ofstr << m_quantityReq << "\t";
			ofstr.setf(ios::fixed);
			ofstr.precision(2);
			ofstr << m_price;
			ofstr.unsetf(ios::fixed);
		}
		return ofstr;
	}
	std::ifstream& Item::load(std::ifstream& ifstr)
	{
		int tempSKU;
		char tempDescription[500];
		int tempQuantityInHand;
		int tempQuantityReq;
		double tempPrice;
		ifstr >> tempSKU;
		ifstr.ignore();
		ifstr.getline(tempDescription, 500, '\t');
		ifstr >> tempQuantityInHand;
		ifstr.ignore();
		ifstr >> tempQuantityReq;
		ifstr.ignore();
		ifstr >> tempPrice;
		ifstr.ignore();
		m_sku = tempSKU;
		ut.alocpy(m_itemDescription, tempDescription);
		m_quantityInHand = tempQuantityInHand;
		m_quantityReq = tempQuantityReq;
		m_price = tempPrice;
		if (ifstr.bad())
		{
			m_state = "Input file stream read failed!";
		}
		tempDescription[0] = '\0';
		return ifstr;
	}
	std::ostream& Item::display(std::ostream& ostr) const
	{

		if (!m_state)
		{
			ostr << m_state;
		}
		else
		{
			if (linear())
			{
				ostr.setf(ios::fixed);
				ostr.width(5);
				ostr << m_sku;
				ostr.unsetf(ios::fixed);
				ostr << " | ";
				ostr.setf(ios::fixed);
				bool done = false;
				int i = 0;
				for (i = 0; i < 35 && done != true; i++)
				{
					if (m_itemDescription[i] != '\0')
					{
						ostr << m_itemDescription[i];
					}
					else
					{
						done = true;
					}
				}
				if (i < 35)
				{
					int tempLength = 35 - strlen(m_itemDescription);
					for (int j = 0; j < tempLength; j++)
					{
						ostr << " ";
					}
				}
				ostr.unsetf(ios::fixed);
				ostr << " | ";
				ostr.setf(ios::fixed);
				ostr.width(4);
				ostr.fill(' ');
				ostr << right << m_quantityInHand;
				ostr.unsetf(ios::fixed);
				ostr << " | ";
				ostr.setf(ios::fixed);
				ostr.width(4);
				ostr.fill(' ');
				ostr << right << m_quantityReq;
				ostr.unsetf(ios::fixed);
				ostr << " | ";
				ostr.setf(ios::fixed);
				ostr.width(7);
				ostr.fill(' ');
				ostr.precision(2);
				ostr << right << m_price;
				ostr.unsetf(ios::fixed);
				ostr << " |";
			}
			else
			{
				int tempQty = m_quantityReq - m_quantityInHand;
				ostr << "AMA Item:" << endl;
				ostr << m_sku << ": " << m_itemDescription << endl;
				ostr << "Quantity Needed: " << m_quantityReq << endl;
				ostr << "Quantity Available: " << m_quantityInHand << endl;
				ostr.setf(ios::fixed);
				ostr.precision(2);
				ostr << "Unit Price: $" << m_price << endl;
				ostr << "Needed Purchase Fund: $" << (m_price * tempQty) << endl;
				ostr.unsetf(ios::fixed);
			}
		}

		return ostr;
	}
	std::istream& Item::read(std::istream& istr)
	{
		//delete[] m_description;
		m_state.clear();
		char tempDescription[100];
		int tempQuantityReq;
		int tempQuantityInHand;
		double tempPrice;
		cout << "AMA Item:" << endl;
		/*m_sku = ut.getint(10000, 39999, "SKU: ");*/
		m_sku = ut.getint(m_minSkuNum, m_maxSkuNum, "SKU: ");
		cout << "Description: ";
		istr.ignore(1000, '\n');
		istr.getline(tempDescription, 100);

		tempQuantityReq = ut.getint(1, 9999, "Quantity Needed: ");
		tempQuantityInHand = ut.getint(0, tempQuantityReq, "Quantity On Hand: ");
		tempPrice = ut.getdouble(0.0, 9999.0, "Unit Price: $");
		ut.alocpy(m_itemDescription, tempDescription);
		m_quantityReq = tempQuantityReq;
		m_quantityInHand = tempQuantityInHand;
		m_price = tempPrice;
		if (istr.fail())
		{
			m_state = "Console entry failed!";
		}
		m_minSkuNum = 40000;
		m_maxSkuNum = 99999;
		return istr;
	}
	int Item::readSku(std::istream& istr)
	{
		/*m_sku = ut.getint(40000, 99999, "SKU: ");*/
		m_sku = ut.getint(m_minSkuNum, m_maxSkuNum, "SKU: ");
		m_minSkuNum = 40000;
		m_maxSkuNum = 99999;
		return 0;
	}
}