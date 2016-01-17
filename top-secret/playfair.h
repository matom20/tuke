
/**
 * Funkcia na zašifrovanie textu aplikovaním Playfairovej šifry
 * @method playfair_encrypt
 * @param  key              [@1]
 * @param  text             [@2]
 * @return                  [referencia na zašifrovaný reťazec ]
 *
 * @1: Odkaz na reťazec, ktorý reprezentuje text na zašifrovanie.
 Tento text môže pozostávať len z písmen, pričom na veľkosti písmen nezáleží,
 alebo zo znaku medzery. Žiadne iné znaky nie sú prípustné (nie je možné ich zašifrovať).
 * @2: Odkaz na reťazec, ktorý reprezentuje kľúč, pomocou ktorého bude text zašifrovaný.
 Kľúč je reprezentovaný jedným slovom, v ktorom nezáleží na veľkosti písmen.
 Jednotlivé písmená sa v kľúči nemôžu opakovať (ak sa opakujú tak vo vašej
 implementácii zabezpečte, že duplikáty budú odstránené).
 */

char* playfair_encrypt(const char* key, const char* text);


/**
 * Funkcia na dešifrovanie textu aplikovaním Playfairovej šifry
 * @method playfair_decrypt
 * @param  key              [Odkaz na reťazec, ktorý reprezentuje text na dešifrovanie]
 * @param  text             [@1]
 * @return                  [referencia na dešifrovaný reťazec]
 *
 * @1: Odkaz na reťazec, ktorý reprezentuje kľúč, pomocou ktorého je text
 zašifrovaný. Kľúč je reprezentovaný jedným slovom, v ktorom nezáleží na veľkosti písmen.
 */

char* playfair_decrypt(const char* key, const char* text);
