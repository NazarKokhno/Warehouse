#pragma once

#include "product.h";

bool IsValidDateFormat(const char date[]);
void ShowSearchMenu();
void SearchMenu(Product arr[], int globalQuantity);
bool EnsureWarehouseExists(Product arr[], int size, int& globalQuantity);
void AddProducts(Product arr[], int SIZE, int& globalQuantity);
