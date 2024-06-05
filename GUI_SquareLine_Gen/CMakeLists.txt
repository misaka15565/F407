SET(SOURCES screens/ui_Screen1.c
    screens/ui_Screen2.c
    screens/ui_ExplorerScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    fonts/ui_font_ysFont.c
    fonts/ui_font_ysFont40.c)

add_library(ui ${SOURCES})
