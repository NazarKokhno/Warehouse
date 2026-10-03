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

void ShowMenu(int globalQuantity)
{
    cout << "\n===== WAREHOUSE MENU =====" << endl;
    cout << "Products in warehouse: " << globalQuantity << " / " << WAREHOUSE_SIZE << endl;
    cout << "1 - Add product" << endl;
    cout << "2 - Remove product" << endl;
    cout << "3 - Replace product" << endl;
    cout << "4 - Search product" << endl;
    cout << "0 - Exit" << endl;
    cout << "Your choice: ";
}

int main()
{

    Product warehouseData[WAREHOUSE_SIZE];
    
    int globalQuantity = 0;

    int choice;
    
    do
    {
        ShowMenu(globalQuantity);
        
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Invalid input! Enter a number: ";
        }
        
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');

        switch (choice)
        {
        
        case 1:

            AddProducts(warehouseData, WAREHOUSE_SIZE, globalQuantity);
            break;
        
        case 2:
            if (EnsureWarehouseExists(warehouseData, WAREHOUSE_SIZE, globalQuantity))
            {
                // RemoveProduct(warehouse, globalQuantity);
            }
                break;
        
        case 3:
            if (EnsureWarehouseExists(warehouseData, WAREHOUSE_SIZE, globalQuantity))
            {
                // ReplaceProduct(warehouse, globalQuantity);
            }
                break;
       
        case 4:

        if (EnsureWarehouseExists(warehouseData, WAREHOUSE_SIZE, globalQuantity))
        {
            SearchMenu(warehouseData, globalQuantity);
        }
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

