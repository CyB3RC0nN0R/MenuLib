# MenuLib
CUI generation library for C on Windows


## Einbindung in eine Visual Studio Projektmappe:

Repository klonen und das Projekt "MenuLib" zur Projektmappe hinzufügen:
> Rechtsklick auf Projektmappe -> Hinzufügen -> Vorhandenes Projekt...

Verweis auf die Bibliothek im Aufruferprojekt anlegen:
> Rechtsklick auf Aufruferprojekt -> Hinzufügen -> Verweis...
> Haken bei "MenuLib" setzen.

Zusätzliches Includeverzeichnis hinzufügen:
> Rechtsklick auf Aufruferprojekt -> Eigenschaften -> C/C++ -> Allgemein -> Zusätzliche Includeverzeichnisse -> Bearbeiten...

> Ordner, der "menu.h" enthält, auswählen

> Diese Einstellung muss für die Konfiguration erfolgen, die später compiliert werden soll.

Headerdatei einbinden:
> Zeile ```#include "menu.h"``` zur Quelldatei hinzufügen

### Anwendungsbeispiel
```C
struct MenuItem items[] = {
	{"Euklidscher Algorithmus",	'1', (void*)&euklid},	// String = Name des Menüpunktes
	{"Gerstenkorn",			'2', (void*)&gerste},	// Char = Taste zum Aufrufen
	{"Osterdatum ausrechnen",	'3', (void*)&ostern},	// (void*)&MethodenName = Methode, die aufgerufen wird
	{"ASCII Tabelle",		'4', (void*)&ascii},	// Methode MUSS nicht vom Typ void sein! 
	{"DB-Pruefziffer",		'5', (void*)&db},	// (void*)& MUSS immer davor stehen!
	{"Modulo 11",			'6', (void*)&mod11},
	{"BLANK",			NULL, (void*)NULL},	// Fügt einen leere Zeile hinzu -> Gliederung
	{"Namen TEST",			'7', (void*)&namen},
	{"BLANK",			NULL, (void*)NULL},
	{"Exit",			'q', (void*)&exit}	// exit beendet das Programm
};

struct MenuItem stringsEX[] = {
	{"strcat()",	'1', (void*)&strcatEx},
	{"strlen()",	'2', (void*)&strlenEx},
	{"strncpy()",	'3', (void*)&strncpyEx},
	{"strchr()",	'4', (void*)&strchrEx},
	{"strstr()",	'5', (void*)&strstrEx},
	{"strtok()",	'6', (void*)&strtokEx},
	{"BLANK",	NULL, (void*)NULL},
	{"Ersetzen",	'7', (void*)&replace}
};

struct MenuPage pages[] = {
	{items, sizeof(items) / sizeof(struct MenuItem), "Vorlesungsaufgaben", true, true, &SOLID},
	{stringsEX, sizeof(stringsEX) / sizeof(struct MenuItem), "String - Beispiele", true, true, &SOLID}
	
	/*
	 * 1. Argument: Vorher angelegtes struct; Enthält alle Items der Seite
	 * 2. Argument: Anzahl der Elemente der Seite; Einfach so lassen
	 * 3. Argument: Titel der Seite
	 * 4. Argument: Menü im Loop; Nach beenden der Methode wieder Menü aufrufen	
 	 * 5. Argument: Pause nach dem Ausführen der Methode; Ausgaben lesbar
	 * 6. Argument: Style des Menüs: Standardmäßig wird DEFAULT, MODERN, SOLID und NO_BORDER unterstützt
	 */
};
show_menu(pages, sizeof(pages) / sizeof(struct MenuPage), true);

/* 
 * 1. Argument: Vorher angelegtes struct; Enthält alle Seiten des Menüs
 * 2. Argument: Anzahl der Seiten; Einfach so lassen
 * 3. Argument: Gesamtes Menü in einer unendlich-Schleife
 */
```
### Border hinzufügen
Eigene Border-Styles können wie folgt hinzugefügt werden:		
```C
const struct MenuBorder NAME = {	 
 'a', 	// Char für den rechten und linken Rand
 'b', 	// Char für den oberen und unteren Rand
 'c', 	// Char für die linke obere Ecke
 'd', 	// Char für die rechte obere Ecke
 'e', 	// Char für die linke untere Ecke
 'f', 	// Char für die rechte untere Ecke
 'g', 	// Char zwischen Border und Titel - links
 'h'	// Char zwischen Border und Titel - rechts
}
```

Neue Border am Besten direkt unter den ```#include``` Anweisungen einfügen. Die neue Border kann über den angegebenen Namen, wie im obigen Beispiel erläutert, verwendet werden.
