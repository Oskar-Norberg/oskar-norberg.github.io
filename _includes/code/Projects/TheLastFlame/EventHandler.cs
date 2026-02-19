namespace ringo.EventSystem
{
    public abstract class EventHandler<T> : IEventHandler where T : IEvent
    {
        public void Activate()
        {
            EventBus.Subscribe<T>(this);
        }
        
        public void Deactivate()
        {
            EventBus.Unsubscribe<T>(this);
        }

        public abstract void Handle(IEvent @event);
    }
}