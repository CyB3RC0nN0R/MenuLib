#pragma once

#include "pch.h"


/// <summary>Represents one menu item in a menu.</summary>
struct MenuItem {
	char* text;
	char key;
	void* (*action)(void);
};

/// <summary>Represents a border in which a menu is displayed.</summary>
struct MenuBorder {
	char line_vertical;
	char line_horizontal;
	char corner_upper_left;
	char corner_upper_right;
	char corner_lower_left;
	char corner_lower_right;
	char title_left;
	char title_right;
};

const extern struct MenuBorder DEFAULT, MODERN, NO_BORDER, SOLID;


/// <summary>Represents a page in the menu.</summary>
struct MenuPage {
	const struct MenuItem* items;
	const size_t item_count;
	char* title;
	bool loopback, pause;
	const struct MenuBorder* border;
};


/// <summary>Constructs a menu with a specific amount of pages</summary>
/// <param name="pages">An array of all pages to display.</param>
/// <param name="page_count">The length of the array <c>pages</c>.</param>
/// <param name="infinite_loop">Always display the first page after a loopback=false item finished executing.</param>
void page(const struct MenuPage* pages, const size_t page_count, const bool infinite_loop);

/// <summary>Displaces a CUI menu to the user</summary>
/// <param name="itemc">The length of the array <c>itemv</c> of menu items.</param>
/// <param name="itemv">An array of all menu items to display in the menu.</param>
/// <param name="title">The title of the menu.</param>
/// <param name="border">Specifies the border in which the menu is displayed.</param>
void show_menu(const int itemc, const struct MenuItem itemv[], const char title[], const struct MenuBorder *border);