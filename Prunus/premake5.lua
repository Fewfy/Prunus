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
    kind "SharedLib"
    language "C++"

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

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.19041.0"
  
        defines
        {
            "PRUNUS_BUILD_DLL",
            "PRUNUS_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
    
    filter "configurations:Debug"
        defines "PRUNUS_DEBUG"
		buildoptions "/MDd"
        symbols "On"
    
    filter "configurations:Release"
        defines "PRUNUS_RELEASE"
		buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "PRUNUS_DIST"
		buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.19041.0"

        defines
        {
            "PRUNUS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PRUNUS_DEBUG"
        symbols "On"
		buildoptions "/MDd"
    
    filter "configurations:Release"
        defines "PRUNUS_RELEASE"
        optimize "On"
		buildoptions "/MD"

    filter "configurations:Dist"
        defines "PRUNUS_DIST"
        optimize "On"
		buildoptions "/MD"
