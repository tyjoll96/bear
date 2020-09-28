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
		"%{includedir.GLFW}",
		"%{includedir.entt}"
	}

	links
	{
		"bear"
	}

	filter "system:windows"
		systemversion "latest"

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