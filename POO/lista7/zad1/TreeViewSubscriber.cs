using System;
using System.Collections.Generic;
using System.Diagnostics;
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
            foreach (TreeNode node in this.Nodes)
            {
                node.Nodes.RemoveByKey(notification.Id.ToString());
                Debug.WriteLine(node.Text);
            }

            if (!this.Nodes.ContainsKey(notification.Category))
            {
                this.Nodes.Add(notification.Category, notification.Category);
            }
            this.Nodes[notification.Category].Nodes.Add(notification.Id.ToString(), notification.Name + " " + notification.Surname);
        }

        public void Handle(UserCreatedNotification notification)
       {
            if (!this.Nodes.ContainsKey(notification.Category))
            {
                this.Nodes.Add(notification.Category, notification.Category);
            }
            this.Nodes[notification.Category].Nodes.Add(notification.Id.ToString(), notification.Name + " " + notification.Surname);
        }
    }
}
