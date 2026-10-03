#pragma once
#include "constants.h"

struct Product
{
    char productName[PRODUCT_NAME_SIZE];
    char manufacturerName[MANUFACTURER_NAME_SIZE];
    double productPrice;
    char groupName[GROUP_NAME_SIZE];
    char arrivalDate[ARRIVAL_DATE_SIZE];
    char expirationDate[EXPIRATION_DATE_SIZE];
};
