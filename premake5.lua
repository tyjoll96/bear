workspace "bear"
	architecture "x64"
	startproject "sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includedir = {}
includedir["GLFW"] = "%{wks.location}/bear/vendor/GLFW/include"
includedir["glm"] = "%{wks.location}/bear/vendor/glm"
includedir["entt"] = "%{wks.location}/bear/vendor/entt/include"

includedir["bgfx"] = "%{wks.location}/bear/vendor/bgfx/include"
includedir["bimg"] = "%{wks.location}/bear/vendor/bimg/include"
includedir["bx"] = "%{wks.location}/bear/vendor/bx/include"

function setBxCompat()
	filter "action:vs*"
		includedirs { "%{wks.location}/bear/vendor/bx/include/compat/msvc" }
	filter { "system:windows", "action:gmake" }
		includedirs { "%{wks.location}/bear/vendor/bx/include/compat/mingw" }
	filter { "system:macosx" }
		includedirs { "%{wks.location}/bear/vendor/bx/include/compat/osx" }
		buildoptions { "-x objective-c++" }
end

group "Dependencies"
	include "bear/vendor/GLFW"
	include "bear/vendor/bgfx"
	include "bear/vendor/bimg"
	include "bear/vendor/bx"
group ""

group "Games"
	include "games/bear_basketball"
group ""

include "bear"
include "sandbox"