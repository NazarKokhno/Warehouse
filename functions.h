#pragma once

#include "product.h";


// Validation functions
bool IsValidDateFormat(const char date[]);

// File Operations Functions
void SaveAll(Product arr[], int globalQuantity);
void AppendProducts(Product arr[], int start, int end);

// ----------------------------
void InputProduct(Product& p);
// ----------------------------

//Menu functions
void AddProducts(Product arr[], int SIZE, int& globalQuantity);
void QuickCheckForDemo(Product arr[], int SIZE, int& globalQuantity);
bool EnsureWarehouseExists(Product arr[], int size, int& globalQuantity);
void RemoveProduct(Product arr[], int& globalQuantity);
void ReplaceProduct(Product arr[], int globalQuantity);
void ShowAllProducts(Product arr[], int globalQuantity);
void SearchByName(Product arr[], int globalQuantity);
void SearchByManufacturer(Product arr[], int globalQuantity);
void SearchByPrice(Product arr[], int globalQuantity);
void SearchByGroup(Product arr[], int globalQuantity);
void SearchByArrivalDate(Product arr[], int globalQuantity);
void SearchByExpirationDate(Product arr[], int globalQuantity);


// MENU
void ShowMenu(int globalQuantity);
void ShowSearchMenu();
void SearchMenu(Product arr[], int globalQuantity);
void ShowSortMenu();
void SortMenu(Product arr[], int globalQuantity);
