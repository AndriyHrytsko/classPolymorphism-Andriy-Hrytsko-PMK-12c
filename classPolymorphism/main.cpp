#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Telefon {
protected:
    string name;
    string brand;
    double price;
public:
    Telefon(string n, string b, double p) : name(n), brand(b), price(p) {}
    virtual void display() = 0;
    double getPrice() { return price; }
};

class MobilnyiTelefon : public Telefon {
private:
    string color;
    int memory;
public:
    MobilnyiTelefon(string n, string b, double p, string c, int m) : Telefon(n, b, p), color(c), memory(m) {}
    void display() {
        cout << name << " " << brand << " (color: " << color << ", memory: " << memory << "GB, price: " << price << ")\n";
    }
};

class Radiotelefon : public Telefon {
private:
    int range;
    bool autoAnswer;
public:
    Radiotelefon(string n, string b, double p, int r, bool aa) : Telefon(n, b, p), range(r), autoAnswer(aa) {}
    void display() {
        cout << name << " " << brand << " (range: " << range << "km, ";
        if (autoAnswer) {
            cout << "with auto-answer, ";
        }
        else {
            cout << "without auto-answer, ";
        }
        cout << "price: " << price << ")\n";
    }
    bool hasAutoAnswer() { return autoAnswer; }
};

void readTelefonsFromFile(string filename, vector<Telefon*>& telefons) {
    ifstream file(filename);
    string name, brand, color;
    double price;
    int memory, range;
    bool autoAnswer;

    while (file >> name >> brand >> price) {
        string type;
        file >> type;
        if (type == "mobilnyi") {
            file >> color >> memory;
            telefons.push_back(new MobilnyiTelefon(name, brand, price, color, memory));
        }
        else if (type == "radiotelefon") {
            file >> range >> autoAnswer;
            telefons.push_back(new Radiotelefon(name, brand, price, range, autoAnswer));
        }
    }
}

void writeTelefonsToFile(string filename, vector<Telefon*>& telefons) {
    ofstream file(filename);
    double totalCost = 0;
    sort(telefons.begin(), telefons.end(), [](Telefon* a, Telefon* b) {
        return a->getPrice() < b->getPrice();
        });

    for (Telefon* telefon : telefons) {
        telefon->display();
        totalCost += telefon->getPrice();
    }

    file << "Total cost: " << totalCost << endl;
}

int main() {
    vector<Telefon*> telefons;
    readTelefonsFromFile("telefons1.txt", telefons);
    readTelefonsFromFile("telefons2.txt", telefons);
    vector<Radiotelefon*> autoAnswerTelefons;

    for (Telefon* telefon : telefons) {

    }
}
