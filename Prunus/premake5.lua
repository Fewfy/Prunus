workspace "Prunus"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "${cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"    
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PRUNUS_BUILD_DLL",
            "PRUNUS_PLATFORM_WINDOWS"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
    
    filter "configurations:Debug"
        defines "PRUNUS_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "PRUNUS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "PRUNUS_DIST"
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
        "Prunus/src"   
    }

    links
    {
        "Prunus"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PRUNUS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PRUNUS_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "PRUNUS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "PRUNUS_DIST"
        optimize "On"
