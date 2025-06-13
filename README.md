# CIS17B-S25-33477-Assignment4
Creating a storage management system using ordered and unordered collections 

this assignment design and implement a C++ application model a Storage Management System using the starter code provided by Professor O'Connor 
this are the requirement: 

Requirements

1. Create a StoredItem class with the following attributes:
std::string id: A unique identifier (e.g., "ITEM001")
std::string description: A short item description (e.g., "LED Light")
std::string location: Where the item is stored (e.g., "Aisle 3, Shelf 1")
Include a constructor and getters.

2. Implement a StorageManager class with the following:
std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemById
std::map<std::string, std::shared_ptr<StoredItem>> itemByDescription

Public Methods:
void addItem(const std::shared_ptr<StoredItem>& item): Adds an item to both maps. Throw a DuplicateItemException if the ID already exists.
std::shared_ptr<StoredItem> findById(const std::string& id) const: Find and return item by ID. Throw an ItemNotFoundException if not found.
void removeItem(const std::string& id): Remove the item from both maps. Throw an exception if the item doesn't exist.
void listItemsByDescription() const: Prints items in order of their description.

3. Define custom exception classes:
DuplicateItemException
ItemNotFoundException

4. In main():
Use std::make_shared to create a few sample items.
Add them using addItem().
Attempt to find an item by ID.
Attempt to remove a non-existent item and catch the exception.
Call listItemsByDescription() to display items in order.
Write simple test functions for:
Adding duplicate items
Finding an item that doesn't exist

It supports:
- Fast item lookups by ID
- Sorted listing by item description
- Safe memory management using `std::shared_ptr`
- Custom exception handling for duplicate and missing items

---

## Features

- Add items to inventory
-  Lookup items by unique ID (using `std::unordered_map`)
- List all items alphabetically by description (using `std::map`)
- Remove items with proper error checking
- Handles duplicates and missing entries with custom exceptions

---

## How to Compile

Make sure you have a C+171-compatible compiler installed (like `g++`).

```bash
g++ -std=c++17 -o congo_inventory main.cpp
