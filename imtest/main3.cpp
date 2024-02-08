//
// Created by zzm on 24-2-7.
//
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "implot.h"
#include "math.h"

void RenderTableView()
{
    // 模拟一些数据
    const int numColumns = 3;
    const int numRows = 5;
    const char* columnHeaders[numColumns] = { "Name", "Age", "Country" };
    const char* rowData[numRows][numColumns] = {
            { "John", "25", "USA" },
            { "Emily", "30", "Canada" },
            { "Taro", "40", "Japan" },
            { "Sophie", "35", "France" },
            { "Alex", "28", "Germany" }
    };

    // 计算表格布局
    float columnWidth = ImGui::GetContentRegionAvail().x / numColumns;

    // 绘制表头
    ImGui::Columns(numColumns);
    for (int i = 0; i < numColumns; i++)
    {
        ImGui::Text("%s", columnHeaders[i]);
        ImGui::NextColumn();
    }
    ImGui::Separator();

    // 绘制行数据
    for (int row = 0; row < numRows; row++)
    {
        ImGui::Columns(numColumns);
        for (int col = 0; col < numColumns; col++)
        {
            ImGui::Text("%s", rowData[row][col]);
            ImGui::NextColumn();
        }
    }
}

int main()
{
    // 初始化 GLFW
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui TableView Example", NULL, NULL);
    glfwMakeContextCurrent(window);

    // 初始化 ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");

    ImPlot::CreateContext();

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // 开始 ImGui 帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

//        bool testm = true;
//        ImPlot::ShowDemoWindow(&testm);
        if (ImPlot::BeginPlot("Curvature data show"))
        {
            // 将数据传递给 ImPlot，并绘制折线图
            float xs[100], ys[100];
            for (int i = 0; i < 100; ++i)
            {
                xs[i] = i * 0.1f;
                ys[i] = sin(xs[i]);
            }
            ImPlot::PlotLine("Curvature", xs, ys, 100);

            // 结束 ImPlot 绘制
            ImPlot::EndPlot();
        }

//        bool test = true;
//        ImGui::ShowDemoWindow(&test);

//        // 渲染 TableView
//        RenderTableView();

        // 结束 ImGui 帧并渲染
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // 清理 ImPlot 资源
    ImPlot::DestroyContext();
    // 清理 ImGui 相关资源
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // 清理 GLFW 相关资源
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}