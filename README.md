#### Points: 10/10

# Druhá domácí úloha z předmětu IAL (Algoritmy) VUT FIT, Brno

V druhé domácí úloze na Vás čekají následující čtyři příklady:

1. hashtable: tabulka s rozptýlenými položkami (3b),
2. btree/rec: binární vyhledávací strom a operace nad ním implementované rekurzivně (2.5b)
3. btree/iter: binární vyhledávací strom a operace nad ním implementované iterativně (2.5b)
4. btree/exa: jednoduché použití a vybalancování binárního vyhledávacího stromu (2b)

Vaší úlohou je v souborech

- _hashtable/hashtable.c_,
- _btree/rec/btree.c_,
- _btree/iter/btree.c_, a
- _btree/exa/exa.c_

doplnit těla funkcí. Tyto soubory, **se zachováním adresářové struktury**, odevzdejte prostřednictvím STUDISu jako _tar_ achiv (bez komprimace, kódování UTF-8). Do jiných souborů nezasahujte (neodevzdávají se = nebude hodnoceno) a neupravujte předpisy funkcí. Pomocné funkce by něměly být potřeba, pokud nejsou explicitně zmíněny.

Obsah archivu tedy bude vypadat následovně:

- xlogin00.tar
  - hashtable
    - hashtable.c
  - btree
    - rec
      - btree.c
    - iter
      - btree.c
    - exa
      - exa.c

Správnost implementace si můžete částečně ověřit pomocí přiložené testovací aplikace, kterou přeložíte pomocí připraveného _Makefile (make test, make clean)_. Poskytnuté testy nepokrývají vše co bude testováno a je doporučeno napsat si vlastní testy.

Vaše řešení musí být přeložitelné a spustitelné na serveru _eva.fit.vutbr.cz_. Nedodržení zadání (zásahy do kostry, přejmenovaní souborů, nezachování adresářové struktury apod.) **bude hodnoceno 0 body**. Stejně tak bude 0 body hodnoceno i řešení nepřeložitelné či řešení, které se po spuštění zacyklí — testy budou časově limitované. Bodovou ztrátou budou dále postiženy projekty bez vhodných komentářů.

Domácí úlohu vypracovávejte, prosím, samostatně a své řešení nikde volně nepublikujte! **V případě odhalení plagiátorství či nedovolené spolupráce nebude udělen zápočet a dále bude zváženo zahájení disciplinárního řízení.**
