#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>  
#include <string.h> 
#include <limits>
#include <errno.h>   
#include "constants.h"


struct Product
{
    char productName[PRODUCT_NAME_SIZE];
    char manufacturerName[MANUFACTURER_NAME_SIZE];
    double productPrice;
    char groupName[GROUP_NAME_SIZE];
    char arrivalDate[ARRIVAL_DATE_SIZE];

};

using namespace std;

void CreateWarehouse(Product arr[], int SIZE, int& globalQuantity)
{
    
    cout << "How many products would you like to add?: ";
    int quantity;
    do 
    {
        cin >> quantity;

        if (quantity <= 0 || quantity > WAREHOUSE_SIZE)
        {
            cout << "Enter the correct quantity.(1 - " << WAREHOUSE_SIZE << "): ";
        }
    
    } while (quantity <= 0 || quantity > WAREHOUSE_SIZE);

    globalQuantity += quantity;

    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    for (int i = 0; i < quantity; i++)
    {
        cout << "POSITION " << i + 1 << endl;

        cout << "Enter the manufacturer's name: ";
        cin.getline(arr[i].manufacturerName, MANUFACTURER_NAME_SIZE);
        
        cout << "Enter the product name: ";
        cin.getline(arr[i].productName, PRODUCT_NAME_SIZE);
        
        cout << "Enter the product price: ";
        cin >> arr[i].productPrice;
        
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        
        cout << "Enter the product`s group name: ";
        cin.getline(arr[i].groupName, GROUP_NAME_SIZE);

        cout << "Enter the date of arrival at the warehouse (DD.MM.YY): ";
        cin.getline(arr[i].arrivalDate, ARRIVAL_DATE_SIZE);

    }

    cout << "Save changes? (0/1)";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 0:
    {
        return;
    }

    case 1:
    {
        FILE* warehouseFile = fopen("warehouse.txt","w");
        
        if (warehouseFile == NULL)
        {
            perror("Error opening file");
            return;
        }
        fprintf(warehouseFile, "%-20s %-20s %-10s %-20s %-15s\n",
            "Manufacturer", "Product", "Price", "Group", "Date of arrival");

        for (int i = 0; i < quantity; i++)
        {
            fprintf(warehouseFile, "%-20s %-20s %-10.2f %-20s %-15s\n",
                arr[i].manufacturerName,
                arr[i].productName,
                arr[i].productPrice,
                arr[i].groupName,
                arr[i].arrivalDate);
        }
        
        fclose(warehouseFile);
    }

   }


}

int main()
{

    int globalQuantity = 0;

    Product warehouseData[WAREHOUSE_SIZE];
    
}

