using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad1.event_aggregator
{
    internal interface IEventAggregator
    {
        void AddSubscriber<T>(ISubscriber<T> subscriber);
        void RemoveSubscriber<T>(ISubscriber<T> subscriber);
        void Publish<T>(T notification);
    }
}
