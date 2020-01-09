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
	{"Euklidscher Algorithmus",	'1', (void*)&euklid},		// String = Name des Menüpunktes
	{"Gerstenkorn",			'2', (void*)&gerste},		// Char = Taste zum Aufrufen
	{"Osterdatum ausrechnen",	'3', (void*)&ostern},		// (void*)&MethodenName = Methode, die aufgerufen wird
	{"ASCII Tabelle",		'4', (void*)&ascii},			// Methode MUSS nicht vom Typ void sein! 
	{"DB-Pruefziffer",		'5', (void*)&db},			// (void*)& MUSS immer davor stehen!
	{"Modulo 11",			'6', (void*)&mod11},
	{"BLANK",			NULL, (void*)NULL},		// Fügt einen leere Zeile hinzu -> Gliederung
	{"Namen TEST",			'a', (void*)&namen},
	{"Strings",			'b', (void*)&strHeader},
	{"BLANK",			NULL, (void*)NULL}, 
	{"Exit",			'q', (void*)&exit}		// exit beendet das Programm
};
show_menu(sizeof(items) / sizeof(struct MenuItem), items, "Vorlesungsaufgaben", true, true, NO_BORDER); 
	
/* 
 * 1. Argument: Anzahl der Elemente; Einfach so lassen
 * 2. Argument: Vorher angelegtes struct; Einfach so lassen
 * 3. Argument: Titel des Menüs	 
 * 4. Argument: Menü im loop; Nach beenden der Methode wieder Menü aufrufen	
 * 5. Argument: Pause nach dem Ausführen der Methode; Ausgaben lesbar
 * 6. Argument: Style des Menüs: DEFAULT, MODERN und NO_BORDER zur Zeit unterstützt
*/
  ````
  
  
