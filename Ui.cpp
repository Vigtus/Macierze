#include "Ui.h"

void Ui::panel_sterowania() {
    // Wczytywanie rozmiarów macierzy z pliku
    std::ifstream sizesFile("matrix_sizes.txt");
    if (sizesFile.is_open()) {
        int rowsA, columnsA, rowsB, columnsB, rowsV, columnsV;
        int dataArray[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        sizesFile >> rowsA >> columnsA >> rowsB >> columnsB >> rowsV >> columnsV;
        for (;;) {
            // Tworzenie macierzy A i B o odczytanych rozmiarach
            Matrix matrixA(rowsA, columnsA);
            Matrix matrixB(rowsB, columnsB);
            Matrix uniguematrix(3, 3, dataArray);
            Matrix V(rowsV, columnsV);
            V.readFromFile("macierzV.txt", rowsV, columnsV);
            // Utworzenie macierzy B jako kopii macierzy V
            Matrix B = V;
            // Utworzenie macierzy C jako przeniesienia macierzy V
            Matrix C = std::move(V);
            C.display();
            Matrix D;
            Matrix E;

            // Wczytywanie danych z plików do macierzy A i B
            matrixA.readFromFile("macierzA.txt", rowsA, columnsA);
            matrixB.readFromFile("macierzB.txt", rowsB, columnsB);
            std::cout << "==========MENU==========" << std::endl;
            std::cout << "1.Poka¿ macierze" << std::endl;
            std::cout << "2.Dodaj macierze" << std::endl;
            std::cout << "3.Odejmij macierze" << std::endl;
            std::cout << "4.Transponuj macierze" << std::endl;
            std::cout << "5.Pomnó¿ macierze" << std::endl;
            std::cout << "6.Konstruktory i operatory" << std::endl;
            std::cout << "0.Wyjœcie z programu" << std::endl;
            std::cout << "========================" << std::endl;
            std::cout << "\n";
            std::cout << "Wybor: ";
            int wybor;
            std::cin >> wybor;
            switch (wybor) {
            case 1:
                std::cout << "Macierz A:" << std::endl;
                matrixA.display();
                std::cout << "Macierz B:" << std::endl;
                matrixB.display();
                break;
            case 2:
                matrixA.add(matrixB);
                std::cout << "Wynik dodawania macierzy A i B:" << std::endl;
                matrixA.display();
                matrixA.saveToFile("add_result.txt");
                break;
            case 3:
                matrixA.subtract(matrixB);
                std::cout << "Wynik odejmowania macierzy B od A:" << std::endl;
                matrixA.display();
                matrixA.saveToFile("subtract_result.txt");
                break;
            case 4:
                matrixA.transpose();
                std::cout << "Wynik transpozycji macierzy A:" << std::endl;
                matrixA.display();
                matrixA.saveToFile("transpose_result.txt");
                break;
            case 5:
                matrixA.multiply(matrixB);
                std::cout << "Wynik mno¿enia macierzy A i B:" << std::endl;
                matrixA.display();
                matrixA.saveToFile("multiply_result.txt");
                break;
            case 6:
                uniguematrix.print();
                std::cout << "---------" << std::endl;
                V.display();
                std::cout << "+++++++++++" << std::endl;
                B.display();
                std::cout << "---------" << std::endl;
                C.display();
                std::cout << "---------" << std::endl;
                // Przypisanie macierzy B do macierzy D
                D = B;
                D.display();
                std::cout << "---------" << std::endl;
                // Przypisanie macierzy C do macierzy E
                E - std::move(C);
                E.display();
                break;
            case 0:
                exit(0);
                break;
            default:
                std::cout << "Niepoprawna opcja" << std::endl;
                break;
            }
            getchar();
            getchar();
            system("cls");
        }
    }
    else {
        std::cerr << "Nie mo¿na otworzyæ pliku z rozmiarami macierzy." << std::endl;
    }
}
