project "bear"
    kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	pchheader "brpch.h"
	pchsource "src/brpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
	}

	defines
	{
		-- "_CRT_SECURE_NO_WARNINGS",
		-- "GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"%{includedir.json}",
		"%{includedir.bgfx}",
		"%{includedir.bx}",
		"%{includedir.bimg}",
		"%{includedir.GLFW}",
		"%{includedir.glm}",
		"%{includedir.entt}",
		"%{includedir.reactphysics3d}",
		"%{includedir.imgui}"
	}

	links
	{
		"bgfx",
		"bimg",
		"bx",
		"GLFW",
		"reactphysics3d",
		"imgui"
	}

	filter "system:windows"
		systemversion "latest"

		links { "gdi32", "kernel32", "psapi" }

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
	setBxCompat()