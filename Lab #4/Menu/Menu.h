#ifndef MENU
#define MENU

#include <iostream>

#include "../Containers/List.h"
#include "./MenuItem.h"
#include "../Comparators.h"
#include "../ConsoleCorrectEnterer.h"

class Menu
{
private:
	const char *m_Title{};
	List<MenuItem> m_Items{};
	bool m_IsExit{ false };
	ConsoleCorrectEnterer enterer{};

public:
	Menu() = delete;
	Menu(const Menu&) = delete;
	Menu(Menu&&) = delete;

	Menu(char* title, std::initializer_list<MenuItem> items, 
		char* exitItemTitle)
		: m_Title(title)
	{
		uint16_t i{ (uint16_t)m_Items.Size() };
		for (const MenuItem& item : items)
		{
			MenuItem newItem{ ++i, item.GetName(), item.GetAction()};
			m_Items.AddBack(newItem);
		}

		MenuItem exitItem{ ++i, exitItemTitle };
		m_Items.AddBack(exitItem);
	}

	~Menu() = default;

	void MainLoop()
	{
		while (1)
		{
			system("cls");
			std::cout << m_Title << '\n';

			PrintItems();

			uint16_t selectedItemIndex = (uint16_t)
				ConsoleCorrectEnterer::EnterNumber<int32_t>
				("Select item: ", 1, (int32_t)m_Items.Size());

			if (selectedItemIndex == m_Items.Size())
			{
				break;
			}
			InvokeSelected(selectedItemIndex);
		}
	}
	
private:
	void PrintItems()
	{
		List<MenuItem>::Iterator iter{ m_Items.begin() };

		do
		{
			std::cout << iter.GetCurrent() << '\n';
		} while (iter.MoveNext());
		std::cout << '\n';
	}
	void InvokeSelected(uint16_t index)
	{
		MenuItem item{ *m_Items.Search(index, Comps::ItemIndexComp) };

		system("cls");
		std::cout << "You selected: " << item << '\n';
		item.Invoke();

		system("pause");
	}

};

#endif