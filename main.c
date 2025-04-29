#include <windows.h>
#include <stdio.h>

int main() {
    DEVMODE dm;
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);

    dm.dmPelsWidth = 1600;
    dm.dmPelsHeight = 900;

    LONG result = ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY | CDS_GLOBAL);

    if(result == DISP_CHANGE_SUCCESSFUL) {
        if (result == DISP_CHANGE_SUCCESSFUL) {
            printf("Resolution changed successfully to %d x %d\n", dm.dmPelsWidth, dm.dmPelsHeight);
        } else {
            printf("Failed to change resolution permanently.\n");
        }
    } else {
        printf("The display mode is not supported.\n");
    }
    
    return 0;
}