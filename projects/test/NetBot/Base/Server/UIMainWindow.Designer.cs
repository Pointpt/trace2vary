namespace Server
{
    partial class UIMainWindow
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UIMainWindow));
            this.StatusBar = new System.Windows.Forms.StatusStrip();
            this.statusBarTextLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.MenuBar = new System.Windows.Forms.MenuStrip();
            this.dateiToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ansichtToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aktualisierenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MainUISplitter = new System.Windows.Forms.SplitContainer();
            this.pcTreeView = new System.Windows.Forms.TreeView();
            this.MainUIImages = new System.Windows.Forms.ImageList(this.components);
            this.StatusBar.SuspendLayout();
            this.MenuBar.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MainUISplitter)).BeginInit();
            this.MainUISplitter.Panel1.SuspendLayout();
            this.MainUISplitter.SuspendLayout();
            this.SuspendLayout();
            // 
            // StatusBar
            // 
            this.StatusBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusBarTextLabel});
            this.StatusBar.Location = new System.Drawing.Point(0, 325);
            this.StatusBar.Name = "StatusBar";
            this.StatusBar.Size = new System.Drawing.Size(664, 22);
            this.StatusBar.TabIndex = 0;
            // 
            // statusBarTextLabel
            // 
            this.statusBarTextLabel.Name = "statusBarTextLabel";
            this.statusBarTextLabel.Size = new System.Drawing.Size(0, 17);
            // 
            // MenuBar
            // 
            this.MenuBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.dateiToolStripMenuItem,
            this.ansichtToolStripMenuItem});
            this.MenuBar.Location = new System.Drawing.Point(0, 0);
            this.MenuBar.Name = "MenuBar";
            this.MenuBar.Size = new System.Drawing.Size(664, 24);
            this.MenuBar.TabIndex = 1;
            this.MenuBar.Text = "menuStrip1";
            // 
            // dateiToolStripMenuItem
            // 
            this.dateiToolStripMenuItem.Name = "dateiToolStripMenuItem";
            this.dateiToolStripMenuItem.Size = new System.Drawing.Size(46, 20);
            this.dateiToolStripMenuItem.Text = "Datei";
            // 
            // ansichtToolStripMenuItem
            // 
            this.ansichtToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aktualisierenToolStripMenuItem});
            this.ansichtToolStripMenuItem.Name = "ansichtToolStripMenuItem";
            this.ansichtToolStripMenuItem.Size = new System.Drawing.Size(59, 20);
            this.ansichtToolStripMenuItem.Text = "Ansicht";
            // 
            // aktualisierenToolStripMenuItem
            // 
            this.aktualisierenToolStripMenuItem.Name = "aktualisierenToolStripMenuItem";
            this.aktualisierenToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.aktualisierenToolStripMenuItem.Text = "Aktualisieren";
            this.aktualisierenToolStripMenuItem.Click += new System.EventHandler(this.aktualisierenToolStripMenuItem_Click);
            // 
            // MainUISplitter
            // 
            this.MainUISplitter.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MainUISplitter.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.MainUISplitter.Location = new System.Drawing.Point(0, 24);
            this.MainUISplitter.Name = "MainUISplitter";
            // 
            // MainUISplitter.Panel1
            // 
            this.MainUISplitter.Panel1.Controls.Add(this.pcTreeView);
            this.MainUISplitter.Size = new System.Drawing.Size(664, 301);
            this.MainUISplitter.SplitterDistance = 300;
            this.MainUISplitter.TabIndex = 2;
            // 
            // pcTreeView
            // 
            this.pcTreeView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pcTreeView.Location = new System.Drawing.Point(0, 0);
            this.pcTreeView.Name = "pcTreeView";
            this.pcTreeView.Size = new System.Drawing.Size(300, 301);
            this.pcTreeView.TabIndex = 0;
            // 
            // MainUIImages
            // 
            this.MainUIImages.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("MainUIImages.ImageStream")));
            this.MainUIImages.TransparentColor = System.Drawing.Color.Transparent;
            this.MainUIImages.Images.SetKeyName(0, "pcicon.jpg");
            // 
            // UIMainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(664, 347);
            this.Controls.Add(this.MainUISplitter);
            this.Controls.Add(this.StatusBar);
            this.Controls.Add(this.MenuBar);
            this.MainMenuStrip = this.MenuBar;
            this.Name = "UIMainWindow";
            this.Text = "Network Collaboration System - Server";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.UIMainWindow_FormClosed);
            this.Load += new System.EventHandler(this.UIMainWindow_Load);
            this.StatusBar.ResumeLayout(false);
            this.StatusBar.PerformLayout();
            this.MenuBar.ResumeLayout(false);
            this.MenuBar.PerformLayout();
            this.MainUISplitter.Panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.MainUISplitter)).EndInit();
            this.MainUISplitter.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip StatusBar;
        private System.Windows.Forms.MenuStrip MenuBar;
        private System.Windows.Forms.SplitContainer MainUISplitter;
        private System.Windows.Forms.TreeView pcTreeView;
        private System.Windows.Forms.ToolStripMenuItem dateiToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ansichtToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aktualisierenToolStripMenuItem;
        private System.Windows.Forms.ImageList MainUIImages;
        private System.Windows.Forms.ToolStripStatusLabel statusBarTextLabel;
    }
}