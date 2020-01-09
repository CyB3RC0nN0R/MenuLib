# MenuLib
CUI generation library for C on Windows


## Einbindung in eine Visual Studio Projektmappe:

Repository klonen und das Projekt "MenuLib" zur Projektmappe hinzufügen:
> Rechtsklick auf Projektmappe -> Hinzufügen -> Vorhandenes Projekt...

Verweis auf die Bibliothek im Aufruferprojekt anlegen:
> Rechtsklick auf Aufruferprojekt -> Hinzufügen -> Verweis...
> Haken bei "MenuLib" setzen.

Zusätzliches Includeverzeichnis hinzufügen:
> Rechtsklick auf Aufruferprojekt -> Eigenschaften -> Linked -> Eingabe -> Zusätzliche Abhängigkeiten -> Bearbeiten...
> Ordner, der "menu.h" enthält, auswählen

Headerdatei einbinden:
> Zeile ```#include "menu.h"``` zur Quelldatei hinzufügen

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
  
