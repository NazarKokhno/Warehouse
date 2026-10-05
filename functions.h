#pragma once

#include "product.h";


// Validation functions
bool IsValidExpirationDate(const char date[]);
bool IsValidDateFormat(const char date[]);

//Menu functions
void AddProducts(Product arr[], int SIZE, int& globalQuantity);
void quickCheckForDemo(Product arr[], int SIZE, int& globalQuantity);
bool EnsureWarehouseExists(Product arr[], int size, int& globalQuantity);

// MENU
void ShowSearchMenu();
void SearchMenu(Product arr[], int globalQuantity);