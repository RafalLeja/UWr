using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad1.event_aggregator
{
    public class EventAggregator : IEventAggregator
    {
        private Dictionary<Type, List<object>> _subscribers = new Dictionary<Type, List<object>>();

        public void AddSubscriber<T>(ISubscriber<T> subscriber)
        {
            if (!_subscribers.ContainsKey(typeof(T)))
            {
                _subscribers.Add(typeof(T), new List<object>());
            }

            _subscribers[typeof(T)].Add(subscriber);
        }

        public void RemoveSubscriber<T>(ISubscriber<T> subscriber)
        {
            if (_subscribers.ContainsKey(typeof(T)))
            {
                _subscribers[typeof(T)].Remove(subscriber);
            }
        }

        public void Publish<T>(T notification)
        {
            if (_subscribers.ContainsKey(typeof(T)))
            {
                foreach (ISubscriber<T> subscriber in _subscribers[typeof(T)])
                {
                    subscriber.Handle(notification);
                }
            }
        }
    }
}
