---
title: RNGOEngine
description: RNGOEngine is a C++ game engine runtime and editor with ECS, custom made OpenGL RHI Wrapper and RenderPass system.
layout: project

cover_image: assets/projects/RNGOEngine/RNGOEngine.gif
main_video: assets/projects/RNGOEngine/Spotlight.mp4

duration: 5 weeks
team_size: 1
tags: ["C++", "OpenGL", "ImGui", "EnTT"]

github: https://github.com/Oskar-Norberg/RNGOEngine-Core

featured_main: 10
---

Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.


#### Header

Random text

- [asdf](https://www.asdf.com) asdf text
- [qwer](https://www.qwer.com) qwer text
- [zxcv](https://www.zxcv.com) zxcv text

<div class="selectable-dropdown">
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="RendererAPI-Header">RenderAPI.h</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="RendererAPI-Source">RenderAPI.cpp</button>
<div class="selectable-dropdown-area">
<div class="selectable-text" data-code-text-name="RendererAPI-Header" markdown="1">
```c++
//
// Created by ringo on 2025-10-05.
//

#pragma once

#include "RenderPass/RenderContext.h"
#include "RenderPass/RenderPass.h"
#include "Renderer/DrawQueue.h"
#include "ResourceManager/ResourceManager.h"

namespace RNGOEngine::Core::Renderer
{
    class RenderAPI
    {
    public:
        explicit RenderAPI(IRenderer& renderer, int width, int height);

        void SubmitDrawQueue(DrawQueue&& drawQueue);
        void RenderToScreen(int width, int height);
        void RenderToTarget(
            int width, int height, Containers::GenerationalKey<Resources::RenderTarget> targetKey
        );

    public:
        template<typename T, typename... Args>
        T& RegisterPass(Args&&... args)
        {
            m_passes.push_back(std::make_unique<T>(std::forward<Args>(args)...));

            // If target defines any attachments.
            const auto passSpecification = m_passes.back()->GetRenderTargetSpecification();
            if (!passSpecification.Attachments.empty())
            {
                CreateRenderTarget(passSpecification, m_width, m_height);
            }

            return static_cast<T&>(*m_passes.back());
        }

    public:
        Containers::GenerationalKey<Resources::RenderTarget> CreateRenderTarget(
            const Resources::RenderTargetSpecification& specification, int width, int height);

    private:
        IRenderer& m_renderer;

    private:
        RenderContext m_context;
        std::vector<std::unique_ptr<RenderPass>> m_passes;

    private:
        int m_width, m_height;

    private:
        void Render(
            int width, int height, std::optional<std::reference_wrapper<Resources::RenderTarget>> target
        );

        void EnsureTargetSizes(int width, int height);
    };
}
```
</div>
<div class="selectable-text" data-code-text-name="RendererAPI-Source" markdown="1">
```c++
//
// Created by ringo on 2025-10-05.
//

#include "Renderer/API/RenderAPI.h"

#include "Assets/AssetManager/Managers/MaterialManager.h"
#include "Assets/AssetManager/Managers/ShaderManager.h"
#include "Assets/AssetManager/Managers/TextureManager.h"
#include "EventQueue/EventQueue.h"
#include "EventQueue/EngineEvents/EngineEvents.h"
#include "Renderer/IRenderer.h"

namespace RNGOEngine::Core::Renderer
{
    RenderAPI::RenderAPI(IRenderer& renderer, const int width, const int height)
        : m_renderer(renderer),
        m_context(),
        m_width(width),
        m_height(height)
    {
        m_renderer.SetViewPortSize(width, height);
        m_renderer.EnableFeature(DepthTesting | BackFaceCulling | Blending));
    }

    void RenderAPI::SubmitDrawQueue(DrawQueue&& drawQueue)
    {
        m_context.drawQueue = std::move(drawQueue);
    }

    void RenderAPI::RenderToScreen(const int width, const int height)
    {
        Render(width, height, std::nullopt);
    }

    void RenderAPI::RenderToTarget(const int width, const int height,
                                Containers::GenerationalKey<Resources::RenderTarget> targetKey)
    {
        const auto renderTarget = Resources::ResourceManager::GetInstance().GetRenderTargetManager().
            GetRenderTarget(targetKey);

        RNGO_ASSERT(renderTarget && "RenderAPI::RenderToTarget - Invalid Render Target supplied.");

        Render(width, height, renderTarget->get());
    }

    void RenderAPI::Render(const int width, const int height,
                        std::optional<std::reference_wrapper<Resources::RenderTarget>> target)
    {
        // TODO: Add documentation / put this in a configuration file.
        constexpr std::string_view finalOutputTargetName = "Final Output";

        if (target)
        {
            m_context.renderPassResources.
                    RegisterExternalFrameBuffer(finalOutputTargetName, target->get().ID);
        }
        else
        {
            m_context.renderPassResources.RegisterExternalFrameBuffer(finalOutputTargetName, 0);
        }

        EnsureTargetSizes(width, height);
        m_renderer.SetViewPortSize(width, height);

        for (const auto& pass : m_passes)
        {
            pass->OnResize(width, height);
            pass->Execute(m_context);
        }

        m_context.renderPassResources.DeregisterExternalFramebuffer(finalOutputTargetName);
        m_renderer.BindFrameBuffer(0);
    }

    void RenderAPI::EnsureTargetSizes(int width, int height)
    {
        for (const auto& [spec, targetKey] : m_managedTargets)
        {
            auto& targetManager = Resources::ResourceManager::GetInstance().GetRenderTargetManager();
            const auto targetOpt = targetManager.GetRenderTarget(targetKey);
            if (!targetOpt)
            {
                continue;
            }

            const auto& target = targetOpt->get();

            RNGO_ASSERT(spec.Attachments.size() == target.Attachments.size() &&
                "RenderAPI::EnsureTargetSizes - Mismatched attachment count. Does specification not match target?"
            );

            for (size_t i = 0; i < spec.Attachments.size(); ++i)
            {
                const auto attachmentKey = target.Attachments[i];
                const auto& attachmentSpec = spec.Attachments[i];

                const auto attachmentOpt = targetManager.GetFrameBufferAttachment(attachmentKey);
                if (!attachmentOpt)
                {
                    RNGO_ASSERT(false && "RenderAPI::EnsureTargetSizes - Invalid FrameBufferAttachment.");
                    continue;
                }

                auto& attachmentRef = attachmentOpt->get();
                const auto desiredWidth =
                    Resources::GetDesiredAttachmentSize(
                        attachmentSpec.Size, width, height
                    );

                // Resize if necessary.
                if (attachmentRef.width != desiredWidth.first || attachmentRef.height != desiredWidth.second)
                {
                    targetManager.ResizeAttachment(targetKey, attachmentKey, desiredWidth.first,
                                                desiredWidth.second);
                }
            }
        }
    }
}
```
</div>
</div>
</div>