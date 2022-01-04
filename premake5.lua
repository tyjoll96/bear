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
includedir["json"] = "%{wks.location}/bear/vendor/json/single_include"
includedir["GLFW"] = "%{wks.location}/bear/vendor/GLFW/include"
includedir["glm"] = "%{wks.location}/bear/vendor/glm"
includedir["entt"] = "%{wks.location}/bear/vendor/entt/include"
includedir["reactphysics3d"] = "%{wks.location}/bear/vendor/reactphysics3d/include"
includedir["imgui"] = "%{wks.location}/bear/vendor/imgui"

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
	project "GLFW"
		kind "StaticLib"
		language "C"
		location "./build"
		basedir "bear/vendor/GLFW"

		-- targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		-- objdir ("obj/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{wks.location}/bear/vendor/GLFW/include/GLFW/glfw3.h",
			"%{wks.location}/bear/vendor/GLFW/include/GLFW/glfw3native.h",
			"%{wks.location}/bear/vendor/GLFW/src/glfw_config.h",
			"%{wks.location}/bear/vendor/GLFW/src/context.c",
			"%{wks.location}/bear/vendor/GLFW/src/init.c",
			"%{wks.location}/bear/vendor/GLFW/src/input.c",
			"%{wks.location}/bear/vendor/GLFW/src/monitor.c",
			"%{wks.location}/bear/vendor/GLFW/src/vulkan.c",
			"%{wks.location}/bear/vendor/GLFW/src/window.c"
		}
		filter "system:linux"
			pic "on"

			systemversion "latest"
			staticruntime "on"

			files
			{
				"%{wks.location}/bear/vendor/GLFW/src/x11_init.c",
				"%{wks.location}/bear/vendor/GLFW/src/x11_monitor.c",
				"%{wks.location}/bear/vendor/GLFW/src/x11_window.c",
				"%{wks.location}/bear/vendor/GLFW/src/xkb_unicode.c",
				"%{wks.location}/bear/vendor/GLFW/src/posix_time.c",
				"%{wks.location}/bear/vendor/GLFW/src/posix_thread.c",
				"%{wks.location}/bear/vendor/GLFW/src/glx_context.c",
				"%{wks.location}/bear/vendor/GLFW/src/egl_context.c",
				"%{wks.location}/bear/vendor/GLFW/src/osmesa_context.c",
				"%{wks.location}/bear/vendor/GLFW/src/linux_joystick.c"
			}

			defines
			{
				"_GLFW_X11"
			}

		filter "system:windows"
			systemversion "latest"
			staticruntime "on"

			files
			{
				"%{wks.location}/bear/vendor/GLFW/src/win32_init.c",
				"%{wks.location}/bear/vendor/GLFW/src/win32_joystick.c",
				"%{wks.location}/bear/vendor/GLFW/src/win32_monitor.c",
				"%{wks.location}/bear/vendor/GLFW/src/win32_time.c",
				"%{wks.location}/bear/vendor/GLFW/src/win32_thread.c",
				"%{wks.location}/bear/vendor/GLFW/src/win32_window.c",
				"%{wks.location}/bear/vendor/GLFW/src/wgl_context.c",
				"%{wks.location}/bear/vendor/GLFW/src/egl_context.c",
				"%{wks.location}/bear/vendor/GLFW/src/osmesa_context.c"
			}

			defines 
			{ 
				"_GLFW_WIN32",
				"_CRT_SECURE_NO_WARNINGS"
			}

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"

	project "bgfx"
		location "./build"
		basedir "%{wks.location}/bear/vendor/bgfx"
		kind "StaticLib"
		language "C++"
		cppdialect "C++14"
		staticruntime "on"
		exceptionhandling "Off"
		rtti "Off"
		defines "__STDC_FORMAT_MACROS"
		files
		{
			"%{wks.location}/bear/vendor/bgfx/include/bgfx/**.h",
			"%{wks.location}/bear/vendor/bgfx/src/*.cpp",
			"%{wks.location}/bear/vendor/bgfx/src/*.h",
		}
		excludes
		{
			"%{wks.location}/bear/vendor/bgfx/src/amalgamated.cpp",
		}
		includedirs
		{
			includedir["bx"],
			includedir["bimg"],
			includedir["bgfx"],
			"%{wks.location}/bear/vendor/bgfx/3rdparty",
			"%{wks.location}/bear/vendor/bgfx/3rdparty/dxsdk/include",
			"%{wks.location}/bear/vendor/bgfx/3rdparty/khronos"
		}
		filter "configurations:Debug"
			defines "BGFX_CONFIG_DEBUG=1"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"

		filter "action:vs*"
			defines "_CRT_SECURE_NO_WARNINGS"
			excludes
			{
				"%{wks.location}/bear/vendor/bgfx/src/glcontext_glx.cpp",
				"%{wks.location}/bear/vendor/bgfx/src/glcontext_egl.cpp"
			}

		filter "system:macosx"
			files
			{
				"%{wks.location}/bear/vendor/bgfx/src/*.mm",
			}
			
		setBxCompat()
	project "bimg"
		location "./build"
		basedir "%{wks.location}/bear/vendor/bimg"
		kind "StaticLib"
		language "C++"
		cppdialect "C++14"
		staticruntime "on"
		exceptionhandling "Off"
		rtti "Off"
		files
		{
			"%{wks.location}/bear/vendor/bimg/include/bimg/*.h",
			"%{wks.location}/bear/vendor/bimg/src/image.cpp",
			"%{wks.location}/bear/vendor/bimg/src/image_gnf.cpp",
			"%{wks.location}/bear/vendor/bimg/src/*.h",
			"%{wks.location}/bear/vendor/bimg/3rdparty/astc-codec/src/decoder/*.cc"
		}
		includedirs
		{
			includedir["bx"],
			"%{wks.location}/bear/vendor/bimg/include",
			"%{wks.location}/bear/vendor/bimg/3rdparty/astc-codec",
			"%{wks.location}/bear/vendor/bimg/3rdparty/astc-codec/include",
		}
	
		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"
	
		filter "configurations:Release"
			runtime "Release"
			optimize "on"
	
		setBxCompat()
	project "bx"
		location "./build"
		basedir "%{wks.location}/bear/vendor/bx"
		kind "StaticLib"
		language "C++"
		cppdialect "C++14"
		staticruntime "on"
		exceptionhandling "Off"
		rtti "Off"
		defines "__STDC_FORMAT_MACROS"
		files
		{
			"%{wks.location}/bear/vendor/bx/include/bx/*.h",
			"%{wks.location}/bear/vendor/bx/include/bx/inline/*.inl",
			"%{wks.location}/bear/vendor/bx/src/*.cpp"
		}
		excludes
		{
			"%{wks.location}/bear/vendor/bx/src/amalgamated.cpp",
			"%{wks.location}/bear/vendor/bx/src/crtnone.cpp"
		}
		includedirs
		{
			"%{wks.location}/bear/vendor/bx/3rdparty",
			"%{wks.location}/bear/vendor/bx/include"
		}
	
		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"
	
		filter "configurations:Release"
			runtime "Release"
			optimize "on"
	
		filter "action:vs*"
			defines "_CRT_SECURE_NO_WARNINGS"
		setBxCompat()
	project "reactphysics3d"
		location "./build"
		basedir "bear/vendor/reactphysics3d"
		kind "StaticLib"
		language "C++"
		cppdialect "C++14"
		staticruntime "on"
		files
		{
			-- HEADER FILES
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/configuration.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/decimal.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/reactphysics3d.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/body/CollisionBody.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/body/RigidBody.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/ContactPointInfo.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/ContactManifoldInfo.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/ContactPair.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/broadphase/DynamicAABBTree.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/CollisionDispatch.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/GJK/VoronoiSimplex.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/GJK/GJKAlgorithm.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SAT/SATAlgorithm.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseAlgorithm.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsSphereAlgorithm.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/CapsuleVsCapsuleAlgorithm.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsCapsuleAlgorithm.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseInput.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseInfoBatch.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsSphereNarrowPhaseInfoBatch.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/CapsuleVsCapsuleNarrowPhaseInfoBatch.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsCapsuleNarrowPhaseInfoBatch.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/AABB.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/ConvexShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/ConvexPolyhedronShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/ConcaveShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/BoxShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/CapsuleShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/CollisionShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/ConvexMeshShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/SphereShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/TriangleShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/ConcaveMeshShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/HeightFieldShape.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/RaycastInfo.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/Collider.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/TriangleVertexArray.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/PolygonVertexArray.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/TriangleMesh.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/PolyhedronMesh.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/HalfEdgeStructure.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/ContactManifold.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/constraint/BallAndSocketJoint.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/constraint/ContactPoint.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/constraint/FixedJoint.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/constraint/HingeJoint.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/constraint/Joint.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/constraint/SliderJoint.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/engine/Entity.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/engine/EntityManager.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/engine/PhysicsCommon.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/systems/ConstraintSolverSystem.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/systems/ContactSolverSystem.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/systems/DynamicsSystem.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/systems/CollisionDetectionSystem.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/systems/SolveBallAndSocketJointSystem.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/systems/SolveFixedJointSystem.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/systems/SolveHingeJointSystem.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/systems/SolveSliderJointSystem.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/engine/PhysicsWorld.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/engine/EventListener.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/engine/Island.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/engine/Islands.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/engine/Material.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/engine/Timer.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/engine/OverlappingPairs.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/systems/BroadPhaseSystem.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/components/Components.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/components/CollisionBodyComponents.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/components/RigidBodyComponents.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/components/TransformComponents.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/components/ColliderComponents.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/components/JointComponents.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/components/BallAndSocketJointComponents.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/components/FixedJointComponents.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/components/HingeJointComponents.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/components/SliderJointComponents.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/CollisionCallback.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/collision/OverlapCallback.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/mathematics.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/mathematics_functions.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Matrix2x2.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Matrix3x3.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Quaternion.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Transform.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Vector2.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Vector3.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Ray.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/memory/MemoryAllocator.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/memory/PoolAllocator.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/memory/SingleFrameAllocator.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/memory/HeapAllocator.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/memory/DefaultAllocator.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/memory/MemoryManager.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/containers/Stack.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/containers/LinkedList.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/containers/List.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/containers/Map.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/containers/Set.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/containers/Pair.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/containers/Deque.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/utils/Profiler.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/utils/Logger.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/utils/DefaultLogger.h",
			"%{wks.location}/bear/vendor/reactphysics3d/include/reactphysics3d/utils/DebugRenderer.h",

			-- SOURCE FILES
			"%{wks.location}/bear/vendor/reactphysics3d/src/body/CollisionBody.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/body/RigidBody.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/broadphase/DynamicAABBTree.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/CollisionDispatch.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/GJK/VoronoiSimplex.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/GJK/GJKAlgorithm.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/SAT/SATAlgorithm.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/SphereVsSphereAlgorithm.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/CapsuleVsCapsuleAlgorithm.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/SphereVsCapsuleAlgorithm.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/NarrowPhaseInput.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/NarrowPhaseInfoBatch.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/SphereVsSphereNarrowPhaseInfoBatch.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/CapsuleVsCapsuleNarrowPhaseInfoBatch.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/narrowphase/SphereVsCapsuleNarrowPhaseInfoBatch.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/AABB.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/ConvexShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/ConvexPolyhedronShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/ConcaveShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/BoxShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/CapsuleShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/CollisionShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/ConvexMeshShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/SphereShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/TriangleShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/ConcaveMeshShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/shapes/HeightFieldShape.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/RaycastInfo.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/Collider.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/TriangleVertexArray.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/PolygonVertexArray.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/TriangleMesh.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/PolyhedronMesh.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/HalfEdgeStructure.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/ContactManifold.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/constraint/BallAndSocketJoint.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/constraint/ContactPoint.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/constraint/FixedJoint.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/constraint/HingeJoint.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/constraint/Joint.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/constraint/SliderJoint.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/engine/PhysicsCommon.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/systems/ConstraintSolverSystem.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/systems/ContactSolverSystem.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/systems/DynamicsSystem.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/systems/CollisionDetectionSystem.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/systems/SolveBallAndSocketJointSystem.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/systems/SolveFixedJointSystem.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/systems/SolveHingeJointSystem.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/systems/SolveSliderJointSystem.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/engine/PhysicsWorld.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/engine/Island.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/engine/Material.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/engine/Timer.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/engine/OverlappingPairs.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/engine/Entity.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/engine/EntityManager.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/systems/BroadPhaseSystem.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/components/Components.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/components/CollisionBodyComponents.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/components/RigidBodyComponents.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/components/TransformComponents.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/components/ColliderComponents.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/components/JointComponents.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/components/BallAndSocketJointComponents.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/components/FixedJointComponents.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/components/HingeJointComponents.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/components/SliderJointComponents.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/CollisionCallback.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/collision/OverlapCallback.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/mathematics/mathematics_functions.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/mathematics/Matrix2x2.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/mathematics/Matrix3x3.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/mathematics/Quaternion.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/mathematics/Transform.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/mathematics/Vector2.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/mathematics/Vector3.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/memory/PoolAllocator.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/memory/SingleFrameAllocator.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/memory/HeapAllocator.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/memory/MemoryManager.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/utils/Profiler.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/utils/DefaultLogger.cpp",
			"%{wks.location}/bear/vendor/reactphysics3d/src/utils/DebugRenderer.cpp",
		}
		includedirs
		{
			includedir["reactphysics3d"]
		}
		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"
		filter "configurations:Release"
			runtime "Release"
			optimize "on"
	project "imgui"
		kind "StaticLib"
		language "C++"
		location "./build"
		basedir "bear/vendor/imgui"
		staticruntime "on"
		
		-- targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		-- objdir ("obj/" .. outputdir .. "/%{prj.name}")
	
		files
		{
			"%{wks.location}/bear/vendor/imgui/imconfig.h",
			"%{wks.location}/bear/vendor/imgui/imgui.h",
			"%{wks.location}/bear/vendor/imgui/imgui.cpp",
			"%{wks.location}/bear/vendor/imgui/imgui_draw.cpp",
			"%{wks.location}/bear/vendor/imgui/imgui_internal.h",
			"%{wks.location}/bear/vendor/imgui/imgui_tables.cpp",
			"%{wks.location}/bear/vendor/imgui/imgui_widgets.cpp",
			"%{wks.location}/bear/vendor/imgui/imstb_rectpack.h",
			"%{wks.location}/bear/vendor/imgui/imstb_textedit.h",
			"%{wks.location}/bear/vendor/imgui/imstb_truetype.h",
			"%{wks.location}/bear/vendor/imgui/imgui_demo.cpp"
		}
		
		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"
	
		filter "configurations:Release"
			runtime "Release"
			optimize "on"
group ""

group "Games"
	include "games/bear_basketball"
group ""

include "bear"
include "sandbox"
include "editor"