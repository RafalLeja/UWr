namespace zad1
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            nameLabel = new Label();
            nameTextBox = new TextBox();
            surnameLabel = new Label();
            surnameTextBox = new TextBox();
            DateLabel = new Label();
            dateTimePicker1 = new DateTimePicker();
            categoryLabel = new Label();
            categoryTextBox = new TextBox();
            button1 = new Button();
            button2 = new Button();
            SuspendLayout();
            // 
            // nameLabel
            // 
            nameLabel.AutoSize = true;
            nameLabel.Location = new Point(12, 15);
            nameLabel.Name = "nameLabel";
            nameLabel.Size = new Size(30, 15);
            nameLabel.TabIndex = 0;
            nameLabel.Text = "Imie";
            // 
            // nameTextBox
            // 
            nameTextBox.Location = new Point(12, 33);
            nameTextBox.Name = "nameTextBox";
            nameTextBox.Size = new Size(100, 23);
            nameTextBox.TabIndex = 1;
            // 
            // surnameLabel
            // 
            surnameLabel.AutoSize = true;
            surnameLabel.Location = new Point(12, 59);
            surnameLabel.Name = "surnameLabel";
            surnameLabel.Size = new Size(57, 15);
            surnameLabel.TabIndex = 2;
            surnameLabel.Text = "Nazwisko";
            // 
            // surnameTextBox
            // 
            surnameTextBox.Location = new Point(12, 77);
            surnameTextBox.Name = "surnameTextBox";
            surnameTextBox.Size = new Size(100, 23);
            surnameTextBox.TabIndex = 3;
            // 
            // DateLabel
            // 
            DateLabel.AutoSize = true;
            DateLabel.Location = new Point(12, 103);
            DateLabel.Name = "DateLabel";
            DateLabel.Size = new Size(86, 15);
            DateLabel.TabIndex = 4;
            DateLabel.Text = "Data urodzenia";
            // 
            // dateTimePicker1
            // 
            dateTimePicker1.Location = new Point(12, 121);
            dateTimePicker1.Name = "dateTimePicker1";
            dateTimePicker1.Size = new Size(200, 23);
            dateTimePicker1.TabIndex = 5;
            // 
            // categoryLabel
            // 
            categoryLabel.AutoSize = true;
            categoryLabel.Location = new Point(12, 147);
            categoryLabel.Name = "categoryLabel";
            categoryLabel.Size = new Size(57, 15);
            categoryLabel.TabIndex = 6;
            categoryLabel.Text = "Kategoria";
            // 
            // categoryTextBox
            // 
            categoryTextBox.Location = new Point(12, 165);
            categoryTextBox.Name = "categoryTextBox";
            categoryTextBox.Size = new Size(100, 23);
            categoryTextBox.TabIndex = 7;
            // 
            // button1
            // 
            button1.Location = new Point(12, 205);
            button1.Name = "button1";
            button1.Size = new Size(75, 23);
            button1.TabIndex = 8;
            button1.Text = "Dodaj";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Location = new Point(138, 205);
            button2.Name = "button2";
            button2.Size = new Size(74, 23);
            button2.TabIndex = 9;
            button2.Text = "Cofnij";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // Form2
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(235, 240);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(categoryTextBox);
            Controls.Add(categoryLabel);
            Controls.Add(dateTimePicker1);
            Controls.Add(DateLabel);
            Controls.Add(surnameTextBox);
            Controls.Add(surnameLabel);
            Controls.Add(nameTextBox);
            Controls.Add(nameLabel);
            Name = "Form2";
            Text = "Form2";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label nameLabel;
        private TextBox nameTextBox;
        private Label surnameLabel;
        private TextBox surnameTextBox;
        private Label DateLabel;
        private DateTimePicker dateTimePicker1;
        private Label categoryLabel;
        private TextBox categoryTextBox;
        private Button button1;
        private Button button2;
    }
}