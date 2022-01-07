project "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
        "%{wks.location}/bear/src",
		"%{wks.location}/bear/vendor",
		"%{includedir.bgfx}",
		"%{includedir.bx}",
		"%{includedir.bimg}",
		"%{includedir.GLFW}",
		"%{includedir.glm}",
		"%{includedir.entt}",
		"%{includedir.reactphysics3d}",
		"%{includedir.imgui}",
		"%{includedir.spdlog}"
	}

	links
	{
		"bgfx",
		"bimg",
		"bx",
		"bear",
		"reactphysics3d",
		"imgui"
	}

	filter "system:windows"
		systemversion "latest"

		links { "gdi32", "kernel32", "psapi" }

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