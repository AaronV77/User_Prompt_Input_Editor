#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

struct input_event {
      struct timeval time;
      // Type of event that is occuring
      unsigned short type;
      // The key that is being pressed
      unsigned short code;
      // The type of event that is occuring, key pressed, key unpressed, and key continous pressing
      unsigned int value; 
};

int main(int argc, char *argv[])
{
    struct input_event event;
    FILE* fd;

    if (!(fd = fopen("/dev/input/event3", "rb"))) {
        perror("ERROR: Couldn't open input device");
        return 1;
    }

    for (int i = 0; i < 15; i++) {
        memset(&event, 0, sizeof(event));

        fread(&event, sizeof(event), 1, fd);

        // Strict the type to just key events.
        if (event.type == 1) {
            printf("Time: %ld.%06ld\n", event.time.tv_sec, event.time.tv_usec);
            printf("Type: %u\n", event.type);
            printf("Code: %u\n", event.code);
            printf("Value: %u\n", event.value);
        } else {
			i--;
		}
    }
    
    fclose(fd);

    return 0;
}
