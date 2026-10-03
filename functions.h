#pragma once

#include "product.h";

bool IsValidDateFormat(const char date[]);
void CreateWarehouse(Product arr[], int SIZE, int& globalQuantity);