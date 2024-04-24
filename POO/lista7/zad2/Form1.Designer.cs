namespace zad2;

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
        System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
        toolStrip1 = new ToolStrip();
        toolStripButton1 = new ToolStripButton();
        toolStripButton2 = new ToolStripButton();
        toolStripButton3 = new ToolStripButton();
        toolStripSeparator1 = new ToolStripSeparator();
        toolStripButton4 = new ToolStripButton();
        toolStripButton5 = new ToolStripButton();
        toolStripSeparator2 = new ToolStripSeparator();
        toolStripButton6 = new ToolStripButton();
        toolStripButton7 = new ToolStripButton();
        backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
        canvas1 = new Canvas();
        toolStrip1.SuspendLayout();
        SuspendLayout();
        // 
        // toolStrip1
        // 
        toolStrip1.Items.AddRange(new ToolStripItem[] { toolStripButton1, toolStripButton2, toolStripButton3, toolStripSeparator1, toolStripButton4, toolStripButton5, toolStripSeparator2, toolStripButton6, toolStripButton7 });
        toolStrip1.Location = new Point(0, 0);
        toolStrip1.Name = "toolStrip1";
        toolStrip1.Size = new Size(800, 25);
        toolStrip1.TabIndex = 0;
        // 
        // toolStripButton1
        // 
        toolStripButton1.DisplayStyle = ToolStripItemDisplayStyle.Text;
        toolStripButton1.Image = (Image)resources.GetObject("toolStripButton1.Image");
        toolStripButton1.ImageTransparentColor = Color.Magenta;
        toolStripButton1.Name = "toolStripButton1";
        toolStripButton1.Size = new Size(41, 22);
        toolStripButton1.Text = "Kółko";
        toolStripButton1.Click += toolStripButton1_Click;
        // 
        // toolStripButton2
        // 
        toolStripButton2.DisplayStyle = ToolStripItemDisplayStyle.Text;
        toolStripButton2.Image = (Image)resources.GetObject("toolStripButton2.Image");
        toolStripButton2.ImageTransparentColor = Color.Magenta;
        toolStripButton2.Name = "toolStripButton2";
        toolStripButton2.Size = new Size(54, 22);
        toolStripButton2.Text = "Kwadrat";
        toolStripButton2.Click += toolStripButton2_Click;
        // 
        // toolStripButton3
        // 
        toolStripButton3.DisplayStyle = ToolStripItemDisplayStyle.Text;
        toolStripButton3.Image = (Image)resources.GetObject("toolStripButton3.Image");
        toolStripButton3.ImageTransparentColor = Color.Magenta;
        toolStripButton3.Name = "toolStripButton3";
        toolStripButton3.Size = new Size(61, 22);
        toolStripButton3.Text = "Prostokąt";
        toolStripButton3.Click += toolStripButton3_Click;
        // 
        // toolStripSeparator1
        // 
        toolStripSeparator1.Name = "toolStripSeparator1";
        toolStripSeparator1.Size = new Size(6, 25);
        // 
        // toolStripButton4
        // 
        toolStripButton4.DisplayStyle = ToolStripItemDisplayStyle.Text;
        toolStripButton4.Image = (Image)resources.GetObject("toolStripButton4.Image");
        toolStripButton4.ImageTransparentColor = Color.Magenta;
        toolStripButton4.Name = "toolStripButton4";
        toolStripButton4.Size = new Size(52, 22);
        toolStripButton4.Text = "Przesuń";
        toolStripButton4.Click += toolStripButton4_Click;
        // 
        // toolStripButton5
        // 
        toolStripButton5.DisplayStyle = ToolStripItemDisplayStyle.Text;
        toolStripButton5.Image = (Image)resources.GetObject("toolStripButton5.Image");
        toolStripButton5.ImageTransparentColor = Color.Magenta;
        toolStripButton5.Name = "toolStripButton5";
        toolStripButton5.Size = new Size(38, 22);
        toolStripButton5.Text = "Usuń";
        toolStripButton5.Click += toolStripButton5_Click;
        // 
        // toolStripSeparator2
        // 
        toolStripSeparator2.Name = "toolStripSeparator2";
        toolStripSeparator2.Size = new Size(6, 25);
        // 
        // toolStripButton6
        // 
        toolStripButton6.DisplayStyle = ToolStripItemDisplayStyle.Text;
        toolStripButton6.Image = (Image)resources.GetObject("toolStripButton6.Image");
        toolStripButton6.ImageTransparentColor = Color.Magenta;
        toolStripButton6.Name = "toolStripButton6";
        toolStripButton6.Size = new Size(40, 22);
        toolStripButton6.Text = "Undo";
        toolStripButton6.Click += toolStripButton6_Click;
        // 
        // toolStripButton7
        // 
        toolStripButton7.DisplayStyle = ToolStripItemDisplayStyle.Text;
        toolStripButton7.Image = (Image)resources.GetObject("toolStripButton7.Image");
        toolStripButton7.ImageTransparentColor = Color.Magenta;
        toolStripButton7.Name = "toolStripButton7";
        toolStripButton7.Size = new Size(38, 22);
        toolStripButton7.Text = "Redo";
        toolStripButton7.Click += toolStripButton7_Click;
        // 
        // canvas1
        // 
        canvas1.BackgroundImageLayout = ImageLayout.None;
        canvas1.Dock = DockStyle.Fill;
        canvas1.Location = new Point(0, 25);
        canvas1.Name = "canvas1";
        canvas1.Size = new Size(800, 425);
        canvas1.TabIndex = 1;
        // 
        // Form1
        // 
        AutoScaleDimensions = new SizeF(7F, 15F);
        AutoScaleMode = AutoScaleMode.Font;
        ClientSize = new Size(800, 450);
        Controls.Add(canvas1);
        Controls.Add(toolStrip1);
        Name = "Form1";
        Text = "Form1";
        toolStrip1.ResumeLayout(false);
        toolStrip1.PerformLayout();
        ResumeLayout(false);
        PerformLayout();
    }

    #endregion

    private ToolStrip toolStrip1;
    private ToolStripButton toolStripButton1;
    private ToolStripButton toolStripButton2;
    private ToolStripButton toolStripButton3;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripButton toolStripButton4;
    private ToolStripButton toolStripButton5;
    private ToolStripSeparator toolStripSeparator2;
    private ToolStripButton toolStripButton6;
    private ToolStripButton toolStripButton7;
    private System.ComponentModel.BackgroundWorker backgroundWorker1;
    private Canvas canvas1;
}
