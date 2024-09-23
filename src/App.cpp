#include "App.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <iostream>

App::Screen::Screen(int w, int h, int h_pad, int w_pad, int fps)
    : width(w), height(h), h_padding(h_pad), w_padding(w_pad), fps(fps)
{
}

App::App(const Screen& screen, const char* title, Color bgColor, Color border_color)
    : m_default_bg_color(bgColor),
      m_screen(screen),
      m_wav("audio7.wav"),
      m_default_border_color(border_color)

{
    InitWindow(m_screen.width, m_screen.height, title);
    SetTargetFPS(m_screen.fps);
    // topscreen
    SetWindowMonitor(1);
    game_loop();
}

// Implement the game_loop function
void App::game_loop()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        render();

        EndDrawing();
    }

    cleanup();
}


void App::render_borders()
{
    //files overview rect
    const Rectangle files_rect =
    {
        .x = m_screen.w_padding, .y = m_screen.h_padding, .width = m_screen.h_padding * 8,
        .height = m_screen.h_padding * 14
    };
    DrawRectangleLinesEx(files_rect, 3, m_default_border_color);
    DrawText("files", files_rect.width / 2 + files_rect.x, files_rect.height / 2 + files_rect.y,
             20, WHITE);

    // composite signal rect
    const Rectangle comp_sig_rect =
    {
        .x = files_rect.x + files_rect.width + m_screen.h_padding, .y = m_screen.h_padding,
        .width = (m_screen.width - m_screen.w_padding * 2.0f) - (files_rect.width + m_screen.w_padding),
        .height = files_rect.height
    };
    DrawRectangleLinesEx(comp_sig_rect, 3, m_default_border_color);
    DrawText("comp signal", comp_sig_rect.width / 2 + comp_sig_rect.x, comp_sig_rect.height / 2 + m_screen.h_padding,
             20, WHITE);

    // partial signals rectø
    const Rectangle part_sig_rect =
    {
        .x = m_screen.w_padding, .y = (m_screen.height / 2.0f) + m_screen.h_padding * 4.0f,
        .width = m_screen.width - m_screen.w_padding * 2.0f, .height = 350.0f
    };
    DrawRectangleLinesEx(part_sig_rect, 3, m_default_border_color);
    DrawText("part signal", part_sig_rect.width / 2 + part_sig_rect.x, part_sig_rect.height / 2 + part_sig_rect.y,
             20, WHITE);


    // options devider
    Vector2 devider_start_pos = {
        .x = part_sig_rect.x + m_screen.w_padding * 8, .y = (m_screen.height / 2.0f) + m_screen.h_padding * 4.0f
    };
    Vector2 devider_end_pos = {
        .x = part_sig_rect.x + m_screen.w_padding * 8, .y = part_sig_rect.y + part_sig_rect.height,
    };

    DrawLineEx(devider_start_pos, devider_end_pos, 3, m_default_border_color);
}

// here we render gui stuff that does not change i think
void App::render()
{
    ClearBackground(m_default_bg_color);
    render_borders();
}

void event_handler()
{
}


void App::cleanup()
{
    CloseWindow();
}
