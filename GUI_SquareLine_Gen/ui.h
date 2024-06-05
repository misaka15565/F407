// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 9.1.0
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t * ui_Screen1;
void ui_event_Screen1_Textarea_TextArea1(lv_event_t * e);
extern lv_obj_t * ui_Screen1_Textarea_TextArea1;
extern lv_obj_t * ui_Screen1_Keyboard_Keyboard1;
extern lv_obj_t * ui_Screen1_Label_Label3;
void ui_event_Screen1_Button_Button4(lv_event_t * e);
extern lv_obj_t * ui_Screen1_Button_Button4;
extern lv_obj_t * ui_Screen1_Label_Label5;
// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
void ui_event_Screen2(lv_event_t * e);
extern lv_obj_t * ui_Screen2;
extern lv_obj_t * ui_Screen2_Label_Label6;
void ui_event_Screen2_Button_Button1(lv_event_t * e);
extern lv_obj_t * ui_Screen2_Button_Button1;
extern lv_obj_t * ui_Screen2_Label_Label1;
void ui_event_Screen2_Slider_Slider1(lv_event_t * e);
extern lv_obj_t * ui_Screen2_Slider_Slider1;
extern lv_obj_t * ui_Screen2_Label_Label2;
// SCREEN: ui_ExplorerScreen
void ui_ExplorerScreen_screen_init(void);
void ui_event_ExplorerScreen(lv_event_t * e);
extern lv_obj_t * ui_ExplorerScreen;
extern lv_obj_t * ui_Startevents____initial_actions0;





LV_FONT_DECLARE(ui_font_ysFont);
LV_FONT_DECLARE(ui_font_ysFont40);



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
