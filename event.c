#include <stdio.h>

int read_battery () {
    FILE *fptr = fopen("/sys/class/power_supply/BAT0/capacity", "r"); 
    
    int percent = 0; 
    fscanf(fptr, "%d", &percent);
    
    fclose(fptr);

    return percent;
}
