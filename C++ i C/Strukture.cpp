#include <iostream>
#include <map>
#include <string>
#include <algorithm>

struct Item {
    int id;
    std::string name;
    double price;
};

struct User {
    int id;
    std::string username;
};

struct Wishlist {
    User owner;
    std::map<int, Item> items;
};

void addItem(Wishlist& wl, const Item& item) {
    wl.items[item.id] = item;
}

bool removeItemById(Wishlist& wl, int id) {
    auto it = wl.items.find(id);

    if (it != wl.items.end()) {
        wl.items.erase(it);
        return true;
    }
    return false;
}

void printWishlist(const Wishlist& wl) {
    std::cout << "Wishlist usera: " << wl.owner.username << "\n";

    for (auto it = wl.items.begin(); it != wl.items.end(); ++it) {
        const Item& item = it->second;
        std::cout << item.id << " | "
                  << item.name << " | "
                  << item.price << " KM\n";
    }
}

bool containsItem(const Wishlist& wl, int id) {
    return wl.items.find(id) != wl.items.end();
}

void printExpensiveItems(const Wishlist& wl, double minPrice) {
    std::for_each(
        wl.items.begin(),
        wl.items.end(),
        [minPrice](const auto& pair) {
            if (pair.second.price > minPrice) {
                std::cout << pair.second.name
                          << " (" << pair.second.price << " KM)\n";
            }
        }
    );
}

int main() {
    User user{1, "adin"};
    Wishlist wl{user};

    addItem(wl, {101, "Laptop", 1800});
    addItem(wl, {102, "Mis", 40});
    addItem(wl, {103, "Tastatura", 120});

    printWishlist(wl);

    std::cout << "\nProvjera postojanja itema ID=103:\n";
    if (containsItem(wl, 103))
        std::cout << "Item postoji\n";

    std::cout << "\nBrisanje itema ID=102\n";
    removeItemById(wl, 102);
    printWishlist(wl);

    std::cout << "\nSkupi itemi (>100 KM):\n";
    printExpensiveItems(wl, 100);

    return 0;
}