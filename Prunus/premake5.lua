workspace "Prunus"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "${cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Prunus/vendor/GLFW/include"
IncludeDir["Glad"] = "Prunus/vendor/Glad/include"
IncludeDir["ImGui"] = "Prunus/vendor/imgui"
IncludeDir["glm"] = "Prunus/vendor/glm"

include "Prunus/vendor/GLFW"
include "Prunus/vendor/Glad"
include "Prunus/vendor/imgui"

project "Prunus"
    location "Prunus"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pnpch.h"
    pchsource "Prunus/src/pnpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/**.hpp",
        "%{prj.name}/vendor/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }
    
    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "10.0.19041.0"
  
        defines
        {
            "PRUNUS_BUILD_DLL",
            "PRUNUS_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }
    
    filter "configurations:Debug"
        defines "PRUNUS_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "PRUNUS_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "PRUNUS_DIST"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Prunus/vendor/spdlog/include",
        "Prunus/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Prunus"
    }

    filter "system:windows"
        systemversion "10.0.19041.0"

        defines
        {
            "PRUNUS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PRUNUS_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "PRUNUS_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "PRUNUS_DIST"
        optimize "on"
