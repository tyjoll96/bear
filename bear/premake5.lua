project "bear"
    kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	-- pchheader "rlpch.h"
	-- pchsource "src/rlpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	defines
	{
		-- "_CRT_SECURE_NO_WARNINGS",
		-- "GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"%{includedir.GLFW}",
		"%{includedir.entt}"
	}

	links
	{
		"GLFW",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "BR_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "BR_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "BR_DIST"
		runtime "Release"
		optimize "on"
