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
includedir["reactphysics3d"] = "%{wks.location}/bear/vendor/reactphysics3d/include"

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
			"bear/vendor/reactphysics3d/include/reactphysics3d/configuration.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/decimal.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/reactphysics3d.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/body/CollisionBody.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/body/RigidBody.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/ContactPointInfo.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/ContactManifoldInfo.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/ContactPair.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/broadphase/DynamicAABBTree.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/CollisionDispatch.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/GJK/VoronoiSimplex.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/GJK/GJKAlgorithm.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SAT/SATAlgorithm.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseAlgorithm.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsSphereAlgorithm.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/CapsuleVsCapsuleAlgorithm.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsCapsuleAlgorithm.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseInput.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseInfoBatch.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsSphereNarrowPhaseInfoBatch.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/CapsuleVsCapsuleNarrowPhaseInfoBatch.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsCapsuleNarrowPhaseInfoBatch.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/AABB.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/ConvexShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/ConvexPolyhedronShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/ConcaveShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/BoxShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/CapsuleShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/CollisionShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/ConvexMeshShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/SphereShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/TriangleShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/ConcaveMeshShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/shapes/HeightFieldShape.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/RaycastInfo.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/Collider.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/TriangleVertexArray.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/PolygonVertexArray.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/TriangleMesh.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/PolyhedronMesh.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/HalfEdgeStructure.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/ContactManifold.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/constraint/BallAndSocketJoint.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/constraint/ContactPoint.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/constraint/FixedJoint.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/constraint/HingeJoint.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/constraint/Joint.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/constraint/SliderJoint.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/engine/Entity.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/engine/EntityManager.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/engine/PhysicsCommon.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/systems/ConstraintSolverSystem.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/systems/ContactSolverSystem.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/systems/DynamicsSystem.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/systems/CollisionDetectionSystem.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/systems/SolveBallAndSocketJointSystem.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/systems/SolveFixedJointSystem.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/systems/SolveHingeJointSystem.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/systems/SolveSliderJointSystem.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/engine/PhysicsWorld.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/engine/EventListener.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/engine/Island.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/engine/Islands.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/engine/Material.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/engine/Timer.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/engine/OverlappingPairs.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/systems/BroadPhaseSystem.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/components/Components.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/components/CollisionBodyComponents.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/components/RigidBodyComponents.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/components/TransformComponents.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/components/ColliderComponents.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/components/JointComponents.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/components/BallAndSocketJointComponents.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/components/FixedJointComponents.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/components/HingeJointComponents.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/components/SliderJointComponents.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/CollisionCallback.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/collision/OverlapCallback.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/mathematics.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/mathematics_functions.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Matrix2x2.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Matrix3x3.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Quaternion.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Transform.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Vector2.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Vector3.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/mathematics/Ray.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/memory/MemoryAllocator.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/memory/PoolAllocator.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/memory/SingleFrameAllocator.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/memory/HeapAllocator.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/memory/DefaultAllocator.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/memory/MemoryManager.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/containers/Stack.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/containers/LinkedList.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/containers/List.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/containers/Map.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/containers/Set.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/containers/Pair.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/containers/Deque.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/utils/Profiler.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/utils/Logger.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/utils/DefaultLogger.h",
			"bear/vendor/reactphysics3d/include/reactphysics3d/utils/DebugRenderer.h",

			-- SOURCE FILES
			"bear/vendor/reactphysics3d/src/body/CollisionBody.cpp",
			"bear/vendor/reactphysics3d/src/body/RigidBody.cpp",
			"bear/vendor/reactphysics3d/src/collision/broadphase/DynamicAABBTree.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/CollisionDispatch.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/GJK/VoronoiSimplex.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/GJK/GJKAlgorithm.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/SAT/SATAlgorithm.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/SphereVsSphereAlgorithm.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/CapsuleVsCapsuleAlgorithm.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/SphereVsCapsuleAlgorithm.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/NarrowPhaseInput.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/NarrowPhaseInfoBatch.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/SphereVsSphereNarrowPhaseInfoBatch.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/CapsuleVsCapsuleNarrowPhaseInfoBatch.cpp",
			"bear/vendor/reactphysics3d/src/collision/narrowphase/SphereVsCapsuleNarrowPhaseInfoBatch.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/AABB.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/ConvexShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/ConvexPolyhedronShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/ConcaveShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/BoxShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/CapsuleShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/CollisionShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/ConvexMeshShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/SphereShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/TriangleShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/ConcaveMeshShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/shapes/HeightFieldShape.cpp",
			"bear/vendor/reactphysics3d/src/collision/RaycastInfo.cpp",
			"bear/vendor/reactphysics3d/src/collision/Collider.cpp",
			"bear/vendor/reactphysics3d/src/collision/TriangleVertexArray.cpp",
			"bear/vendor/reactphysics3d/src/collision/PolygonVertexArray.cpp",
			"bear/vendor/reactphysics3d/src/collision/TriangleMesh.cpp",
			"bear/vendor/reactphysics3d/src/collision/PolyhedronMesh.cpp",
			"bear/vendor/reactphysics3d/src/collision/HalfEdgeStructure.cpp",
			"bear/vendor/reactphysics3d/src/collision/ContactManifold.cpp",
			"bear/vendor/reactphysics3d/src/constraint/BallAndSocketJoint.cpp",
			"bear/vendor/reactphysics3d/src/constraint/ContactPoint.cpp",
			"bear/vendor/reactphysics3d/src/constraint/FixedJoint.cpp",
			"bear/vendor/reactphysics3d/src/constraint/HingeJoint.cpp",
			"bear/vendor/reactphysics3d/src/constraint/Joint.cpp",
			"bear/vendor/reactphysics3d/src/constraint/SliderJoint.cpp",
			"bear/vendor/reactphysics3d/src/engine/PhysicsCommon.cpp",
			"bear/vendor/reactphysics3d/src/systems/ConstraintSolverSystem.cpp",
			"bear/vendor/reactphysics3d/src/systems/ContactSolverSystem.cpp",
			"bear/vendor/reactphysics3d/src/systems/DynamicsSystem.cpp",
			"bear/vendor/reactphysics3d/src/systems/CollisionDetectionSystem.cpp",
			"bear/vendor/reactphysics3d/src/systems/SolveBallAndSocketJointSystem.cpp",
			"bear/vendor/reactphysics3d/src/systems/SolveFixedJointSystem.cpp",
			"bear/vendor/reactphysics3d/src/systems/SolveHingeJointSystem.cpp",
			"bear/vendor/reactphysics3d/src/systems/SolveSliderJointSystem.cpp",
			"bear/vendor/reactphysics3d/src/engine/PhysicsWorld.cpp",
			"bear/vendor/reactphysics3d/src/engine/Island.cpp",
			"bear/vendor/reactphysics3d/src/engine/Material.cpp",
			"bear/vendor/reactphysics3d/src/engine/Timer.cpp",
			"bear/vendor/reactphysics3d/src/engine/OverlappingPairs.cpp",
			"bear/vendor/reactphysics3d/src/engine/Entity.cpp",
			"bear/vendor/reactphysics3d/src/engine/EntityManager.cpp",
			"bear/vendor/reactphysics3d/src/systems/BroadPhaseSystem.cpp",
			"bear/vendor/reactphysics3d/src/components/Components.cpp",
			"bear/vendor/reactphysics3d/src/components/CollisionBodyComponents.cpp",
			"bear/vendor/reactphysics3d/src/components/RigidBodyComponents.cpp",
			"bear/vendor/reactphysics3d/src/components/TransformComponents.cpp",
			"bear/vendor/reactphysics3d/src/components/ColliderComponents.cpp",
			"bear/vendor/reactphysics3d/src/components/JointComponents.cpp",
			"bear/vendor/reactphysics3d/src/components/BallAndSocketJointComponents.cpp",
			"bear/vendor/reactphysics3d/src/components/FixedJointComponents.cpp",
			"bear/vendor/reactphysics3d/src/components/HingeJointComponents.cpp",
			"bear/vendor/reactphysics3d/src/components/SliderJointComponents.cpp",
			"bear/vendor/reactphysics3d/src/collision/CollisionCallback.cpp",
			"bear/vendor/reactphysics3d/src/collision/OverlapCallback.cpp",
			"bear/vendor/reactphysics3d/src/mathematics/mathematics_functions.cpp",
			"bear/vendor/reactphysics3d/src/mathematics/Matrix2x2.cpp",
			"bear/vendor/reactphysics3d/src/mathematics/Matrix3x3.cpp",
			"bear/vendor/reactphysics3d/src/mathematics/Quaternion.cpp",
			"bear/vendor/reactphysics3d/src/mathematics/Transform.cpp",
			"bear/vendor/reactphysics3d/src/mathematics/Vector2.cpp",
			"bear/vendor/reactphysics3d/src/mathematics/Vector3.cpp",
			"bear/vendor/reactphysics3d/src/memory/PoolAllocator.cpp",
			"bear/vendor/reactphysics3d/src/memory/SingleFrameAllocator.cpp",
			"bear/vendor/reactphysics3d/src/memory/HeapAllocator.cpp",
			"bear/vendor/reactphysics3d/src/memory/MemoryManager.cpp",
			"bear/vendor/reactphysics3d/src/utils/Profiler.cpp",
			"bear/vendor/reactphysics3d/src/utils/DefaultLogger.cpp",
			"bear/vendor/reactphysics3d/src/utils/DebugRenderer.cpp",
		}
		includedirs
		{
			includedir["reactphysics3d"]
		}
group ""

group "Games"
	include "games/bear_basketball"
group ""

include "bear"
include "sandbox"