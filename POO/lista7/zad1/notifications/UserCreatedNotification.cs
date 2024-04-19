using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad1.notifications
{
    internal class UserCreatedNotification 
    { 
        public string Name { get; set; }
        public string Surname { get; set; }
        public DateTime DateOfBirth { get; set; }
        public string Category { get; set; }

        public UserCreatedNotification(string name, string surname, DateTime dateOfBirth, string category)
        {
            Name = name;
            Surname = surname;
            DateOfBirth = dateOfBirth;
            Category = category;
        }
    }
}
