---
title: RNGOEngine
description: RNGOEngine is a C++ game engine runtime and editor with ECS, custom made OpenGL RHI Wrapper and RenderPass system.
layout: project

cover_video: assets/projects/RNGOEngine/Trailer.webm
trailer_video: assets/projects/RNGOEngine/Trailer.webm

duration: Ongoing
team_size: 1
tags: ["C++", "OpenGL", "ImGui", "EnTT"]

github: https://github.com/Oskar-Norberg/RNGOEngine-Core

gallery:
  - type: video
    src: assets/projects/RNGOEngine/Trailer2.webm
    thumb: assets/projects/RNGOEngine/Trailer2.jpg

  - type: video
    src: assets/projects/RNGOEngine/Trailer.webm
    thumb: assets/projects/RNGOEngine/Trailer.jpg

  - type: image
    src: assets/projects/RNGOEngine/Scene.png

featured_main: 10

permalink: /projects/RNGOEngine.html
---

RNGOEngine is a Data Oriented ECS Game Engine developed in C++. The purpose of the project is ultimately to make a generic game engine to use for future projects and to further widen my knowledge of C++ and rendering far beyond something like Unreal Engine. For rendering the engine uses OpenGL, GLFW and ImGui for its editor.

## Entities
Entities are handled by the Entity Component System implemented using EnTT. Components can be added through the interface in a Unity-like manner through the Entity Properties. Entities can be operated on by adding any system which inherits from the base-class ISystem to the SystemScheduler. These Systems run each frame and operate on and transform the data represented in the ECSWorld. Whether it be Physics, gathering the RenderWorld or any other system.
<div class="selectable-dropdown">
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="Components-Header">Components.h</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="ISystem-Header">ISystem.h</button>
<div class="selectable-dropdown-area">
<div class="selectable-text" data-code-text-name="Components-Header" markdown="1">
```c++
{% include code/Projects/RNGOEngine/Components.h %}
```
</div>
<div class="selectable-text" data-code-text-name="ISystem-Header" markdown="1">
```c++
{% include code/Projects/RNGOEngine/ISystem.h %}
```
</div>
</div>
</div>

## Rendering
<div class="columns">
<div class="column is-three-fifths" markdown="1">
Rendering is handled in three stages: RenderSystem, RenderAPI and IRenderer. The RenderSystem collects all MeshRenderers, Lighting and Camera information and submits draw calls. The RenderAPI is a higher-level abstraction on top of the RenderAPI and handles higher-level concepts of FrameTargets and RenderPasses. RenderPasses have virtual functions for their execution and are passed a reference to the IRenderer to separate the logic for things such as ShadowPass and ForwardPass. Currently the Engine only supports Forward Rendering with Shadow Mapping, but a deferred pipeline is planned. One of the philosophies behind this design is to keep a specific graphics API limited only to the lower-level IRenderer and to never have direct OpenGL calls anywhere outside of that class. 
</div>
<div class="column">
<video width="100%" height="auto" src="{{ "assets/projects/RNGOEngine/Spotlight.mp4" | relative_url }}" controls></video>
</div>
</div>

<div class="selectable-dropdown">
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="RenderSystemUpdate">RenderSystem::Update</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="RenderPass-Header">RenderPass.h</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="ForwardPassExecute">ForwardPass::Execute</button>
<div class="selectable-dropdown-area">
<div class="selectable-text" data-code-text-name="RenderSystemUpdate" markdown="1">
```c++
{% include code/Projects/RNGOEngine/RenderSystemUpdate %}
```
</div>
<div class="selectable-text" data-code-text-name="RenderPass-Header" markdown="1">
```c++
{% include code/Projects/RNGOEngine/RenderPass.h %}
```
</div>
<div class="selectable-text" data-code-text-name="ForwardPassExecute" markdown="1">
```c++
{% include code/Projects/RNGOEngine/ForwardPassExecute %}
```
</div>
</div>
</div>

## Assets/Registries
<div class="columns">
<div class="column" markdown="1">
![some text]({{ "assets/projects/RNGOEngine/ContentDrawer.png" | relative_url }})
</div>
<div class="column is-two-fifths" markdown="1">
In order to render anything we first need to have a shader, model and texture assets. Taking inspiration from Unity I developed an asset-metadata system for persistently storing UUIDs and import settings of different assets. In this way, Assets can be stored in a central registry and referenced in the ECS using AssetHandles. As AssetHandles are just UUIDs/integers under the hood this greatly cuts down on the size of storing something like a stack-allocated string for path and improves the cache-locality of using a heap-allocated string. 
</div>
</div>


<div class="selectable-dropdown">
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="UUID-Header">UUID.h</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="RuntimeAssetRegistry-Header">RuntimeAssetRegistry.h</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="AssetDatabase-Header">AssetDatabase.h</button>
<div class="selectable-dropdown-area">
<div class="selectable-text" data-code-text-name="UUID-Header" markdown="1">
```c++
{% include code/Projects/RNGOEngine/UUID.h %}
```
</div>
<div class="selectable-text" data-code-text-name="RuntimeAssetRegistry-Header" markdown="1">
```c++
{% include code/Projects/RNGOEngine/RuntimeAssetRegistry.h %}
```
</div>
<div class="selectable-text" data-code-text-name="AssetDatabase-Header" markdown="1">
```c++
{% include code/Projects/RNGOEngine/AssetDatabase.h %}
```
</div>
</div>
</div>

## Asset Importing
Importing assets is done through the AssetLoader and submodule AssetImporters. The AssetLoader acts as an orchestrator between the different AssetImporters and communicates between the AssetDatabase pulling any relevant metadata for asset importing. AssetImporters themselves are responsible for the actual I/O of reading from the disk, transforming the data to an engine native format and then uploading said data to the correct thread. Thus asset loading is generally done in two or more steps, an asset is imported and then requested whereupon it will be loaded from the disk. The importer will then load the asset from the disk and store its data in a local thread-safe queue for processing. During the update loop of another thread it can then query for the finalization of the load, so the renderer can request X amount of meshes to buffer to the GPU. This approach is both modular and thread-safe, which is necessary to support threaded audio and rendering.

<div class="selectable-dropdown">
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="Asset-Header">Asset.h</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="ThreadType-Header">ThreadType.h</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="AssetImporter-Header">AssetImporter.h</button>
<div class="selectable-dropdown-area">
<div class="selectable-text" data-code-text-name="Asset-Header" markdown="1">
```c++
{% include code/Projects/RNGOEngine/Asset.h %}
```
</div>
<div class="selectable-text" data-code-text-name="ThreadType-Header" markdown="1">
```c++
{% include code/Projects/RNGOEngine/ThreadType.h %}
```
</div>
<div class="selectable-text" data-code-text-name="AssetImporter-Header" markdown="1">
```c++
{% include code/Projects/RNGOEngine/AssetImporter.h %}
```
</div>
</div>
</div>

## Modern C++
Throughout the engine I try to apply modern C++ practices wherever possible. The engine itself is written in C++23 and heavily uses the std::expected result-pattern for error handling. I find this approach far more declarative than exception based error handling because the call-site has to explicitly unwrap the value in order to use it, meaning it forces the functions user to pay mind to the potential errors. Apart from the result syntax I also try to favour a generic API wherever possible, favoring to use concepts such as std::span and std::string_view rather than forcing the calling end to use an std::vector or std::string. I have found this modern way of writing C++ extremely beneficial from a data oriented standpoint as it makes you think of the underlying data rather than the object which contains it.

<div class="selectable-dropdown">
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="ShaderPreProcessor-Parse">ShaderPreProcessor::Parse</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="IRenderer-Buffer">IRenderer::BufferVBOData</button>
<div class="selectable-dropdown-area">
<div class="selectable-text" data-code-text-name="ShaderPreProcessor-Parse" markdown="1">
```c++
{% include code/Projects/RNGOEngine/ShaderPreProcessorParse %}
```
</div>
<div class="selectable-text" data-code-text-name="IRenderer-Buffer" markdown="1">
```c++
{% include code/Projects/RNGOEngine/IRendererBuffer %}
```
</div>
</div>
</div>

## Reflection
While not yet over, this project has been an incredible learning experience throughout. Starting out I had limited experience working in desktop C++, having mainly worked with CLI and UE previously. Through this project I have learnt a lot of C++ principles from memory management, working close to hardware and writing maintainable code. 

Going on I feel far more confident in my C++ skills and am excited to continue to develop the engine and my skills even further.

