﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad1.event_aggregator
{
    public interface ISubscriber<T>
    {
        void Handle(T Notification);
    }
}
