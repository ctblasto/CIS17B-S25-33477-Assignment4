#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <stdexcept>

// Custom exceptions
class DuplicateItemException : public std::runtime_error {
public:
    DuplicateItemException(const std::string& msg) : std::runtime_error(msg) {}
};

class ItemNotFoundException : public std::runtime_error {
public:
    ItemNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

// StoredItem class
class StoredItem {
private:
    std::string id;
    std::string description;
    std::string location;

public:
    StoredItem(std::string id, 
        std::string desc,
        std::string loc): id(std::move(id)), 
        description(std::move(desc)),
        location(std::move(loc)) {
    }

    std::string getId() const { return id; }
    std::string getDescription() const { return description; }
    std::string getLocation() const { return location; }
};

// StorageManager class
class StorageManager {
private:
    std::unordered_map<std::string,
        std::shared_ptr<StoredItem>> itemById;
    std::map<std::string,
        std::shared_ptr<StoredItem>> itemByDescription;

public:
    void addItem(const std::shared_ptr<StoredItem>& item) {
        const std::string& id = item->getId();
        const std::string& desc = item->getDescription();

        if (itemById.count(id)) {
            throw DuplicateItemException
            ("Item with ID " + id + " already exists!");
        }

        itemById[id] = item;
        itemByDescription[desc] = item;
        std::cout << "Adding item: " << id << " - " << desc << std::endl;
    }

    std::shared_ptr<StoredItem> findById(const std::string& id) const {
        auto it = itemById.find(id);
        if (it == itemById.end()) {
            throw ItemNotFoundException
            ("Item with ID " + id + " not found!");
        }
        return it->second;
    }

    void removeItem(const std::string& id) {
        auto it = itemById.find(id);
        if (it == itemById.end()) {
            throw ItemNotFoundException
            ("Item with ID " + id + " not found!");
        }

        std::string desc = it->second->getDescription();
        itemById.erase(it);
        itemByDescription.erase(desc);
        std::cout << "Removed item with ID " << id << std::endl;
    }

    void listItemsByDescription() const {
        std::cout << "Items in Description Order:\n";
        for (const auto& pair : itemByDescription) {
            std::cout << "- " << pair.second->getDescription()
                << ": " << pair.second->getLocation() << std::endl;
        }
    }
};

// Test: Adding duplicate item
void testDuplicateAddition(StorageManager& sm) {
    std::cout << "Attempting to add ITEM001 again...\n";
    try {
        auto duplicateItem = std::make_shared<StoredItem>("ITEM001", "LED Light", "Aisle 3, Shelf 1");
        sm.addItem(duplicateItem);
    }
    catch (const DuplicateItemException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Test: Finding nonexistent item
void testItemNotFound(StorageManager& sm) {
    std::cout << "Removing ITEM003...\n";
    try {
        sm.removeItem("ITEM003");
    }
    catch (const ItemNotFoundException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Main demo
int main() {
    StorageManager manager;

    // Add sample items
    auto item1 = std::make_shared<StoredItem>("ITEM001", "LED Light", "Aisle 3, Shelf 1");
    auto item2 = std::make_shared<StoredItem>("ITEM002", "Fan Motor", "Aisle 2, Shelf 5");

    manager.addItem(item1);
    manager.addItem(item2);

    // Test duplicate
    testDuplicateAddition(manager);

    // Find item
    std::cout << "Retrieving ITEM002...\n";
    try {
        auto found = manager.findById("ITEM002");
        std::cout << "Found: " << found->getDescription()
            << " at " << found->getLocation() << std::endl;
    }
    catch (const ItemNotFoundException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test not found
    testItemNotFound(manager);

    // List items
    manager.listItemsByDescription();

    return 0;
}
