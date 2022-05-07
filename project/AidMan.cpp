#include <iostream>
#include <fstream>
#include "Utils.h"
#include "AidMan.h"

using namespace std;

namespace sdds
{
	unsigned int AidMan::menu() const
	{
		int year = 0;
		int month = 0;
		int day = 0;
		ut.getSystemDate(&year, &month, &day);
		cout << "Aid Management System" << endl;
		cout << "Date: " << year << "/0" << month << "/" << day << endl;
		cout << "Data file: ";
		if (m_file != nullptr)
		{
			cout << m_file << endl;
		}
		else
		{
			cout << "No file" << endl;
		}
		cout << "---------------------------------" << endl;
		int  num = Menu::run();
		return num;
	}

	AidMan::AidMan(unsigned int num, const char* str) :Menu(num, str)
	{
		m_file = nullptr;
	}

	AidMan::~AidMan()
	{
		deallocate();
	}

	void AidMan::run()
	{
		int num = 0;
		char tempName[30] = { "\0" };
		do
		{
			num = menu();
			if (m_file == nullptr && num != 0)
			{
				switch (num)
				{
				default:
					cout << "\n****New/Open Aid Database****" << endl;
					cout << "Enter file name: ";
					char tempName[30] = { "\0" };
					cin >> tempName;
					if (load(tempName))
					{
						cout << m_numIProdItems << " records loaded!" << endl << endl;
					}
					break;
				}
			}
			else
			{
				switch (num)
				{
				case 0:
					cout << "Exiting Program!" << endl;
					save();
					break;
				case 1:
					cout << "\n****List Items****" << endl;
					list();
					break;
				case 2:
					cout << "\n****Add Item****" << endl;
					addItem();
					break;
				case 3:
					cout << "\n****Remove Item****" << endl;
					remove();
					break;
				case 4:
					cout << "\n****Update Quantity****" << endl;
					updateQuantity();
					break;
				case 5:
					cout << "\n****Sort****" << endl;
					sort();
					break;
				case 6:
					cout << "\n****Ship Items****" << endl;
					shipOrderFile();
					break;
				case 7:
					cout << "\n****New/Open Aid Database****\n" << endl;
					cout << "Enter file name: ";
					
					cin >> tempName;
					if (load(tempName))
					{
						cout << m_numIProdItems << " records loaded!" << endl;
					}
					break;
				default:
					break;
				}
			}
		} while (num != 0);
	}
	int AidMan::list(const char* sub_desc)
	{
		int rowCounter = 0;
		bool rowInput = true;
		if (m_numIProdItems > 0) {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			if (sub_desc == nullptr)
			{

				for (int i = 0; i < m_numIProdItems; i++)
				{
					cout << " ";
					cout.setf(ios::right);
					cout.width(3);
					cout.fill(' ');
					cout << i + 1;
					cout.unsetf(ios::right);
					cout << " | ";
					m_ptr[i]->linear(true);
					m_ptr[i]->display(cout);
					cout << endl;
					rowCounter++;
				}
			}
			else
			{
				for (int i = 0; i < m_numIProdItems; i++)
				{
					if (m_ptr[i]->operator==(sub_desc))
					{
						cout << " ";
						cout.setf(ios::right);
						cout.width(3);
						cout.fill(' ');
						cout << i + 1;
						cout.unsetf(ios::right);
						cout << " | ";
						m_ptr[i]->linear(true);
						m_ptr[i]->display(cout);
						cout << endl;
						rowCounter++;
						rowInput = false;
					}
				}
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			
			if (rowInput) {
				cout << "Enter row number to display details or <ENTER> to continue:\n> ";
				cin.ignore();
				if (cin.peek() != '\n') {
					char temp[4] = "";
					cin >> temp;
					int tempNum = atoi(temp);
					m_ptr[tempNum - 1]->linear(false);
					m_ptr[tempNum - 1]->display(cout);
				}
				cout << endl;
			}
		}
		else
		{
			cout << "The list is emtpy!" << endl;
		}
		return rowCounter;
	}
	AidMan& AidMan::save()
	{
		if (m_file)
		{
			ofstream file;
			file.open(m_file);
			for (int i = 0; i < m_numIProdItems; i++)
			{
				m_ptr[i]->save(file)<<endl;
			}
		}
		return *this;
	}
	AidMan& AidMan::deallocate()
	{
		for (int i = 0; i < m_numIProdItems; i++)
		{
			delete m_ptr[i];
		}
		delete[] m_file;
		m_file = nullptr;
		m_numIProdItems = 0;
		return *this;
	}
	bool AidMan::load(const char* tempFileName)
	{
		bool isLoaded = false;
		bool done = false;
		int loadCounter = 0;
		save();
		deallocate();
		ut.alocpy(m_file, tempFileName);
		ofstream newFile;
		ifstream file;
		file.open(m_file);
		if (!file.is_open())
		{
			cout << "Failed to open " << m_file << " for reading!";
			cout << "Would you like to create a new data file?";
			cout << "1- Yes!\n0- Exit\n>";
			int tempNum = ut.getint();
			switch (tempNum)
			{
			case 1:
				newFile.open(m_file);
				done = true;
				break;
			case 0:
				break;
			default:
				break;
			}
		}
		if (file.is_open() && done != true)
		{
			while (file)
			{
				char peek = file.peek();
				if (peek == '1' || peek == '2' || peek == '3')
				{
					m_ptr[m_numIProdItems] = new Perishable;
					
					m_ptr[m_numIProdItems]->load(file);
					if (m_ptr[m_numIProdItems]->operator bool())
					{
						m_numIProdItems++;
						loadCounter++;
					}
					else
					{
						delete m_ptr[m_numIProdItems];
					}
				}
				else if (peek == '4' || peek == '5' || peek == '6' || peek == '7' || peek == '8' || peek == '9')
				{
					m_ptr[m_numIProdItems] = new Item;
					m_ptr[m_numIProdItems]->load(file);
					if (m_ptr[m_numIProdItems]->operator bool())
					{
						m_numIProdItems++;
						loadCounter++;
					}
					else
					{
						delete m_ptr[m_numIProdItems];
					}
				}
				else if (!isdigit(file.peek()))
				{
					file.setstate(ios::failbit);
				}
			}
		}
		if (m_numIProdItems > 0)
		{
			isLoaded = true;
		}
		return isLoaded;
	}
	int AidMan::search(int sku) const
	{
		int retIndex = -1;
		bool done = false;
		for (int i = 0; i < m_numIProdItems && done!= true; i++)
		{
			if (m_ptr[i]->operator==(sku))
			{
				retIndex = i;
				done = true;
			}
		}
		return retIndex;
	}
	AidMan& AidMan::addItem()
	{
		if (m_numIProdItems > sdds_max_num_items)
		{
			cout << "Database full!" << endl;
		}
		else
		{
			bool done = false;
			iProduct* tempPerishable;
			iProduct* tempItem;
			int tempSku = 0;
			cout << "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ";
			int num = 0;
			cin >> num;
			switch (num)
			{
			case 1:
				tempPerishable = new Perishable;
				cout << "SKU: ";
				cin >> tempSku;
				for (int i = 0; i < m_numIProdItems && done != true; i++)
				{
					if (m_ptr[i]->operator==(tempSku))
					{
						cout << "Sku: " << tempSku << " is already in the system, try updating quantity instead.\n" << endl;
						done = true;
						delete tempPerishable;
					}
				}
				
				if(done == false)
				{
					tempPerishable->read(cin);
					cout << endl;
					if (tempPerishable->operator bool())
					{
						m_ptr[m_numIProdItems] = tempPerishable;
						m_numIProdItems++;
					}
					else
					{
						tempPerishable->display(cout);
						delete tempPerishable;
					}
				}
				break;
			case 2:
				tempItem = new Item;
				cout << "SKU: ";
				cin >> tempSku;
				for (int i = 0; i < m_numIProdItems && done != true; i++)
				{
					if (m_ptr[i]->operator==(tempSku))
					{
						cout << "Sku: " << tempSku << " is already in the system, try updating quantity instead.\n" << endl;
						done = true;
						delete tempItem;
					}
				}
				if(done == false)
				{
					tempItem->read(cin);
					cout << endl;
					if (tempItem->operator bool())
					{
						m_ptr[m_numIProdItems] = tempItem;
						m_numIProdItems++;
					}
					else
					{
						tempItem->display(cout);
						delete tempItem;
					}
				}
				break;
			case 0:
				cout << "Aborted\n";
				break;
			default:
				break;
			}
		}
		return *this;
	}
	AidMan& AidMan::remove()
	{
		bool done = false;
		int delIndex = 0;
		char tempDes[100] = { "\0" };
		cout << "Item description: ";
		cin.ignore(1000, '\n');
		cin.getline(tempDes, 100, '\n');
		int num = list(tempDes);
		if (num > 0)
		{
			int tempSku = ut.getint("Enter SKU: ");
			for (int i = 0; i < m_numIProdItems && done != true; i++)
			{
				if (m_ptr[i]->operator==(tempSku))
				{
					cout << "Following item will be removed: " << endl;
					m_ptr[i]->linear(false);
					m_ptr[i]->display(cout) << endl;
					cout << "Are you sure?\n1- Yes!\n0- Exit\n> ";
					int tempInt = 0;
					cin >> tempInt;
					switch (tempInt)
					{
					case 1:
						delIndex = i;
						delete m_ptr[i];
						for (int j = delIndex; j < m_numIProdItems; j++)
						{
							m_ptr[j] = m_ptr[j + 1];
						}
						m_numIProdItems--;
						cout << "Item removed!" << endl << endl;
						done = true;
						break;
					case 0:
						cout << "Aborted!" << endl;
						break;
					default:
						break;
					}
				}
			}
		}
		return *this;
	}
	AidMan& AidMan::updateQuantity()
	{
		bool done = false;
		char tempDes[100] = { "\0" };
		cout << "Item description: ";
		cin.ignore(1000, '\n');
		cin.getline(tempDes, 100, '\n');
		int num = list(tempDes);
		if (num > 0)
		{
			int tempSku = ut.getint("Enter SKU: ");
			for (int i = 0; i < m_numIProdItems && done != true; i++)
			{
				if (m_ptr[i]->operator==(tempSku))
				{
					int select = 0;
					cout << "1- Add\n2- Reduce\n0- Exit\n> ";
					cin >> select;
					switch (select)
					{
					case 1:
						if (m_ptr[i]->qty() >= m_ptr[i]->qtyNeeded())
						{
							cout << "Quantity Needed already fulfilled!\n" << endl;
						}
						else
						{
							int tempAdd = ut.getint(1, m_ptr[i]->qtyNeeded(), "Quantity to add: ");
							m_ptr[i]->operator+=(tempAdd);
							cout << tempAdd << " items added!\n" << endl;
						}
						break;
					case 2:
						if (m_ptr[i]->qty() == 0)
						{
							cout << "Quaintity on hand is zero!\n" << endl;
						}
						else
						{
							int tempReduce = ut.getint(1, m_ptr[i]->qtyNeeded(), "Quantity to reduce: ");
							m_ptr[i]->operator-=(tempReduce);
							cout << tempReduce << " items removed!\n" << endl;
						}
						break;
					case 0:
						cout << "Aborted!\n" << endl;
						break;
					default:
						break;
					}
					done = true;
				}
			}
			if (done != true)
			{
				cout << "SKU not found!\n";
			}
		}
		else
		{
			cout << "No matches found!\n";
		}
		return *this;
	}
	AidMan& AidMan::sort()
	{
		
		for (int i = 0; i < m_numIProdItems - 1; i++)
		{
			
			for (int j = 0; j < m_numIProdItems - i - 1; j++)
			{
				int leftQty = m_ptr[j]->qty();
				int leftQtyNeed = m_ptr[j]->qtyNeeded();
				int left = leftQtyNeed - leftQty;
				int rightQty = m_ptr[j + 1]->qty();
				int rightQtyNeed = m_ptr[j + 1]->qtyNeeded();
				int right = rightQtyNeed - rightQty;
				if (left < right)
				{
					iProduct* temp;
					temp = m_ptr[j];
					m_ptr[j] = m_ptr[j + 1];
					m_ptr[j + 1] = temp;
				}
			}
		}
		cout << "Sort completed!\n" << endl;

		return *this;
	}
	AidMan& AidMan::shipOrderFile()
	{
		int shipCounter = 0;
		int day = 0;
		int month = 0;
		int year = 0;
		ut.getSystemDate(&year, &month, &day);
		ofstream file;
		file.open("shippingOrder.txt");
		file << "Shipping Order, Date: " << year << "/0" << month << "/" << day << endl;
		file << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		for (int i = 0; i < m_numIProdItems; i++)
		{
			if (m_ptr[i]->qty() == m_ptr[i]->qtyNeeded())
			{
				m_ptr[i]->linear(true);
				shipCounter++;
				file << " ";
				file.setf(ios::right);
				file.width(3);
				file << shipCounter;
				file.unsetf(ios::right);
				file << " | ";
				m_ptr[i]->display(file) << endl;
				removeByIndex(i);
			}
		}
		file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		cout << "Shipping Order for " << shipCounter << " times saved!\n" << endl;
		return *this;
	}
	int AidMan::removeByIndex(int index)
	{
		int delIndex = index;
		delete m_ptr[index];
		for (int j = delIndex; j < m_numIProdItems; j++)
		{
			m_ptr[j] = m_ptr[j + 1];
		}
		m_numIProdItems--;
		return 0;
	}
}