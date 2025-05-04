#include "Matrix.h"

Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns) {
    // Alokacja pami�ci dla macierzy
    data = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new int[columns];
    }

}


// Konstruktor bezargumentowy
Matrix::Matrix() : data(nullptr), rows(0), columns(0) {}

// Konstruktor kopiuj�cy
Matrix::Matrix(const Matrix& other) : rows(other.rows), columns(other.columns) {
    data = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new int[columns];
        for (int j = 0; j < columns; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Konstruktor z danymi i wymiarami
Matrix::Matrix(int rows, int columns, int* dataArray) : rows(rows), columns(columns) {
    // Alokacja pami�ci za pomoc� std::make_unique
    uniquedata = std::make_unique<std::unique_ptr<int[]>[]>(rows);
    for (int i = 0; i < rows; ++i) {
        uniquedata[i] = std::make_unique<int[]>(columns);
    }

    // Przypisanie danych
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            uniquedata[i][j] = dataArray[i * columns + j];
        }
    }
}

// Konstruktor przenosz�cy
Matrix::Matrix(Matrix&& other) : data(nullptr), rows(0), columns(0) {
    // Przeniesienie zasob�w z obiektu �r�d�owego do obiektu docelowego
    std::swap(data, other.data);
    std::swap(rows, other.rows);
    std::swap(columns, other.columns);
}

Matrix::~Matrix() {
    // Zwolnienie pami�ci zaalokowanej dla macierzy
    clear();
}

// Operator przypisania
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        // Zwolnienie bie��cych zasob�w
        clear();

        // Przypisanie nowych zasob�w
        rows = other.rows;
        columns = other.columns;

        data = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[columns];
            for (int j = 0; j < columns; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

// Operator przypisania przenosz�cy
Matrix& Matrix::operator-(Matrix&& other) noexcept {
    if (this != &other) {
        // Zwolnienie bie��cych zasob�w
        clear();

        // Przeniesienie zasob�w z obiektu �r�d�owego do obiektu docelowego
        std::swap(data, other.data);
        std::swap(rows, other.rows);
        std::swap(columns, other.columns);
    }
    return *this;
}


// Funkcja wczytuj�ca macierz z pliku
void Matrix::readFromFile(const std::string& filename,int rows, int colums) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        int row = 0;
        int column = 0;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int value;
            while (iss >> value) {
                if (column >= columns) {
                    std::cerr << "Zbyt du�o danych w wierszu " << row + 1 << ", ograniczono do " << columns << " kolumn." << std::endl;
                    break;
                }
                data[row][column++] = value;
            }
            if (column < columns) {
                std::cerr << "Za ma�o danych w wierszu " << row + 1 << ", uzupe�niono zerami." << std::endl;
                while (column < columns) {
                    data[row][column++] = 0;
                }
            }
            ++row;
            column = 0;
            if (row >= rows) {
                break;
            }
        }

        if (row < rows) {
            std::cerr << "Za ma�o wierszy w pliku, uzupe�niono zerami." << std::endl;
            while (row < rows) {
                for (int j = 0; j < columns; ++j) {
                    data[row][j] = 0;
                }
                ++row;
            }
        }

        file.close();
        std::cout << "Macierz wczytana z pliku: " << filename << std::endl;
    }
    else {
        std::cerr << "Nie mo�na otworzy� pliku do odczytu." << std::endl;
    }
}

void const Matrix::display()  {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::add(const Matrix& other) {
    if (rows != other.rows || columns != other.columns) {
        std::cerr << "Nie mo�na doda� macierzy o r�nych rozmiarach." << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            data[i][j] += other.data[i][j];
        }
    }
    std::cout << "Macierze dodane." << std::endl;
}

void Matrix::subtract(const Matrix& other) {
    if (rows != other.rows || columns != other.columns) {
        std::cerr << "Nie mo�na odj�� macierzy o r�nych rozmiarach." << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            data[i][j] -= other.data[i][j];
        }
    }
    std::cout << "Macierze odj�te." << std::endl;
}

void Matrix::transpose() {
    // Utworzenie nowej macierzy do przechowania wyniku transpozycji
    int** transposedData = new int* [columns];
    for (int i = 0; i < columns; ++i) {
        transposedData[i] = new int[rows];
    }

    // Przepisanie danych z bie��cej macierzy do macierzy transponowanej
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            transposedData[j][i] = data[i][j];
        }
    }

    // Zwolnienie pami�ci bie��cej macierzy i ustawienie nowej macierzy transponowanej
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;

    data = transposedData;

    // Zamiana liczby wierszy i kolumn miejscami
    std::swap(rows, columns);

    std::cout << "Macierz transponowana." << std::endl;
}


void Matrix::multiply(const Matrix& other) {
    if (columns != other.rows) {
        std::cerr << "Nie mo�na pomno�y� macierzy o nieodpowiednich rozmiarach." << std::endl;
        return;
    }

    // Utworzenie nowej macierzy do przechowania wyniku mno�enia
    int** multipliedData = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        multipliedData[i] = new int[other.columns]();
    }

    // Obliczenie wyniku mno�enia macierzy
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.columns; ++j) {
            for (int k = 0; k < columns; ++k) {
                multipliedData[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }

    // Zwolnienie pami�ci bie��cej macierzy i ustawienie nowej macierzy wynikowej
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;

    data = multipliedData;

    // Ustawienie liczby kolumn na liczb� kolumn macierzy drugiej
    columns = other.columns;

    std::cout << "Macierze pomno�one." << std::endl;
}


void Matrix::saveToFile(const char* filename) const {
    // Zapisanie wyniku macierzy do nowego pliku
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                file << data[i][j] << " ";
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Wynik zapisany do pliku: " << filename << std::endl;
    }
    else {
        std::cerr << "Nie mo�na otworzy� pliku do zapisu." << std::endl;
    }
}

void Matrix::clear() {
    if (data) {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
    rows = 0;
    columns = 0;
    data = nullptr;
}

// Metoda do wy�wietlania macierzy
void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << uniquedata[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
