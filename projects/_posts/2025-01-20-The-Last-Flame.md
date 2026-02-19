---
title: The Last Flame
description: The Last Flame is an narrative-driven adventure game set in the arctic of Eryndor. Worked on AI, EventBus and cutscene management, developed reusable Unity Packages.
layout: project

cover_video: assets/projects/TheLastFlame/Fox.mp4
trailer_video: assets/projects/TheLastFlame/Trailer.webm

duration: 4 weeks
team_size: 16
tags: ["C#", "Unity", "Design Patterns", "Custom Unity Packages"]

gallery:
  - type: video
    src: assets/projects/TheLastFlame/Trailer.webm
    thumb: assets/projects/TheLastFlame/TrailerThumbnail.jpg

  - type: image
    src: assets/projects/TheLastFlame/HumanPic.jpg

  - type: image
    src: assets/projects/TheLastFlame/FoxPic.jpg

  - type: image
    src: assets/projects/TheLastFlame/FoxPic2.jpg

  - type: image
    src: assets/projects/TheLastFlame/PlayGame.jpg

itch: https://futuregames.itch.io/the-last-flame
github: https://github.com/Oskar-Norberg/The-Last-Flame-GP2-Code-Only

featured_main: 8

permalink: /projects/TheLastFlame.html
---

A project where I truly felt at home in Unity. For this project I worked on AI, Cutscene Management and making an EventBus for modular cross system communication. For the Behaviour Trees and EventBus I eventually set up custom Unity Packages so the code can easily be reused in future projects.

## Behaviour Tree
For AI I decided to continue the development of my Behaviour Tree from a previous project. Making improvements to overall structure, modularity and performance of the implementation. The Behaviour Tree as most implementations is built upon a graph structure and its control flow is evaluated left to right using a depth-first search. The tree's flow can be altered using different predicates for the decorators and different sequencing nodes.

The tree’s structure is specified by passing the root node as an argument to the tree's constructor. The tree then constructs a blackboard and sets the blackboard references in all of the child-nodes. The nodes communicate using the BlackBoard structure which stores all entries in a type-erased dictionary, this way all objects can be stored together in one dictionary for simplicity while still being accessible through a string as a key. One potential optimization here would have been to key entries based on their typeid rather than a string. This is quicker than hashing a string, which is essentially a non-determinate number of integers/chars which would lead to multiple hash-calls and hash-combines. Comparatively, [hashing a System.Type](https://source.dot.net/#System.Private.CoreLib/src/libraries/System.Private.CoreLib/src/System/Type.cs,e8937d5bb4bb6af3,references) is far quicker because it has a pre-cached hash given to it at compile-time based on its type. This however was ultimately not implemented as it would’ve made storing multiple entries of the same type impossible. Furthermore BlackBoard accesses never proved to be a significant bottleneck during profiling.

<video width="60%" height="auto" src="{{ "assets/projects/TheLastFlame/HumanTracking.mp4" | relative_url }}" controls></video>
*Human tracking and avoiding staying too close to the player.*

<div class="selectable-dropdown">
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="BehaviourTree">BehaviourTree.cs</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="BlackBoard">BlackBoard.cs</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="Node">Node.cs</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="Leaf">Leaf.cs</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="Decorator">Decorator.cs</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="Composite">Composite.cs</button>
<div class="selectable-dropdown-area">
<div class="selectable-text" data-code-text-name="BehaviourTree" markdown="1">
```c#
{% include code/Projects/TheLastFlame/BehaviourTree.cs %}
```
</div>
<div class="selectable-text" data-code-text-name="BlackBoard" markdown="1">
```c#
{% include code/Projects/TheLastFlame/BlackBoard.cs %}
```
</div>
<div class="selectable-text" data-code-text-name="Node" markdown="1">
```c#
{% include code/Projects/TheLastFlame/Node.cs %}
```
</div>
<div class="selectable-text" data-code-text-name="Leaf" markdown="1">
```c#
{% include code/Projects/TheLastFlame/Leaf.cs %}
```
</div>
<div class="selectable-text" data-code-text-name="Decorator" markdown="1">
```c#
{% include code/Projects/TheLastFlame/Decorator.cs %}
```
</div>
<div class="selectable-text" data-code-text-name="Composite" markdown="1">
```c#
{% include code/Projects/TheLastFlame/Composite.cs %}
```
</div>
</div>
</div>

## EventBus
For communication between different systems I opted to implement the EventBus pattern, which I’ve really come to greatly appreciate. EventBuses help alleviate many of the common problems of tight coupling between systems by rather than giving systems direct access to each other they leverage events to give and receive information and commands from other systems. 

To subscribe to an Event any class can create an instance of an ArgumentEventHandler<T> or a NoArgumentEventHandler<T>. The <T> type parameter dictates the type of the Event to listen to. Alongside the type parameter the constructor for the EventHandler also takes in a delegate to call when an event of type <T> is published. Based on whether the class uses the Argument or NonArgumentEventHandler the subscribed delegate can either take the event as a parameter or choose to ignore the data of the event, only using it as a sort of “notification”

Events can be created by simply inheriting from the *Event* interface. The events themselves can contain any amount of arbitrary data, or none at all. Internally in the EventBus all EventHandlers are kept in a Dictionary that is keyed based on the EventHandlers event type and stores event handlers of that type in a HashSet to avoid storing multiple instances of the same EventListener. 

One potential improvement to the EventHandler I have not yet had the time to implement would be to move it away from static memory and to break it into a “scope agnostic” reusable object instead. This would allow for the construction of multiple EventBuses rather than having one global one. This is good not only for code-reusability, as it would benefit other systems but also has some quite interesting gameplay implications as it could function in a smaller scope. Meaning an EventBus could be shared only among Enemies to for example indicate they should target another entity. Or a player specific EventBus in a multiplayer game so only events for that specific player take place.

<div class="selectable-dropdown">
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="Event">EventBus.cs</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="EventBus">IEvent.cs</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="EventHandler">EventHandler.cs</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="ArgumentEventHandler">ArgumentEventHandler.cs</button>
<button class="selectable-dropdown-button button" data-dropdown-selectable-name="NoArgumentEventHandler">NoArgumentEventHandler.cs</button>
<div class="selectable-dropdown-area">
<div class="selectable-text" data-code-text-name="Event" markdown="1">
```c#
{% include code/Projects/TheLastFlame/Event.cs %}
```
</div>
<div class="selectable-text" data-code-text-name="EventBus" markdown="1">
```c#
{% include code/Projects/TheLastFlame/EventBus.cs %}
```
</div>
<div class="selectable-text" data-code-text-name="EventHandler" markdown="1">
```c#
{% include code/Projects/TheLastFlame/EventHandler.cs %}
```
</div>
<div class="selectable-text" data-code-text-name="ArgumentEventHandler" markdown="1">
```c#
{% include code/Projects/TheLastFlame/ArgumentEventHandler.cs %}
```
</div>
<div class="selectable-text" data-code-text-name="NoArgumentEventHandler" markdown="1">
```c#
{% include code/Projects/TheLastFlame/NoArgumentEventHandler.cs %}
```
</div>
</div>
</div>

## Custom Unity Packages
In order to be able to reuse these Systems for future projects I also decided to package them up as separate Unity Packages for the [Behaviour Tree](https://github.com/Oskar-Norberg/Unity-BehaviourTree) and [Event Listener](https://github.com/Oskar-Norberg/Unity-EventBus) respectively. While this process was a bit unfamiliar to me, learning about how the Unity Package pipeline works and how to create reusable units was very interesting to me and when I got the hang of it I ended up creating packages for some more of my [projects](https://github.com/Oskar-Norberg/UnityPackages).


## Reflection
The Last Flame has been an incredible learning opportunity for me, allowing me to truly spread my wings in Unity regarding systems design and applying clean code practices and design patterns. My biggest takeaway from this has definitely been the benefits and importance of modularly designing code in reusable parts rather than a monolith. Having set up the Unity Packages for Behaviour Trees and EventBus which I have used countless times in projects after this one for fast iteration it has been truly one of the best uses of my time and I am looking forward to keep on developing my different [Unity Packages](https://github.com/Oskar-Norberg/UnityPackages).
