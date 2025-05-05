# Matrix Calculator

Konsolowa aplikacja w C++ do wykonywania podstawowych operacji na macierzach.

## Spis treści

- [Opis projektu](#opis-projektu)  
- [Funkcjonalności](#funkcjonalności)  
- [Wymagania](#wymagania)  
- [Budowanie i uruchamianie](#budowanie-i-uruchamianie)  
- [Przykłady użycia](#przykłady-użycia)  
- [Struktura plików](#struktura-plików)  
- [Szczegóły implementacji](#szczegóły-implementacji)  

## Opis projektu

Aplikacja umożliwia:
- Wczytanie rozmiarów macierzy z pliku `matrix_sizes.txt`  
- Załadowanie danych macierzy A, B i V z plików tekstowych  
- Wyświetlanie macierzy w konsoli  
- Dodawanie, odejmowanie, transpozycję i mnożenie macierzy  
- Zapis wyników operacji do plików tekstowych  
- Demonstrację konstruktorów kopiujących i przenoszących oraz operatorów przypisania  

## Funkcjonalności

1. **Wyświetlanie macierzy**  
2. **Dodawanie** macierzy A i B → zapis do `add_result.txt`  
3. **Odejmowanie** macierzy B od A → zapis do `subtract_result.txt`  
4. **Transpozycja** macierzy A → zapis do `transpose_result.txt`  
5. **Mnożenie** macierzy A i B → zapis do `multiply_result.txt`  
6. **Testy**: konstruktorów i operatorów kopiujących/przenoszących  

## Wymagania

- Kompilator C++11 lub nowszy  
- Standardowa biblioteka C++  
- Pliki z danymi w formacie tekstowym  

## Budowanie i uruchamianie

1. **Kompilacja**  
   ```bash
   g++ Źródło.cpp Ui.cpp Matrix.cpp -o matrix_calculator

2.Przygotowanie plików
- Utwórz matrix_sizes.txt, np.:
  3 3 3 3 3 3
- Przygotuj macierzA.txt, macierzB.txt, macierzV.txt zgodnie z powyższymi wymiarami.

3. Uruchomienie

   ```./matrix_calculator```
   
