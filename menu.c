#include "pch.h"
#include "framework.h"
#include "menu.h"

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

void page(const struct MenuPage *pages, const size_t page_count) {
	unsigned int page_index = 0;
	bool action_performed, loop, pageChanged = true;
	char pageKey, itemKey;

	do {
		do {
			show_menu(pages[page_index].item_count, pages[page_index].items, pages[page_index].title, pages[page_index].border);

			// Wait for user selection
			putchar('>');
			putchar(' ');
	
			loop = pages[page_index].loopback;
			pageKey = _getch();

			if (pageKey == 'm')
				page_index < page_count - 1 ? page_index++ : page_index;
			else if (pageKey == 'n') 
				page_index > 0 ? page_index-- : page_index;
			else {
				pageChanged = false;
				itemKey = pageKey;
				do {
					action_performed = false;

					itemKey != pageKey ? itemKey = _getch() : pageKey;
					pageKey = 0;
					for (int i = 0; i < pages[page_index].item_count; ++i) {
						if (pages[page_index].items[i].key == itemKey) {
							// Perform action
							system("cls");
							pages[page_index].items[i].action();
							action_performed = true;

							// Pause if requested
							if (pages[page_index].pause) {
								putchar('\n');
								system("pause");
							}
						} 
					}
				} while (!action_performed);
			}
		} while (loop || pageChanged);

		page_index = 0;
	} while (1);
}

void show_menu(const int itemc, const struct MenuItem itemv[], const char title[], const struct MenuBorder *border)
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
				if (j == ((width - strlen(title)) - 2)/ 2)
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
		else if (is_item_line(i, itemc, &item_index))
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