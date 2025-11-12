#include <imgui.h>
#include <implot.h>
#include <implot_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <stdio.h>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include <GLFW/glfw3.h>

#include "Stock.h"
#include "JsonParser.h"

// --- 繪製 K 線 (改良版) ---
// bullCol: 上漲顏色 (預設綠色)
// bearCol: 下跌顏色 (預設紅色)
void PlotCandlestick(const char* label_id,
                     const CandleArrays& data,
                     ImVec4 bullCol = ImVec4(0, 1, 0, 1),
                     ImVec4 bearCol = ImVec4(1, 0, 0, 1))
{
    ImDrawList* draw_list = ImPlot::GetPlotDrawList();
    const double half_width = 0.3; // K棒寬度 (X 軸單位)

    if (ImPlot::BeginItem(label_id)) {
        // 設定圖例顏色
        ImPlot::GetCurrentItem()->Color = ImGui::GetColorU32(bullCol);

        // 若開啟 Fit 功能，自動縮放
        if (ImPlot::FitThisFrame()) {
            for (size_t i = 0; i < data.x.size(); ++i) {
                ImPlot::FitPoint(ImPlotPoint(data.x[i], data.low[i]));
                ImPlot::FitPoint(ImPlotPoint(data.x[i], data.high[i]));
            }
        }

        // 繪製每一根 K 棒
        for (size_t i = 0; i < data.x.size(); ++i) {
            bool isBear = data.close[i] < data.open[i];
            ImU32 color = ImGui::GetColorU32(isBear ? bearCol : bullCol);

            // 開盤、收盤左右位置
            ImVec2 open_pos  = ImPlot::PlotToPixels(data.x[i] - half_width, data.open[i]);
            ImVec2 close_pos = ImPlot::PlotToPixels(data.x[i] + half_width, data.close[i]);

            // 最高、最低點
            ImVec2 low_pos   = ImPlot::PlotToPixels(data.x[i], data.low[i]);
            ImVec2 high_pos  = ImPlot::PlotToPixels(data.x[i], data.high[i]);

            // 畫實體矩形 (K棒)
            draw_list->AddRectFilled(open_pos, close_pos, color);

            // 畫上下影線
            draw_list->AddLine(low_pos, high_pos, color, 1.0f);
        }

        ImPlot::EndItem();
    }
}

int main(int argc, char** argv) {
    // ---- load stock data ----
    std::string filepath = "data/0050_20251112.json";
    Stock stock("0050");
    try {
        auto candles = Parser::parseTWSEJsonFile(filepath);
        stock.addCandles(candles);
        std::cout << "Loaded " << candles.size() << " candles\n";
    } catch (const std::exception& e) {
        std::cerr << "Error loading JSON: " << e.what() << "\n";
        return 1;
    }

    CandleArrays data = stock.getCandleArrays();

    // ---- setup GLFW + OpenGL ----
    if (!glfwInit()) return 1;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Stock Candlestick Viewer", NULL, NULL);
    if (window == NULL) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    // ---- setup ImGui ----
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // ---- main loop ----
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Candlestick Chart");
        if (ImPlot::BeginPlot("Stock Candlestick")) {
            ImPlot::SetupAxes("Index", "Price");
            PlotCandlestick("Candles", data);
            ImPlot::EndPlot();
        }
        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // ---- cleanup ----
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}