# Lab Assignment-6

This C program reads data from a CSV file(listings.csv) and sorts the data by keys host_name and price separately and writes that data into two different files(listings_hostname.csv and listings_price.csv).

# Functions
**getfields** : To parse each line in the csv file

**sorting** : sorts the array of list items using qsort and writing the sorted data to files using fprintf.

**compare_hostname && compare_price** : The functions used by qsort to compare two pointers.

**main function** : Reads the data in csv file using fgets and calls the function sorting with different file names and different functions.

# Structure of listing
**Integer** : id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count, availability_365;

**String** : host_name, neighbourhood_group, neighbourhood, room_type;

**Float** : latitude, longitude, price;

# Compilation
**To compile** : use the make file to compile the program

**To Run** : ./lab_Assignment6

# output
![Terminal](lab6_1.png)

![Files created](lab6_2.png)

