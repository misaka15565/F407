// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 9.1.0
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen2, lv_color_hex(0xCBFCD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen2_Label_Label6 = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_Screen2_Label_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen2_Label_Label6, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Screen2_Label_Label6, "TIME:");
    lv_obj_set_style_text_color(ui_Screen2_Label_Label6, lv_color_hex(0xF30000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen2_Label_Label6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen2_Label_Label6, &ui_font_ysFont40, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen2_Button_Button1 = lv_button_create(ui_Screen2);
    lv_obj_set_width(ui_Screen2_Button_Button1, 100);
    lv_obj_set_height(ui_Screen2_Button_Button1, 50);
    lv_obj_set_x(ui_Screen2_Button_Button1, 345);
    lv_obj_set_y(ui_Screen2_Button_Button1, -209);
    lv_obj_set_align(ui_Screen2_Button_Button1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Screen2_Button_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_Screen2_Button_Button1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen2_Label_Label1 = lv_label_create(ui_Screen2_Button_Button1);
    lv_obj_set_width(ui_Screen2_Label_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen2_Label_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen2_Label_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen2_Label_Label1, "锁定");
    lv_obj_set_style_text_color(ui_Screen2_Label_Label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen2_Label_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen2_Label_Label1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen2_Label_Label1, &ui_font_ysFont40, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen2_Slider_Slider1 = lv_slider_create(ui_Screen2);
    lv_slider_set_value(ui_Screen2_Slider_Slider1, 0, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Screen2_Slider_Slider1) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(
            ui_Screen2_Slider_Slider1, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Screen2_Slider_Slider1, 700);
    lv_obj_set_height(ui_Screen2_Slider_Slider1, 50);
    lv_obj_set_x(ui_Screen2_Slider_Slider1, 0);
    lv_obj_set_y(ui_Screen2_Slider_Slider1, 111);
    lv_obj_set_align(ui_Screen2_Slider_Slider1, LV_ALIGN_CENTER);


    //Compensating for LVGL9.1 draw crash with bar/slider max value when top-padding is nonzero and right-padding is 0
    if(lv_obj_get_style_pad_top(ui_Screen2_Slider_Slider1,
                                LV_PART_MAIN) > 0) lv_obj_set_style_pad_right(ui_Screen2_Slider_Slider1,
                                                                                  lv_obj_get_style_pad_right(ui_Screen2_Slider_Slider1, LV_PART_MAIN) + 1, LV_PART_MAIN);
    ui_Screen2_Label_Label2 = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_Screen2_Label_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen2_Label_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen2_Label_Label2, 0);
    lv_obj_set_y(ui_Screen2_Label_Label2, 50);
    lv_label_set_text(ui_Screen2_Label_Label2, "GNSS:");
    lv_obj_set_style_text_color(ui_Screen2_Label_Label2, lv_color_hex(0x0800FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen2_Label_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen2_Label_Label2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen2_Label_Label2, &ui_font_ysFont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen2_Button_Button2 = lv_button_create(ui_Screen2);
    lv_obj_set_width(ui_Screen2_Button_Button2, 100);
    lv_obj_set_height(ui_Screen2_Button_Button2, 50);
    lv_obj_set_x(ui_Screen2_Button_Button2, 346);
    lv_obj_set_y(ui_Screen2_Button_Button2, -153);
    lv_obj_set_align(ui_Screen2_Button_Button2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Screen2_Button_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_Screen2_Button_Button2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen2_Label_Label4 = lv_label_create(ui_Screen2_Button_Button2);
    lv_obj_set_width(ui_Screen2_Label_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen2_Label_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen2_Label_Label4, 0);
    lv_obj_set_y(ui_Screen2_Label_Label4, 1);
    lv_obj_set_align(ui_Screen2_Label_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen2_Label_Label4, "文件");
    lv_obj_set_style_text_font(ui_Screen2_Label_Label4, &ui_font_ysFont40, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen2_Switch_Switch1 = lv_switch_create(ui_Screen2);
    lv_obj_set_width(ui_Screen2_Switch_Switch1, 93);
    lv_obj_set_height(ui_Screen2_Switch_Switch1, 52);
    lv_obj_set_x(ui_Screen2_Switch_Switch1, 345);
    lv_obj_set_y(ui_Screen2_Switch_Switch1, -95);
    lv_obj_set_align(ui_Screen2_Switch_Switch1, LV_ALIGN_CENTER);


    lv_obj_add_event_cb(ui_Screen2_Button_Button1, ui_event_Screen2_Button_Button1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen2_Slider_Slider1, ui_event_Screen2_Slider_Slider1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen2_Button_Button2, ui_event_Screen2_Button_Button2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen2_Switch_Switch1, ui_event_Screen2_Switch_Switch1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen2, ui_event_Screen2, LV_EVENT_ALL, NULL);

}
