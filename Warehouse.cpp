#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>  
#include <string.h> 
#include <limits>
#include <errno.h>   

#include "constants.h"
#include "product.h"
#include "functions.h"

using namespace std;

int main()
{


    Product warehouseData[WAREHOUSE_SIZE];
    int globalQuantity = 0;
    int choice;

    do
    {
        ShowMenu();
        cin >> choice;
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');

        switch (choice)
        {
        
        case 1:
            if (EnsureWarehouseExists(warehouseData, WAREHOUSE_SIZE, globalQuantity))
            {
                // 
            }
            break;
        
        case 2:
            // RemoveProduct(warehouse, globalQuantity);
            break;
        
        case 3:
            // ReplaceProduct(warehouse, globalQuantity);
            break;
        
        case 4:
            SearchMenu(warehouseData, globalQuantity);
            break;
        
        case 0:
            cout << "Goodbye!" << endl;
            break;
        
        default:
            cout << "Invalid input!" << endl;
        }
    } while (choice != 0);

    return 0;

   
}

