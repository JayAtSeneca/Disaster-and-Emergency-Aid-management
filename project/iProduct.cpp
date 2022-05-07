#include "iProduct.h"
using namespace std;
namespace sdds
{
	std::ostream& operator<<(std::ostream& ostr, const iProduct& i)
	{
		return i.display(ostr);
	}

	std::istream& operator>>(std::istream& istr, iProduct& i)
	{
		return i.read(istr);
	}

}

