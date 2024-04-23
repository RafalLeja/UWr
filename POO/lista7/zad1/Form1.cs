using zad1.notifications;
using zad1.event_aggregator;
using System.Diagnostics;

namespace zad1;

public partial class Form1 : Form
{
    public IEventAggregator event_aggregator;

    public Form1()
    {
        InitializeComponent();

        event_aggregator = new EventAggregator();

        event_aggregator.AddSubscriber<CategorySelectedNotification>(listView1);
        event_aggregator.AddSubscriber<UserProfileSelectedNotification>(listView1);
        event_aggregator.AddSubscriber<UserCreatedNotification>(listView1);
        event_aggregator.AddSubscriber<UserModifiedNotification>(listView1);

        event_aggregator.AddSubscriber<UserCreatedNotification>(treeView1);
        event_aggregator.AddSubscriber<UserModifiedNotification>(treeView1);

        event_aggregator.Publish(new UserCreatedNotification("John", "Doe", new DateTime(1990, 1, 1), "Student", 1));
        event_aggregator.Publish(new UserCreatedNotification("Jane", "Doe", new DateTime(1990, 1, 1), "Student", 2));

        listView1.View = View.Details;

        Debug.WriteLine("Form1 constructor");
    }

    private void splitContainer1_SplitterMoved(object sender, SplitterEventArgs e)
    {
        Debug.WriteLine("Splitter moved");
    }

    private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
    {
        if (e.Node != null)
        {
            if (e.Node.Nodes.Count == 0)
            {
                event_aggregator.Publish(new UserProfileSelectedNotification(e.Node.Text));
            }
            else
            {
                event_aggregator.Publish(new CategorySelectedNotification(e.Node.Text));
            }
        }
    }

    private void button1_Click(object sender, EventArgs e)
    {
        Form form = new Form2(-1, this.event_aggregator);
        form.Show();

    }

    private void button2_Click(object sender, EventArgs e)
    {
        int id = -1;
        foreach (ListViewItem item in listView1.Items)
        {
            if (item.Selected)
            {
                id =  Int32.Parse(item.SubItems[0].Text);
            }
        }

        if (id != -1)
        {
            Form form = new Form2(id, this.event_aggregator);
            form.Show();
        }
    }
}
