#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINESIZE 1024

struct listing {
    int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count,availability_365;
    char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
    float latitude, longitude, price;
};

struct listing getfields(char* line){
    struct listing item;
    item.id = atoi(strtok(line, ","));
    item.host_id = atoi(strtok(NULL, ","));
    item.host_name = strdup(strtok(NULL, ","));
    item.neighbourhood_group = strdup(strtok(NULL, ","));
    item.neighbourhood = strdup(strtok(NULL, ","));
    item.latitude = atof(strtok(NULL, ","));
    item.longitude = atof(strtok(NULL, ","));
    item.room_type = strdup(strtok(NULL, ","));
    item.price = atof(strtok(NULL, ","));
    item.minimum_nights = atoi(strtok(NULL, ","));
    item.number_of_reviews = atoi(strtok(NULL, ","));
    item.calculated_host_listings_count = atoi(strtok(NULL, ","));
    item.availability_365 = atoi(strtok(NULL, ","));
    return item;
}
/*void displayStruct(struct listing item) {
    printf("ID : %d\n", item.id);
    printf("Host ID : %d\n", item.host_id);
    printf("Host Name : %s\n", item.host_name);
    printf("Neighbourhood Group : %s\n", item.neighbourhood_group);
    printf("Neighbourhood : %s\n", item.neighbourhood);
    printf("Latitude : %f\n", item.latitude);
    printf("Longitude : %f\n", item.longitude);
    printf("Room Type : %s\n", item.room_type);
    printf("Price : %f\n", item.price);
    printf("Minimum Nights : %d\n", item.minimum_nights);
    printf("Number of Reviews : %d\n", item.number_of_reviews);
    printf("Calculated Host Listings Count : %d\n", item.calculated_host_listings_count);
    printf("Availability_365 : %d\n\n", item.availability_365);
}*/

int compare_hostname(const void *a, const void *b) {
    const struct listing *la = (const struct listing *)a;
    const struct listing *lb = (const struct listing *)b;
    
    return strcmp(la->host_name, lb->host_name);
}


int compare_price(const void *a, const void *b) {
    int p = ((const struct listing *)a)->price;
    int q = ((const struct listing *)b)->price;

    return p - q;
}

void sorting(const char *filename, struct listing *list_items, int count, int (*compare)(const void *, const void *)){
    
    qsort(list_items, count, sizeof(struct listing), compare);

    FILE *fptr = fopen(filename, "w");
    if(fptr == NULL){
        printf("Error reading input file listings.csv\n");
        exit (-1);
    }
    for(int i=0; i < count; i++){
        fprintf(fptr, "%d,%d,%s,%s,%s,%.6f,%.6f,%s,%.2f,%d,%d,%d,%d\n",
                list_items[i].id, list_items[i].host_id, list_items[i].host_name,
                list_items[i].neighbourhood_group, list_items[i].neighbourhood,
                list_items[i].latitude, list_items[i].longitude, list_items[i].room_type,
                list_items[i].price, list_items[i].minimum_nights, list_items[i].number_of_reviews,
                list_items[i].calculated_host_listings_count, list_items[i].availability_365);
    }
    fclose(fptr);


}

int main(int argc, char* args[]) {
    struct listing list_items[22555];
    char line[LINESIZE];
    const char *file_hostname = "listings_hostname.csv";
    const char *file_price = "listings_price.csv";
    int count;
    FILE *fptr = fopen("listings.csv", "r");
    if(fptr == NULL){
        printf("Error reading input file listings.csv\n");
        exit (-1);
    }
    count = 0;
    while (fgets(line, LINESIZE, fptr) != NULL){
        list_items[count++] = getfields(line);
    }
    fclose(fptr);
    /*for (i=0; i<count; i++){
        displayStruct(list_items[i]);
    }*/
    sorting(file_hostname, list_items, count, compare_hostname);

    sorting(file_price, list_items, count, compare_price);
    return 0;
}