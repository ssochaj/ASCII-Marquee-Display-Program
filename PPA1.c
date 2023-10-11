#include <stdio.h>
#include "MacUILib.h"


// PREPROCESSOR DIRECTIVE CONSTANTS
// ================================
// For program-wide constants, define them here using #define.  Add as seen needed.
# define SIZE 21


// GLOBAL VARIABLES
// ================================
int exitFlag;   // Program Exiting Flag, used to determine whether to leave the program loop and shutdown the program

// Add more variables here as needed
char cmd;
char displayString[SIZE] = ">><<                 ";
int startPos;
int userInput;
int i;
int currentIndex;
int insert;
char c = '<';





// FUNCTION PROTOTYPES
// ================================
// Declare function prototypes here, so that we can organize the function implementation after the main function for code readability.

// These are the six required program loop function to build our "McMaster Terminal Program Engine"
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Add more function prototypes here as needed





// MAIN PROGRAM
// ===============================
// This is the "Program Loop" as described in the PPA1 flow chart.  Read Lab Documents to visualize how a persisting program works under the hood.
// Typically, when you use some sort of "Software Design Engine", this part is scaffolded - you will only be responsible of scripting the functions.
//
// In future PPA's and Projects, you are expected to be able to set up a program loop like this from scratch whenever a persisting program is required.
int main(void)
{

    // Start-Up
    Initialize();

    // Program Loop
    while(!exitFlag)  
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();
    }

    // Tear-Down
    CleanUp();

    return 0;

}





// INITIALIZATION ROUTINE
// ===============================
// This routine is run only once before the start of the program loop - aka Start-Up Routine.
// You would typically do the following in this function:
//  1. Initialize global variables
//  2. Allocated memories for dynamic variables (we will talk about this after midterm)
//  3. Call the relevant initialization functions to enable certain library supports.

void Initialize(void)
{
    // [TODO]: Call the MacUI Library Initialization Function 
    MacUILib_init();

    // [TODO]: Initialize variables
    exitFlag = 0;  // 0 - do not exit, non-zero - exit the program

    // [TODO]: Add more variables initializations here as seen needed.
    // You can add more start-up operations here

    startPos = 0;
    insert = 2;
    i = 0;

}


void GetInput(void)
{
    
    userInput = MacUILib_hasChar();
    
    // if the input is valid (ANSCII character)
    if (userInput != 0)
    {
        // the input is saved
        cmd = MacUILib_getChar();
    }

    // if ESC is pressed, the program is terminated
    if (cmd == 27)
    {
        // exit is true
        exitFlag = 1;
    }

}




// MAIN LOGIC ROUTINE - "Think"
// ===============================
// The second action in our program loop is to execute the main program logic.  
// In this routine, we should determine the outcome of the logic using a) current status / state / behaviour of the program, and b) the most recent input
// The outcome of the logic then will be drawn on the screen.
//
// In later activities, we will delve deeper into this design philosophy later in the course - Finite State Machine design principle.
// 
// Let's now think about how we can complete the marquee display logic...

void RunLogic(void)
{
    
    //  The name of the game is to play with the array index - track the position where you start printing, always print N characters, and make sure any index access beyond N-1
    //  ** WRAPS AROUND ** back to index 0.
    //
    //  You should recall from our lecture how to deploy index wraparound calculation.
    //
    //  You should also think about how to rotate the string RIGHTWARD.  It has something to do with how you update the printing start position.

    

    // Pseudocode for Marquee Display with Dynamically Changing String:
    // 1. Check if there was a valid input command collected
    //      1.1 if YES, perform the following
    //           x 1.1.a  If input command is 'ESC' (or your choice of ASCII character)
    //                  x Set exitFlag to true.  
    // Then, in the next program loop iteration, the loop will break, leading to CleanUp() routine and program shutdown.
    //           1.1.b  (Above and Beyond Feature) If input command is 'SHIFT' (or your choice of ASCII character)
    //                  Toggle the marquee rotation direction.  Think about how!
    //           1.1.c  Otherwise, the input command is just a plain character that needs to be added to the marquee display string.
    //                  Update the string contents.
    // 2. Then, update the printing start position (rightward or leftward), so that the Draw routine will be able to print the string from the correct character
    // DONE

    // [TODO]: Implement the above pseudocode logic

    // DO NOT print anything out.  This routine is the "thinking" part, not the "acting" part.
    // You should only update all the key program parameters here.

    // increment start position after every iteration
    startPos++;

    // if the user's input is between the <<>>
    if (insert <= (SIZE - 4))
    {
        // if the input is valid
        if (cmd != 0)
        {
            // makes the input wrap around 
            if (startPos >= (SIZE - 1))
            {
                startPos = 0;
            }

            // user's command is added to the array
            displayString[insert] = cmd;

            displayString[insert + 2] = c;

            // set the command to 0 (ready to add another input for next iteration)
            cmd = 0;
            // increment the 
            insert++;
        }
    }

}







// DRAW ROUTINE - "Act"
// ===============================
// This routine creates the output of the program for a given iteration, using the resultant parameters from the RunLogic() routine.
// In the completed program, this should be the only routine calling the MACUILib_printf().
// If we apply the animation technique discussed in the lab document, we can then create a smooth marquee display animation on the terminal.
//
// Animation Basics (Review):
//  In every iteration
//      - Clear the screen (remove the printed contents from the previous iteration, a.k.a. previous frame)
//      - Use the calculated parameters from RunLogic(), draw line-by-line on the terminal screen to build the desired display contents for this iteration
//        (a.k.a. draw the current frame)
//
//  If we repeat the actions above at a suitable rate, the contents on the screen will look like it's moving smoothly on the screen,
//  as if we are flipping through pages of pictures.
//  - If too slow, the animation will look choppy (frame rate too low)
//  - If too fast, you won't see the animation at all (frame rate too high)

void DrawScreen(void)
{
    // Pesudocode
    // x 1. Clear the screen
    // 2. Draw the new frame by printing new contents on the screen
    //      - For static contents, just print them as is
    //      - For dynamic contents (namely, the marquee display portion), make sure you print the shifted string using the most updated printing start position
    //        and HEED THE WRAPAROUND.
    
    // [TODO]: Complete the implementation of the above pseudocode

    // for loop index

    // clear screen
    MacUILib_clearScreen();

    // print lines
    MacUILib_printf("McMaster Marquee Display\n");
    MacUILib_printf("====================\n");
    
    
    for (i = 0; i < (SIZE-1); i++)
    {
        MacUILib_printf("%c", displayString[(i + startPos) % (SIZE - 1)]); 
    }
    
    MacUILib_printf("\n");
    
    MacUILib_printf("====================\n");
   
}





// DELAY ROUTINE - "Wait"
// ===============================
// Sometimes referred to as the "stupidifier", this routine is only intended to slow down the program loop so that
// 1. The animation is not too fast to be appreciated
// 2. The main logic is not executed too often, such that the game won't act too ahead of the player's reaction.  Otherwise, the game will be impossible to be beaten.

void LoopDelay(void)
{
    // [TODO]: For now, just call the MacUILib_Delay routine here, and introduce sufficient delay constant so that the marquee display runs at a comfortable speed.
    MacUILib_Delay(100000);

}



// TEAR-DOWN ROUTINE
// ===============================
// This routine is run only once at the end of the program right before shutdown, intended to clean up all the resources used by the program.
// This routine is VERY IMPORTANT to prevent memory leak.  We will cover this after the midterm.

void CleanUp(void)
{
    // For now, you only need to call MacUILib_uninit() routine to shut down the MacUILib module.
    MacUILib_uninit();

    // In future activities, you will have to add the memory deallocation routines here to ensure no memory leakage.
}