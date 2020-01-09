# MenuLib
CUI generation library for C on Windows


## Hinweis zum Installieren:

Sowohl "menu.c" als auch "menu.h" zum Projektordner hinzufügen und mit ```#include "menu.h"``` einbinden.

### Anwendungsbeispiel
```C
struct MenuItem items[] = {
		{"Euklidscher Algorithmus",	'1', (void*)&euklid},
		{"Gerstenkorn",			'2', (void*)&gerste},
		{"Osterdatum ausrechnen",	'3', (void*)&ostern},
		{"ASCII Tabelle",		'4', (void*)&ascii},
		{"DB-Pruefziffer",		'5', (void*)&db},
		{"Modulo 11",			'6', (void*)&mod11},
		{"BLANK",			NULL, (void*)NULL},
		{"Namen TEST",			'a', (void*)&namen},
		{"Strings",			'b', (void*)&strHeader},
		{"BLANK",			NULL, (void*)NULL},
		{"Exit",			'q', (void*)&exit}
	};
	show_menu(sizeof(items) / sizeof(struct MenuItem), items, "Vorlesungsaufgaben", true, true, NO_BORDER);
  ````
  
