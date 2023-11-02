# Blockchain - supaprastinta blokų grandinė

Blokų grandinių technologijų **2 - oji** užduotis.

## v0.1

Ši programa sukuria supaprastintą blokų grandinę ir gali atspausdinti norimą bloką ar transakciją.

### Build

Nusiklonavus programos failus, naudojantis komandine eilute, atidarome `\blockchain-uni\src` ir paleidžiame `make` komandą. Įvykdžius šią komandą yra sukuriama `program.exe` programa, kurią reikia paleisti, norint naudotis blokų grandine.

### Running

Programos valdymas vyskta komandinėje eilutėje. Programa nurodo galimas funkcijas ir prašo įvesti skaičius, reikalingus programos vykdymui. 

Pradžiai reikės sukurti blokų grandinę pagal pasirinktus ar numatytus parametrus. Kiekvienas sukurtas naujas blokas yra iškarto įrašomas į `\src\blocks`, į atskirą failą. Visa **tarnybinė** ir **transakcijų**, kurios buvo atsitiktinai parinktos, informacija bus matoma bloko faile.

Baigus generuoti blokus bus galima atsispausdinti pasirinkto bloko ar atskiros transakcijos informaciją. Pasirinkto bloko informacija įrašoma į naują `block-1.txt` failą, o pasirinktos transakcijos informacija pateikiama komandinėje eilutėje.

## Development road map

Dabartinės pastangos yra sutelktos į programos funkcionalumą, sekančioje versijoje bus tobulinamos detalės ir papidomos funkcijos.

 - [x] Piniginių generavimas
 - [x] Transakcijų generavimas
 - [x] Blokų generavimas
 - [x] Transakcijos informacijos pateikimas
 - [x] Bloko informacijos pateikimas
 - [ ] Vartotojo sąsaja
 - [ ] UTXO modelis
 - [ ] Lygiagretūs skaičiavimai
 - [ ] Merkel Root Hash
 - [ ] Balanso apskaičiavimas
 - [ ] Trasakcijos validumo patikra
 - [ ] Transakcijų šalinimas, regeneracija
 - [ ] Vartotojo įvedamos transakcijos
 - [ ] Detalesnė transakcijų informacija
       
