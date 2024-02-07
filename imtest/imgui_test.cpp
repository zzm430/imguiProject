//
// Created by zzm on 24-2-7.
//
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// GLFW和OpenGL的头文件
#include <GLFW/glfw3.h>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

int main()
{
    // 初始化 GLFW 和 OpenGL 上下文

    // 初始化 Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io; // 避免未使用的警告
    ImGui::StyleColorsDark(); // 设定样式

    // 初始化 ImGui 并配置与渲染上下文相关的平台/图形后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // 在开始新一帧之前调用 ImGui 函数
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 创建停靠空间
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        // 创建第一个示例窗口
        {
            ImGui::Begin("Window 1");
            ImGui::Text("This is window 1");
            ImGui::End();
        }

        // 创建第二个示例窗口
        {
            ImGui::Begin("Window 2");
            ImGui::Text("This is window 2");
            ImGui::End();
        }

        // 渲染
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // 清理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // 终止 GLFW 及 OpenGL 上下文

    return 0;
}
