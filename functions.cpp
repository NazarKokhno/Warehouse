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

    if (date[2] != '.' || date[5] != '.')
        return false;

    return true;
}

void SaveAll(Product arr[], int globalQuantity)
{
    FILE* f = fopen("warehouse.txt", "w");
    if (f == NULL)
    {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < globalQuantity; i++)
    {
        fprintf(f, "%s|%s|%.2f|%s|%s|%s\n",
            arr[i].manufacturerName,
            arr[i].productName,
            arr[i].productPrice,
            arr[i].groupName,
            arr[i].arrivalDate,
            arr[i].expirationDate);
    }

    fclose(f);
}
void AppendProducts(Product arr[], int start, int end)
{
    FILE* f = fopen("warehouse.txt", "a"); 
    if (f == NULL)
    {
        perror("Error opening file");
        return;
    }

    for (int i = start; i < end; i++)
    {
        fprintf(f, "%s|%s|%.2f|%s|%s|%s\n",
            arr[i].manufacturerName,
            arr[i].productName,
            arr[i].productPrice,
            arr[i].groupName,
            arr[i].arrivalDate,
            arr[i].expirationDate);
    }

    fclose(f);
}

//Menu functions
void AddProducts(Product arr[], int SIZE, int& globalQuantity)
{
   
    int freeSpace = SIZE - globalQuantity;
    
    if (freeSpace <= 0)
    {
        cout << "Warehouse is full!" << endl;
        return;
    }

    cout << "Free space: " << freeSpace << endl;
    cout << "How many products would you like to add?: ";

    int quantity;
    
    do
    {
        while (!(cin >> quantity))
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Invalid input! Enter a number: ";
        }
        
        if (quantity <= 0 || quantity > freeSpace)
        {
            cout << "Enter the correct quantity.(1 - " << freeSpace << "): ";
        }

    } while (quantity <= 0 || quantity > freeSpace);

    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    int start = globalQuantity;
    int end = globalQuantity + quantity;

    for (int i = start; i < end; i++)
    {
        cout << "POSITION " << i + 1 << endl;

        cout << "Enter the product name: ";
        cin.getline(arr[i].productName, PRODUCT_NAME_SIZE);

        cout << "Enter the manufacturer's name: ";
        cin.getline(arr[i].manufacturerName, MANUFACTURER_NAME_SIZE);

        cout << "Enter the product price: ";
        
        while (!(cin >> arr[i].productPrice) || arr[i].productPrice < 0)
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Invalid input! Enter a non-negative number: ";
        }

        cin.ignore((numeric_limits<streamsize>::max)(), '\n');

        cout << "Enter the product`s group name: ";
        cin.getline(arr[i].groupName, GROUP_NAME_SIZE);

        bool isValid;
        
        do
        {
            cout << "Enter the date of arrival at the warehouse (DD.MM.YYYY): ";
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
            while (!(cin >> choiceForDate))
            {
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cout << "Invalid input! Enter a number: ";
            }

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

                isValid = IsValidDateFormat(arr[i].expirationDate);

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
        cout << "Save changes? (0 - No, 1 - Yes): ";
        
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Invalid input! Enter a number: ";
        }

        switch (choice)
        {

            case 0:
            {
                return;
            }

            case 1:
            {
                AppendProducts(arr, start, end);
                    globalQuantity += quantity;
                break;
            }

            default:
                cout << "Invalid input!" << endl;
                break;
        }

    } while (choice != 0 && choice != 1);
               

}
void QuickCheckForDemo(Product arr[], int SIZE, int& globalQuantity)
{
    int freeSpace = SIZE - globalQuantity;

    if (freeSpace < 10)
    {
        cout << "Warehouse is full!" << endl;
        cout << "To use the quick check mode, free up space for 10 items." << endl;
        return;
    }
   

    Product products[10] =
    {
    {"Nestle", "Nesquik", 129.50, "Food", "05.10.2026", "05.04.2027"},
    {"Coca-Cola", "Coca-Cola 0.5L", 35.00, "Drinks", "05.10.2026", "05.04.2027"},
    {"Milka", "Milk Chocolate", 89.99, "Food", "05.10.2026", "05.03.2027"},
    {"Barilla", "Spaghetti", 74.50, "Food", "05.10.2026", "05.10.2028"},
    {"J7", "Orange Juice", 69.90, "Drinks", "05.10.2026", "05.01.2027"},
    {"Nivea", "Shower Gel", 119.00, "Cosmetics", "05.10.2026", "05.10.2029"},
    {"Colgate", "Toothpaste", 85.00, "Hygiene", "05.10.2026", "05.10.2029"},
    {"Rexona", "Deodorant", 109.50, "Hygiene", "05.10.2026", "05.10.2029"},
    {"Lay's", "Potato Chips", 54.99, "Snacks", "05.10.2026", "05.02.2027"},
    {"Orbit", "Chewing Gum", 39.50, "Snacks", "05.10.2026", "05.10.2027"} };


    for (int i = 0; i < 10; i++)
    {
        arr[globalQuantity + i] = products[i];
    }

    AppendProducts(arr, globalQuantity, globalQuantity + 10);
    globalQuantity += 10;
}
bool EnsureWarehouseExists(Product arr[], int size, int& globalQuantity)
{
    if (globalQuantity > 0)
    {
        return true;
    }

    cout << "The warehouse is empty. Add products first or use Quick Check." << endl;

    int choice;
    cout << "1 - Add products; 2 - Quick Check; 0 - Exit" << endl;
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    switch (choice)
    {
        case 1:
        {
            AddProducts(arr, size, globalQuantity);
            return globalQuantity > 0;
        }

        case 2:
        {
            QuickCheckForDemo(arr, size, globalQuantity);
            return globalQuantity > 0;
        }

        case 0:
        {
            return false;
        }

        default:
        {
            cout << "Invalid input!" << endl;
            return false;
        }
    }
    
}
void RemoveProduct(Product arr[], int& globalQuantity)
{
    char item[PRODUCT_NAME_SIZE];
    int index = -1;
    cout << "Which item do you want to remove?" << endl;
    cout << "--> ";
    cin.getline(item, PRODUCT_NAME_SIZE);
   

    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].productName, item) == 0)
        {
            index = i;
            break;
        }

    }

    if (index == -1)
    {
        cout << "Product not found!" << endl;
        return;
    }

    for (int i = index; i < globalQuantity - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    globalQuantity--;
    cout << "The product was removed." << endl;
    SaveAll(arr, globalQuantity);
}

// MENU
void ShowSearchMenu()
{
    cout << "\n===== SEARCH =====" << endl;
    cout << "1 - By product name" << endl;
    cout << "2 - By manufacturer" << endl;
    cout << "3 - By price" << endl;
    cout << "4 - By product group" << endl;
    cout << "5 - By arrival date" << endl;
    cout << "6 - By expiration date" << endl;
    cout << "0 - Back" << endl;
    cout << "Your choice: ";
}
void SearchMenu(Product arr[], int globalQuantity)
{
    int choice;

    do
    {
        ShowSearchMenu();
        
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
            // SearchByName(arr, globalQuantity);
            break;
        case 2:
            // SearchByManufacturer(arr, globalQuantity);
            break;
        case 3:
            // SearchByPrice(arr, globalQuantity);
            break;
        case 4:
            // SearchByGroup(arr, globalQuantity);
            break;
        case 5:
            // SearchByArrivalDate(arr, globalQuantity);
            break;
        case 6:
            // SearchByExpirationDate(arr, globalQuantity);
            break;
        case 0:
            break;
        default:
            cout << "Invalid input!" << endl;
        }
    } while (choice != 0);
}

