#include "pch.h"
#include "framework.h"
#include "menu.h"

// Checks if a line index should display a menu item
bool is_item_line(const int line, const int itemc, int* item_index)
{
	if (line >= 2 && line % 2 == 0)
	{
		// Lines 2, 4, ...
		*item_index = (line - 2) / 2;
		return *item_index < itemc;
	}
	return false;
}

// Acquires the dimensions (width and height) of the console window
void get_console_dimensions(int* width, int* height)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	*width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	*height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void show_menu(const int itemc, struct MenuItem itemv[], const char title[], bool loopback, bool pause)
{
	unsigned width, height, item_index;
	char key;
	bool action_performed;

	// Clear the console window
	system("cls");

	// Get the width and height of the console window
	get_console_dimensions(&width, &height);

	// Print frame with title
	for (unsigned i = 0; i < height - 1; ++i)
	{
		// Top line with title
		if (i == 0)
		{
			for (unsigned j = 0; j < width - strlen(title) + 1; ++j)
			{
				if (j == (width - strlen(title)) / 2)
				{
					fputs(title, stdout);
				}
				else
				{
					putchar('*');
				}
			}
		}
		// Line with menu item
		else if (is_item_line(i, itemc, &item_index))
		{
			// Print item text
			printf("*\t%c) %s", itemv[item_index].key, itemv[item_index].text);

			// Print right side of frame
			for (unsigned j = 0; j < width - strlen(itemv[item_index].text) - 12; ++j)
			{
				putchar(' ');
			}
			putchar('*');
		}
		// Line above bottom line
		else if (i == height - 2)
		{
			for (unsigned j = 0; j < width; ++j)
			{
				putchar('*');
			}
		}
		// Blank line
		else
		{
			putchar('*');
			for (unsigned j = 0; j < width - 2; ++j)
			{
				putchar(' ');
			}
			putchar('*');
		}
		putchar('\n');
	}

	// Wait for user selection
	putchar('> ');
	action_performed = false;
	do {
		key = _getch();
		for (int i = 0; i < itemc; ++i)
		{
			if (itemv[i].key == key)
			{
				// Perform action
				system("cls");
				itemv[i].action();
				action_performed = true;

				// Pause if requested
				if (pause)
				{
					putchar('\n');
					system("pause");
				}
			}
		}
	} while (!action_performed);

	// Show menu again if requested
	if (loopback)
	{
		show_menu(itemc, itemv, title, loopback, pause);
	}
}