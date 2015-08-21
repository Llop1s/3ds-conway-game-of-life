/*
	Hello World example made by Aurelio Mannara for ctrulib
	This code was modified for the last time on: 12/12/2014 21:00 UTC+1

	This wouldn't be possible without the amazing work done by:
	-Smealum
	-fincs
	-WinterMute
	-yellows8
	-plutoo
	-mtheall
	-Many others who worked on 3DS and I'm surely forgetting about
*/

#include <3ds.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
    srand(time(NULL));
    
	gfxInitDefault();
        
        //We need one PrintConsole for each screen
	PrintConsole topScreen, bottomScreen;

	//Initialize console for both screen using the two different PrintConsole we have defined
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
        
        //Initialize World Matrix
        int world[30][50];  

        
        void drawWorld(){
               consoleSelect(&topScreen);
              int i,j;
              for (i = 0; i<30; i++){
            
                  for (j= 0; j < 50; j++){
                      if (world[i][j] == 1)
                       printf("\x1b[%d;%dH\x1b[%dm%c", i, j, 0, 254);
                      else
                       printf("\x1b[%d;%dH\x1b[%dm ", i, j, 0); 
                    }
            
              }
            
        }
        
        void naturalSelection(){
              int i,j;
              for (i = 0; i<30; i++){
            
                  for (j= 0; j < 50; j++){
                       int sides = 0;
                          if (world[i-1][j] == 1 && i >= 0){sides++;}
                          if (world[i-1][j-1] == 1 && i >= 0  && j > 0){sides++;}
                          if (world[i-1][j+1] == 1 && i >= 0  && j+1 < 50){sides++;}
                          if (world[i][j-1] == 1  && j >= 0){sides++;}
                          if (world[i][j+1] == 1 && j+1 < 50){sides++;}
                          if (world[i+1][j] == 1 && i+1 < 30){sides++;}
                          if (world[i+1][j-1] == 1 && i+1 < 30  && j >= 0){sides++;}
                          if (world[i+1][j+1] == 1 && i+1 < 30 && j+1 < 50){sides++;} 

                      if (world[i][j] == 1){
                          if (sides > 3 || sides < 2){
                              world[i][j] = 0;
                              
                          }
                      }
                       if (world[i][j] == 0){               
                          if (sides == 3){
                              world[i][j] = 1;
                          }
                          
                          
                      }
                    }
            
              }
            
            
        }
        
        int i,j, humans = 50;
        while (humans > 0){
              for (i = 0; i<30; i++){
            
                  for (j= 0; j < 50; j++){
                      if (rand()%30 % 2 == 0  && humans > 0){
                          world[i][j] = 1;
                          humans--;
                      }
                      else
                          world[i][j] = 0;
                          
                    }
              }
        }
        
        consoleSelect(&bottomScreen);
        printf("\x1b[12;9HConway's Game of Life");
	printf("\x1b[14;10HPress Start to Exit");
        printf("\x1b[29;10HDeveloped by \x1b[31mLlopis");
	// Main loop
	while (aptMainLoop())
	{
            drawWorld();
        
            naturalSelection();
                consoleSelect(&topScreen);
                
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
