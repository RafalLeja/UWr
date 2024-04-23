using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.Text;
using System.Threading.Tasks;
using zad1.notifications;
using zad1.event_aggregator;

namespace zad1
{
    internal class ListViewSubscriber : ListView, ISubscriber<CategorySelectedNotification>, ISubscriber<UserProfileSelectedNotification>, ISubscriber<UserCreatedNotification>, ISubscriber<UserModifiedNotification>
    {
        private Dictionary<string, List<User>> users = new Dictionary<string, List<User>>();

        public void Handle(CategorySelectedNotification notification)
        {
            Debug.WriteLine("Category selected: {0}", notification.Category);
        }

        public void Handle(UserProfileSelectedNotification notification)
        {
            Debug.WriteLine("User profile selected: {0} {1}", notification.Name, notification.Surname);
        }

        public void Handle(UserCreatedNotification notification)
        {
            if (!users.ContainsKey(notification.Category))
            {
                users.Add(notification.Category, new List<User>());
            }
            users[notification.Category].Add(new User(notification.Name, notification.Surname, notification.DateOfBirth, notification.Category));
            Debug.WriteLine("User created: {0} {1} {2} {3}", notification.Name, notification.Surname, notification.DateOfBirth, notification.Category);

        }

        public void Handle(UserModifiedNotification notification)
        {
            Debug.WriteLine("User profile selected: {0} {1} {2} {3} {4}", notification.Name, notification.Surname, notification.DateOfBirth, notification.Category, notification.Id);
        }
    }   
}
