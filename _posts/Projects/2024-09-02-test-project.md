---
title: Test Project Name
date: 2024-09-02 00:00:00 +01:00
tags: [tag1, tag2, tag3]
description: Test post
layout: project

duration: 5 weeks

team-size: 5
---

Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. [itch.io](https://futuregames.itch.io/lizardescape).


#### Header

Random text

- [asdf](https://www.asdf.com) asdf text
- [qwer](https://www.qwer.com) qwer text
- [zxcv](https://www.zxcv.com) zxcv text

```c++
#pragma once

#include "System.h"

#include "TestSystem.h"
#include "TestSystem2.h"
#include "TestSystem3.h"
#include "TestSystem4.h"

class World;
class ISystem;

// TODO: Implement destruction of systems.
class SystemScheduler
{
public:
    SystemScheduler();

    void Update(World& world, float deltaTime);

private:
    std::tuple<TestSystem, TestSystem2, TestSystem3, TestSystem4> m_systems;
    bool m_initialized;

    void InitializeSystems();
};
```