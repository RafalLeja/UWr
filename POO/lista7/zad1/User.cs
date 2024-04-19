using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad1
{
    internal class User
    {
        public string Name { get; set; }
        public string Surname { get; set; }
        public System.DateTime DateOfBirth { get; set; }
        public string Category { get; set; }
        public int Id { get; set; }

        public User(string name, string surname, System.DateTime dateOfBirth, string category)
        {
            Name = name;
            Surname = surname;
            DateOfBirth = dateOfBirth;
            Category = category;
            // random id
            Id = new Random().Next(0, 1000);
        }
    }
}
