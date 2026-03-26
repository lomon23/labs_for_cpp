#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ==========================================
// 1. АБСТРАКТНИЙ БАЗОВИЙ КЛАС
// ==========================================
class Phone {
protected:
    string brand;
    double price;
    string color;

public:
    Phone(string b, double p, string c) : brand(b), price(p), color(c) {}
    
    // ВІРТУАЛЬНИЙ ДЕСТРУКТОР (ОБОВ'ЯЗКОВО!)
    virtual ~Phone() {}

    // Чисто віртуальні функції (роблять клас абстрактним)
    virtual void printInfo(ostream& out = cout) const = 0; 
    virtual string getType() const = 0;

    // Геттери для доступу в функціях
    double getPrice() const { return price; }
    string getBrand() const { return brand; }
    string getColor() const { return color; }
};

// ==========================================
// 2. ПОХІДНИЙ КЛАС 1
// ==========================================
class MobilePhone : public Phone {
private:
    string cpu;
    int ram;

public:
    // Виклик конструктора базового класу
    MobilePhone(string b, double p, string c, string cp, int r) 
        : Phone(b, p, c), cpu(cp), ram(r) {}

    void printInfo(ostream& out = cout) const override {
        out << "[Mobile] " << brand << " | Color: " << color 
            << " | Price: " << price << " | CPU: " << cpu 
            << " | RAM: " << ram << "GB\n";
    }

    string getType() const override { return "Mobile"; }
};

// ==========================================
// 3. ПОХІДНИЙ КЛАС 2
// ==========================================
class RadioPhone : public Phone {
private:
    double radius;
    bool hasAutoAnswer;

public:
    RadioPhone(string b, double p, string c, double rad, bool autoA) 
        : Phone(b, p, c), radius(rad), hasAutoAnswer(autoA) {}

    void printInfo(ostream& out = cout) const override {
        out << "[Radio] " << brand << " | Color: " << color 
            << " | Price: " << price << " | Radius: " << radius 
            << "m | AutoAnswer: " << (hasAutoAnswer ? "Yes" : "No") << "\n";
    }

    string getType() const override { return "Radio"; }
};

// ==========================================
// ФУНКЦІЯ 1: Сортування за ціною (Бульбашка для вказівників)
// ==========================================
void sortByPrice(Phone** arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Зверни увагу: порівнюємо через вказівники ->
            if (arr[j]->getPrice() > arr[j + 1]->getPrice()) {
                Phone* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ==========================================
// ФУНКЦІЯ 2: Вивід заданої фірми (вже відсортованих) + сума
// ==========================================
void printByBrandAndGetTotal(Phone** arr, int size, string targetBrand) {
    double totalCost = 0;
    cout << "\n--- Phones of brand: " << targetBrand << " ---\n";
    for (int i = 0; i < size; i++) {
        if (arr[i]->getBrand() == targetBrand) {
            arr[i]->printInfo(); // Вивід у консоль
            totalCost += arr[i]->getPrice();
        }
    }
    cout << "Total cost: " << totalCost << "\n";
}

// ==========================================
// ФУНКЦІЯ 3: Запис у файл мобільних заданого кольору в діапазоні
// ==========================================
void saveMobilesToFile(Phone** arr, int size, string targetColor, double minPrice, double maxPrice, string filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "File error!\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        // Перевіряємо тип через нашу віртуальну функцію
        if (arr[i]->getType() == "Mobile") {
            if (arr[i]->getColor() == targetColor && 
                arr[i]->getPrice() >= minPrice && 
                arr[i]->getPrice() <= maxPrice) {
                
                arr[i]->printInfo(outFile); // Вивід у файл!
            }
        }
    }
    outFile.close();
    cout << "\nData saved to " << filename << "\n";
}

// ==========================================
// MAIN
// ==========================================
int main() {
    const int SIZE = 4;
    
    // Створення динамічного масиву вказівників на базовий клас
    Phone** phones = new Phone*[SIZE];

    // Поліморфізм у дії: вказівник бази вказує на об'єкт спадкоємця
    phones[0] = new MobilePhone("Samsung", 1200, "Black", "Snapdragon", 8);
    phones[1] = new RadioPhone("Panasonic", 150, "White", 50.5, true);
    phones[2] = new MobilePhone("Samsung", 900, "Black", "Exynos", 6);
    phones[3] = new RadioPhone("Motorola", 200, "Black", 100.0, false);

    // 1. Сортуємо
    sortByPrice(phones, SIZE);

    // Вивід усіх для перевірки (опціонально)
    cout << "--- All phones sorted by price ---\n";
    for(int i = 0; i < SIZE; i++) {
        phones[i]->printInfo();
    }

    // 2. Друк фірми та сума
    printByBrandAndGetTotal(phones, SIZE, "Samsung");

    // 3. Запис у файл
    saveMobilesToFile(phones, SIZE, "Black", 500, 1500, "result.txt");

    // Звільнення пам'яті (важливо для масиву вказівників)
    for (int i = 0; i < SIZE; i++) {
        delete phones[i]; // Тут відпрацює віртуальний деструктор
    }
    delete[] phones;

    return 0;
}