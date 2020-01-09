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

/// <summary>Displaces a CUI menu to the user and lets them choose an option, then calls the corresponding function.</summary>
/// <param name="itemc">The length of the array <c>itemv</c> of menu items.</param>
/// <param name="itemv">An array of all menu items to display in the menu.</param>
/// <param name="title">The title of the menu.</param>
/// <param name="loopback">If this parameter is set to <c>true</c>, the menu will be displayed again after an action is executed.</param>
/// <param name="pause">If this parameter is set to <c>true</c>, a <c>pause</c>command will be run after an action is executed.</param>
/// <param name="border">Specifies the border in which the menu is displayed.</param>
void show_menu(const int itemc, const struct MenuItem itemv[], const char title[], const bool loopback, const bool pause, const struct MenuBorder *border);