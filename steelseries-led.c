#include <hidapi/hidapi.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE	8

#define COLOR_OFF	0
#define COLOR_RED	1
#define COLOR_ORANGE	2
#define COLOR_YELLOW	3
#define COLOR_GREEN	4
#define COLOR_SKY	5
#define COLOR_BLUE	6
#define COLOR_PURPLE	7
#define COLOR_WHITE	8

#define LEVEL_LIGHT	3
#define LEVEL_LOW	2
#define LEVEL_MED	1
#define LEVEL_HIGH	0

#define MODE_NORMAL	1
#define MODE_GAMING	2
#define MODE_BREATHE	3
#define MODE_DEMO	4
#define MODE_WAVE	5

#define REGION_LEFT	1
#define REGION_MIDDLE	2
#define REGION_RIGHT	3

#define COMMAND_MODE	0
#define COMMAND_SET	1
#define COMMAND_HELP	2

void printHelp()
{
	printf("Usage: steelseries-led mode MODE\n");
	printf("  or:  steelseries-led set REGION COLOR LEVEL\n");
	printf("Configure the lighting of a SteelSeries laptop keyboard.\n\n");
	
	printf("MODE can be one of the following:\n");
	printf("\tnormal\t\tSolid lighting for each of the three regions\n");
	printf("\tgaming\t\tOnly the left region is lit\n");
	printf("\tbreathe\t\tLighting fades in and out\n");
	printf("\tdemo\t\tCycles between various colors and modes\n");
	printf("\twave\t\tColors flow from left to right\n\n");
	
	printf("REGION can be one of the following:\n");
	printf("\tleft\n");
	printf("\tright\n");
	printf("\tmiddle\n\n");
	
	printf("COLOR can be one of the following:\n");
	printf("\toff\n");
	printf("\tred\n");
	printf("\torange\n");
	printf("\tyellow\n");
	printf("\tgreen\n");
	printf("\tsky\n");
	printf("\tblue\n");
	printf("\tpurple\n");
	printf("\twhite\n\n");
	
	printf("LEVEL can be one of the following:\n");
	printf("\tlight\n");
	printf("\tlow\n");
	printf("\tmed\n");
	printf("\thigh\n\n");
	
	printf("Examples:\n");
	printf("\tsteelseries-led mode normal\n");
	printf("\t\tPuts the keyboard in normal mode.\n\n");
	
	printf("\tsteelseries-led set left blue high\n");
	printf("\t\tSets the left side of the keyboard to bright blue.\n\n");
	
	printf("\tsteelseries-led set middle off light\n");
	printf("\t\tTurns off the LEDs in the middle of the keyboard.\n");
	printf("\t\tThe last argument is irrelevant in this case.\n\n");
	
	printf("Report bugs to me@bradleylaboon.com\n");
	printf("Home page: <http://www.bradleylaboon.com/projects/steelseries-led/>\n");
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "Missing command.\n");
		fprintf(stderr, "Run 'steelseries-led help' for more information.\n");
		return 1;
	}
	
	// Get mode from arguments
	int command = -1;
	if (strcmp(argv[1], "mode") == 0)
		command = COMMAND_MODE;
	else if (strcmp(argv[1], "set") == 0)
		command = COMMAND_SET;
	else if (strcmp(argv[1], "help") == 0)
		command = COMMAND_HELP;
	
	if (command == -1) {
		fprintf(stderr, "Invalid command -- '%s'\n", argv[1]);
		fprintf(stderr, "Run 'steelseries-led help' for more information.\n");
		return 2;
	}
	
	unsigned char buffer[BUFFER_SIZE];
	for (int i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = 0;
	
	// Populate buffer
	switch (command) {
	case COMMAND_MODE:
		if (argc < 3) {
			fprintf(stderr, "No mode specified.\n");
			fprintf(stderr, "Run 'steelseries-led help' for more information.\n");
			return 1;
		}
		
		// Get the mode argument
		int mode = -1;
		if (strcmp(argv[2], "normal") == 0)
			mode = MODE_NORMAL;
		else if (strcmp(argv[2], "gaming") == 0)
			mode = MODE_GAMING;
		else if (strcmp(argv[2], "breathe") == 0)
			mode = MODE_BREATHE;
		else if (strcmp(argv[2], "demo") == 0)
			mode = MODE_DEMO;
		else if (strcmp(argv[2], "wave") == 0)
			mode = MODE_WAVE;
		
		if (mode == -1) {
			fprintf(stderr, "Invalid mode -- '%s'\n", argv[2]);
			fprintf(stderr, "Run 'steelseries-led help' for more information.\n");
			return 2;
		}
		
		// Bytes for setting mode
		buffer[0] = 1;
		buffer[1] = 2;
		buffer[2] = 65; // Set mode
		buffer[3] = (unsigned char) mode;
		buffer[7] = 236; // End of request
		break;
	case COMMAND_SET:
		if (argc < 5) {
			fprintf(stderr, "Missing arguments for command 'set'.\n");
			fprintf(stderr, "Run 'steelseries-led help' for more information.\n");
			return 1;
		}
		
		// Get the region argument
		int region = -1;
		if (strcmp(argv[2], "left") == 0)
			region = REGION_LEFT;
		else if (strcmp(argv[2], "right") == 0)
			region = REGION_RIGHT;
		else if (strcmp(argv[2], "middle") == 0)
			region = REGION_MIDDLE;
		
		if (region == -1) {
			fprintf(stderr, "Invalid region -- '%s'\n", argv[2]);
			fprintf(stderr, "Run 'steelseries-led help' for more information.\n");
			return 2;
		}
		
		// Get the color argument
		int color = -1;
		if (strcmp(argv[3], "off") == 0)
			color = COLOR_OFF;
		else if (strcmp(argv[3], "red") == 0)
			color = COLOR_RED;
		else if (strcmp(argv[3], "orange") == 0)
			color = COLOR_ORANGE;
		else if (strcmp(argv[3], "yellow") == 0)
			color = COLOR_YELLOW;
		else if (strcmp(argv[3], "green") == 0)
			color = COLOR_GREEN;
		else if (strcmp(argv[3], "sky") == 0)
			color = COLOR_SKY;
		else if (strcmp(argv[3], "blue") == 0)
			color = COLOR_BLUE;
		else if (strcmp(argv[3], "purple") == 0)
			color = COLOR_PURPLE;
		else if (strcmp(argv[3], "white") == 0)
			color = COLOR_WHITE;
		
		if (color == -1) {
			fprintf(stderr, "Invalid color -- '%s'\n", argv[3]);
			fprintf(stderr, "Run 'steelseries-led help' for more information.\n");
			return 2;
		}
		
		// Get the level argument
		int level = -1;
		if (strcmp(argv[4], "light") == 0)
			level = LEVEL_LIGHT;
		else if (strcmp(argv[4], "low") == 0)
			level = LEVEL_LOW;
		else if (strcmp(argv[4], "med") == 0)
			level = LEVEL_MED;
		else if (strcmp(argv[4], "high") == 0)
			level = LEVEL_HIGH;
		
		if (level == -1) {
			fprintf(stderr, "Invalid level -- '%s'\n", argv[4]);
			fprintf(stderr, "Run 'steelseries-led help' for more information.\n");
			return 2;
		}
		
		// Bytes for setting the backlight
		buffer[0] = 1;
		buffer[1] = 2;
		buffer[2] = 66; // Set backlight
		buffer[3] = (unsigned char) region;
		buffer[4] = (unsigned char) color;
		buffer[5] = (unsigned char) level;
		buffer[7] = 236; // End of request
		break;
	case COMMAND_HELP:
	default:
		printHelp();
		return 0;
	}
	
	// Initialize HIDAPI library
	if (hid_init() == -1) {
		fprintf(stderr, "hid_init(): Couldn't initialize HIDAPI.\n");
		return 3;
	}
	
	// Open device
	hid_device *device = hid_open(0x1770, 0xff00, NULL);
	if (device == NULL) {
		fprintf(stderr, "hid_open(): Couldn't open device.\n");
		hid_exit();
		return 3;
	}
	
	// Send the data
	int retVal = 0;
	if (hid_send_feature_report(device, buffer, BUFFER_SIZE) == -1) {
		wchar_t *err = hid_error(device);
		if (err == NULL)
			err = L"Couldn't send data.";
		fprintf(stderr, "hid_send_feature_report(): %ls\n", err);
		retVal = 3;
	}
	
	// Close the device and finalize HIDAPI
	hid_close(device);
	hid_exit();
	
	return retVal;
}
