using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using zad1.notifications;
using zad1.event_aggregator;

namespace zad1
{
    internal class ListViewSubscriber : ListView, ISubscriber<CategorySelectedNotification>, ISubscriber<UserProfileSelectedNotification>
    {
        public void Handle(CategorySelectedNotification notification)
        {
            Console.WriteLine("Category selected: {0}", notification.Category);
        }

        public void Handle(UserProfileSelectedNotification notification)
        {
            Console.WriteLine("User profile selected: {0} {1}", notification.Name, notification.Surname);
        }
    }   
}
