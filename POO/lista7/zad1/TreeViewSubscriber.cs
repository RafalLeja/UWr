using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using zad1.event_aggregator;
using zad1.notifications;

namespace zad1
{
    internal class TreeViewSubscriber : TreeView, ISubscriber<UserModifiedNotification>, ISubscriber<UserCreatedNotification>
    {
        public void Handle(UserModifiedNotification notification)
        {
            Console.WriteLine("User profile selected: {0} {1} {2} {3} {4}", notification.Name, notification.Surname, notification.DateOfBirth, notification.Category, notification.Id);
        }

        public void Handle(UserCreatedNotification notification)
        {
            Console.WriteLine("User created: {0} {1} {2} {3} {4}", notification.Name, notification.Surname, notification.DateOfBirth, notification.Category, notification.Id);
        }
    }
}
