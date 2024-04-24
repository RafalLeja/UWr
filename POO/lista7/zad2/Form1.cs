using System.Diagnostics;
using zad2.shapes;

namespace zad2;

public partial class Form1 : Form
{
    public Form1()
    {
        InitializeComponent();
    }

    private void toolStripButton1_Click(object sender, EventArgs e)
    {
        canvas1.SetTool("Circle");
    }

    private void toolStripButton2_Click(object sender, EventArgs e)
    {
        canvas1.SetTool("Square");
    }

    private void toolStripButton3_Click(object sender, EventArgs e)
    {
        canvas1.SetTool("Rectangle");
    }

    private void toolStripButton4_Click(object sender, EventArgs e)
    {
        canvas1.SetTool("Move");
    }

    private void toolStripButton5_Click(object sender, EventArgs e)
    {
        canvas1.SetTool("Delete");
    }

    private void toolStripButton6_Click(object sender, EventArgs e)
    {
        canvas1.Undo();
    }

    private void toolStripButton7_Click(object sender, EventArgs e)
    {
        canvas1.Redo();
    }
}
