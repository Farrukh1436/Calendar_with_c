#include <stdio.h>
#include <time.h>
#include <conio.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define CLEAR_SCREEN "\x1B[2J"
#define ANSI_COLOR_BLUE "\033[34m"
void drawcalendar(int d_month, int d_year, int l_day);
int getLastDayOfMonth(int year, int month);
time_t t;
struct tm* current_time;
void main()
{
	time(&t);
	current_time = localtime(&t);
	// Determine the current month
	int c_month = current_time->tm_mon;
	// Determine the current year
	int c_year = (1900 + current_time->tm_year);
	// Adjust the year (e.g., to 2023)
	int desired_year = c_year; // Adjust this value as needed
	// Adjust the month (0 for January, 1 for February, and so on)
	int desired_month = c_month; // Adjust this value as needed 
	int lastday = getLastDayOfMonth(desired_year, desired_month + 1);
	drawcalendar(desired_month, desired_year, lastday);
	// waiting for arrow key
	while (1)
	{
		if (_kbhit())
		{
			int key = _getch();
			// Check for arrow keys
			if (key == 0xE0)
			{
				key = _getch(); // Read the extended key code

				// Handle arrow keys
				switch (key)
				{
				case 72: // Up arrow key
					desired_year += 1;
					break;
				case 80:// Down arrow key
					desired_year -= 1;
					break;
				case 75://Left arrow key
					if (desired_month == 0)
					{
						desired_month = 11;
						desired_year -= 1;
					}
					else
						desired_month -= 1;
					break;
				case 77://Right arrow key
					if (desired_month == 11)
					{
						desired_month = 0;
						desired_year += 1;
					}
					else
						desired_month += 1;
					break;
				}
			}

			// Clear the screen 
			system("cls"); // Windows-specific, for Unix-like systems, use "clear"
			lastday = getLastDayOfMonth(desired_year, desired_month + 1);
			drawcalendar(desired_month, desired_year, lastday);
		}
	}
}

void drawcalendar(int d_month, int d_year, int l_day)
{
	time(&t);
	current_time = localtime(&t);
	int c_day = current_time->tm_mday;
	current_time->tm_year = d_year - 1900; // Adjust to year minus 1900
	current_time->tm_mon = d_month; // Adjust to 0-based index
	// Set the day of the month to 1 to get the first day of the adjusted month
	current_time->tm_mday = 1;
	mktime(current_time);
	// Get the day of the week for the first day of the adjusted month
	int first_day_of_month = current_time->tm_wday;
	char* weeks[7] = { "Mon","Tue","Wed","Thu","Fri","Sat","Sun" };
	char* months[12] = { "January","February","March","April","May","June","July","August","September",
	"October","November","December" };
	//printing current month and year
	printf(ANSI_COLOR_RED"\t   %s %d\n\n"ANSI_COLOR_RESET, months[d_month], d_year);
	//printing weekdays
	for (int i = 0; i < 7; i++)
		printf(ANSI_COLOR_YELLOW"%s  "ANSI_COLOR_RESET, weeks[i]);
	printf("\n");
	int days = 1;
	for (int i = 0; i < 37; i++)
	{
		if (i >= first_day_of_month - 1)
		{
			if (days < 10)
			{
				printf(ANSI_COLOR_GREEN"%d    ", days);
				days++;
			}
			else if (days == c_day)
			{
				printf(ANSI_COLOR_BLUE"%d   "ANSI_COLOR_RESET, days);
				days++;
			}
			else
			{
				printf(ANSI_COLOR_GREEN"%d   "ANSI_COLOR_RESET, days);
				if (days == l_day)
					break;
				days++;
			}
			if (i % 7 == 6)
			{
				printf("\n");
			}
		}
		else
		{
			printf("     ");
		}

	}
}
int getLastDayOfMonth(int year, int month)
{
	struct tm lastDay = { 0 };
	// Set the first day of the next month
	lastDay.tm_year = year - 1900;
	lastDay.tm_mon = month; // month is zero-based
	lastDay.tm_mday = 1;

	// Subtract one day to get the last day of the current month
	time_t lastDayTime = mktime(&lastDay);
	lastDayTime -= 86400; // 86400 seconds in a day

	// Convert back to struct tm
	struct tm* lastDayStruct = localtime(&lastDayTime);

	return lastDayStruct->tm_mday;
}
