#include "App.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <iostream>

App::Screen::Screen(int w, int h, int fps)
    : width(w), height(h), h_padding(h * 0.02f), w_padding(w * 0.02f), fps(fps)
{
    std::cout << h_padding << "\n" << w_padding;
}

App::App(const Screen& screen, const char* title, Color bgColor, Color border_color)
    : m_default_bg_color(bgColor),
      m_screen(screen),
      m_wav("audio7.wav"),
      m_default_border_color(border_color),
      m_fs_rect( {
        .x = m_screen.w_padding, .y = m_screen.h_padding, .width = m_screen.width / 6,
        .height = m_screen.height / 2 + (2 * screen.w_padding)
      }),
      m_comp_sig_rect(
    {
        .x = m_fs_rect.x + m_fs_rect.width + m_screen.w_padding, .y = m_screen.h_padding,
        .width = (m_screen.width - m_screen.w_padding * 2) - (m_fs_rect.width + m_screen.w_padding),
        .height = m_fs_rect.height
      }),
      m_part_sig_rect({
        .x = m_screen.w_padding, .y = m_fs_rect.height + m_screen.h_padding * 2,
        .width = m_screen.width - m_screen.w_padding * 2.0f, .height = m_screen.height - (3 * m_screen.h_padding + m_fs_rect.height)
      })

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

    //TODO: REFACTOR X AND Y VALUES INTO MEMBER VARIABLES (a lot faster maybe ???)
    //files overview rect
    DrawRectangleLinesEx(m_fs_rect, 3, m_default_border_color);
    DrawText("files", m_fs_rect.width / 2 + m_fs_rect.x, m_fs_rect.height / 2 + m_fs_rect.y,
             20, WHITE);

    // composite signal rect

    DrawRectangleLinesEx(m_comp_sig_rect, 3, m_default_border_color);
    DrawText("comp signal", m_comp_sig_rect.width / 2 + m_comp_sig_rect.x, m_comp_sig_rect.height / 2 + m_screen.h_padding,
             20, WHITE);

    // partial signals rectø
    DrawRectangleLinesEx(m_part_sig_rect, 3, m_default_border_color);
    DrawText("part signal", m_part_sig_rect.width / 2 + m_part_sig_rect.x, m_part_sig_rect.height / 2 + m_part_sig_rect.y,
             20, WHITE);


    // options devider
    Vector2 devider_start_pos = {
        .x = m_part_sig_rect.x + m_fs_rect.width, .y = m_part_sig_rect.y
    };
    Vector2 devider_end_pos = {
        .x = m_part_sig_rect.x + m_fs_rect.width, .y = m_part_sig_rect.y + m_part_sig_rect.height,
    };

    DrawLineEx(devider_start_pos, devider_end_pos, 3, m_default_border_color);
}

void App::render_axis()
{
    // comp signal axis


    // part signal axis

}

// here we render gui stuff that does not change i think
void App::render()
{
    ClearBackground(m_default_bg_color);
    render_axis();
    render_borders();
}

void event_handler()
{
}


void App::cleanup()
{
    CloseWindow();
}
