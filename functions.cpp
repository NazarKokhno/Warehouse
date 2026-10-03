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

using namespace std;


bool IsValidDateFormat(const char date[])
{
    if (strlen(date) != 10)
        return false;

    if (date[2] != '-' || date[5] != '-')
        return false;

    return true;
}

bool IsValidExpirationDate(const char date[])
{
    if (strlen(date) != 10)
        return false;

    if (date[2] != '.' || date[5] != '.')
        return false;

    return true;
}

void CreateWarehouse(Product arr[], int SIZE, int& globalQuantity)
{

    cout << "How many products would you like to add?: ";
    int quantity;
    do
    {
        cin >> quantity;

        if (quantity <= 0 || quantity > SIZE)
        {
            cout << "Enter the correct quantity.(1 - " << SIZE << "): ";
        }

    } while (quantity <= 0 || quantity > SIZE);


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
        
        bool isValid;
        do
        {
            cout << "Enter the date of arrival at the warehouse (DD-MM-YYYY): ";
            cin.getline(arr[i].arrivalDate, ARRIVAL_DATE_SIZE);

            isValid = IsValidDateFormat(arr[i].arrivalDate);

            if (!isValid)
            {
                cout << "Invalid input!" << endl;
            }

        } while (!isValid);


        int choiceForDate;

        do
        {
            cout << "Does this product have an expiration date? (0 - No, 1 - Yes): ";
            cin >> choiceForDate;

            if (choiceForDate != 0 && choiceForDate != 1)
            {
                cout << "Invalid input!" << endl;
            }

        } while (choiceForDate != 0 && choiceForDate != 1);

        cin.ignore((numeric_limits<streamsize>::max)(), '\n');


        if (choiceForDate == 0)
        {
            strncpy(arr[i].expirationDate, "No expiration date", EXPIRATION_DATE_SIZE - 1);
            arr[i].expirationDate[EXPIRATION_DATE_SIZE - 1] = '\0';
        }
        else
        {
            do
            {
                cout << "Enter the product's expiration date (DD.MM.YYYY): ";
                cin.getline(arr[i].expirationDate, EXPIRATION_DATE_SIZE);

                isValid = IsValidExpirationDate(arr[i].expirationDate);

                if (!isValid)
                {
                    cout << "Invalid input!" << endl;
                }

            } while (!isValid);
        }

    }
    int choice;
    
    do
    {
        cout << "Save changes? (0/1): ";
        cin >> choice;

        switch (choice)
        {

        case 0:
        {
            return;
        }

        case 1:
        {

            FILE* warehouseFile = fopen("warehouse.txt", "w");

            if (warehouseFile == NULL)
            {
                perror("Error opening file");
                return;
            }

            globalQuantity += quantity;

            fprintf(warehouseFile, "%-20s %-20s %-20s %-20s %-20s %-25s\n\n",
                "Manufacturer",
                "Product",
                "Price",
                "Group",
                "Date of arrival",
                "Best-before date");

            for (int i = 0; i < quantity; i++)
            {
                fprintf(warehouseFile, "%-20s %-20s %-20.2f %-20s %-20s %-25s\n",
                    arr[i].manufacturerName,
                    arr[i].productName,
                    arr[i].productPrice,
                    arr[i].groupName,
                    arr[i].arrivalDate,
                    arr[i].expirationDate);
            }

            fclose(warehouseFile);
            break;
        }

        default:
        {
            cout << "invalid input";
            break;
        }

        }

    } while (choice != 0 && choice != 1);
}
