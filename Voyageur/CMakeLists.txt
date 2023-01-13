# CMakeList.txt : CMake project for Imgui Demo, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Voyageur "Voyageur.cpp" "Voyageur.h" "imgui/imgui_impl_win32.cpp" "imgui/imgui_impl_win32.h" "imgui/imgui.cpp" "imgui/imgui_demo.cpp" "imgui/imgui_draw.cpp" "imgui/imgui_impl_dx11.cpp" "imgui/imgui_tables.cpp" "imgui/imgui_widgets.cpp" "imgui/imconfig.h" "imgui/imgui.h" "imgui/imgui_impl_dx11.h" "imgui/imgui_internal.h" "imgui/imstb_rectpack.h" "imgui/imstb_textedit.h" "imgui/imstb_truetype.h" "Game/Planet.cpp" "Game/Planet.h" "GUI/Planet_Overview.cpp" "GUI/Planet_Overview.h" "Game/Resource.cpp" "Game/Resource.h" "Game/UpdateTime.cpp" "Game/UpdateTime.h" "GUI/Gui_Start.cpp" "GUI/Gui_Start.h" "GUI/Game_Overview.cpp" "GUI/Game_Overview.h" "GUI/Gui_Top_Menu.cpp" "GUI/Gui_Top_Menu.h" "Game/MainGame.cpp" "Game/MainGame.h" Game/Person.cpp Game/Person.h Game/People.cpp Game/People.h Game/ResourceTemplate.cpp Game/ResourceTemplate.h Constants.h)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Voyageur PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

target_link_libraries(${PROJECT_NAME} d3d11.lib)