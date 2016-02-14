Doc by `© Copyright 2010-2015 KPI FEI TUKE - Miroslav Biňas`  
[URL DOCS](http://it4kt.cnl.sk/c/pvjc/2015/problemset.03.hangman.html)  
Thanks!

***

# Hangman

### Ciele
1. Pracovať s jednorozmerným poľom (reťazcami).
2. Používať pole ako parameter (vstupný a výstupný) vo funkciách.

### Hangman
Určite ste už niekedy hrali hru so slovami Hangman, v ktorej je potrebné hádať slovo po písmenách. Uhádnuté písmená sa postupne dopisujú do tajničky a pri každom neúspešnom pokuse sa naopak nakreslí časť šibenice. Hra sa končí, keď hráč uhádne slovo alebo keď druhý hráč nakreslí celú šibenicu.

V našej implementácii bude prvým hráčom používateľ, ktorý bude hádať slovo tak, že vždy napíše na obrazovku jedno písmeno. Na uhádnutie slova bude mať 8 pokusov. Druhým hráčom bude vždy počítač, ktorý si najskôr náhodne vyberie tajné slovo zo slovníka. Výber bude zabezpečený volaním funkcie `int getWord(char secret[])`, ktorá vráti slovo s max. dĺžkou **15** znakov (túto funkciu už budete mať pripravenú).

Vašou úlohou bude naprogramovať štyri funkcie:
1. `int isWordGuessed(const char secret[], const char lettersGuessed[])` - Zistí, či na základe hádaných písmen hráč uhádol tajné slovo (malé písmená)
2. `void getGuessedWord(const char secret[], const char lettersGuessed[], char guessedWord[])` - Aktualizuje hádané slovo (malé písmená) tak, že na tajných, zatiaľ neuhádnutých pozíciách bude obsahovať znak `_` a na odkrytých, už uhádnutých miestach bude obsahovať konkrétne písmeno
3. `void getAvailableLetters(const char lettersGuessed[], char availableLetters[])` - Aktualizuje zoznam dostupných písmen, ktoré ešte neboli hádané (malé písmená)
4. `void hangman(const char secret[])` - Obsahuje funkcionalitu samotnej hry

Všetkých 5 funkcií (štyri, ktoré máte naprogramovať a funkcia `getWord()`, ktorú už dostanete) sa bude nachádzať v súbore `hangman.c`, ktorých deklarácie sú uvedené v súbore `hangman.h`. Hlavný program sa nachádza v súbore `main.c`, ktorý načíta náhodné slovo pomocou funkcie `getWord()` a odovzdá ho funkcii `hangman()` na realizáciu samotnej hry.

Okrem požadovaných funkcií si môžete vytvoriť aj vlastné funkcie. Tieto však budú súkromné pre váš modul (nebudú deklarované v hlavičkovom súbore hangman.h).

Na začiatku hry je hráč oboznámený s dĺžkou tajného slova. V každom kole je spracované práve jedno písmeno a hráč je okamžite oboznámený s tým, či sa písmeno nachádza v tajnom slove alebo nie. Po každom kole by sa tiež malo zobraziť samotné slovo tak, aby bolo jasné, ktoré písmená už boli uhádnuté a ktoré zatiaľ nie.

Nezabudnite hráčovi pripomenúť, koľko pokusov má ešte k dipozícii. Hráč stráca pokus iba ak háda nesprávne, t.j. dané písmeno sa v tajnom slove nenachádza. Ak hráč zadá to isté písmeno viackrát, neprichádza o pokus, oznámte mu však, že sa jeho tip už zopakoval.

#### Úloha 1: Je slovo uhádnuté?

Naprogramujte funkciu int `isWordGuessed(const char secret[], const char lettersGuessed[])` s dvoma parametrami:

1. `const char secret[]` - Reťazec reprezentujúci tajné slovo (malé písmená)
2. `const char lettersGuessed[]` - Reťazec so všetkými doposiaľ hádanými písmenami

Funkcia vráti hodnotu `1`, ak tajné slovo uložené v parametri `secret` bolo uhádnuté (je ho možné zostaviť z hádaných písmen uložených v parametri **lettersGuessed**). V opačnom prípade vráti funkcia hodnotu `0`.

#### Úloha 2: Aktualizácia hádaného slova

Naprogramujte funkciu `void getGuessedWord(const char secret[], const char lettersGuessed[], char guessedWord[])` s troma paramerami:

1. `const char secret[]` - Reťazec reprezentujúci tajné slovo (malé písmená)
2. `const char lettersGuessed[]` - Reťazec so všetkými doposiaľ hádanými písmenami
3. `char guessedWord[]` - Výstupný parameter funkcie, ktorý bude reprezentovať reťazec hádaného slova
Funkcia nevracia žiadnu hodnotu.

Funkcia aktualizuje hádané slovo guessedWord tak, že na tajných, zatiaľ neuhádnutých pozíciách bude obsahovať znak `_` a na odkrytých, už uhádnutých miestach bude obsahovať konkrétne písmeno.

#### Úloha 3: Aktualizácia dostupných písmen

Naprogramujte funkciu `void getAvailableLetters(const char lettersGuessed[], char availableLetters[])` s dvoma parametrami:

1. `char lettersGuessed[]` - Reťazec so všetkými doposiaľ hádanými písmenami (malé písmená)
2. `char availableLetters[]` - Reťazec abecedy okrem doposiaľ hádaných písmen. Výstupný parameter funkcie.
Funkcia nevracia žiadnu hodnotu.

Funkcia aktualizuje reťazec dostupných písmen **availableLetters** vynechaním už hádaných písmen pomocou parametra **lettersGuessed**. Tento zoznam písmen bude usporiadaný vzostupne.

#### Úloha 4: Hra

Naprogramujte funkciu `void hangman(const char secret[])` s jednym parametrom:

1. `char secret[]` - Reťazec reprezentujúci tajné slovo.
Funkcia nevracia žiadnu hodnotu.

Funkcia realizuje interaktívnu hru medzi používateľom a počítačom s využitím vami vytvorených funkcií `int isWordGuessed()`, `void getGuessedWord()` a `void getAvailableLetters()`.

Na začiatku hra oboznámi hráča s dĺžkou tajného slova. V každom kole hry sa spracuje práve jedno písmeno a hráč je oboznámený s počtom zostávajúcich pokusov a reťazcom dostupných písmen. Po zadaní znaku je hráč okamžite informovaný o úspešnosti jeho tipu spolu s výpisom aktuálneho hádaného slova s vyznačenými uhádnutými písmenami.

Hráč však môže z klávesnice zadať ľubovoľné písmeno - aj veľké aj malé! V tomto prípade sú si písmená rovnocenné ***(nezáleží na ich veľkosti)***. Túto funkcionalitu naprogramujte priamo vo funkcii `hangman()`

Hra by mala po každom pokuse vypísať počet zostávajúcich pokusov. Počet pokusov sa znižuje o jedno, ak bol tip hráča nesprávny. Naopak, počet pokusov zostáva rovnaký, ak bol tip hráča správny, ale aj keď hráč zadá opakovane rovnaký tip. Vtedy je potrebné o tom hráča informovať.

Slovo, ktoré ste získali ako výstup z funkcie `getGuessedWord()`, kvôli zvýšeniu čitateľnosti vypisujte v tvare **l a _ _ s _ a _ e**.

Ak hráč zadá celé slovo (nie iba 1 písmeno), hra ihneď končí a hráčovi oznámi, či **vyhral** alebo **nie**.
***
### Figúra
**To už v zadaní nebolo.**  
Po aktivovaní figúri v `hangman.c` sa zobrazí simple figúrka pri absolvovaní hry!  
Default: `true`

Príklad (kompletná figúrka):
```
Figure:
______
	 #
	 O
	/|\
	 |
	/ \  
```
***
### Structure
```
.
├── hangman
│   ├── figure.c
│   ├── figure.h
│   ├── hangman.c
│   ├── hangman.h
│   ├── main.c
│   └── Makefile
```
***

### Compile/Run App

**Compile:** `make all`  
 or  
 `gcc -std=c11 -Werror -Wall -lm main.c hangman.c figure.c -o hangman`

 **Run:**
  `./hangman`

**Remove:** `make clean`

***

* #BadCode #Amateur
