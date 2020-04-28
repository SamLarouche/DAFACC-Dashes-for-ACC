#include <iostream>
#include <stdio.h>
#include <string>

#include <GL/gl3w.h>
#include <SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "accDataManager.h"

void drawWindowInnerBorder(ImVec2 windowPos, ImVec2 windowSize, int extraPaddingX = 0, int extraPaddingY = 0)
{
    int paddingX = 7;
    int paddingY = 9;
    ImVec2 borderRectStart(windowPos.x + paddingX + extraPaddingX, windowPos.y + paddingY + extraPaddingY);
    ImVec2 borderRectEnd(borderRectStart.x + (windowSize.x - (paddingX + extraPaddingX) * 2), borderRectStart.y + (windowSize.y - (paddingY + extraPaddingY) * 2));
    ImGui::GetWindowDrawList()->AddRect(borderRectStart, borderRectEnd, ImColor(235, 235, 235), 0, 0, 5.0f);
}

void displayRPM(ImGuiWindowFlags flags, int currentRPM, int maxRPM)
{
    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(760, 100), ImGuiCond_Once);
    ImGui::Begin("RPM", NULL, flags);

    // Todo: compute number of lines from max RPM instead of a static 8000 max rpm for all cars
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(40 + 90 * 0, 50), ImVec2(40 + 90 * 0 + 2, 50 + 50), ImColor(235, 235, 235), 0);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(40 + 90 * 1, 50), ImVec2(40 + 90 * 1 + 2, 50 + 50), ImColor(235, 235, 235), 0);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(40 + 90 * 2, 50), ImVec2(40 + 90 * 2 + 2, 50 + 50), ImColor(235, 235, 235), 0);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(40 + 90 * 3, 50), ImVec2(40 + 90 * 3 + 2, 50 + 50), ImColor(235, 235, 235), 0);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(40 + 90 * 4, 50), ImVec2(40 + 90 * 4 + 2, 50 + 50), ImColor(235, 235, 235), 0);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(40 + 90 * 5, 50), ImVec2(40 + 90 * 5 + 2, 50 + 50), ImColor(235, 235, 235), 0);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(40 + 90 * 6, 50), ImVec2(40 + 90 * 6 + 2, 50 + 50), ImColor(235, 235, 235), 0);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(40 + 90 * 7, 50), ImVec2(40 + 90 * 7 + 2, 50 + 50), ImColor(235, 235, 235), 0);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(40 + 90 * 8, 50), ImVec2(40 + 90 * 8 + 2, 50 + 50), ImColor(235, 235, 235), 0);
    ImGui::GetWindowDrawList()->AddText(ImVec2(38 + 90 * 0, 30), ImColor(235, 235, 235), "0");
    ImGui::GetWindowDrawList()->AddText(ImVec2(38 + 90 * 1, 30), ImColor(235, 235, 235), "1");
    ImGui::GetWindowDrawList()->AddText(ImVec2(38 + 90 * 2, 30), ImColor(235, 235, 235), "2");
    ImGui::GetWindowDrawList()->AddText(ImVec2(38 + 90 * 3, 30), ImColor(235, 235, 235), "3");
    ImGui::GetWindowDrawList()->AddText(ImVec2(38 + 90 * 4, 30), ImColor(235, 235, 235), "4");
    ImGui::GetWindowDrawList()->AddText(ImVec2(38 + 90 * 5, 30), ImColor(235, 235, 235), "5");
    ImGui::GetWindowDrawList()->AddText(ImVec2(38 + 90 * 6, 30), ImColor(235, 235, 235), "6");
    ImGui::GetWindowDrawList()->AddText(ImVec2(38 + 90 * 7, 30), ImColor(235, 235, 235), "7");
    ImGui::GetWindowDrawList()->AddText(ImVec2(38 + 90 * 8, 30), ImColor(235, 235, 235), "8");
    ImGui::End();
}

void displayPositionStats(ImGuiWindowFlags flags, int currentPosition, int completedLaps)
{
    const ImVec2 windowPos  = ImVec2(20, 120);
    const ImVec2 windowSize = ImVec2(280, 100);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);

    ImGui::Begin("Position", NULL, flags);
    drawWindowInnerBorder(windowPos, windowSize);
    ImGui::End();
}

void displaySplit(ImGuiWindowFlags flags, const char* split)
{
    const ImVec2 windowPos  = ImVec2(300, 120);
    const ImVec2 windowSize = ImVec2(200, 100);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);

    ImGui::Begin("Split", NULL, flags);
    drawWindowInnerBorder(windowPos, windowSize);
    ImGui::End();
}

void displayCurrentSpeed(ImGuiWindowFlags flags, float currentKPH)
{
    const ImVec2 windowPos  = ImVec2(500, 120);
    const ImVec2 windowSize = ImVec2(280, 100);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);

    ImGui::Begin("Speed", NULL, flags);
    drawWindowInnerBorder(windowPos, windowSize);
    ImGui::End();
}

void displayCurrentLapTime(ImGuiWindowFlags flags)
{
    const ImVec2 windowPos = ImVec2(20, 220);
    const ImVec2 windowSize = ImVec2(280, 100);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);

    ImGui::Begin("Current Time", NULL, flags);
    drawWindowInnerBorder(windowPos, windowSize);
    ImGui::End();
}

void displayBestLapTime(ImGuiWindowFlags flags)
{
    const ImVec2 windowPos = ImVec2(20, 320);
    const ImVec2 windowSize = ImVec2(280, 100);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);

    ImGui::Begin("Best Time", NULL, flags);
    drawWindowInnerBorder(windowPos, windowSize);
    ImGui::End();
}

void displayCurrentGear(ImGuiWindowFlags flags)
{
    const ImVec2 windowPos = ImVec2(300, 220);
    const ImVec2 windowSize = ImVec2(200, 200);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);

    ImGui::Begin("Gear", NULL, flags);
    drawWindowInnerBorder(windowPos, windowSize, 10);
    ImGui::End();
}

void displayCarControls(ImGuiWindowFlags flags)
{
    const ImVec2 windowPos = ImVec2(500, 220);
    const ImVec2 windowSize = ImVec2(280, 100);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);

    ImGui::Begin("Car Control", NULL, flags);
    drawWindowInnerBorder(windowPos, windowSize);
    ImGui::End();
}

void displayFuel(ImGuiWindowFlags flags)
{
    const ImVec2 windowPos = ImVec2(500, 320);
    const ImVec2 windowSize = ImVec2(280, 100);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);

    ImGui::Begin("Fuel", NULL, flags);
    drawWindowInnerBorder(windowPos, windowSize);
    ImGui::End();
}

// Main code
int main(int, char**)
{
    // ------------------------------------------------------------------
    //
    // Usual SDL and ImGui setup
    //
    // ------------------------------------------------------------------
    // init SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // create window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("DaFACC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 480, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // init GL loader
    gl3wInit();

    // setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);

    // ------------------------------------------------------------------
    //
    // Main Loop
    //
    // ------------------------------------------------------------------
    DaFACC::AccDataManager accData;
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_NoMove;
        flags |= ImGuiWindowFlags_NoResize;
        flags |= ImGuiWindowFlags_NoCollapse;
        flags |= ImGuiWindowFlags_NoTitleBar;

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.WindowBorderSize = 0.0f;

        accData.updateDataset(DaFACC::AccDataSet::DASHBOARD);
        const DaFACC::DashBoardData dashData = accData.getDashboardData();

        displayRPM(flags, dashData.currentRPM, dashData.maxRPM);
        displayPositionStats(flags, 1, 12);
        displaySplit(flags, dashData.split);
        displayCurrentSpeed(flags, dashData.currentKPH);
        displayCurrentLapTime(flags);
        displayBestLapTime(flags);
        displayCurrentGear(flags);
        displayCarControls(flags);
        displayFuel(flags);

        /*        
        ImGui::Begin("All");
        ImGui::Text(dashData.carModel);
        ImGui::Text(std::to_string(dashData.completedLaps).c_str());
        ImGui::Text(std::to_string(dashData.currentPosition).c_str());

        ImGui::Text(std::to_string(dashData.currentGear).c_str());
        ImGui::Text(std::to_string(dashData.currentKPH).c_str());
        ImGui::Text(dashData.currentTime);
        ImGui::Text(dashData.bestTime);
        ImGui::Text(dashData.split);
        ImGui::End();
        */

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}