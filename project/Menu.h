#ifndef SDDS_MENU_H
#define SDDS_MENU_H
namespace sdds
{
	class Menu
	{
		char* m_content{};
		unsigned int m_options = 0u;
	public:
		Menu(unsigned int num = 16, const char* str = nullptr);
		Menu(const Menu& m) = delete;
		Menu& operator=(const Menu& m) = delete;
		virtual ~Menu();
		unsigned int run()const;
	};
}
#endif // !SDDS_MENU_H
