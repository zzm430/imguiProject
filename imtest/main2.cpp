#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// GLFW和OpenGL的头文件
#include <GLFW/glfw3.h>
#include <algorithm>
#include <stdio.h>

int main() {
    // 初始化glfw和opengl上下文
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Canvas Instance", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // 启用垂直同步

    // 初始化Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // 定义画布缩放因子和多边形顶点列表
    float canvas_scale = 1.0f;
    ImVec2 poly_points[4] = {{100, 100}, {200, 150}, {250, 300}, {150, 250}};

    bool show_polygon = false;

    static ImVec2 drag_delta = ImVec2(0, 0);
    static bool is_dragging = false;
    // 主循环
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // 渲染Dear ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 开始绘制
        ImGui::Begin("tractor simulator",nullptr, ImGuiWindowFlags_NoMove);

        // 获取绘制命令列表
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
//            ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {
                    show_polygon = !show_polygon;
                }
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // 在ImGui窗口中添加一个条件语句，以便在鼠标左键按下的情况下捕获多边形的顶点
        if (show_polygon) {
            if (ImGui::IsMouseDragging(0, 0.0f)) {
                ImVec2 mouse_delta = ImGui::GetIO().MouseDelta;
                for (int i = 0; i < 4; i++) {
                    poly_points[i].x += mouse_delta.x;
                    poly_points[i].y += mouse_delta.y;
                }
            }
        }

        // 获取画布的位置和尺寸
        ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
        ImVec2 canvas_size = ImGui::GetWindowContentRegionMax();
        canvas_size.x = 1280;
        canvas_size.y = 1280;

        // 绘制画布
        draw_list->AddRectFilled(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), IM_COL32(255, 255, 255, 255));

//        // 绘制多边形
        if(show_polygon){
            ImVec2 scaled_points[4] = {{poly_points[0].x * canvas_scale, poly_points[0].y * canvas_scale},
                                       {poly_points[1].x * canvas_scale, poly_points[1].y * canvas_scale},
                                       {poly_points[2].x * canvas_scale, poly_points[2].y * canvas_scale},
                                       {poly_points[3].x * canvas_scale, poly_points[3].y * canvas_scale}};

            draw_list->AddLine(ImVec2(canvas_pos.x + scaled_points[0].x, canvas_pos.y + scaled_points[0].y),
                               ImVec2(canvas_pos.x + scaled_points[1].x, canvas_pos.y + scaled_points[1].y),
                               IM_COL32(255, 0, 0, 255));
            draw_list->AddLine(ImVec2(canvas_pos.x + scaled_points[1].x, canvas_pos.y + scaled_points[1].y),
                               ImVec2(canvas_pos.x + scaled_points[2].x, canvas_pos.y + scaled_points[2].y),
                               IM_COL32(255, 0, 0, 255));
            draw_list->AddLine(ImVec2(canvas_pos.x + scaled_points[2].x, canvas_pos.y + scaled_points[2].y),
                               ImVec2(canvas_pos.x + scaled_points[3].x, canvas_pos.y + scaled_points[3].y),
                               IM_COL32(255, 0, 0, 255));
            draw_list->AddLine(ImVec2(canvas_pos.x + scaled_points[3].x, canvas_pos.y + scaled_points[3].y),
                               ImVec2(canvas_pos.x + scaled_points[0].x, canvas_pos.y + scaled_points[0].y),
                               IM_COL32(255, 0, 0, 255));

            // 显示多边形顶点的坐标
            for (int i = 0; i < 4; i++) {
                // 创建显示坐标的字符串
                char coord_text[32];
                snprintf(coord_text, sizeof(coord_text), "(%.1f, %.1f)", poly_points[i].x, poly_points[i].y);
                // 绘制坐标文本，稍微偏离顶点位置以避免重叠
                draw_list->AddText(ImVec2(canvas_pos.x +scaled_points[i].x + 5, canvas_pos.y+ scaled_points[i].y + 5),
                                   IM_COL32(0, 0, 255, 255), coord_text);
            }
        }
        // 结束绘制
        ImGui::End();

        // 处理画布缩放
        ImGuiIO& io = ImGui::GetIO();
        if (io.MouseWheel != 0.0) {
            canvas_scale += io.MouseWheel * 0.1; // 根据需要调整缩放速度
            canvas_scale = std::max(canvas_scale, 0.1f); // 限制最小缩放值
        }

        // 渲染
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwSwapBuffers(window);
    }

    // 清理资源
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}