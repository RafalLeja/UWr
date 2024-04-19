using zad1.notifications;
using zad1.event_aggregator;
using System.Diagnostics;

namespace zad1;

public partial class Form1 : Form
{
    private IEventAggregator event_aggregator;

    public Form1()
    {
        InitializeComponent();

        event_aggregator = new EventAggregator();

        event_aggregator.AddSubscriber<CategorySelectedNotification>(listView1);
        event_aggregator.AddSubscriber<UserProfileSelectedNotification>(listView1);

        //event_aggregator.AddSubscriber<UserCreatedNotification>(treeView1);
        //event_aggregator.AddSubscriber<UserModifiedNotification>(treeView1);

        treeView1.Nodes.Add("Categories");
        treeView1.Nodes[0].Nodes.Add("Category 1");

        Debug.WriteLine("Form1 constructor");
    }

    private void splitContainer1_SplitterMoved(object sender, SplitterEventArgs e)
    {
        Debug.WriteLine("Splitter moved");
    }

    private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
    {
        Debug.WriteLine(e.Node.Text);
        if (e.Node != null)
        {
            if (e.Node.Nodes.Count == 0)
            {
                event_aggregator.Publish(new UserProfileSelectedNotification(e.Node.Text.Split(" ")[0], e.Node.Text.Split(" ")[1]));
            }
            else
            {
                event_aggregator.Publish(new CategorySelectedNotification(e.Node.Text));
            }
        }
    }

    private void button1_Click(object sender, EventArgs e)
    {
        Form form = new Form2();
        form.Show();
    }
}
