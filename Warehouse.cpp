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

    int globalQuantity = 0;

    Product warehouseData[WAREHOUSE_SIZE];

    CreateWarehouse( warehouseData,WAREHOUSE_SIZE,globalQuantity);


    
}

