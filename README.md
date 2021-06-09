# Asociatyvių konteinerių naudojimas

##  Programos naudojimas ir veikimo principas

### Veikimo princimas

Šioje programoje tekstas apdorojamas tokiu būdu:  
* Iš pradžių, nuskaitinėjant tekstą programoje tikrinama ar konkretus žodis yra URL’as. Žodžiai dedami i viena konteineri  o URL’ai į kita.   
* Toliau, naudojant asociatyvių konteinerių savybės paskaičiuojama kiek kartu kiekvienas žodis 
kartojasi ir išvedami į failą visi žodžiai kartojantis daugiau negu 1 karta.  
* Toliau sugeneruojama cross-reference tipo lentelė kurioje nurodyta kuriose eilutėse galima rasti kiekviena išvesta žodį.  
* Pabaigoje, į failą bus išvesti visi nuskaitymo metu rasti URL’ai.

### Programos naudojimas

Paleidus programą naudotojo bus paprašyta įvesti failo pilną arba santykinį kelią.  
***(Nepamirškite nurodyti failo išplėtimą; Programa veiks tik su*** ```.txt``` ***išplėtimu)***  

```
Enter file location: ../Texts/ExampleText.txt
Reading text...
...

```

Jeigu programa bus naudojimą per komandinę eilutę kelia galima iškart nurodyti kaip parametrą. Tokiu atveju naudotojo paleidus programoje jau neprašys nurodyti kelią.

```
C:\Users\stolo\Desktop\Associative Container>main ../Texts/ExampleText.txt
Reading text...
...

```

Toliau programoje naudotojas bus informuotas kuriame žingsnyje yra programa:  

```
Enter file location: ../Texts/ExampleText.txt
Reading text...
Counting words...
Generating cross reference table...
Getting URLs...
Finished
Press any key to continue . . .

```

* ```Reading text...``` – programa nuskaito tekstą  
* ```Counting words...``` – programa skaičiuoja kiek kartu kiekvienas žodis kartojasi ir išveda atitinkamus į failą  
* ```Generating cross reference table...``` – programa sugeneruoja cross-reference tipo lentelė  
* ```Getting URLs...``` – programa išveda URL’us  
* ```Finished``` – programa baigė vykdymą  

Programai baigus vykdymą jos folder’yje atsiras 3 nauji failai:  
  
* ```WordCount.txt``` – žodžiai kartojanti daugiau negu 1 karta  
* ```CrossRefTable.txt``` – cross-reference tipo lentelė  
* ```URLs.txt``` – URL’ai  

## Įdiegimas
Atsiustą ```main.cpp``` failą sukompiliuokite C++11 arba naujesniu standartu.  
Jeigu turite GNU C++ kopilatorių ir komandinėje eilutėje esant folder'yje galite sukompilioti paleistadimi šias komandas:  
```g++ --std=c++11 main.cpp -o text_analyzer``` arba ```g++ --std=c++11 main.cpp -o text_analyzer```
