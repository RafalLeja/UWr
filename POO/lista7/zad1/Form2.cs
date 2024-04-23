using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using zad1.event_aggregator;
using zad1.notifications;

namespace zad1
{
    public partial class Form2 : Form
    {
        private int id;

        private IEventAggregator event_aggregator;

        public Form2(int id, IEventAggregator eventAggregator)
        {
            this.id = id;
            this.event_aggregator = eventAggregator;
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (id == -1)
            {
                event_aggregator.Publish(new UserCreatedNotification(nameTextBox.Text, surnameTextBox.Text, dateTimePicker1.Value, categoryTextBox.Text, new Random().Next(0, 100)));
            } else
            {
                event_aggregator.Publish(new UserModifiedNotification(nameTextBox.Text, surnameTextBox.Text, dateTimePicker1.Value, categoryTextBox.Text, id));
            }

            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
