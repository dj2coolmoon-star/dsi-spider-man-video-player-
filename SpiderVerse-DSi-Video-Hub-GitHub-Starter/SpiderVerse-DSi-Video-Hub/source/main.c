#include <nds.h>
#include <fat.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VIDEOS 64
#define NAME_LEN  96

static char videos[MAX_VIDEOS][NAME_LEN];
static int video_count = 0;
static int selected = 0;
static char videos_path[128];

static bool has_fv_extension(const char *name) {
    size_t n = strlen(name);
    return n > 3 &&
        name[n - 3] == '.' &&
        (name[n - 2] == 'f' || name[n - 2] == 'F') &&
        (name[n - 1] == 'v' || name[n - 1] == 'V');
}

static void scan_videos(void) {
    video_count = 0;
    DIR *dir = opendir(videos_path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && video_count < MAX_VIDEOS) {
        if (entry->d_name[0] == '.') continue;
        if (has_fv_extension(entry->d_name)) {
            strncpy(videos[video_count], entry->d_name, NAME_LEN - 1);
            videos[video_count][NAME_LEN - 1] = '\0';
            video_count++;
        }
    }
    closedir(dir);
}

static void draw_screen(const char *message) {
    consoleClear();
    iprintf("\x1b[1;1H");
    iprintf("********************************\n");
    iprintf("      SPIDER-VERSE VIDEO HUB    \n");
    iprintf("********************************\n\n");
    iprintf("SD folder: Videos\n");
    iprintf("-------------------------------\n");

    if (video_count == 0) {
        iprintf("\nNo .fv videos found.\n");
        iprintf("Create a folder named Videos\n");
        iprintf("on your SD card and add files.\n");
    } else {
        int start = selected - 5;
        if (start < 0) start = 0;
        for (int i = start; i < video_count && i < start + 10; i++) {
            iprintf("%s %s\n", i == selected ? ">" : " ", videos[i]);
        }
        iprintf("\n%d video(s)", video_count);
    }

    iprintf("\n\n%s\n", message);
    iprintf("\nUP/DOWN: Select");
    iprintf("\nA: Open selected");
    iprintf("\nX: Rescan folder");
    iprintf("\nSTART: Exit");
}

int main(void) {
    consoleDemoInit();
    video_count = 0;

    if (!fatInitDefault()) {
        draw_screen("SD card could not be mounted.");
        while (1) swiWaitForVBlank();
    }

    const char *drive = fatGetDefaultDrive();
    snprintf(videos_path, sizeof(videos_path), "%sVideos", drive);
    mkdir(videos_path, 0777);

    scan_videos();
    draw_screen("Prototype build: video decoder not connected yet.");

    while (1) {
        scanKeys();
        int keys = keysDown();

        if (keys & KEY_UP) {
            if (selected > 0) selected--;
            draw_screen("Choose a video with UP/DOWN.");
        }
        if (keys & KEY_DOWN) {
            if (selected < video_count - 1) selected++;
            draw_screen("Choose a video with UP/DOWN.");
        }
        if (keys & KEY_X) {
            scan_videos();
            if (selected >= video_count) selected = video_count - 1;
            if (selected < 0) selected = 0;
            draw_screen("Video list refreshed.");
        }
        if ((keys & KEY_A) && video_count > 0) {
            char message[NAME_LEN + 64];
            snprintf(message, sizeof(message),
                     "Selected: %s\nPlayback engine is the next build step.",
                     videos[selected]);
            draw_screen(message);
        }
        if (keys & KEY_START) break;

        swiWaitForVBlank();
    }

    return 0;
}
