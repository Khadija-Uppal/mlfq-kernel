#include <stdio.h>
#include <unistd.h> // for usleep

void load_kernel() {
    printf("\033[1;32m"); // Set text color to green
    printf("Starting MyKernel OS...\n");
    char* modules[] = {"Initializing Memory...", "Loading CPU Scheduler...", "Mounting MLFQ...", "Ready!"};
    
    for(int i = 0; i < 4; i++) {
        printf("[ OK ] %s\n", modules[i]);
        usleep(800000); // Wait 0.8 seconds
    }
    printf("\033[0m"); // Reset color
    printf("\nPress Enter to enter the MLFQ Scheduler Terminal...");
    getchar();
}
