using System;

namespace ringo.EventSystem
{
    public class NoArgumentEventHandler<T> : EventHandler<T> where T : IEvent
    {
        Action _callback;
        
        public NoArgumentEventHandler(Action callback) : base()
        {
            _callback = callback;
        }

        public override void Handle(IEvent @event)
        {
            _callback.Invoke();
        }
    }
}