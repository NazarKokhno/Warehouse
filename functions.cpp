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

// Validation function
bool IsValidDateFormat(const char date[])
{
    if (strlen(date) != 10)
        return false;

    if (date[2] != '.' || date[5] != '.')
        return false;

    return true;
}

// File Operations Functions
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

//Filling an array
void InputProduct(Product& p)
{

    cout << "Enter the manufacturer's name: ";
    cin.getline(p.manufacturerName, MANUFACTURER_NAME_SIZE);

    cout << "Enter the product name: ";
    cin.getline(p.productName, PRODUCT_NAME_SIZE);


    cout << "Enter the product price: ";

    while (!(cin >> p.productPrice) || p.productPrice < 0)
    {
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        cout << "Invalid input! Enter a non-negative number: ";
    }

    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    cout << "Enter the product`s group name: ";
    cin.getline(p.groupName, GROUP_NAME_SIZE);

    bool isValid;

    do
    {
        cout << "Enter the date of arrival at the warehouse (DD.MM.YYYY): ";
        cin.getline(p.arrivalDate, ARRIVAL_DATE_SIZE);

        isValid = IsValidDateFormat(p.arrivalDate);

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
        strncpy(p.expirationDate, "No expiration date", EXPIRATION_DATE_SIZE - 1);

        p.expirationDate[EXPIRATION_DATE_SIZE - 1] = '\0';
    }

    else
    {
        do
        {
            cout << "Enter the product's expiration date (DD.MM.YYYY): ";
            cin.getline(p.expirationDate, EXPIRATION_DATE_SIZE);

            isValid = IsValidDateFormat(p.expirationDate);

            if (!isValid)
            {
                cout << "Invalid input!" << endl;
            }

        } while (!isValid);
    }


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
    cout << "How many products would you like to add?" << endl;
    cout << "--> ";

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
        InputProduct(arr[i]);
        
    }

    int choice;

    do
    {
        cout << "Save changes? (0 - No, 1 - Yes)" << endl;
        cout << "--> ";

        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Invalid input! Enter a number: ";
        }
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');

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
               
    cout << "Product added. To see the changes, select \"Show all products\" in the menu." << endl;
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

    cout << "Products added." << endl << endl;
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
    cout << "--> ";
 
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
    SaveAll(arr, globalQuantity);
    cout << "The product was removed. To see the changes, select \"Show all products\" in the menu." << endl;
}
void ReplaceProduct(Product arr[], int& globalQuantity)
{
    char item[PRODUCT_NAME_SIZE];
    

    int index = -1;

    cout << "Enter the name of the current product." << endl;
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

    cout << "\nProduct found" << endl;
    cout << "Enter new product data ⬇" << endl << endl;

    InputProduct(arr[index]);

    SaveAll(arr, globalQuantity);
    cout << "The product was replaced. To see the changes, select \"Show all products\" in the menu." << endl;
    
}
void ShowAllProducts(Product arr[], int& globalQuantity)
{
    if (globalQuantity == 0)
    {
        cout << "The warehouse is empty." << endl;
        return;
    }
    
    for (int i = 0; i < globalQuantity; i++)
    {
        cout << i + 1 << ". "
            << arr[i].manufacturerName << " | "
            << arr[i].productName << " | "
            << arr[i].productPrice << " | "
            << arr[i].groupName << " | "
            << arr[i].arrivalDate << " | "
            << arr[i].expirationDate << endl;
    }
}
void SearchByName(Product arr[], int& globalQuantity)
{
    char nameChoice[PRODUCT_NAME_SIZE];
    cout << "Enter the product name to search" << endl;
    cout << "--> ";
    cin.getline(nameChoice, PRODUCT_NAME_SIZE);

    int matches = 0;

    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].productName, nameChoice) == 0)
        {
            matches++;
        }
    }

    if (matches == 0)
    {
        cout << "Product not found!" << endl;
        return;
    }

    cout << "\nMatches found: " << matches << endl;

    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].productName, nameChoice) == 0)
        {
            cout << arr[i].manufacturerName << " | "
                << "(" << arr[i].productName << ")" << " | "
                << arr[i].productPrice << " | "
                << arr[i].groupName << " | "
                << arr[i].arrivalDate << " | "
                << arr[i].expirationDate << endl;
        }
    }

}
void SearchByManufacturer(Product arr[], int& globalQuantity)
{
    char manufacturerChoice[MANUFACTURER_NAME_SIZE];
    cout << "Enter the product manufacturer to search" << endl;
    cout << "--> ";
    cin.getline(manufacturerChoice, MANUFACTURER_NAME_SIZE);

    int matches = 0;

    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].manufacturerName, manufacturerChoice) == 0)
        {
            matches++;
        }
    }

    if (matches == 0)
    {
        cout << "Product not found!" << endl;
        return;
    }

    cout << "\nMatches found: " << matches << endl;

    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].manufacturerName, manufacturerChoice) == 0)
        {
            cout << "(" << arr[i].manufacturerName << ")" << " | "
                << arr[i].productName << " | "
                << arr[i].productPrice << " | "
                << arr[i].groupName << " | "
                << arr[i].arrivalDate << " | "
                << arr[i].expirationDate << endl;
        }
    }

}
void SearchByPrice(Product arr[], int& globalQuantity)
{
    double priceChoice;
    cout << "Enter the product price to search" << endl;
    cout << "--> ";
    cin >> priceChoice;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    int matches = 0;

    for (int i = 0; i < globalQuantity; i++)
    {
        if (arr[i].productPrice == priceChoice)
        {
            matches++;
        }
    }

    if (matches == 0)
    {
        cout << "Product not found!" << endl;
        return;
    }

    cout << "\nMatches found: " << matches << endl;

    for (int i = 0; i < globalQuantity; i++)
    {
        if (arr[i].productPrice == priceChoice)
        {
            cout << arr[i].manufacturerName << " | "
                << arr[i].productName << " | "
                << "(" << arr[i].productPrice << ")" << " | "
                << arr[i].groupName << " | "
                << arr[i].arrivalDate << " | "
                << arr[i].expirationDate << endl;
        }
    }

}
void SearchByGroup(Product arr[], int& globalQuantity)
{
    char groupChoice[GROUP_NAME_SIZE];
    cout << "Enter the product group to search (e.g. Food)" << endl;
    cout << "--> ";
    cin.getline(groupChoice, GROUP_NAME_SIZE);

    int matches = 0;

    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].groupName, groupChoice) == 0)
        {
            matches++;
        }
    }

    if (matches == 0)
    {
        cout << "Product not found!" << endl;
        return;
    }

    cout << "\nMatches found: " << matches << endl;

    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].groupName, groupChoice) == 0)
        {
            cout << arr[i].manufacturerName << " | "
                << arr[i].productName << " | "
                << arr[i].productPrice << " | "
                << "(" << arr[i].groupName << ")" << " | "
                << arr[i].arrivalDate << " | "
                << arr[i].expirationDate << endl;
        }
    }

}
void SearchByArrivalDate(Product arr[], int& globalQuantity)
{
    char ArrivalDateChoice[ARRIVAL_DATE_SIZE];
    
    int matches = 0;
    bool isValid;

    do
    {
        cout << "Enter the arrival date to search (DD.MM.YYYY)" << endl;
        cout << "--> ";
        cin.getline(ArrivalDateChoice, ARRIVAL_DATE_SIZE);

        isValid = IsValidDateFormat(ArrivalDateChoice);

        if (!isValid)
        {
            cout << "Invalid input!" << endl;
        }

    } while (!isValid);

    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].arrivalDate, ArrivalDateChoice) == 0)
        {
            matches++;
        }
    }

    if (matches == 0)
    {
        cout << "Product not found!" << endl;
        return;
    }

    cout << "\nMatches found: " << matches << endl;

    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].arrivalDate, ArrivalDateChoice) == 0)
        {
            cout << arr[i].manufacturerName << " | "
                << arr[i].productName << " | "
                << arr[i].productPrice << " | "
                << arr[i].groupName << " | "
                << "(" << arr[i].arrivalDate << ")" << " | "
                << arr[i].expirationDate << endl;
        }
    }

}
void SearchByExpirationDate(Product arr[], int& globalQuantity)
{
    char ExpirationDateChoice[EXPIRATION_DATE_SIZE];

    int matches = 0;
    bool isValid;

    do
    {
        cout << "Enter the expiration date to search (DD.MM.YYYY): ";
        cin.getline(ExpirationDateChoice, EXPIRATION_DATE_SIZE);

        isValid = IsValidDateFormat(ExpirationDateChoice);

        if (!isValid)
        {
            cout << "Invalid input!" << endl;
        }

    } while (!isValid);



    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].expirationDate, ExpirationDateChoice) == 0)
        {
            matches++;
        }
    }

    if (matches == 0)
    {
        cout << "Product not found!" << endl;
        return;
    }

    cout << "\nMatches found: " << matches << endl;

    for (int i = 0; i < globalQuantity; i++)
    {
        if (strcmp(arr[i].expirationDate, ExpirationDateChoice) == 0)
        {
            cout << arr[i].manufacturerName << " | "
                << arr[i].productName << " | "
                << arr[i].productPrice << " | "
                << arr[i].groupName << " | "
                << arr[i].arrivalDate  << " | "
                << "(" << arr[i].expirationDate << ")" << endl;
        }
    }

}



// MENU

void ShowMenu(int globalQuantity)
{
    cout << "\n===== WAREHOUSE DEMO MODE =====" << endl;
    cout << "Products in warehouse: " << globalQuantity << " / " << WAREHOUSE_SIZE << endl;
    cout << "1 - Add product" << endl;
    cout << "2 - Remove product" << endl;
    cout << "3 - Replace product" << endl;
    cout << "4 - Search product" << endl;
    cout << "5 - Sort product" << endl;
    cout << "6 - Quick Check (Add 10 Demo Products)" << endl;
    cout << "7 - Show all products" << endl;
    cout << "0 - Exit" << endl;
    cout << "Your choice: ";
}
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
void ShowSortMenu()
{
    cout << "\n===== SORT =====" << endl;
    cout << "1 - By price" << endl;
    cout << "2 - By product group" << endl;
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
             SearchByName(arr, globalQuantity);
            break;
        case 2:
             SearchByManufacturer(arr, globalQuantity);
            break;
        case 3:
             SearchByPrice(arr, globalQuantity);
            break;
        case 4:
             SearchByGroup(arr, globalQuantity);
            break;
        case 5:
             SearchByArrivalDate(arr, globalQuantity);
            break;
        case 6:
             SearchByExpirationDate(arr, globalQuantity);
            break;
        case 0:
            break;
        default:
            cout << "Invalid input!" << endl;
        }
    } while (choice != 0);
}
void SortMenu(Product arr[], int globalQuantity)
{
    int choice;

    do
    {
        ShowSortMenu();

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
            // SortByName(arr, globalQuantity);
            break;
        case 2:
            // SortByProductGroup(arr, globalQuantity);
            break;
        case 0:
            break;
        default:
            cout << "Invalid input!" << endl;
        }
    } while (choice != 0);


}

