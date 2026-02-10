//#include "LPC17xx.h"
//#include <stdint.h>
//#include "GLCD/GLCD.h" 
//#include "Main.h"

//static unsigned char snap[ROWS][COLS];
//static unsigned char prev_grid[ROWS][COLS];

//static volatile uint8_t lcd_dirty = 1;

//static int prev_paused = -1;
//static int prev_slowdown = -1;
//static uint32_t prev_score = 0xFFFFFFFF;
//static uint32_t prev_high  = 0xFFFFFFFF;
//static uint32_t prev_lines = 0xFFFFFFFF;

///* ---- Layout ---- */
//#define CELL      10      
//#define FIELD_X   20
//#define FIELD_Y   20
//#define FIELD_W   (COLS * CELL)
//#define FIELD_H   (ROWS * CELL)

///* HUD position */
//#define HUD_X    140
//#define HUD_Y     20
//#define HUD_DY    15

//extern volatile int slowdown_active;
//extern void LCD_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

//static void Draw_Cell(int r, int c, unsigned char v) {
//    uint16_t x = (uint16_t)(FIELD_X + c * CELL);
//    uint16_t y = (uint16_t)(FIELD_Y + r * CELL);
//    
//    uint16_t color;
//    switch(v) {
//        case BLOCK:
//            color = White;
//            break;
//        case PWR_CLR:
//            color = Green;  // Clear half - GREEN
//            break;
//        case PWR_SLOW:
//            color = Blue;   // Slow down  - BLUE
//            break;
//        default:
//            color = Black;  
//            break;
//    }
//    
//    LCD_FillRect(x, y, CELL, CELL, color);
//}

//static void Draw_Field_Border(void) {
//    uint16_t x0 = FIELD_X - 1;
//    uint16_t y0 = FIELD_Y - 1;
//    uint16_t x1 = FIELD_X + FIELD_W;
//    uint16_t y1 = FIELD_Y + FIELD_H;

//    LCD_DrawLine(x0, y0, x1, y0, Yellow);
//    LCD_DrawLine(x0, y1, x1, y1, Yellow);
//    LCD_DrawLine(x0, y0, x0, y1, Yellow);
//    LCD_DrawLine(x1, y0, x1, y1, Yellow);
//}

//static void u32_to_str(uint32_t v, uint8_t *out) {
//    uint8_t tmp[11];
//    int i = 0, j = 0;

//    if (v == 0) { out[0] = '0'; out[1] = 0; return; }

//    while (v > 0 && i < 10) {
//        tmp[i++] = (uint8_t)('0' + (v % 10));
//        v /= 10;
//    }
//    while (i > 0) out[j++] = tmp[--i];
//    out[j] = 0;
//}
//void Update_Values(void){
//    uint8_t buf[12];

//    if (prev_score != (uint32_t)score) { 
//        prev_score = (uint32_t)score;
//        u32_to_str(prev_score, buf);
//        GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 0*HUD_DY, (uint8_t*)"        ", White, Black);
//        GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 0*HUD_DY, buf, White, Black);
//    }

//    if (prev_high != (uint32_t)high_score) {
//        prev_high = (uint32_t)high_score;
//        u32_to_str(prev_high, buf);
//        GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 1*HUD_DY, (uint8_t*)"        ", White, Black);
//        GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 1*HUD_DY, buf, White, Black);
//    }

//    if (prev_lines != (uint32_t)lines_cleared) {
//        prev_lines = (uint32_t)lines_cleared;
//        u32_to_str(prev_lines, buf);
//        GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 2*HUD_DY, (uint8_t*)"        ", White, Black);
//        GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 2*HUD_DY, buf, White, Black);
//    }

//    if (prev_paused != (int)game_paused) {
//        prev_paused = (int)game_paused;
//        GUI_Text(HUD_X, HUD_Y + 3*HUD_DY, (uint8_t*)"        ", White, Black);
//        GUI_Text(HUD_X, HUD_Y + 3*HUD_DY, (uint8_t*)(game_paused ? "PAUSED " : "PLAYING"), White, Black);
//    }

//    if (prev_slowdown != (int)slowdown_active) {
//        prev_slowdown = (int)slowdown_active;
//        GUI_Text(HUD_X, HUD_Y + 4*HUD_DY, (uint8_t*)"        ", White, Black);
//        if (slowdown_active) {
//            GUI_Text(HUD_X, HUD_Y + 4*HUD_DY, (uint8_t*)"SLOW!  ", Cyan, Black);
//        }
//    }
//}


//void TetrisView_Init(void) {
//    LCD_Clear(Black);
//    Draw_Field_Border();

//    for (int r = 0; r < ROWS; r++)
//        for (int c = 0; c < COLS; c++)
//            prev_grid[r][c] = 0;   

//    lcd_dirty = 1;
//	
//    prev_paused = -1;
//    prev_slowdown = -1;
//	  prev_score = prev_high = prev_lines = 0xFFFFFFFF;

//    GUI_Text(HUD_X, HUD_Y + 0*HUD_DY, (uint8_t*)"SCORE:", White, Black);
//    GUI_Text(HUD_X, HUD_Y + 1*HUD_DY, (uint8_t*)"HIGH :", White, Black);
//    GUI_Text(HUD_X, HUD_Y + 2*HUD_DY, (uint8_t*)"LINES:", White, Black);
//}

//void TetrisView_Redraw(void) {
//    lcd_dirty = 1;
//}

//void Clear(void){	
//    for (int r = 0; r < ROWS; r++)
//        for (int c = 0; c < COLS; c++)
//            snap[r][c] = 0;
//}

//void TetrisView_Render(void) {
//    if (!lcd_dirty) return;
//    lcd_dirty = 0;

//    __disable_irq();
//     for (int r = 0; r < ROWS; r++)
//        for (int c = 0; c < COLS; c++)
//            snap[r][c] = display_grid[r][c];
//    __enable_irq();

//    for (int r = 0; r < ROWS; r++) {
//        for (int c = 0; c < COLS; c++) {
//            unsigned char cur = snap[r][c];          
//            if (cur != prev_grid[r][c]) {
//                Draw_Cell(r, c, cur);
//                prev_grid[r][c] = cur;
//            }
//        }
//    }

//    Update_Values();
//}

