#include "UI.h"
#include <iostream>
#define RAYGUI_IMPLEMENTATION
#include <algorithm>
#include <raygui.h>
#include <ranges>
#include <string>

UI::Screen::Screen(int w, int h, int fps)
    : width(w), height(h), fps(fps), w_padding(w * 0.01f), h_padding(h * 0.01f)
{
}

UI::UI(const Screen& screen, Color bgColor, Color border_color, Color UI_rect_bg)
    : screen(screen), bg_color(bgColor), border_color(border_color),
      fm(), UI_rect_bg(UI_rect_bg)

{
    define_ui_rectangles();
}


void UI::define_ui_rectangles()
{
    fs_rect = {
        .x = screen.h_padding,
        .y = screen.h_padding,
        .width = screen.width / 7,
        .height = screen.height / 2 + 2 * screen.h_padding
    };
    comp_sig_rect =
    {
        .x = fs_rect.x + fs_rect.width + screen.h_padding,
        .y = screen.h_padding,
        .width = screen.width - screen.h_padding * 3 - fs_rect.width,
        .height = screen.height / 2 + 2 * screen.h_padding
    };

    part_sig_rect = {
        .x = comp_sig_rect.x,
        .y = screen.height / 2 + 2 * screen.h_padding + screen.h_padding * 2,
        .width = comp_sig_rect.width,
        .height = screen.height - (3 * screen.h_padding + screen.height / 2 + 2 * screen.h_padding)
    };

    part_sig_options_rec = {
        .x = fs_rect.x,
        .y = 2 * screen.h_padding + fs_rect.height,
        .width = fs_rect.width,
        .height = part_sig_rect.height
    };


    float padding = comp_sig_rect.width * 0.02f;

    comp_plotting_rect = {
        comp_sig_rect.x + padding,
        comp_sig_rect.y + padding,
        comp_sig_rect.width - 2 * padding,
        comp_sig_rect.height - 2 * padding
    };

    graph_display_window = comp_plotting_rect;
}

void UI::load_font(const std::string& file_name)
{
    const std::string font_path = "../Fonts/" + file_name;
    font = LoadFont(font_path.c_str());
}

//TODO: do styles for individual gui elements so it doesnt look fucked ty <3
void UI::gui_style_setup()
{
    // sliders
    //TODO: look more into slider knob color
    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, 0x252525FF);
    GuiSetStyle(SLIDER, BASE_COLOR_FOCUSED, 0x252525FF);

    GuiSetStyle(SLIDER, TEXT_COLOR_NORMAL, 0x909090FF);
    GuiSetStyle(SLIDER, TEXT_COLOR_FOCUSED, 0x909090FF);
    GuiSetStyle(SLIDER, TEXT_COLOR_PRESSED, 0x909090FF);

    GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, 0x606060FF);
    GuiSetStyle(SLIDER, BORDER_COLOR_FOCUSED, 0x909090FF);
    GuiSetStyle(SLIDER, BORDER_COLOR_PRESSED, 0x909090FF);

    // buttons
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x252525FF);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x252525FF);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0x606060FF);

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0x909090FF);
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, 0x909090FF);
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, 0x909090FF);

    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x606060FF);
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, 0x909090FF);
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, 0x909090FF);


    // panels (containers ???)
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0x252525FF);
    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, 0x252525FF);
    GuiSetStyle(DEFAULT, LINE_COLOR, 0x252525FF);
}


void UI::render_ui_areas() const
{
    gui_style_setup();

    // files overview rect
    GuiDrawRectangle(fs_rect, 3, border_color, UI_rect_bg);

    // composite signal rect
    GuiDrawRectangle(comp_sig_rect, 3, border_color, UI_rect_bg);

    // partial signals rect
    GuiDrawRectangle(part_sig_rect, 3, border_color, UI_rect_bg);
}

void UI::render_axis() const
{
    // x-axis
    DrawLine(comp_plotting_rect.x, comp_plotting_rect.y + comp_plotting_rect.height,
             comp_plotting_rect.x + comp_plotting_rect.width, comp_plotting_rect.y + comp_plotting_rect.height, WHITE);

    // y-axis
    DrawLine(comp_plotting_rect.x, comp_plotting_rect.y,
             comp_plotting_rect.x, comp_plotting_rect.y + comp_plotting_rect.height, WHITE);

    constexpr int dotted_line_len = 8;
    constexpr int dotted_line_gap = 8;
    constexpr int rect_border_width = 5;

    constexpr int total_step_size = dotted_line_len + dotted_line_gap;
    const int num_lines = comp_plotting_rect.width / total_step_size;

    //TODO: refine at some point so that line len is a fraction of the drawable width

    // dotted center line
    for (int i = 0; i < num_lines; ++i)
    {
        int step_size = i * total_step_size;
        DrawLine((comp_plotting_rect.x + rect_border_width) + step_size,
                 comp_plotting_rect.y + comp_plotting_rect.height / 2,
                 (comp_plotting_rect.x + rect_border_width) + step_size + dotted_line_len,
                 comp_plotting_rect.y + comp_plotting_rect.height / 2,
                 WHITE);
    }
}

void UI::update_screen_size()
{
    if (IsWindowResized())
    {
        // NEW SCREEN
        screen.height = GetScreenHeight();
        screen.width = GetScreenWidth();
        screen.h_padding = GetScreenHeight() * 0.01f;
        screen.w_padding = GetScreenWidth() * 0.01f;

        define_ui_rectangles();
    }
}

void UI::render()
{
    ClearBackground(bg_color);
    update_screen_size();
    render_ui_areas();
    render_axis();
}

void UI::part_sig_options() const
{
    // OPTIONS WINDOW
    static float freq_slider_val = 50.0f;
    static float amp_slider_val = 50.0f;
    const float option_element_spacing = part_sig_options_rec.height / 15;

    // freq slider
    GuiPanel(part_sig_options_rec, "Options");
    GuiSlider({
                  .x = part_sig_options_rec.x + part_sig_options_rec.width / 5,
                  .y = part_sig_options_rec.y + option_element_spacing,
                  .width = part_sig_options_rec.width - part_sig_options_rec.width / 3,
                  .height = part_sig_options_rec.height / 30
              },
              "Frequency", TextFormat("%i", static_cast<int>(freq_slider_val)), &freq_slider_val, 0, 500);

    // amp slider
    GuiSlider({
                  .x = part_sig_options_rec.x + part_sig_options_rec.width / 5,
                  .y = part_sig_options_rec.y + option_element_spacing * 2,
                  .width = part_sig_options_rec.width - part_sig_options_rec.width / 3,
                  .height = part_sig_options_rec.height / 30
              },
              "Amplitude", TextFormat("%i", static_cast<int>(amp_slider_val)), &amp_slider_val, 0, 255);

    DrawCircle(part_sig_rect.x + part_sig_rect.width / 2, part_sig_rect.y + part_sig_rect.height / 2, freq_slider_val,
               {static_cast<unsigned char>(amp_slider_val), 100, 100, 255});

    GuiButton({
                  .x = part_sig_options_rec.x + part_sig_options_rec.width / 5,
                  .y = part_sig_options_rec.y + option_element_spacing * 3,
                  .width = (part_sig_options_rec.width - part_sig_options_rec.width / 3) / 2 - option_element_spacing /
                  3,
                  .height = part_sig_options_rec.height / 20
              }, "#125# +");

    GuiButton({
                  .x = part_sig_options_rec.x + part_sig_options_rec.width / 5 + (part_sig_options_rec.width -
                      part_sig_options_rec.width / 3) / 2 + option_element_spacing / 3,
                  .y = part_sig_options_rec.y + option_element_spacing * 3,
                  .width = (part_sig_options_rec.width - part_sig_options_rec.width / 3) / 2 - option_element_spacing /
                  3,
                  .height = part_sig_options_rec.height / 20
              }, "#125# -");
}

void UI::filename_buttons(Wav& wav) const
{
    const int filename_spacing = static_cast<int>(fs_rect.height) / static_cast<int>(fm.get_files().size());
    static bool show_err = false;

    for (int i = 0; i < fm.get_files().size(); ++i)
    {
        const int spacing = i * filename_spacing;
        const char* filename = fm.get_files()[i].path().filename().generic_string().c_str();
        const float x_pos = fs_rect.x + screen.h_padding;
        const float y_pos = fs_rect.y + screen.h_padding + static_cast<float>(spacing);

        if (GuiLabelButton(Rectangle{.x = x_pos, .y = y_pos, .width = 50, .height = 20}, filename))
        {
            Wav::Signal sig = wav.extract_signal(filename);
            if (!sig.samples.empty() && sig.samplerate != 0)
            {
                wav.set_signal(sig);
                return;
            }
            show_err = true;
        }

        if (show_err)
        {
            const Rectangle msg_box_rect = {
                screen.width / 2 - screen.width / 16, screen.height / 2 - screen.height / 16, screen.width / 8,
                screen.height / 8
            };

            if (GuiMessageBox(msg_box_rect, "Warning!", "not a wav file", "okay") == 1)
            {
                show_err = false;
            }
        }
    }
}


void UI::reload_file_names()
{
    if (GuiButton(Rectangle{
                      .x = fs_rect.x + fs_rect.width - screen.w_padding * 2, .y = fs_rect.y + screen.w_padding,
                      .width = 20, .height = 20
                  },
                  "R"))
    {
        fm.load_audio_files();
    }
}

void UI::file_drop()
{
    Vector2 mouse_pos = GetMousePosition();

    if (IsFileDropped() && CheckCollisionPointRec(mouse_pos, fs_rect))
    {
        FilePathList files = LoadDroppedFiles();

        const auto file_path = std::string(*files.paths);

        int file_name_start_idx = 0;

        for (int i = file_path.size() - 1; i >= 0; --i)
        {
            if (file_path[i] == '\\')
            {
                file_name_start_idx = i;
                break;
            }
        }
        if (file_name_start_idx > 0)
        {
            std::string file_name = file_path.substr(file_name_start_idx);
            fm.copy_file_to_folder(file_path, file_name);
        }


        UnloadDroppedFiles(files);
        fm.load_audio_files();
    }
}


void UI::event_handler(Wav& wav)
{
    reload_file_names();
    filename_buttons(wav);
    part_sig_options();
    graph_zoom();
    file_drop();
}


void UI::plot_signal(const Wav::Signal& sig) const
{
    // Resize samples to the correct size and populate it
    std::vector<double> samples(sig.samples.size());
    for (size_t i = 0; i < sig.samples.size(); ++i)
    {
        samples[i] = sig.samples[i].real();
    }

    // labda comparing absolute values
    const double largest_val = *std::ranges::max_element(samples.begin(), samples.end(),
                                                         [](const double a, const double b)
                                                         {
                                                             return std::abs(a) < std::abs(b);
                                                         });
    // scaling the values so that the largest value in the signal will fir onside our plotting window
    const double y_scale = comp_plotting_rect.height / 2.0 / largest_val;

    const int step_size = samples.size() / comp_plotting_rect.width;


    for (int i = 0; i < comp_plotting_rect.width; i++)
    {
        float y_pos = comp_plotting_rect.y + comp_plotting_rect.height / 2 - samples[i * step_size] * y_scale;
        DrawCircle(comp_plotting_rect.x + i, y_pos, 1, RED);
    }
}

void UI::graph_zoom() const
{
    Vector2 mouse_pos = GetMousePosition();
    static Vector2 mouse_pos_start = {0, 0};
    static bool is_dragging;

    if (CheckCollisionPointRec(mouse_pos, comp_plotting_rect))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            mouse_pos_start = mouse_pos;
            is_dragging = true;
        }
    }
    if (is_dragging)
    {
        float rect_x = std::min(mouse_pos_start.x, mouse_pos.x);
        float rect_y = std::min(mouse_pos_start.y, mouse_pos.y);
        float rect_width = std::abs(mouse_pos.x - mouse_pos_start.x);
        float rect_height = std::abs(mouse_pos.y - mouse_pos_start.y);

        rect_x = std::max(rect_x, comp_plotting_rect.x);
        rect_y = std::max(rect_y, comp_plotting_rect.y);
        rect_width = std::min(rect_width, comp_plotting_rect.x + comp_plotting_rect.width - rect_x);
        rect_height = std::min(rect_height, comp_plotting_rect.y + comp_plotting_rect.height - rect_y);

        DrawRectangleLines(rect_x, rect_y, rect_width, rect_height, RED);
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        is_dragging = false;

        std::cout << "mouse start position [" << mouse_pos_start.x << ", " << mouse_pos_start.y << "]" << "\n"
            << "mouse end position [" << mouse_pos.x << ", " << mouse_pos.y << "]" << std::endl;
    }
}


