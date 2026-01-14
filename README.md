# DataSensorAnalyser(c++)

Ett enkelt konsolprogram för att mata in, lagra, visa, sortera och analysera temperaturvärden.

Funktioner
- Manuell inmatning** av temperaturvärden
- Stoppsignal (sentinel): skriv 'QUIT', 'quit' eller 'q' för att avsluta inmatningen
- Visa all sparad data med formaterad utskrift
- Analysera temperaturer:
  - antal värden
  - medeltemperatur
  - lägsta temperatur
  - högsta temperatur
- Sortering och visning:
  - Låg → Hög
  - Hög → Låg
- Inmatningsvalidering för både menyval och temperaturvärden

Hur programmet fungerar
När programmet startas visas en meny:

1. Mata in temperaturvärden manuellt  
2. Visa all data  
3. Analysera data  
4. Visa sorterad data (Låg till Hög)  
5. Visa sorterad data (Hög till Låg)  
6. Avsluta  

Temperaturerna lagras i minnet i en 'std::vector<double>' under programmets körning.

Krav
- En C++-kompilator med stöd för C++11 eller nyare  
  Exempel: 'g++', 'clang++', MSVC (Visual Studio)

Bygga och köra

Alternativ 1: g++ (Linux / macOS / WSL)
'''bash
g++ -std=c++11 -O2 -o temp_manager DataSensorAnalyser.cpp
./temp_manager
