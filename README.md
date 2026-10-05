# Warehouse

Simple console warehouse management application written in C++.

## Features

- Add products
- Delete products
- Replace products
- Search products
- Sort products
- Display all products
- Demo mode

## Search

Products can be searched by:

- Name
- Manufacturer
- Price
- Product group
- Arrival date
- Expiration date

## Sorting

Products can be sorted by:

- Price
- Product group

## Demo Mode

The project includes a `QuickCheckForDemo()` function that adds example products,
so the main features can be tested without entering products manually.

## Project Structure

```text
Warehouse/
├── warehouse.cpp
├── functions.cpp
├── functions.h
├── product.h
└── constants.h
