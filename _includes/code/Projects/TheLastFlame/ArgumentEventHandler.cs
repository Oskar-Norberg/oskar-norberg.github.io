using System;

namespace ringo.EventSystem
{
    public class ArgumentEventHandler<T> : EventHandler<T> where T : IEvent
    {
        Action<T> _callback;
        
        public ArgumentEventHandler(Action<T> callback) : base()
        {
            _callback = callback;
        }

        public override void Handle(IEvent @event)
        {
            _callback.Invoke((T) @event);
        }
    }
}