namespace zad1;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    ///  Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }
        base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    ///  Required method for Designer support - do not modify
    ///  the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        splitContainer1 = new SplitContainer();
        button1 = new Button();
        treeView1 = new TreeViewSubscriber();
        button2 = new Button();
        listView1 = new ListViewSubscriber();
        columnHeader4 = new ColumnHeader();
        columnHeader1 = new ColumnHeader();
        columnHeader2 = new ColumnHeader();
        columnHeader3 = new ColumnHeader();
        ((System.ComponentModel.ISupportInitialize)splitContainer1).BeginInit();
        splitContainer1.Panel1.SuspendLayout();
        splitContainer1.Panel2.SuspendLayout();
        splitContainer1.SuspendLayout();
        SuspendLayout();
        // 
        // splitContainer1
        // 
        splitContainer1.Dock = DockStyle.Fill;
        splitContainer1.Location = new Point(0, 0);
        splitContainer1.Name = "splitContainer1";
        // 
        // splitContainer1.Panel1
        // 
        splitContainer1.Panel1.Controls.Add(button1);
        splitContainer1.Panel1.Controls.Add(treeView1);
        // 
        // splitContainer1.Panel2
        // 
        splitContainer1.Panel2.Controls.Add(button2);
        splitContainer1.Panel2.Controls.Add(listView1);
        splitContainer1.Size = new Size(800, 450);
        splitContainer1.SplitterDistance = 181;
        splitContainer1.TabIndex = 0;
        splitContainer1.SplitterMoved += splitContainer1_SplitterMoved;
        // 
        // button1
        // 
        button1.Location = new Point(54, 415);
        button1.Name = "button1";
        button1.Size = new Size(75, 23);
        button1.TabIndex = 1;
        button1.Text = "Dodaj";
        button1.UseVisualStyleBackColor = true;
        button1.Click += button1_Click;
        // 
        // treeView1
        // 
        treeView1.Location = new Point(0, 0);
        treeView1.Name = "treeView1";
        treeView1.Size = new Size(183, 450);
        treeView1.TabIndex = 0;
        treeView1.AfterSelect += treeView1_AfterSelect;
        // 
        // button2
        // 
        button2.Location = new Point(14, 12);
        button2.Name = "button2";
        button2.Size = new Size(75, 23);
        button2.TabIndex = 1;
        button2.Text = "Edytuj";
        button2.UseVisualStyleBackColor = true;
        button2.Click += button2_Click;
        // 
        // listView1
        // 
        listView1.Columns.AddRange(new ColumnHeader[] { columnHeader4, columnHeader1, columnHeader2, columnHeader3 });
        listView1.Location = new Point(3, 41);
        listView1.Name = "listView1";
        listView1.Size = new Size(607, 406);
        listView1.TabIndex = 0;
        listView1.UseCompatibleStateImageBehavior = false;
        // 
        // columnHeader4
        // 
        columnHeader4.Text = "ID";
        // 
        // columnHeader1
        // 
        columnHeader1.Text = "Imie";
        // 
        // columnHeader2
        // 
        columnHeader2.Text = "Nazwisko";
        // 
        // columnHeader3
        // 
        columnHeader3.Text = "Data urodzenia";
        // 
        // Form1
        // 
        AutoScaleDimensions = new SizeF(7F, 15F);
        AutoScaleMode = AutoScaleMode.Font;
        ClientSize = new Size(800, 450);
        Controls.Add(splitContainer1);
        Name = "Form1";
        Text = "Form1";
        splitContainer1.Panel1.ResumeLayout(false);
        splitContainer1.Panel2.ResumeLayout(false);
        ((System.ComponentModel.ISupportInitialize)splitContainer1).EndInit();
        splitContainer1.ResumeLayout(false);
        ResumeLayout(false);
    }

    #endregion

    private SplitContainer splitContainer1;
    private TreeViewSubscriber treeView1;
    private ListViewSubscriber listView1;
    private Button button1;
    private ColumnHeader columnHeader1;
    private ColumnHeader columnHeader2;
    private ColumnHeader columnHeader3;
    private Button button2;
    private ColumnHeader columnHeader4;
}
