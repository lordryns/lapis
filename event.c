#include <stdio.h>

int read_battery () {
    FILE *fptr = fopen("/sys/class/power_supply/BAT0/capacity", "r"); 
    
    int percent = 0; 
    fscanf(fptr, "%d", &percent);
    
    fclose(fptr);

    return percent;
}


void read_time (char *r_time) {
    FILE *f = popen("date '+%I:%M'", "r");
    fgets(r_time, 20, f);

    pclose(f);
}
