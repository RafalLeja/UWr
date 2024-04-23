using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad1.notifications
{
    internal class UserProfileSelectedNotification
    {
        public string Name { get; set; }

        public UserProfileSelectedNotification(string name)
        {
            Name = name;
        }
    }
}
