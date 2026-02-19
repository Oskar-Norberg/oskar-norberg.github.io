using System;
using System.Collections.Generic;
using UnityEngine;

namespace ringo.EventSystem
{
    public static class EventBus
    {
        private static Dictionary<Type, HashSet<IEventHandler>> _handlers = new();
        
        [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.SubsystemRegistration)]
        private static void InitializeOnLoad()
        {
            _handlers = new();
        }
        
        public static void Subscribe<T>(IEventHandler handler) where T : IEvent
        {
            if (handler == null)
            {
                Debug.LogWarning("[EventBus] Subscribed to null subscriber");
                return;
            }
            
            if (_handlers.ContainsKey(typeof(T)))
            {
                _handlers[typeof(T)].Add(handler);
                return;
            }

            var newHandlerList = new HashSet<IEventHandler> { handler };
            _handlers.Add(typeof(T), newHandlerList);
        }
        
        public static void Unsubscribe<T>(IEventHandler handler) where T : IEvent
        {
            if (!_handlers.ContainsKey(typeof(T)))
            {
                Debug.LogWarning("[EventBus] Could not find event type to unsubscribe");
                return;
            }

            _handlers[typeof(T)].Remove(handler);
        }
        
        public static void Publish<T>(T @event) where T : IEvent
        {
            if (!_handlers.ContainsKey(@event.GetType()))
                return;
            
            // Saves a snapshot of handlers to prevent concurrent modification
            var handlers = new HashSet<IEventHandler>(_handlers[@event.GetType()]);

            foreach (var handler in handlers)
            {
                handler.Handle(@event);
            }
        }
    }
}