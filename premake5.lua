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
includedir["entt"] = "%{wks.location}/bear/vendor/entt/include"

group "Dependencies"
	include "bear/vendor/GLFW"
group ""

include "bear"
include "sandbox"