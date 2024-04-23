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
        public Dictionary<string, List<User>> users = new Dictionary<string, List<User>>();

        public void Handle(CategorySelectedNotification notification)
        {
            Items.Clear();
            if (users.ContainsKey(notification.Category))
            {
                foreach (User user in users[notification.Category])
                {
                    Items.Add(new ListViewItem(new string[] { user.Id.ToString(), user.Name, user.Surname, user.DateOfBirth.ToString() }));
                }
            }
        }

        public void Handle(UserProfileSelectedNotification notification)
        {
            Items.Clear();
            foreach (List<User> userList in users.Values)
            {
                foreach (User user in userList)
                {
                    if (user.Name + " " + user.Surname == notification.Name)
                    {
                        Items.Add(new ListViewItem(new string[] { user.Id.ToString(), user.Name, user.Surname, user.DateOfBirth.ToString() }));
                    }
                }
            }
        }

        public void Handle(UserCreatedNotification notification)
        {
            if (!users.ContainsKey(notification.Category))
            {
                users.Add(notification.Category, new List<User>());
            }
            users[notification.Category].Add(new User(notification.Name, notification.Surname, notification.DateOfBirth, notification.Category, notification.Id));
        }

        public void Handle(UserModifiedNotification notification)
        {
            foreach (string category in users.Keys)
            {
                foreach (User user in users[category])
                {
                    if (user.Id == notification.Id)
                    {
                        users[category].Remove(user);
                        break;
                    }
                }
            }

            if (!users.ContainsKey(notification.Category))
            {
                users.Add(notification.Category, new List<User>());
            }
            users[notification.Category].Add(new User(notification.Name, notification.Surname, notification.DateOfBirth, notification.Category, notification.Id));

        }
    }   
}
