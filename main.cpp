#include <iostream>
#include <string>
#include <vector>

bool initialize(bool film[][12]) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            film[i][j] = true;
        }
    }
    return film;
}

void printField(bool film[][12]) {
    std::cout << "Current bubble film condition." << std::endl;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            std::cout << (film[i][j] ? 'O' : 'X');
        }
        std::cout << std::endl;
    }
}

bool bubbleHere(bool film[][12]) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (film[i][j]) return true;
        }
    }
    printField(film);
    std::cout << "All bubbles on film are burst!" << std::endl;
    return false;
}

bool checkInput(std::string coord) {
    if (coord.length() == 3) {
        // checking if coordinates in "Y X" form
        if (coord[1] != ' ') {
            std::cout << "Incorrect input!" << std::endl;
            return false;
        } else {
            if (coord[0] < '1' or coord[0] > '9' or coord[2] < '1' or coord[2] > '9') {
                std::cout << "Incorrect coordinates (position should be in two integers in range 1..12)" << std::endl;
                return false;
            }
        }
    } else if (coord.length() == 4) {
        // checking if coordinates in "Y XX" or "YY X" form
        int space = coord.find(' ');
        if (space == 1) {
            // checking if coordinates in "Y XX" form
            if (coord[2] != '1') {
                std::cout << "Incorrect coordinates (position should be in two integers in range 1..12)" << std::endl;
                return false;
            } else {
                if (coord[0] < '1' or coord[0] > '9' or coord[3] < '0' or coord[3] > '2') {
                    std::cout << "Incorrect coordinates (position should be in two integers in range 1..12)" << std::endl;
                    return false;
                }
            }
        } else if (space == 2) {
            // checking if coordinates in "YY X" form
            if (coord[0] != '1') {
                std::cout << "Incorrect coordinates (position should be in two integers in range 1..12)" << std::endl;
                return false;
            } else {
                if (coord[1] < '0' or coord[1] > '2' or coord[3] < '1' or coord[3] > '9') {
                    std::cout << "Incorrect coordinates (position should be in two integers in range 1..12)" << std::endl;
                    return false;
                }
            }
        } else {
            std::cout << "Incorrect input!" << std::endl;
            return false;
        }
    } else if (coord.length() == 5) {
        // checking if coordinates in "YY XX" form
        if (coord[2] != ' ') {
            std::cout << "Incorrect input!" << std::endl;
            return false;
        } else {
            if (coord[0] != '1' or coord[3] != '1') {
                std::cout << "Incorrect coordinates (position should be in two integers in range 1..12)" << std::endl;
                return false;
            } else {
                if (coord[1] < '0' or coord[1] > '2' or coord[4] < '0' or coord[4] > '2') {
                    std::cout << "Incorrect coordinates (position should be in two integers in range 1..12)" << std::endl;
                    return false;
                }
            }
        }
    } else {
        // input can't be less 3 or more 5 digits
        if (coord.length() < 3) {
            std::cout << "Incorrect input! Only one integer entered." << std::endl;
        } else if (coord.length() > 5) {
            std::cout << "Incorrect input! Probably two spaces entered, or abracodabra." << std::endl;
        }
        return false;
    }
    return true;
}

std::vector<int> coordRedefinition(std::string coord) {
    // redefinition coordinates from strings to integers and return it by vector
    int subCoord1 = std::stoi(coord.substr(0, coord.find(' '))) - 1;
    int subCoord2 = std::stoi(coord.substr(coord.find(' ') + 1)) - 1;
    std::vector<int> coordRedefined{subCoord1, subCoord2};
    return coordRedefined;
}

bool burstIt(std::vector<int> coord_1, std::vector<int> coord_2, bool film[][12]) {
    int coord_1_1 = coord_1[0];
    int coord_1_2 = coord_1[1];
    int coord_2_1 = coord_2[0];
    int coord_2_2 = coord_2[1];
    if (coord_1_1 > coord_2_1) std::swap(coord_1_1, coord_2_1);
    if (coord_1_2 > coord_2_2) std::swap(coord_1_2, coord_2_2);

    for (int i = coord_1_1; i <= coord_2_1; ++i) {
        for (int j = coord_1_2; j <= coord_2_2; ++j) {
            if (film[i][j]) {
                film[i][j] = false;
                std::cout << "Pop! ";
            }
        }
    }
    std::cout << std::endl;
    return film;
}

int main() {
    std::cout << "Bubble Film" << std::endl;
    bool field[12][12];
    initialize(field);
    std::cout << "Let's burst it!" << std::endl;
    std::string coordFirstCorner, coordSecondCorner;
    while (bubbleHere(field)) {
        printField(field);
        bool correctInput = false;
        while (!correctInput) {
            std::cout << "Enter first corner coordinates (row and column, divided by space) of bubble film area:" << std::endl;
            std::getline(std::cin, coordFirstCorner);
            correctInput = checkInput(coordFirstCorner);
        }
        correctInput = false;
        while (!correctInput) {
            std::cout << "Enter second corner coordinates (row and column, divided by space) of bubble film area:" << std::endl;
            std::getline(std::cin, coordSecondCorner);
            correctInput = checkInput(coordSecondCorner);
        }
        std::vector<int> integCoord_1 = coordRedefinition(coordFirstCorner);
        std::vector<int> integCoord_2 = coordRedefinition(coordSecondCorner);

        burstIt(integCoord_1, integCoord_2, field);
    }
    return 0;
}
/* Задача 17-6-7. Пупырка
Всего в пупырке 12 на 12 шариков-пузырьков. Состояние любого пузырька — это всегда либо он целый, либо нет, т.е. true или false (тип массива bool).
Для начала, требуется реализовать отдельную функцию инициализации пупырки начальным состоянием — полностью целая пупырка, т.е. все элементы true.
Программа заключается в последовательном лопанье целых регионов пузырьков.
Перед каждым таким лопаньем надо показывать пользователю полностью всю плёнку: o — это целый пузырёк, x — лопнутый. Это тоже надо выделить в отдельную функцию.
Пользователь вводит две координаты: координаты начала региона и конца прямоугольного региона.
Сама процедура лопанья пузырей должна быть реализована с помощью отдельной функции, все аргументы должны проверяться на их валидность, что они в в рамках диапазона возможных значений — иначе должна быть выведена ошибка.
После лопанья каждого пузыря, который не был ещё лопнут до того, в консоль должно выводиться сообщение “Pop!”.
Лопанье должно продолжаться до последнего пузырька. Как только вся пупырка потрачена, программа заканчивает выполнение.
В принципе, вы можете подсчитать окончание в самой функции по отображению пузырьков плёнки, т.к. она выполняется после каждого лопанья.
 */