Doc by `© Copyright 2010-2015 KPI FEI TUKE - Miroslav Biňas`  
[URL DOCS](http://it4kt.cnl.sk/c/pvjc/2015/problemset.05.top.secret.html)  
Thanks!

***

# TOP SECRET

#### Ciele
1. Správa dynamickej pamäte (alokácia a dealokácia).  
2. Bitové operácie.

#### Šifrovanie
V rámci tohto zadania bude vašou úlohou vyriešiť niekoľko úloh týkajúcich sa práve šifrovania textu v jazyku C.

**Implementujete dva moduly**:  
1. Modul Playfair, v rámci ktorého implementujete Playfairovu šifru.  
2. Modul BMP, v rámci ktorého implementujete BMP šifru.  

V rámci oboch modulov si samozrejme môžete vytvoriť aj ďalšie pomocné funkcie. Nesmiete však nijako meniť a upravovať hlavičkové súbory oboch modulov!

### Modul Playfair
Tento modul je zameraný na šifrovanie a dešifrovanie textu prostredníctvom [Playfairovej šifry](https://en.wikipedia.org/wiki/Playfair_cipher), ktorú vo filme [National Treasure II.](http://www.imdb.com/title/tt0465234/?ref_=tt_rec_tti) lúštil aj Nicolas Cage. Modul bude obsahovať dve funkcie `playfair_encrypt()` a `playfair_decrypt()` pre zašifrovanie a rozšifrovanie textu a makro ALPHA, ktoré bude obsahovať abecedu na šifrovanie s vynechaným písmenom `'W'`.

```
B E L F A
S T C D G
H I J K M
N O P Q R
U V X Y Z
```

Ak s týmto kľúčom zašifrujeme slovo **KRYPTOGRAFIA**, výsledkom bude šifrovaný text **MQXQIVMZBAME**, pre **MANAGER** to bude **RGRBTAPZ**.

Vašou úlohou je vytvoriť funkcie `char* playfair_encrypt(const char* key, const char* text)` a `char* playfair_decrypt(const char* key, const char* text)`, pomocu ktorých zašifrujete a odšifrujete text aplikovaním Playfairovej šifry. Jednotlivé parametre funkcií sú nasledovné:

* `const char* text` - Odkaz na reťazec, ktorý reprezentuje text na zašifrovanie. Tento text môže pozostávať len z písmen, pričom na veľkosti písmen nezáleží, alebo zo znaku medzery. Žiadne iné znaky nie sú prípustné (nie je možné ich zašifrovať).

* `const char* key` - Odkaz na reťazec, ktorý reprezentuje kľúč, pomocou ktorého bude text zašifrovaný. Kľúč je reprezentovaný textom, v ktorom nezáleží na veľkosti písmen. Jednotlivé písmená sa v kľúči nemôžu opakovať (ak sa opakujú tak vo vašej implementácii zabezpečte, že duplikáty budú odstránené). Medzery v kľúči sú ignorované.

Funkcia vráti referenciu na zašifrovaný reťazec, ak bolo šifrovanie alebo dešifrovanie úspešné. Výsledný reťazec vypisujte v podobe dvojíc veľkých písmen oddelených medzerami.

Ak sa pred šifrovaním zistíte, že sú v texte dve po sebe idúce písmená rovnaké, medzi tieto dve písmená pridajte písmeno `'X'`. Písmeno `'X'` rovnako pridajte na koniec vstupného textu v prípade, ak je jeho dĺžka nepárna (po pridaní `'X'` medzi dvojité znaky a odstránení medzier). Znak `'X'` sa nepridáva medzi 2 rovnaké znaky `'X'` a šifruje sa podľa stĺpca matice.

Pri dešifrovaní sa výskyt znaku `'W'` pri vstupnom texte považuje za chybu a funkcia na dešifrovanie má v takomto prípade vrátiť `NULL`.

V prípade, že niektoré z pravidiel týkajúce sa vstupných parametrov bolo porušené alebo funkcia na vstupe dostane miesto adresy textu hodnotu `NULL`, funkcia hodnotu `NULL` aj vráti.

### Modul BMP

Šifra BMP nesie názov zložený z prvých písmen priezvisk trojice zakladateľov nášho kryptografického tímu (Biňas-Madeja-Pietriková). Výhodou oproti Playfairovej šifre je fakt, že pomocou BMP je možné zašifrovať ľubovoľný text (teda - až na niekoľko výnimiek spomenutých nižšie).

#### Úloha #2: Reverz

Vašou úlohou je vytvoriť funkciu `char* reverse(const char* text)`, vráti kópiu vstupného reťazca v obrátenom poradí (UPPERCASE).

V prípade, že funkcia miesto reťazca dostane hodnotu `NULL`, funkcia túto hodnotu `NULL` aj vráti.

#### Úloha #3: Vigenèrova šifra

[Vigenèrova šifra](https://en.wikipedia.org/wiki/Vigenère_cipher) predstavuje rozšírenie cézarovej šifry o kľúč, ktorý bude pri šifrovaní a dešifrovaní použitý.

Vašou úlohou je vytvoriť funkciu `char* vigenere_encrypt(const char* key, const char* text)` na zašifrovanie a funkciu `char* vigenere_decrypt(const char* key, const char* text)` na dešifrovanie textu pomocou Vénierovej šifry. Výsledný text reprezentujte veľkými písmenami (UPPERCASE)

Význam jednotlivých parametrov funkcií je nasledovný:

* **key** - Reťazec reprezentujúci kľúč použitý na zašifrovanie aj odšifrovanie textu. Kľúč je reprezentovaný ako jedno slovo a môže pozostávať len zo znakov abecedy, pričom na veľkosti písmen nezáleží.
* **text** - Reťazec na zašifrovanie resp. odšifrovanie.

Funkcia vráti adresu kópie reťazca zašifrovanú resp. odšifrovanú pomocou Venierovej šifry alebo `NULL`, ak zašifrovanie resp. odšifrovanie nebolo úspešné.

#### Úloha #4: Bitový chaos
Táto metóda šifrovania ešte nie je nikde publikovaná a v našom tíme bola predmetom dlhých diskusií, počas ktorých sme v blízkych aj vzdialených podnikoch stiahli litre kofoly. Nakoľko je však metodika veľmi jednoduchá, ***je výsledný efekt úplne geniálny***.

Pri šifrovaní postupujte nasledovne: Znak, ktorý má byť zašifrovaný, si rozdeľte na polovicu `(4 bity + 4 bity)`. Následne bity v prvej polovici rozdeľte do párov a ich hodnoty v páre navzájom vymeňte. Takto vytvorenú štvoricu bitov použite pre operáciu **XOR** nad zvyšnými 4 bitmi.

Tento jednoduchý a pritom geniálny princíp si predstavíme na nasledovnom príklade. Reťazec, ktory je potrebné zašifrovať, je `"Hello world!"`. Zašifrovať je potrebné každé jedno písmeno, takže pri šifrovaní budeme postupovať od prvého písmena - `'H'`:

* Písmeno `'H'` má v `ASCII` tabuľke hodnotu `72`. Hodnota `72` vyzerá v dvojkovej sústave nasledovne: `01001000`. Prvé **4 bity** sú teda `0100` a druhé **4 bity** sú `1000`.  
* Prvá polovica bitov 0100 pozostáva z dvoch párov (01 a 00), v ktorých jednotlivé bity navzájom vymeníme (z páru 01 sa stane 10 a z páru 00 sa stane pár 00). Tým dostaneme hodnotu 1000.
* Takto upravenú podobu prvých štyroch bitov použijeme ako parameter operácie XOR spolu so zvyšnými štyrmi bitmi:

```
1000  // druhá polovica
XOR 1000  // prvá polovica po výmene bitov v dvojici
--------
0000
```

* Spojením oboch získaných štvoríc bitov (prvá štvorica 1000, ktorú sme získali ako výsledok v 2. kroku a druhá štvorica 0000, ktorú sme získali ako výsledok v 3. kroku) dostaneme hodnotu 10000000, ktorá predstavuje zašifrovanú podobu písmena 'H' pomocou tejto metódy.

V prípade dešifrovania využite opačný postup.

Vašou úlohou je teda vytvoriť funkcie `char* bit_encrypt(const char* text)` a `char* bit_decrypt(const char* text)`, pomocou ktorých budete vedieť zašifrovať a dešifrovať zadanú postupnosť bytov.

#### Úloha #5: Šifra BMP
Ako už bolo uvedené vyššie, za šifrou _BMP_ stojí (niekedy aj sedí) trojica mladých kryptológov Biňas, Madeja a Pietriková a jej jednoduchosť a z nej vyplývajúca genialita vychádza v kombinácii niekoľkých metód súčasne.

Ak chcete reťazec zašifrovať, postupujte nasledovne:

* vstupný reťazec najprv prežeňte funkciou `reverse()`
* získaný reťazec následne prežeňte funkciou `venier_encrypt()`
* výsledný reťazec ešte prežeňte funkciou `bit_encrypt()`

Pre rozšifrovanie zadanej postupnosti bytov postupujte presne opačne.

Vašou úlohou je teda vytvoriť funkcie `char* bmp_encrypt(const char* key, const char* text)` a `char* bmp_decrypt(const char* key, const char* text)`, pomocou ktorých budete vedieť text zakódovať a dekódovať prostredníctvom šifry BMP.

Význam jednotlivých parametrov funkcií je nasledovný:

* **key** - Reťazec reprezentujúci kľúč použitý na zašifrovanie aj odšifrovanie textu. Kľúč môže pozostávať len zo znakov, pričom na veľkosti nezáleží.
* **text** - Reťazec na zašifrovanie resp. odšifrovanie.

Funkcia vráti adresu kópie reťazca zašifrovanú resp. odšifrovanú pomocou BMP šifry alebo `NULL`, ak zašifrovanie resp. odšifrovanie nebolo úspešné.

### Structure
```
.
├── top-secret
│   ├── playfair.c
│   ├── playfair.h
│   ├── bmp.c
│   ├── bmp.h
│   ├── main.c
│   └── Makefile
```
***

### Compile/Run App

**Compile:** `make all`  
 or  
 `gcc -std=c11 -Werror -Wall main.c playfair.c bmp.c -lm -o top-secret`

 **Run:**
  `./top-secret`

**Remove:** `make clean`
