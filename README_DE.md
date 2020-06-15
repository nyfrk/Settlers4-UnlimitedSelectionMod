# Siedler 4 Auswahllimit-Entferner

Standardmäßig können maximal nur 100 Einheiten selektiert werden. Diese Modifikation versucht, die Beschränkung aufzuheben, sodass große Armeen mit Leichtigkeit verwaltet werden können.

![186-units-selected](units-selected.png)

Für dieses README gibt es eine [englische Version](README.md). Bitte beachte, dass die deutsche Übersetzung ggf. veraltet sein kann.



## Anforderungen

Es wird die **History Edition von Die Siedler 4** benötigt. Beachte, dass die Mod noch nicht mit der älteren Gold-Version funktioniert. Sie wurde mit einer S4_Main.exe mit folgender MD5-Prüfsumme getestet: `bcdd32fd35f85a8eb96641dcc4eacfa9`. 



## Installation

1. [Lade ein Release hier herunter](https://github.com/nyfrk/S4_UnlimitedSelection/releases), entpacke es und kopiere die Dateien wohin Du möchtest. Die enthaltenen Dateien `Injector.exe` und `S4_UnlimitedSelection.dll` müssen lediglich im selben Verzeichnis liegen. 
2. Starte die Datei `Injector.exe` durch einen Doppelklick. Ein Konsolenfenster öffnet sich.
3. Starte das Spiel und warte, bis das Konsolenfenster eine erfolgreiche Injektion bestätigt.
4. Schließe das Konsolenfenster. Die Mod wird weiterhin aktiv bleiben. 

Der Injektor beginnt mit der Injektion der DLL, sobald das Spiel gestartet wird. Beachte, dass Du meinen Injektor nicht benutzen musst. Du kannst auch andere Injektoren verwenden. Achte darauf, dass die Datei `S4_UnlimitedSelection.dll` **nicht umbenannt** wird, wenn du meinen Injektor verwendest. Andernfalls wird der Injektor sie nicht finden.



## Deinstallation

Die Mod verändert keine Dateien dauerhaft. Entferne einfach beide heruntergeladenen Dateien, wenn Du sie nicht mehr benutzen möchtest. 



## Bekannte Probleme

* Das Spiel ist darauf beschränkt, maximal 100 Gesundheitsblasen auf dem Bildschirm zu zeichnen. Das bedeutet, dass Du mit der Zoomstufe herumspielen musst, um die Gesundheit deiner Armee stückchenweise begutachten zu können. 
* Gruppenzuweisungen sind nach wie vor auf maximal 100 Einheiten pro Gruppe beschränkt.
* Es sind noch nicht alle Auswahlwerkzeuge implementiert. Eigentlich ist nur das Kastenauswahlwerkzeug implementiert. Bei der Verwendung von Alt+Klick wird noch immer das ursprüngliche Limit von 100 Einheiten pro Auswahl verwendet.
* Es treten Abstürze auf, wenn zu viele Einheiten ausgewählt werden. Ich habe daher das Limit auf 250 Einheiten pro Auswahl festgelegt, um diese Abstürze zu verhindern. Ich hoffe, dass wir dieses Limit in Zukunft noch weiter erhöhen können.
* Die Mod funktioniert nicht mit der Gold-Edition.



## Wie funktioniert es?

Die Mod modifiziert Codeabschnitte des Spiels während der Laufzeit. Außerdem fügt sie etwas Code hinzu, um Abstürze zu beheben. Wenn Du eine andere Spielversion verwendest, musst Du die dokumentierten Code-Abschnitte unten in der Datei [cheat-unlimited-selection.cpp](S4_UnlimitedSelection/cheat-unlimited-selection.cpp#L240) wiederfinden. Passe einfach die Adressen und Pattern im Quellcode an. Anschließend kannst Du die Mod selber kompilieren. Allerdings sollte der automatische Patternmatcher bereits die Kompatibilität auch über verschiedene Spielversionen hinweg sicherstellen. Hier ist eine kurze Zusammenfassung der Adressen, die durch die Mod modifiziert werden. Beachte, dass sie möglicherweise nicht vollständig ist. Eine vollständigere Liste findet sich im Quellcode.

```
Behebung d. Pufferüberlaufs (fataler Fehler) für die Gesundheitsblasen:
S4_Main.exe+26041B - 8B 0D 2C75A701 - mov ecx,[S4_Main.exe+26041B - 8B 0D 2C75A701 - mov ecx,[S4_Main.exe+105752C]

Entfernt die Beschränkung für das Boxauswahlwerkzeug:
S4_Main.exe+ED241 - 0F83 8400000000 - jae S4_Main.exe+ED2CB

Entfernt die Begrenzung für Einheiten, die durch Rechtsklick bewegt werden können:
S4_Main.exe+EC8CF - B8 6400000000 - mov eax,00000064

ClearSelection()-Funktion des Spiels (Deselektiert alle Einheiten):
S4_Main.exe+EE530 - A1 F836AA01 - mov eax,[S4_Main.exe+10836F8]
```



## Kompilieren

Lade Visual Studio 2017 oder 2019 mit der C++-Toolchain herunter. Ich habe es so konfiguriert, dass die Mod mit der WindowsXP-kompatiblen **v141_xp**-Toolchain gebaut wird. Du solltest jedoch die Toolchain nach Belieben ändern können. Es werden keine zusätzlichen Bibliotheken benötigt, sodass die Mod sich ohne Weiteres kompilieren lassen sollte. Wenn Du einen Debug-Build erstellst, erzeugt die Mod ein Konsolenfenster beim Laden und gibt verschiedene Debug Informationen aus. 



## Beitragen

Das offizielle Repository zu diesem Projekt ist verfügbar unter https://github.com/nyfrk/S4_UnlimitedSelection. Es steht dir frei, dieses Repository zu forken. Du kannst alles verwenden, für was immer Du möchtest. Bitte lies die [LICENSE.md](LICENSE.md) für Einzelheiten und öffne einen Pull-Request, wenn es dir gelingen sollte, einige der ungelösten Probleme dieser Mod zu beheben.
