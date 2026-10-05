#pragma once

#include "product.h";


// Validation functions
bool IsValidDateFormat(const char date[]);

void SaveAll(Product arr[], int globalQuantity);
void AppendProducts(Product arr[], int start, int end);

//Menu functions
void AddProducts(Product arr[], int SIZE, int& globalQuantity);
void QuickCheckForDemo(Product arr[], int SIZE, int& globalQuantity);
bool EnsureWarehouseExists(Product arr[], int size, int& globalQuantity);
void RemoveProduct(Product arr[], int& globalQuantity);
void ReplaceProduct(Product arr[], int& globalQuantity);

// MENU
void ShowSearchMenu();
void SearchMenu(Product arr[], int globalQuantity);
void ShowSortMenu();
void SortMenu(Product arr[], int globalQuantity);
