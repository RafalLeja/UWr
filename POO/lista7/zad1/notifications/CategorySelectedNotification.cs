using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad1.notifications
{
    internal class CategorySelectedNotification
    {
        public string Category { get; set; }

        public CategorySelectedNotification(string category)
        {
            Category = category;
        }
    }
}
