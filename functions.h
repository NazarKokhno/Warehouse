#pragma once

#include "product.h";

bool IsValidDateFormat(const char date[]);
void CreateWarehouse(Product arr[], int SIZE, int& globalQuantity);
void ShowMenu();
void ShowSearchMenu();
void SearchMenu(Product arr[], int globalQuantity);
bool EnsureWarehouseExists(Product arr[], int size, int& globalQuantity);