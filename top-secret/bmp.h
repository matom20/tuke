/**
 * Funkcia vráti kópiu vstupného reťazca v obrátenom poradí
 * @method reverse
 * @param  text    [text]
 * @return         [text reverse]
 */
char* reverse(const char* text);

/**
 * Funkcia na šifrovanie textu pomocou Vénierovej šifry
 * @method vigenere_encrypt
 * @param  {key}  [@1]
 * @param  {text} [reťazec na zašifrovanie]
 * @return        [@2]
 *
 * @1: reťazec reprezentujúci kľúč použitý na zašifrovanie aj odšifrovanie textu.
 Kľúč je reprezentovaný ako jedno slovo a môže pozostávať len zo znakov abecedy,
 pričom na veľkosti písmen nezáleží
 * @2: adresu kópie reťazca zašifrovaného pomocou Venierovej šifry alebo NULL,
 ak zašifrovanie nebolo úspešné
 *
 */
char* vigenere_encrypt(const char* key, const char* text);


/**
 * Funkcia na dešifrovanie textu pomocou Vénierovej šifry
 * @method vigenere_decrypt
 * @param  key              [@1]
 * @param  text             [reťazec na dešifrovanie]
 * @return                  [@2]
 *
 * @1: reťazec reprezentujúci kľúč použitý na zašifrovanie aj odšifrovanie textu.
 Kľúč je reprezentovaný ako jedno slovo a môže pozostávať len zo znakov abecedy,
 pričom na veľkosti písmen nezáleží
 * @2: vráti adresu kópie reťazca dešifrovaného pomocou Venierovej šifry alebo
 NULL, dešifrovanie nebolo úspešné
 *
 */
char* vigenere_decrypt(const char* key, const char* text);


/**
 * Funkcia na šifrovanie po bitoch podľa nasledujúceho postupu:
 * Znak, ktorý má byť zašifrovaný, sa rozdelí na polovicu (4 bity + 4 bity).
 * Následne bity v prvej polovici sa rozdelia do párov a ich hodnoty v páre
 sa navzájom vymenia. Takto vytvorená štvorica bitov sa použije pre operáciu
 * XOR nad zvyšnými 4 bitmi.
 *
 * @method bit_encrypt
 * @param  text        [reťazec na zašifrovanie]
 * @return             [Smerník na novovytvorený reťazec obsahujúci zašifrovaný vstupný text]
 */
char* bit_encrypt(const char* text);


/**
 * Funkcia na dešifrovanie po bitoch - inverzná ku predchádzajúcej funkcii šifrovania (bit_encrypt).
 * @method bit_decrypt
 * @param  text        [reťazec na dešifrovanie]
 * @return             [Smerník na novovytvorený reťazec obsahujúci dešifrovaný text]
 */
char* bit_decrypt(const char* text);


/**
* Funkcia na zakódovanie textu prostredníctvom šifry BMP.
* Postup pri šifrovaní pomocou BMP:
    1. vstupný reťazec najprv šifrujeme pomocou funkcie reverse()
    2. získaný reťazec následne šifrujeme pomocou funkcie venier_encrypt()
    3. na výsledný reťazec ešte aplikujeme funkciu bit_encrypt()
 * @method bmp_encrypt
 * @param  key         [@1]
 * @param  text        [Reťazec na zašifrovanie resp. odšifrovanie]
 * @return             [@2]
 *
 * @1: Reťazec reprezentujúci kľúč použitý na zašifrovanie aj odšifrovanie textu.
 Kľúč môže pozostávať len zo znakov, pričom na veľkosti nezáleží
 * @2: Funkcia vráti adresu kópie reťazca zašifrovaného pomocou šifry BMP alebo
 NULL, ak zašifrovanie nebolo úspešné
 *
 */
char* bmp_encrypt(const char* key, const char* text);


/**
 * Funkcia na dekódovanie textu prostredníctvom šifry BMP.
 * Postup pri dešifrovaní pomocou BMP - opačný ako pri šifrovaní (bmp_encrypt).
 * @method bmp_decrypt
 * @param  key         [@1]
 * @param  text        [Reťazec na dešifrovanie]
 * @return             [@2]
 *
 * @1: Reťazec reprezentujúci kľúč použitý na zašifrovanie aj odšifrovanie textu.
 Kľúč môže pozostávať len zo znakov, pričom na veľkosti nezáleží
 * @2: Funkcia vráti adresu kópie reťazca dešifrovaného pomocou šifry BMP alebo
 NULL, ak dešifrovanie nebolo úspešné
 *
 */
char* bmp_decrypt(const char* key, const char* text);
