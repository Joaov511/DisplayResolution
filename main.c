#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    DEVMODE dm;
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);
    
    // First retrieve the current display settings
    if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm) == 0) {
        printf("Could not retrieve display settings.\n");
        return 1;
    }

    if(dm.dmPelsWidth == 1920 && dm.dmPelsHeight == 1080) {
        dm.dmPelsWidth = 2560;
        dm.dmPelsHeight = 1440;
    } else {
        dm.dmPelsWidth = 1920;
        dm.dmPelsHeight = 1080;
    }
    
    // Now modify only what we need to change
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    
    // Attempt to change the display settings
    long result = ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY | CDS_GLOBAL);
    
    // Process the result
    switch (result) {
        case DISP_CHANGE_SUCCESSFUL:
            printf("Resolution changed successfully to %d x %d\n", dm.dmPelsWidth, dm.dmPelsHeight);
            break;
        case DISP_CHANGE_BADMODE:
            printf("The specified graphics mode is not supported.\n");
            break;
        case DISP_CHANGE_BADPARAM:
            printf("An invalid parameter was passed.\n");
            break;
        case DISP_CHANGE_FAILED:
            printf("The display driver failed the specified graphics mode.\n");
            break;
        case DISP_CHANGE_RESTART:
            printf("The computer needs to be restarted for the graphics mode to work.\n");
            break;
        default:
            printf("Failed with error code: %ld\n", result);
            break;
    }
    system("pause");
    return 0;
}