#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

int main(int argc,char *argv[],char *envp[]){
    time_t Time;  // =object of time_t 
    time(&Time); // returns universal time since January 1, 1970 measured in seconds
    char week[7][4] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    char month[12][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};


    if(argv[1] == NULL){
        struct tm* univeral_time = localtime(&Time);
        printf("%s %s %d %02d:%d:%d %s %d\n",week[univeral_time->tm_wday-1],month[univeral_time->tm_mon], univeral_time->tm_mday,(univeral_time->tm_hour) % 24, univeral_time->tm_min, univeral_time->tm_sec,univeral_time->tm_zone,univeral_time->tm_year + 1900);
        exit(EXIT_SUCCESS);
    }
    else if(strcmp(argv[1],"-u") == 0){
        struct tm* univeral_time = gmtime(&Time);
        printf("%s %s %d %02d:%d:%d %s %d\n",week[univeral_time->tm_wday-1],month[univeral_time->tm_mon], univeral_time->tm_mday,(univeral_time->tm_hour) % 24, univeral_time->tm_min, univeral_time->tm_sec,univeral_time->tm_zone,univeral_time->tm_year + 1900);
        exit(EXIT_SUCCESS);
    }
    else if(strcmp(argv[1], "-R") == 0){
        struct tm* univeral_time = localtime(&Time);
        printf("%s, %d %s %d %02d:%d:%d +0530 \n",week[univeral_time->tm_wday-1],univeral_time->tm_mday,month[univeral_time->tm_mon],univeral_time->tm_year + 1900,(univeral_time->tm_hour) % 24, univeral_time->tm_min, univeral_time->tm_sec);
        exit(EXIT_SUCCESS);
    }
    else{
        printf("msh: Error ! 😔🥲\nNo such operation exists for date.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
