#include "menu.h"

#include <conio.h>
#include <stdio.h>
#include <Windows.h>

const struct MenuBorder DEFAULT = {
	'*', '*', '*', '*', '*', '*', '[', ']'
};

const struct MenuBorder MODERN = {
	'|', '-', '-', '-', '-', '-', '[', ']'
};

const struct MenuBorder NO_BORDER = {
	' ', ' ', ' ', ' ', ' ' ,' ' ,' ' ,' '
};

const struct MenuBorder SOLID = {
	186, 205, 201, 187, 200, 188, '[', ']'
};

void print_content(const size_t itemc, const struct MenuItem itemv[], const char title[], const struct MenuBorder* border);

void show_menu(const struct MenuPage* pages, const size_t page_count, const int infinite_loop)
{
	unsigned page_index = 0;
	int action_performed, page_changed, i;
	char key;

	do {
		print_content(pages[page_index].item_count, pages[page_index].items, pages[page_index].title, pages[page_index].border);

		// Wait for user selection
		putchar('>');
		putchar(' ');

		do {
			page_changed = 0;
			action_performed = 0;

			// Get user selection
			key = _getch();

			// Forward paging
			if (key == 'm' && page_index < page_count - 1)
			{
				++page_index;
				page_changed = 1;
			}
			// Backward paging
			else if (key == 'n' && page_index > 0)
			{
				--page_index;
				page_changed = 1;
			}
			else
			{
				// Search for action with a matching key
				for (i = 0; i < pages[page_index].item_count; ++i)
				{
					if (pages[page_index].items[i].key == key)
					{
						// Perform action
						system("cls");
						pages[page_index].items[i].action(pages[page_index].items[i].param);
						action_performed = 1;

						// Pause if requested
						if (pages[page_index].pause)
						{
							putchar('\n');
							system("pause");
						}
					}
				}
			}
		} while (!action_performed && !page_changed);

		if (!pages[page_index].loopback && !page_changed)
		{
			page_index = 0;
		}
	} while (infinite_loop);
}

// Checks if a line index should display a menu item
int is_item_line(const int line, const int itemc, int* item_index)
{
	if (line >= 2 && line % 2 == 0)
	{
		// Lines 2, 4, ...
		*item_index = (line - 2) / 2;
		return *item_index < itemc;
	}
	return 0;
}

// Acquires the dimensions (width and height) of the console window
void get_console_dimensions(int* width, int* height)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	*width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	*height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Draws a menu to the console
void print_content(const size_t itemc, const struct MenuItem itemv[], const char title[], const struct MenuBorder* border)
{
	unsigned width, height, item_index;

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
			// Upper left corner
			putchar(border->corner_upper_left);

			for (unsigned j = 1; j < width - strlen(title) - 2; ++j)
			{
				if (j == ((width - strlen(title)) - 2) / 2)
				{
					putchar(border->title_left);
					fputs(title, stdout);
					putchar(border->title_right);
				}
				else
				{
					putchar(border->line_horizontal);
				}
			}

			// Upper right corner
			putchar(border->corner_upper_right);
		}
		// Line with menu item
		else if (is_item_line(i, (int)itemc, &item_index))
		{
			// Print item text
			putchar(border->line_vertical);

			if (strcmp(itemv[item_index].text, "BLANK") == 0) {
				putchar('\t');

				// BLANK equals 5 characters 
				// + 3 since it regularly is "%c) " inbetween title and key
				for (unsigned j = 0; j < 8; ++j)
				{
					putchar(' ');
				}
			}
			else
			{
				printf("\t%c) %s", itemv[item_index].key, itemv[item_index].text);
			}

			// Print right side of frame
			for (unsigned j = 0; j < width - strlen(itemv[item_index].text) - 12; ++j)
			{
				putchar(' ');
			}

			putchar(border->line_vertical);
		}
		// Line above bottom line
		else if (i == height - 3)
		{
			// Lower left corner
			putchar(border->corner_lower_left);

			for (unsigned j = 1; j < width - 1; ++j)
			{
				putchar(border->line_horizontal);
			}

			// Lower right corner
			putchar(border->corner_lower_right);
		}
		// Blank line
		else
		{
			i != height - 2 ? putchar(border->line_vertical) : putchar(' ');
			for (unsigned j = 0; j < width - 2; ++j)
			{
				putchar(' ');
			}
			i != height - 2 ? putchar(border->line_vertical) : putchar(' ');
		}
	}
}