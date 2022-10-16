#pragma once

#include "./List.h"
#include "./MenuItem.h"

class Menu
{
private:
	List<MenuItem> m_Items{};

public:
	Menu() = default;
	//Menu(const List<MenuItem>& menuItems)
	//	: m_Items(menuItems)
	//{}


	void InvokeSelected(int8_t)
	{
		// m_Items.Find()
	}
};