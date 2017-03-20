/*
This is the header file for the iola_sound project
for the course Application Development at VAMK
The header file is consisted of 3 parts:
- Data structure definition
- Defined constants
- Function prototypes
*/


// Data structure definition

enum COLORS {BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

// Constants definition

#define UNICODE 1
#define UBAR "\u2590"

// Function prototypes

void setFGcolor(int );
void resetcolor(void);
void gotoXY(int, int);
void displayBar(int, double, int, int);
void clrscr(void);
