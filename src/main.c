#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/misc.h>
//#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "vector.h"
#include "primitives.h"
#include "scene.h"
#include "raytracer.h"

#define LCD_WIDTH 384
#define LCD_HEIGHT 216
int SCALE = 4;

#define FOV 1.5

int PRGM_GetKey(void){
	unsigned char buffer[12];
	PRGM_GetKey_OS( buffer );
	return ( buffer[1] & 0x0F ) * 10 + ( ( buffer[2] & 0xF0 ) >> 4 );
}

int main(void) {
	Bdisp_AllClr_VRAM();
	Bdisp_EnableColor(1);
	EnableStatusArea(0);
	DrawFrame(COLOR_BLACK);
	Bdisp_PutDisp_DD();

	if ((pow((double)2, 4) == 16) && (pow((double)0.5, 3) == 0.125) && (pow((double)17, 0) == 1)) PrintXY(1, 1, "  pow pass", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	else PrintXY(1, 1, "  pow fail", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	int exp;
	if ((frexp(3, &exp) == 0.75) && (exp == 2)) PrintXY(1, 2, "  frexp pass", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	else PrintXY(1, 2, "  frexp fail", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	if (ldexp(0.95, 4) == 15.2) PrintXY(1, 3, "  ldexp pass", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	else PrintXY(1, 3, "  ldexp fail", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	if ((sqrtf(9) == 3) & (sqrtf(0.25) == 0.5)) PrintXY(1, 4, "  sqrtf pass", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	else PrintXY(1, 4, "  sqrtf fail", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	if ((max(6, -3) == 6) & (max(-0.3, 0.6) == 0.6)) PrintXY(1, 5, "  max pass", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	else PrintXY(1, 5, "  max fail", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	if ((min(6, -3) == -3) & (min(-0.3, 0.6) == -0.3)) PrintXY(1, 6, "  min pass", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	else PrintXY(1, 6, "  min fail", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
	
	Bdisp_PutDisp_DD();

	while (1) {
		int x, y;

		for (y = 0; y < (LCD_HEIGHT/SCALE); y++) {
			int key = PRGM_GetKey();
			switch(key){
				case KEY_PRGM_EXIT:
					return 0;
				case KEY_PRGM_MENU:
					return 0;
			}

			for (x = 0; x < (LCD_WIDTH/SCALE); x++) {
				Vector origin = {.x = 0, .y = 0, .z = 0};
				//Vector origin = {.x = x - (LCD_WIDTH/2), .y = y - (LCD_HEIGHT/2), .z = 0};
				Vector direction = {.x = FOV*((float)LCD_WIDTH/(float)LCD_HEIGHT)*(((float)(x*SCALE)/(float)LCD_WIDTH)-0.5), .y = FOV*(((float)-(y*SCALE)/(float)LCD_HEIGHT)+0.5), .z = 1.0};
				//Vector direction = {.x = 0, .y = 0, .z = 1.0};
				Ray ray = {.origin = origin, .direction = direction};

				color_t color = traceRay(ray);

				int x1, y1;
				for (y1 = 0; y1 < SCALE; y1++) {
					for (x1 = 0; x1 < SCALE; x1++) {
						Bdisp_SetPoint_VRAM((x*SCALE)+x1, (y*SCALE)+y1, color);
					}
				}
			}

			Bdisp_PutDisp_DD();
		}

		if (SCALE > 1) SCALE--;
	}
 
	return 0;
}